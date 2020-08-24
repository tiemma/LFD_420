#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>

static LIST_HEAD(process_list);

struct process_entry
{
    char process[TASK_COMM_LEN];
    struct list_head task_list;
    pid_t pid;
};

static int __init start(void)
{
    struct process_entry *pe;
    struct task_struct *p;

    pr_info("Starting module\n");
    for_each_process(p)
    {
        pe = kmalloc(sizeof(struct process_entry), GFP_KERNEL);
        if (!pe)
        {
            pr_err("Memory allocation failed on process %s, pid %d\n", p->comm, p->pid);
        }
        strncpy(pe->process, p->comm, TASK_COMM_LEN);
        pe->pid = p->pid;
        pr_info("Process %s with pid %d added to list\n", p->comm, p->pid);
        list_add(&pe->task_list, &process_list);
    }
    return 0;
}

static void __exit end(void)
{
    struct list_head *head;
    struct list_head *tmp;

    if (list_empty(&process_list))
    {
        pr_info("Process list is empty\n");
    }
    else
    {
        pr_info("Process list is not empty, processing now\n");
    }
    list_for_each_safe(head, tmp, &process_list)
    {
        struct process_entry *pe = list_entry(head, struct process_entry, task_list);

        pr_info("Removed process %s, pid %d from process list\n", pe->process, pe->pid);
        list_del(&pe->task_list);
        kfree(pe);
    }
    if (!list_empty(&process_list))
    {
        pr_err("Process list was not fully emptied\n");
    }
    else
    {
        pr_info("Process list successfully emptied\n");
    }
    pr_info("Exiting the module\n");
}

module_init(start);
module_exit(end);

MODULE_AUTHOR("Bakare Emmanuel");
MODULE_LICENSE("GPL");
