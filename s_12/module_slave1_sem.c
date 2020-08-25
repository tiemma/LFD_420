#include <linux/init.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/errno.h>

#define SEM_WAIT 100

extern struct semaphore sem;

void event(void);

static int __init start(void)
{
    pr_info("Starting slave module, %s\n", KBUILD_MODNAME);
    pr_info("Acquiring semaphore with count %d\n", sem.count);

    if (down_trylock(&sem))
    {

        return -EAGAIN;
    }
    else
    {
        pr_info("Acquired semaphore, count now %d\n", sem.count);
    }

    // if (!down_timeout(&sem, SEM_WAIT))
    // {
    //     pr_info("Acquired sem lock in %s\n", KBUILD_MODNAME);
    // }
    // else
    // {
    //     return -ERESTARTSYS;
    // }
    event();
    return 0;
}

static void __exit end(void)
{
    pr_info("Unlocking semaphore lock acquired, %s\n", KBUILD_MODNAME);
    up(&sem);
    pr_info("Unlocked semaphore, has count %d\n", sem.count);
    pr_info("Exiting the slave module, %s\n", KBUILD_MODNAME);
}

module_init(start);
module_exit(end);

MODULE_AUTHOR("Bakare Emmanuel");
MODULE_LICENSE("GPL");
