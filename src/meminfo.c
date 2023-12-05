#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "syscall.h"
#include "utils.h"

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