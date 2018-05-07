# 桂林理工大学操作系统实习

## 2016级软件工程2班 2018年5月7日
## 姓名：杨易 学号：3162052051639

## Preface
Personally, the most anticipated thing is the various course's practice, I can make a project/algorithm/idea from scratch. I think it's unlikely to give us some intrinsic understandings without any practice. Plain theories are less interesting since I even don't know where to use them and why use them instead of straightforward solutions. Here I have a chance to get a further understanding.


## Part1: Source code analysis
Source code are based on `linux v2.6.39`, you can get an identical copy on [https://elixir.bootlin.com/linux/v2.6.39/source](https://elixir.bootlin.com/linux/v2.6.39/source) freely. Here we would give an insight on linux system call `fork()`, which would spawn a new processs that resources inherited from parent process and load specific program to execute. Intact source code of `fork()` could obtain from [https://elixir.bootlin.com/linux/v2.6.39/source/kernel/fork.c](https://elixir.bootlin.com/linux/v2.6.39/source/kernel/fork.c). And note that I would remove redundant code and comments since I want to give a brief overview instead of detailed explainnations.
```cpp
///
long do_fork(unsigned long clone_flags,
	      unsigned long stack_start,
	      struct pt_regs *regs,
	      unsigned long stack_size,
	      int __user *parent_tidptr,
	      int __user *child_tidptr)
{
	struct task_struct *p;
	int trace = 0;
	long nr;

	/*
	 * Do some preliminary argument and permissions checking before we
	 * actually start allocating stuff
	 */
	if (clone_flags & CLONE_NEWUSER) {
		if (clone_flags & CLONE_THREAD)
			return -EINVAL;
		/* hopefully this check will go away when userns support is
		 * complete
		 */
		if (!capable(CAP_SYS_ADMIN) || !capable(CAP_SETUID) ||
				!capable(CAP_SETGID))
			return -EPERM;
	}

	/*
	 * When called from kernel_thread, don't do user tracing stuff.
	 */
	if (likely(user_mode(regs)))
		trace = tracehook_prepare_clone(clone_flags);

	p = copy_process(clone_flags, stack_start, regs, stack_size,
			 child_tidptr, NULL, trace);
	/*
	 * Do this prior waking up the new thread - the thread pointer
	 * might get invalid after that point, if the thread exits quickly.
	 */
	if (!IS_ERR(p)) {
		struct completion vfork;

		trace_sched_process_fork(current, p);

		nr = task_pid_vnr(p);

		if (clone_flags & CLONE_PARENT_SETTID)
			put_user(nr, parent_tidptr);

		if (clone_flags & CLONE_VFORK) {
			p->vfork_done = &vfork;
			init_completion(&vfork);
		}

		audit_finish_fork(p);
    
		tracehook_report_clone(regs, clone_flags, nr, p);

		/*
		 * We set PF_STARTING at creation in case tracing wants to
		 * use this to distinguish a fully live task from one that
		 * hasn't gotten to tracehook_report_clone() yet.  Now we
		 * clear it and set the child going.
		 */
		p->flags &= ~PF_STARTING;

		wake_up_new_task(p, clone_flags);

		tracehook_report_clone_complete(trace, regs,
						clone_flags, nr, p);

		if (clone_flags & CLONE_VFORK) {
			freezer_do_not_count();
			wait_for_completion(&vfork);
			freezer_count();
			tracehook_report_vfork_done(p, nr);
		}
	} else {
		nr = PTR_ERR(p);
	}
	return nr;
}
```

## Part2: Simulate OS behaviors using ad hoc programs

## License
I don't give a license now, you can do anything you want!
