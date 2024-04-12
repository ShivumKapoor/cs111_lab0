#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>

static struct proc_dir_entry *entry;

static int proc_count(struct seq_file *m, void *v)
{
	// initialize counter to count processes
	int total_processes = 0;

	// points to the task_struct object of each process
	struct task_struct *t;

	// iterate over each running process
	for_each_process(task)
	{
		total_processes++;
		// printk("PID: %d", task->pid);
	}

	// format and print the total running processes to the seq_file object m
	seq_printf(m, "%d\n", total_processes);
}

static int __init proc_count_init(void)
{
	entry = proc_create_single("count", 0, NULL, proc_count);
	pr_info("proc_count: init\n");
	return 0;
}

static void __exit proc_count_exit(void)
{
	proc_remove(entry);
	pr_info("proc_count: exit\n");
}

module_init(proc_count_init);
module_exit(proc_count_exit);

MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("CS111 lab0 count proc number");
MODULE_LICENSE("GPL");
