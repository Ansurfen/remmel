Remmel 架构
=====

[English](../en/arch.md) | 简体中文

Remmel主要由网络、任务调度、解释器、内核、仓库、语言交互接口、运行时、监控等模块组成。这些核心模块都是以动态库(dll/so/dylib)载入的，因此可以重新定制其中的模块，不一定使用C/C++语言编写，C#、Rust、Go等能够编译成动态库的语言也能胜任。

## 网络模块(Net)
网络模块以Reactor模型为基础，利用IOCP（windows）、epoll（linux）、kqueue（mac）实现非阻塞式IO多路复用监听网络来的请求，将请求封装成Task(任务)移交给线程池处理。

## 任务调度（Task scheduler）
任务调度也叫线程池，他负责分发和处理整个Remmel的任务，包括CONN（交付给网络模块处理）、TRAP（交付给Shell）、PARSER/EVAL(交付给解释器处理)、READ/WRITE（交付给Store处理）。如果把处理的过程套用GMP模型来说，每个任务就可以看成是一个协程(goroutine)，那么要运行这些goroutine就需要一个processor和一个machine。毫无疑问，线程池的工作线程（worker）自然就充当起了machine这个角色。而processor从何而来呢，一个由上文说到的网络模块会处理CONN类型的任务，其他的processor由Runtime对象统一管理，这能够减低创建对象的开销，复用对象提高运行效率。

## 解释器（Interpreter）
Remmel的SQL语句相当的多元化，你能够编写任何合理的语法替换相应的动态库(dll/so/dylib)来实现这个功能。因此，你能够写任何SQL语法，例如，MySQL、Redis、Mongodb...等都是合理的如果能够翻译成Remmel定义的IR（中间语法树）。从这个过程来看，Remmel的解释器需要经过至少两次解析，`SQL字符流` -> `SQL抽象语法树` -> `IR 语法树` -> `目标代码`。这里的`目标代码`不是翻译成计算机可以直接执行的代码，而是能够供Remmel内核直接执行的代码，这个在接下来会介绍。为了减少性能上的损耗，未来可能会实现自己的解释引擎一次解析直接执行（见/include/interpreter/rem）。

## 内核（Kernel）
内核由注册表、事务引擎、虚拟机三大模块组成。任何执行的代码都要经过注册表登记，才能统一管理，当内存达到一定的阈值，会自动触发GC（垃圾回收），这都离不开注册表的管理。虚拟机是语言交互接口的抽象，在虚拟机中引入了namespace(命名空间)和cgroup（控制组群）的概念，namespace负责隔离每个不同的数据库，同时和语言交互接口的底层引擎配合实现多线程的执行，而cgroup用于限制虚拟机的资源调度，通过cgroup和注册表配合可以触发GC。事务模块，保证并发安全，主要采用逻辑上的标识符锁实现，支持分布式事务。如果你想要了解更多或参与开发，请看[这里](../en/kernel.md)。

## 语言交互接口（FFI）
解释器生成目标代码执行的入口，因为Remmel还未实现自己的类型管理系统，因此都交给图灵完备、更加健全的编程语言解释器处理。这一层的逻辑也不复杂，主要的功能其实就是Eval求解表达式、执行代码，大部分的逻辑都离不开这个接口。同解释器模块类似，这个接口也是相当多元的，你能够自己拓展理想的解释器，目前Remmel支持Lua、Python、JS，预计在未来的更新中的支持更多的动态语言。

## 仓库（Store）
仓库负责将数据持久化写入硬盘。如果只是简单的写入很容易，但是如果想查询或者重新载入内存就变成棘手起来。因此，仓库采用了同大部分数据库一样的设计LSM树/B+树，两种存储模式都是可以通过动态库拔插的。而要复原他们相比直接写入也更容易，主要通过跳表（Skiplist）这一数据结构稀疏索引实现。

## 监控（Watch）
监控可以说是影响性能重要的模块之一，主要负责统计各个模块的信息，如网络模块的请求数量、线程池中worker和processor的负载情况、定时器的任务数等。基于收集的数据动态的伸缩处理单元，保证请求和处理在一个相对稳定的水平。同时，它还附带信号量模块，能够在服务器宕机时紧急善后，例如立刻调度store模块持久化数据、转移网络上的请求到其他的进程等。它还能fork出子进程执行任务，如服务器重启，定时开机等。

## 其他（Others）
上文中是Remmel中的核心模块，他们都能够以动态库的形式载入。但是要运行起Remmel光靠这些高光的主角还不足够，还需要有很多在背后默默奉献的配角。下面是关于他们的简介。

### 配置文件
Remmel的配置以ini为主，在 /lib/conf 中实现了简单的ini解释器。

### 加密
语言交互接口会内置一些函数来实现JOIN、GROUP等特定SQL语句的功能，这些代码以及数据库存储的数据都是二进制形式存储，但是不会把字符串直接存入bin文件，那样跟直接存储源文件别无二致。因此，代码和数据会经过AES/RSA对称加密，然后转成十六进制在存入bin文件中。