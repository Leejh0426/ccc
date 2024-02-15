/*
 *Austin Kim 소스 코드 참조!
 * */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/init.h>
#include <linux/memblock.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/cpu.h>
#include <linux/delay.h>
#include <asm/setup.h>
#include <linux/input.h>
#include <linux/debugfs.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/mutex.h>
//#include <linux/slub_def.h> // 컴파일 에러남.
#include <linux/uaccess.h>
#include <asm/memory.h>


uint32_t raspbian_debug_state = 0x1000;
static struct dentry *rpi_kernel_debug_debugfs_root;

static int rpi_kernel_debug_stat_get(void *data, u64 *val)
{
	    printk("===OJW [%s][L:%d][val:%d]===\n", __func__, __LINE__, raspbian_debug_state);
	        *val = raspbian_debug_state;

		    return 0;
}

static int rpi_kernel_debug_stat_set(void *data, u64 val)
{
	    raspbian_debug_state = (uint32_t)val;

	        printk("===OJW [raspbian] [%s][L:%d], raspbian_debug_state[%lu],value[%lu]===\n", 
				   __func__, __LINE__, (long unsigned int)raspbian_debug_state, (long unsigned int)val);

		    return 0;
}


DEFINE_SIMPLE_ATTRIBUTE(rpi_kernel_debug_stat_fops, rpi_kernel_debug_stat_get, rpi_kernel_debug_stat_set, "%llu\n");

static int rpi_kernel_debug_debugfs_driver_probe(struct platform_device *pdev)
{
	    printk("===OJW [%s][L:%d]===\n", __func__, __LINE__);
	        return 0;
}

static struct platform_driver rpi_kernel_debug_debugfs_driver = {
	    .probe      = rpi_kernel_debug_debugfs_driver_probe,
	        .driver     = {
			        .owner  = THIS_MODULE,
				        .name   = "rpi_debug",
					    },
};

static int __init rpi_kernel_debug_debugfs_init(void)  //__init 정의 된곳, include/linux/init.h //초기화 할 내용.
{
	    printk("===OJW [%s][L:%d]===\n", __func__, __LINE__);

	        rpi_kernel_debug_debugfs_root = debugfs_create_dir("rpi_debug", NULL); //rpi_debug 디렉토리 생성
		    debugfs_create_file("val", S_IRUGO, rpi_kernel_debug_debugfs_root,
				        NULL, &rpi_kernel_debug_stat_fops);  //rpi_debug디렉토리에, val라는 file 생성.

		        return platform_driver_register(&rpi_kernel_debug_debugfs_driver);
}

late_initcall(rpi_kernel_debug_debugfs_init); //부팅시 초기에 한번 콜 됨.

//커널의 메타데이터 설정
MODULE_DESCRIPTION("raspberrypi debug interface driver");  //모듈 설명
MODULE_AUTHOR("Austin Kim <austindh.kim@gmail.com>"); // 모듈 만든사람
MODULE_LICENSE("GPL"); //모듈의 라이센스 GNU General Public License , 오픈소스, 파생 작업물도, 동일한 라이센스로 공개해야함.
