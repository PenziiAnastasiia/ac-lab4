#include <linux/init.h>
#include <linux/module.h>
#include "hello1.h"


static uint count = 1;

static int __init hello_init(void)
{
  unsigned int i;

  for (i = 0; i < count; i++) {
	   print_hello();
}
}

static void __exit hello_exit(void)
{
  pr_info("Module hello2 is unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
