Remmel kernel
=====
English | [简体中文](../zh/kernel.md)

The kernel consist of transaction and virtual machine and regedit.

# Transaction

# Regedit
The regedit is responsible for storing identifiers, which makes it easier to manage and organize them. For example, garbage collection is triggered when the memory reaches a threshold.

# Virtual machine
The abstract layer of virtual machine has duty to communicate FFI(Foreign Function Interface) which is based on dynamic library.

1. Implementing namespace is integral. If not, it'll become single thread, which will recede efficiency.
2. The implementation of the memory pool is optional, but it's still recommended forcibly, which can lead to better performance.