# levelDB源码解析一

## Introduction

levelDB是是一个持久化的key/value存储，key和value都是任意字节的数组，并且存储时，key值根据用户指定的comparator函数进行排序。

## 基础类结构介绍

### 1.Status

### 2. Slice

### 3. VersionSet



### 4. thread_annotations.h文件

**thread_annotations.h**文件主要是用于 **C-Lang**的编译优化，主要用到`__attribute__((x))`属性

- `guarded_by(x)`：主要是在与多线程的中的`mutex`关联，使用该属性，相应的变量的需要使用mutex上锁，用来保证线程安全

## DB

### 1. introduction

### 2. Variable

### 3. Function

1. `open()`
