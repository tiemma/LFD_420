#include <linux/init.h>
#include <linux/module.h>

static int __init start(void)
{
    pr_info("Starting master module\n");
    return 0;
}

static void __exit end(void)
{
    pr_info("Exiting the master module\n");
}

void event(void)
{
    pr_info("Calling master process from %s\n", __func__);
}

EXPORT_SYMBOL(event);

module_init(start);
module_exit(end);

MODULE_AUTHOR("Bakare Emmanuel");
MODULE_LICENSE("GPL");
