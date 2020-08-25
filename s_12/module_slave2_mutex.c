#include <linux/init.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/errno.h>

extern struct mutex mutex;

void event(void);

static int __init start(void)
{
    pr_info("Starting slave module, %s\n", KBUILD_MODNAME);
    if (mutex_trylock(&mutex))
    {
        pr_info("Acquired lock from module %s", KBUILD_MODNAME);
    }
    else
    {
        pr_info("Issue occurred whilst obtaining lock %s", KBUILD_MODNAME);
        return -EBUSY;
    }
    event();
    return 0;
}

static void __exit end(void)
{
    if (mutex_is_locked(&mutex))
    {
        pr_info("Lock is still acquired by %s", KBUILD_MODNAME);
        mutex_unlock(&mutex);
    }
    else
    {
        pr_info("Mutex is already unlocked, differing...");
    }

    pr_info("Exiting the slave module, %s\n", KBUILD_MODNAME);
}

module_init(start);
module_exit(end);

MODULE_AUTHOR("Bakare Emmanuel");
MODULE_LICENSE("GPL");
