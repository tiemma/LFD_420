#include <linux/init.h>
#include <linux/module.h>

DEFINE_MUTEX(mutex);
EXPORT_SYMBOL(mutex);

static int __init start(void)
{
    pr_info("Starting master module, %s\n", KBUILD_MODNAME);
    return 0;
}

static void __exit end(void)
{
    pr_info("Exiting the master module, %s\n", KBUILD_MODNAME);
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
