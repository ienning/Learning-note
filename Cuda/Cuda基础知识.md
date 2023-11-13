[TOC]

# 第一章Cuda介绍

Cuda能够高并行，低复杂的计算，一块GPU中包含成千上万个线程，GPU中有多个SM，一个SM包含一个control单元，一个cache，多个ALU计算单元。

Cuda接口一般有Cuda Runtime和Cuda Driver两种，最底层的是Cuda Driver，Cuda Runtime是封装了Cuda Driver的。它们是互斥的，一般只能选择一种使用，不可以同时使用。

GPU大致分为：

- 核函数
- 内存管理
- 线程管理
- 流

# 第二章Cuda，Kernel，Grid，block，thread

一个核函数对应一个grid，一个grid有多个block，一个block有多个thread，一般Grid是2维的block组成，而block是三维的thread组成的。

Kernel核函数编写有以下限制

1. 只能访问设备内存
2. 必须有void返回类型
3. 不支持可变数量的参数
4. 不支持静态变量
5. 显示异步行为

# 第三章Cuda执行模型

## SM

GPU每个SM都能支持数百个线程并发执行，每个GPU有多个SM，当一个核函数的网格被启动的时候，多个block会被同时分配到可用的SM上执行。

## 线程束

在硬件的微观上，CUDA 采用单指令多线程SIMT架构管理执行线程，不同设备有不同的线程束大小，但是到目前为止基本所有设备都是维持在32。在某个时刻SM只执行一个线程束，一个线程束中的每个线程都是同时同步执行同一条指令的，其中有些线程可以不选择执行，但是必须等待其它线程。