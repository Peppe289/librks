#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

#include "syscall.h"
#include "utils.h"
#include "memory.h"

static struct sysinfo sys_info;

/**
 * Clean up RAM usage with sync and drop cache.
 * NOTE: Don't need root
 */
int clear_ram(void)
{
    // sync data on disk
    sync();

    // If this syscall isn't present return -1
    if (syscall_drop_cache4() < 0)
        return -1;

    return 0;
}


/**
 * @update: 0 not need, 1 need update
 */
static int load_sysinfo(int update)
{
    static int valid = 0;
    int ret;

    if (valid && !update)
        return 0;

    ret = sysinfo(&sys_info);

    if (ret)
    {
        print_err("Error with sysinfo");
        return -1;
    }
    else
        valid = 1;

    return 0;
}

long int size_ram(void)
{
    return load_sysinfo(0) ? -1 : sys_info.totalram;
}

long int free_ram(void)
{
    return load_sysinfo(1) ? -1 : sys_info.freeram;
}

long int shared_ram(void)
{
    return load_sysinfo(1) ? -1 : sys_info.sharedram;
}

long int buffer_ram(void)
{
    return load_sysinfo(1) ? -1 : sys_info.bufferram;
}

long int size_swap(void)
{
    return load_sysinfo(0) ? -1 : sys_info.totalswap;
}
