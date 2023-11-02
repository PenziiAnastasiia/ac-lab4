#include <linux/list.h>
#include <linux/ktime.h>

struct hello_data {
    struct list_head tlist;
    ktime_t time;
};

void print_hello(void);
