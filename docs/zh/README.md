Remmel
=====
[![License](https://img.shields.io/badge/License-MIT%20License-blue.svg)](https://opensource.org/licenses/MIT)

[English](../../README.md) | 简体中文

# 简介
Remmel是一个对象化数据库，支持内存缓存和硬盘持久化。得益于对象化的特性，Remmel很自然的拥有KV数据库（如，Redis）的功能，同时还具备了map/table、list类型的索引能力，能够很自然的适应按表为单位存储的关系型数据库的需要，甚至还能改造成为文档型数据库，如果查找功能强大的话。

# 使用
你能够使用Socket和Remmel建立通信。我们也提供了REPL客户端与它沟通。如果你想要开发相关的驱动，请看这里。

# 设计
Remmel主要由网络、任务调度、解释器、内核、仓库、语言交互接口、运行时、监控等模块组成。这些核心模块都是以动态库(dll/so/dylib)载入的，因此可以重新定制其中的模块，不一定使用C/C++语言编写，C#、Rust、Go等能够编译成动态库的语言也能胜任。如果你想要开发相关的模块，请看[这里](arch.md)。

# 未来计划
- [ ] 实现并运行Remmel
- [ ] 基于Raft协议，支持集群
- [ ] 支持Ruby、PHP、Perl解释器
- [ ] 实现Remmel类型系统