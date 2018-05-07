# 桂林理工大学操作系统实习

## 2016级软件工程2班 2018年5月7日
## 姓名：杨易 学号：3162052051639

## Preface
Personally, the most anticipated thing is the various course's practice, I can make a project/algorithm/idea from scratch. I think it's unlikely to give us some intrinsic understandings without any practice. Plain theories are less interesting since I even don't know where to use them and why use them instead of straightforward solutions. Here I have a chance to get a further understanding.


## Part1: Source code analysis
> Source code are based on `linux v2.6.39`, you can get an identical copy on [https://elixir.bootlin.com/linux/v2.6.39/source](https://elixir.bootlin.com/linux/v2.6.39/source) freely. Here we would give an insight on linux system call `fork()`, which would spawn a new processs that resources inherited from parent process and load specific program to execute. Intact source code of `fork()` could obtain from [https://elixir.bootlin.com/linux/v2.6.39/source/kernel/fork.c](https://elixir.bootlin.com/linux/v2.6.39/source/kernel/fork.c). And note that I would remove somewhat nonessential code and comments since I want to give a brief overview rather than detailed explainnations.

+ [Source code analysis of system call `fork()`](SYSTEM_CALL_FORK.md)


## Part2: Simulate OS behaviors using ad hoc programs

## License
I don't give a license now, you can do anything you want!
