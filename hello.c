#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("Lazariev Ivan");
MODULE_DESCRIPTION("Lab 6");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int hello_world_num = 1;

module_param(hello_world_num, uint, 0);

MODULE_PARM_DESC(hello_world_num, "'Hello, World!' printing amount.");

struct event_list {
    struct list_head list;
    ktime_t event_time;
};

static struct list_head event_list_head;

static LIST_HEAD(event_list_head);

void new_event(void);

static int __init hello_init(void)
{
    int i = 0;
    /*if (hello_world_num > 10) {
        printk(KERN_ERR "Hello world printing number is too large (>10)");
        return -EINVAL;
    }*/
    BUG_ON(hello_world_num > 10);

    if (hello_world_num == 0) {
        printk(KERN_DEFAULT "Hello world printing number = 0");
    }
    else if (hello_world_num >= 5 && hello_world_num <= 10) {
        printk(KERN_DEFAULT "Hello world printing number is between 5 and 10");
    }
  
    for (i = 0; i < hello_world_num; i++) {
        printk(KERN_DEFAULT "Hello, World!\n");
        new_event();
    }
  return 0;
}

static void __exit hello_exit(void) {
  struct event_list *md, *tmp;
  list_for_each_entry_safe(md, tmp, &event_list_head, list) {
    printk(KERN_EMERG "Time: %lld\n", md->event_time);
    list_del(&md->list);
    kfree(md);
  }
}

void new_event(void) {
    struct event_list *event = NULL;
    event = NULL; //kmalloc(sizeof(struct event_list), GFP_KERNEL);
    event->event_time = ktime_get();
    list_add_tail(&event->list, &event_list_head);
}

module_init(hello_init);
module_exit(hello_exit);
