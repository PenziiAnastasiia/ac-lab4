#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include "hello1.h"

MODULE_AUTHOR("Anastasiia Penzii <penziynastya@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint count = 1;
module_param(count, uint, S_IRUGO);
MODULE_PARM_DESC(count, "count of repeats hello world");

static struct list_head list;
static struct hello_data *data;


static void print_hello(void) {
  ktime_t start, end;
  start = ktime_get();

  pr_info("Hello, world!\n");

  end = ktime_get();
  u64 nanoseconds =  ktime_to_ns(ktime_sub(end, start));

  pr_info("Time taken for print hello: %lld nanoseconds\n", nanoseconds);
}

EXPORT_SYMBOL(print_hello);


static int __init hello_init(void)
{
unsigned int i;
if (count == 0) {
	pr_warn("The parameter value is equal to 0.\n");
} else if (count >= 5 && count <= 10) {
	pr_warn("The parameter value is between 5 and 10.\n");
} else if (count > 10) {
	pr_err("Error. The parameter value is greater than 10.\n");
	return -EINVAL;
}

INIT_LIST_HEAD(&list);

for (i = 0; i < count; i++) {
	struct hello_data *data = kmalloc(sizeof(*data), GFP_KERNEL);

	data->time = ktime_get();
	INIT_LIST_HEAD(&data->tlist);
	list_add_tail(&data->tlist, &list);
	print_hello();
}
return 0;
}

static void __exit hello_exit(void)
{
unsigned int i;

struct hello_data *tmp;
for (i = 0; i < count; i++) {
	list_for_each_entry_safe(data, tmp, &list, tlist) {

		u64 nanoseconds = ktime_to_ns(data->time);
		pr_info("Time in nanoseconds: %lld\n", nanoseconds);
		list_del(&data->tlist);
		kfree(data);
	}
}
}

module_init(hello_init);
module_exit(hello_exit);
