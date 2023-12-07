#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

#include "syscall.h"
#include "utils.h"
#include "memory.h"

// totalram = 0 mean not initialized
static struct sysinfo sys_info = {
    .totalram = 0,
};

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

double ram_size(void)
{
    int ret = 0;

    // is already initialized?
    if (sys_info.totalram == 0)
        ret = sysinfo(&sys_info);

    if (ret < 0)
        return ret;

    return sys_info.totalram / (1024 * 1024 * 1024);
}