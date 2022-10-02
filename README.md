Remmel
=====
[![License](https://img.shields.io/badge/License-MIT%20License-blue.svg)](https://opensource.org/licenses/MIT)

English | [简体中文](./docs/zh/README.md)

# Introduction
Remmel is an objectified database which support cache on memory or persists on disk. With the feature of object, Remmel naturally has the function of kv database(such as Redis), and also has the index ability of map/table and list types. It can naturally adapt to the needs of relational database stored in the uint of table, and even transform into document-based database, if the search ability is powerful.

# Usage
You can use Socket to establish communication with Remmel. We also provide the REPL client to communicate with it. If you want to develop relational drivers, look here.

# Design
Remmel is mainly composed of modules such as network, task scheduler, interpreter, kernel, repository, FFI(Foreign Function Interface), runtime and watch. These core modules are loaded in dynamic libraries(dll/so/dylib), so you can re-customize the modules, not necessarily written in C/C++ language, C#, Rust, Go and other languages that can be compiled into dynamic libraries can also do the job. If you want to develop relational modules, look [here](./docs/en/arch.md).

# Future
- [ ] Implement and run Remmel
- [ ] Support for cluster based on raft-protocol
- [ ] Support for more interpreters such as PHP, Ruby, Perl
- [ ] Implement Remmel type system