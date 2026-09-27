# Process_copy 多进程分块文件复制

基于 Linux 的多进程文件复制程序：父进程将源文件按进程数切片，fork 出多个子进程，每个子进程通过 `execl` 调用 `copy` 程序，并行复制文件的不同偏移块，最后父进程回收所有子进程。

## 项目结构

```
.
├── source/              # 主程序源码
│   ├── main.c           # 入口，解析参数并协调各模块
│   ├── check_pram.c     # 参数校验（文件存在、进程数范围）
│   ├── block_cur.c      # 计算分块大小
│   ├── process_create.c # fork 子进程并 execl 执行 copy
│   └── process_wait.c   # 父进程循环回收子进程
├── MOD/
│   ├── copy.c           # 子进程执行的复制程序
│   └── copy             # 编译生成的 copy 可执行文件
├── include/
│   └── process_copy.h   # 公共头文件与函数声明
└── Process_copy         # 编译生成的主程序
```

## 编译

```bash
gcc source/*.c -I include -o Process_copy
gcc MOD/copy.c -o MOD/copy
```

> 注意：`process_create.c` 中通过 `execl` 以绝对路径加载 `MOD/copy`，编译时请保持目录结构不变。

## 使用

```bash
./Process_copy <源文件> <目标文件> [进程数]
```

- `进程数`：可选参数，默认为 3，取值范围 3 ~ 100
- 示例：

```bash
./Process_copy file1.txt file2.txt 5
```

## 工作原理

1. `check_pram` 校验命令行参数与源文件是否存在；
2. `block_cur` 用 `stat` 获取文件大小，按进程数向上取整计算块大小；
3. `process_create` 循环 `fork` 出 N 个子进程，每个子进程带上偏移量（`i * blocksize`）和块大小，`execl` 执行 `MOD/copy`；
4. `copy` 在源、目标文件中分别 `lseek` 到对应偏移，读取一块数据并写入目标文件；
5. 父进程在 `process_wait` 中用 `waitpid` 循环回收全部子进程并打印回收信息。
