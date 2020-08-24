#include <linux/init.h>
#include <linux/module.h>

void event(void);

static int __init start(void)
{
    pr_info("Starting slave module\n");
    event();
    return 0;
}

static void __exit end(void)
{
    pr_info("Exiting the slave module\n");
}

module_init(start);
module_exit(end);

MODULE_AUTHOR("Bakare Emmanuel");
MODULE_LICENSE("GPL");
