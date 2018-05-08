# 桂林理工大学操作系统实习

## 2016级软件工程2班 2018年5月7日
## 姓名：杨易 学号：3162052051639

## Preface
Personally, the most anticipated things are various practices each term, I can make a project/algorithm/idea from scratch. I think it's unlikely to give us some intrinsic understandings without any practice. Plain theories are less interesting since I even don't know where to use them and why use them instead of straightforward solutions. Here I have a chance to get a further understanding of those theories. Hope enjoy it!

## Part1: Source code analysis
> Source code are based on `linux v2.6.39`, you can get an identical copy on [https://elixir.bootlin.com/linux/v2.6.39/source](https://elixir.bootlin.com/linux/v2.6.39/source) freely. Here we would give an insight on linux system call `fork()`, which would spawn a new processs that resources inherited from parent process and load specific program to execute. Intact source code of `fork()` could obtain from [https://elixir.bootlin.com/linux/v2.6.39/source/kernel/fork.c](https://elixir.bootlin.com/linux/v2.6.39/source/kernel/fork.c). And note that I would remove somewhat nonessential code and comments since I want to give a brief overview rather than detailed explainnations.

+ [Source code analysis of system call `fork()`](SYSTEM_CALL_FORK.md)


## Part2: Simulate OS behaviors using ad hoc programs
+ [**Project 1 : Process scheduling using multi algorithms**](https://github.com/cthulhujk/glut_os_practice/tree/master/src/ProcessScheduling)
> Simulating process scheduling behavior by maximum priority scheduling algorithm policy
![](images/process_scheduling.gif)
[Windows 64bits release download](bin/SchedulingGUI.exe)
+ [**Project 2 : Process synchronization  TODO**](https://github.com/cthulhujk/glut_os_practice/tree/master/src/ThreadSync)
> Multi readers and a single writer.
+ [**Project 3 : The dinning philosophers problem**](https://github.com/cthulhujk/glut_os_practice/tree/master/src/DeadLock)
> In 1965, Dijkstra posed and solved a synchronization problem he called the dining philosophers problem. Here this project intends to simulate it.
+ [**Project 6 : File system**](https://github.com/cthulhujk/glut_os_practice/tree/master/src/YFileSystem)

## License
I don't give a license now, you can do anything you want!
