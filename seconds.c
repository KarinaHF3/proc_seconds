// seconds.c - /proc/seconds: segundos transcurridos desde insmod
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/jiffies.h>

#define PROC_NAME "seconds"
#define BUF_SIZE  64

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Karina");
MODULE_DESCRIPTION("Modulo /proc/seconds: muestra segundos desde que se cargo");
MODULE_VERSION("1.0");

static unsigned long start_jiffies;
static struct proc_dir_entry *proc_entry;

static ssize_t seconds_read(struct file *file, char __user *user_buf,
                            size_t count, loff_t *ppos)
{
    char buf[BUF_SIZE];
    unsigned long elapsed_j = jiffies - start_jiffies;
    unsigned long elapsed_s = elapsed_j / HZ;
    int len = scnprintf(buf, sizeof(buf), "%lu\n", elapsed_s);

    return simple_read_from_buffer(user_buf, count, ppos, buf, len);
}

static const struct proc_ops seconds_proc_ops = {
    .proc_read = seconds_read,
};

static int __init seconds_init(void)
{
    start_jiffies = jiffies;

    proc_entry = proc_create(PROC_NAME, 0444, NULL, &seconds_proc_ops);
    if (!proc_entry) {
        pr_err("seconds: no se pudo crear /proc/%s\n", PROC_NAME);
        return -no memory;
    }

    pr_info("seconds: cargado. /proc/%s listo.\n", PROC_NAME);
    return 0;
}

static void __exit seconds_exit(void)
{
    if (proc_entry)
        proc_remove(proc_entry);

    pr_info("seconds: descargado. /proc/%s eliminado.\n", PROC_NAME);
}

module_init(seconds_init);
module_exit(seconds_exit);