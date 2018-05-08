# Source code analysis of system call `fork()`
`glibc` provided a wrapper function of system call `fork()`, let's start our source code understanding journey here.

The following code is the entry of system_call written in assembly, which would be faster(:) guessing without any profiling). For our purpose, the execution flow would jump to `syscall_badsys` label unless system call id was out of the valid range.
```asm
cmpl $(nr_syscalls), %eax
jae syscall_badsys
```
Next, `system_call` routine would call `sys_call_table`. As its name described, `sys_call_table` took an argument eax to deneote which system call you want to call and searchs item in the table.
```asm
ENTRY(system_call)
	RING0_INT_FRAME			# can't unwind into user space anyway
	pushl_cfi %eax			# save orig_eax
	SAVE_ALL
	GET_THREAD_INFO(%ebp)
					# system call tracing in operation / emulation
	testl $_TIF_WORK_SYSCALL_ENTRY,TI_flags(%ebp)
	jnz syscall_trace_entry
	cmpl $(nr_syscalls), %eax
	jae syscall_badsys
syscall_call:
	call *sys_call_table(,%eax,4)
	movl %eax,PT_EAX(%esp)		# store the return value
syscall_exit:
	LOCKDEP_SYS_EXIT
	DISABLE_INTERRUPTS(CLBR_ANY)	# make sure we don't miss an interrupt
					# setting need_resched or sigpending
					# between sampling and the iret
	TRACE_IRQS_OFF
	movl TI_flags(%ebp), %ecx
	testl $_TIF_ALLWORK_MASK, %ecx	# current->work
	jne syscall_exit_work

restore_all:
	TRACE_IRQS_IRET
restore_all_notrace:
	movl PT_EFLAGS(%esp), %eax	# mix EFLAGS, SS and CS
	# Warning: PT_OLDSS(%esp) contains the wrong/random values if we
	# are returning to the kernel.
	# See comments in process.c:copy_thread() for details.
	movb PT_OLDSS(%esp), %ah
	movb PT_CS(%esp), %al
	andl $(X86_EFLAGS_VM | (SEGMENT_TI_MASK << 8) | SEGMENT_RPL_MASK), %eax
	cmpl $((SEGMENT_LDT << 8) | USER_RPL), %eax
	CFI_REMEMBER_STATE
	je ldt_ss			# returning to user-space with LDT SS
restore_nocheck:
	RESTORE_REGS 4			# skip orig_eax/error_code
irq_return:
	INTERRUPT_RETURN
```
`do_fork()` is the main fork routine. It copies the process, and if successful kick-starts
 * it and waits for it to finish using the VM if required.
```cpp
long do_fork(unsigned long clone_flags,
	      unsigned long stack_start,
	      struct pt_regs *regs,
	      unsigned long stack_size,
	      int __user *parent_tidptr,
	      int __user *child_tidptr)
{
/// *task_struct* represents the PROCESS
	struct task_struct *p;
	int trace = 0;
	long nr;
/// Permissions checking 
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

/// If this invocation was asked by kernel, don't do user tracing stuff. Note that *likely()* is and optimization signal, it told the compiler that "THIS IS HOTSPOT CODE BLOCK, YOU CAN DO MORE RADICAL OPTIMIZATIOS!"
	if (likely(user_mode(regs)))
		trace = tracehook_prepare_clone(clone_flags);
/// Spwan new process and inherit parent process resource
	p = copy_process(clone_flags, stack_start, regs, stack_size,
			 child_tidptr, NULL, trace);

 /// If copy_process() worked well
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

		p->flags &= ~PF_STARTING;
/// Wake up new task via clone_flags and run it firstly since subprocess would call exec*() for their stuff, it's unreasonable to delay it. 
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

# Reference
[0] Linux kernel development Third Edition, Robert Love,2011.6
