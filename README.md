# C++ 数据结构与线性表

数据结构课程实践合集，每个子目录是一个独立的 Visual Studio 工程（各自带 `.sln`）。

## 包含的工程

| 目录 | 内容 |
|---|---|
| `Circle_Queue` | 循环队列 |
| `Dlist` | 双向链表 |
| `List_Queue` | 链表与队列 |
| `Stack` | 栈 |
| `clist` | 线性表 |
| `homework` | 课后作业 |
| `list` | 链表 |
| `seqlist` | 顺序表 |
| `stack_list` | 栈与链表 |
| `stack-queue` | 栈与队列 |
| `work1` / `work2` | 练习 |
| `进阶数据结构` | 进阶数据结构综合 |
| `随便写点例子` | 随手练习 |
| `2408` | 每日练习 |

## 构建

每个目录独立编译（Visual Studio 2019/2022，MSVC）：

```bash
cd Circle_Queue
# 用 Visual Studio 打开 .sln，或命令行
msbuild Circle_Queue.sln /p:Configuration=Debug
```

## 说明

- 编译产物（`Debug/`、`x64/`、`.vs/`）已通过 `.gitignore` 排除
- 每个工程的原始代码完整保留，未做任何修改
