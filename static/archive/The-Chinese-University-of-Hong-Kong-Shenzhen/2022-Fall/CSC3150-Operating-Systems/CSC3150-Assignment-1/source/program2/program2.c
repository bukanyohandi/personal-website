#include <linux/err.h>
#include <linux/fs.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/printk.h>
#include <linux/sched.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

struct wait_opts {
	enum pid_type wo_type;
	int wo_flags;
	struct pid *wo_pid;

	struct waitid_info *wo_info;
	int wo_stat;
	struct rusage *wo_rusage;

	wait_queue_entry_t child_wait;
	int notask_error;
};

extern int do_execve(struct filename *filename,
		     const char __user *const __user *__argv,
		     const char __user *const __user *__envp);
extern void __noreturn do_exit(long code);
extern long do_wait(struct wait_opts *wo);
extern struct filename *getname_kernel(const char *filename);
extern pid_t kernel_clone(struct kernel_clone_args *kargs);

void my_wait(pid_t process_id)
{
	int stat, wait;
	struct wait_opts wo;
	struct pid *wo_pid = NULL;
	enum pid_type type;

	type = PIDTYPE_PID;
	wo_pid = find_get_pid(process_id);

	wo.wo_type = type;
	wo.wo_flags = WUNTRACED | WEXITED;
	wo.wo_pid = wo_pid;
	wo.wo_info = NULL;
	wo.wo_stat = (int __user *)&stat;
	wo.wo_rusage = NULL;

	do {
		wait = do_wait(&wo);
	} while (wait == -10);

	// printk("[program2] -> %d\n", wait);
	// printk("[program2] -> %d\n", wo.wo_stat);

	if (wo.wo_stat == 0) {
		printk("[program2] : get SIGCHLD signal\n");
		printk("[program2] : normal termination with EXIT STATUS = "
		       "%d\n",
		       wo.wo_stat);
	} else if (1 <= wo.wo_stat && wo.wo_stat <= 139) {
		int event = wo.wo_stat;
		if (event > 128)
			event -= 128;
		char signals[16][8] = { "",	   "SIGHUP",  "SIGINT",
					"SIGQUIT", "SIGILL",  "SIGTRAP",
					"SIGABRT", "SIGBUS",  "SIGFPE",
					"SIGKILL", "",	      "SIGSEGV",
					"",	   "SIGPIPE", "SIGALRM",
					"SIGTERM" };
		char reasons[16][20] = { "",
					 "hang up signal",
					 "interrupt signal",
					 "quit signal",
					 "illegal instruction",
					 "trap signal",
					 "abort signal",
					 "bus signal",
					 "floating",
					 "kill signal",
					 "",
					 "segmentation fault",
					 "",
					 "pipe signal",
					 "alarm signal",
					 "termination signal" };

		printk("[program2] : get %s signal\n", signals[event]);
		printk("[program2] : child process has %s\n", reasons[event]);
		printk("[program2] : The return signal is %d\n", event);
	} else {
		printk("[program2] : get SIGSTOP signal \n");
		printk("[program2] : child process stopped\n");
		printk("[program2] : The return signal is 19\n");
	}

	put_pid(wo_pid);

	// do_exit(wo.wo_stat);

	return;
}

int my_exec(void)
{
	// const char path[] = "/home/vagrant/csc3150/AS1_120040025/source/"
	// 		    "program2/test";
	const char path[] = "/tmp/test";
	// const char *const argv[] = {path, NULL, NULL};
	// const char *const envp[] = {"HOME=/", "PATH
	// =/sbin:/user/sbin:/bin:/usr/bin",
	//                             NULL};

	struct filename *file = getname_kernel(path);

	printk("[program2] : child process");

	int exit_stat;
	exit_stat = do_execve(file, NULL, NULL);

	// if (exit_stat)
	//   do_exit(exit_stat);

	return exit_stat;
}

// implement fork function
int my_fork(void *argc)
{
	// set default sigaction for current process
	int i;
	pid_t process_id;
	struct kernel_clone_args kargs = { .flags = SIGCHLD,
					   .stack = (unsigned long)&my_exec,
					   .stack_size = 0,
					   .parent_tid = NULL,
					   .child_tid = NULL,
					   .tls = 0 };

	struct k_sigaction *k_action = &current->sighand->action[0];
	for (i = 0; i < _NSIG; i++) {
		k_action->sa.sa_handler = SIG_DFL;
		k_action->sa.sa_flags = 0;
		k_action->sa.sa_restorer = NULL;
		sigemptyset(&k_action->sa.sa_mask);
		k_action++;
	}

	/* fork a process using kernel_clone or kernel_thread */
	process_id = kernel_clone(&kargs);

	/* execute a test program in child process */
	if (process_id >= 0) {
		my_exec();

		printk("[program2] : The child process has pid = %d\n",
		       process_id);
		printk("[program2] : This is the parent process, pid = %d\n",
		       (pid_t)current->pid);

		/* wait until child process terminates */
		my_wait(process_id);
	} else {
		printk("[program2] : error while forking\n");
	}

	return 0;
}

static int __init program2_init(void)
{
	static struct task_struct *task;

	printk("[program2] : module_init [Yohandi] [120040025]\n");
	printk("[program2] : module_init create kthread start\n");

	/* create a kernel thread to run my_fork */
	task = kthread_create(&my_fork, NULL, "MyThread");
	if (!IS_ERR(task)) {
		printk("[program2] : module_init kthread start");
		wake_up_process(task);
	}

	return 0;
}

static void __exit program2_exit(void)
{
	printk("[program2] : module_exit\n");
}

module_init(program2_init);
module_exit(program2_exit);
