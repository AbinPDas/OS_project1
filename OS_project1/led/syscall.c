#include <linux/module.h>
#include <linux/configfs.h>
#include <linux/init.h>
#include <linux/tty.h>          
#include <linux/kd.h>           
#include <linux/vt.h>
#include <linux/console_struct.h>       
#include <linux/vt_kern.h>
#include <unistd.h>
struct timer_list my_timer;
struct tty_driver *my_driver;

#define BLINK_DELAY   HZ/100
#define RESTORE_LEDS  0xFF

static void my_timer_func(unsigned long ptr)
{
        int *pstatus = (int *)ptr;
        (my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED,
                            *pstatus);
        my_timer.expires = jiffies + BLINK_DELAY;
        add_timer(&my_timer);
}
asmlinkage long sys_ledon(char k)
{

        my_driver = vc_cons[fg_console].d->port.tty->driver;
        init_timer(&my_timer);
        my_timer.function = my_timer_func;
        my_timer.data = (unsigned long)&k;
        my_timer.expires = jiffies + BLINK_DELAY;
        add_timer(&my_timer);
	sleep(2);
        del_timer(&my_timer);
        (my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED,
                            RESTORE_LEDS);
        return 0;
}
