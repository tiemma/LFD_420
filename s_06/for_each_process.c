#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

static int __init start(void)
{
    struct task_struct *p;

    pr_info("Starting process list");
    for_each_process(p)
    {
        pr_info("Process: command %s\npid %d, tgid %d, state %lx, parent id %d, self id %d\n",
                p->comm,
                p->pid,
                p->tgid,
                p->state,
                p->parent_exec_id,
                p->self_exec_id);
    }
    return 0;
}

static void __exit end(void)
{
    pr_info("Unloading the module\n");
}

module_init(start);
module_exit(end);

MODULE_AUTHOR("Bakare Emmanuel");
MODULE_LICENSE("GPL");
