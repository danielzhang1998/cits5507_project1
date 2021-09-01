quick sort 已完成

需要对 quick sort 的代码进行熟悉

https://www.bilibili.com/video/BV1qW41137pF?from=search&seid=3882581415265864220

enumeration sort 已完成

quick sort 和 enumeration sort 合并已完成

merge sort 已完成

https://fishc.com.cn/forum.php?mod=viewthread&tid=79940&highlight=%B9%E9%B2%A2%C5%C5%D0%F2

已经对 main 进行修改,通过输入不同的参数,来执行不同的命令

再下一步进行并行运算的改写

已完成使用 omp 执行的 quick sort algorithm

如何运行代码:
gcc-10 -fopenmp project_file.c -o project_file.out

./project_file.out 800000 quick -omp

对于 quick sort omp, array 大小要大于 40000,才能体现出优势
