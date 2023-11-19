#ifndef __SYSCALL_RKS_H__
#define __SYSCALL_RKS_H__

#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/unistd.h>
#include <asm-generic/unistd.h>
#include <asm/unistd.h>
#include <string.h>
#include <errno.h>
#include <asm/unistd_32.h>

#define DROP_CACHE4 600
#define syscall_drop_cache4(...) syscall(DROP_CACHE4);

#endif // __SYSCALL_RKS_H__
