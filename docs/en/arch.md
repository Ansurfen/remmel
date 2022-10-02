Remmel Arch
=====

English | [简体中文](../zh/arch.md)

Remmel is an objectified database which support cache on memory or persists on disk. With the feature of object, Remmel naturally has the function of kv database(such as Redis), and also has the index ability of map/table and list types. It can naturally adapt to the needs of relational database stored in the uint of table, and even transform into document-based database, if the search ability is powerful.

## Net
The net module is based on the Reactor model. It uses IOCP(windows), epoll(linux) and kqueue(mac) to realize non-blocking IO multiplexing to listen network requests, wraps requests into tasks and transfers them to thread pool for processing.

## Task scheduler
The task scheduler, also known as the thread pool, distributes and processes all Remmel tasks, including CONN(to be processed by the net module), TRAP(to be processed by the shell), PARSER/EVAL(to be processed by the interpreter) and READ/WRITE(to be processed by the store module). If you look on it as GMP model, each task can viewed as a goroutine, and running those goroutines requires a processor and a machine. There is no doubt that the worker of the thread pool is the machine. Where does the processor come from? The net module handles CONN tasks. The other processors are centrally managed by `runtime` object. This reduces the overhead of creating objects and improves the running efficiency by reusing objects.

## Interpreter
Remmel's SQL statements are quite diverse, and you can write any reasonable syntax replacement for the corresponding dynamic libraries (dll/so/dylib) to achieve this functionality. Therefore, you can write any SQL syntax, for example, MySQL, Redis, Mongodb... Etc are reasonable if they can be translated into IR (intermediate syntax tree) as defined by Remmel. From this point of view, Remmel's interpreter needs to be parsed at least twice, `SQL string stream` -> `SQL abstract syntax tree` -> `IR syntax tree` -> `object codfe`. The 'object code' here is not translated into code that can be executed directly by the computer, but code that can be executed directly by the Remmel kernel, as described next. In order to reduce the performance cost, it may be possible in the future to implement their own interpretation engine to execute directly (look on /include/interpreter/rem).

## Kernel
The kernel consists of three modules: regedit, transaction engine and virtual machine. Any executed code must be registered through the regedit, in order to unify the management, when the memory reaches a certain threshold, will automatically trigger GC (garbage collection), which is inseparable from the regedit management. The virtual machine is an abstraction of FFI. The concepts of namespace and cgroup are introduced into virtual machine. Namespace is responsible for isolating each different database and coordinating with the engine of FFI to realize multi-thread execution. The cgroup is used to limit VM resource scheduling. The cgroup and regedit can trigger GC. Transaction module, to ensure the security of concurrency, mainly adopts the logic lock to serve identifiers, support distributed transactions. If you want to learn more or participate in the development，look [here](./kernel.md).

## FFI
The interpreter generates entry points for the execution of the object code, and since Remmel has not implemented its own type management system, it is left to Turing-complete, more robust programming language interpreters. The main function of this layer is to evaluate expressions and execute code. Most of the logic is based on this interface. As with the interpreter module, FFI is also quite diverse, and you can extend your ideal interpreter on your own. Remmel currently supports Lua, Python and JS, and is expected to support more dynamic languages in future updates.

## Store
The store responsible for persisting data to disk. It's easy to write, but tricky to query or reload memory. Therefore, the store uses the same design as most databases, LSM tree/Bplus tree, and both storage modes can be plugged in and out through dynamic libraries. It's also easier to recover them than to write them directly, mainly through the sparse index of the data structure Skiplist.

## Watch
Watch can be said to be one of the modules that have an important impact on performance. It is mainly responsible for counting the information of each module, such as the number of net module requests, the load of workers and processors in the thread pool, and the number of timer tasks. Dynamically scalable processing units based on the collected data ensure requests and processing at a relatively stable level. It also comes with a semaphore module that can deal with the immediate effect of a server outage, such as dispatching the store module to persist data and transferring requests from the net module to other processes. It can also fork out child processes to perform tasks, such as server restart, timed boot, etc.

## Others
The above is the core modules in Remmel, which can be loaded in the form of dynamic library. But to run Remmel, it's not enough to rely on the these protagonists alone, and there are still many supporting actors who silently contribute behind the scenes. Here are their details.

### Configuration
The configuration of Remmel is mainly ini, and a simple ini interpreter is implemented in /lib/conf.

### Crypto
The FFI will have some built-in functions to realize the functions of specific SQL statements such as JOIN, GROUP and so on. The code and data stored in the database will be stored in binary form, but the string will not be directly stored in the bin file, which is the same as directly storing the source file. Therefore, the code and data are encrypted by AES/RSA symmetry and then converted to hexadecimal in the bin file.