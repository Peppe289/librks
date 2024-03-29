#ifndef __UTILS_RK_H__
#define __UTILS_RK_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

#define ERROR_POPEN     (-1)

#define BUFFER_SIZE     255
#ifndef DT_UNKNOWN
#define DT_UNKNOWN	0
#define DT_FIFO     1
#define DT_CHR      2
#define DT_DIR      4
#define DT_BLK      6
#define DT_REG      8
#define DT_LNK      10
#define DT_SOCK     12
#define DT_WHT      14
#endif

#define print_err(...)                     \
    do                                     \
    {                                      \
        fprintf(stderr, "%s: ", __func__); \
        fprintf(stderr, __VA_ARGS__);      \
    } while (0);

#define print_info(...)                    \
    do                                     \
    {                                      \
        fprintf(stdout, "%s: ", __func__); \
        fprintf(stdout, __VA_ARGS__);      \
    } while (0);


#ifdef __cplusplus
extern "C" {
#endif

#define _likely(x)      __builtin_expect((x), 1)
#define _unlikely(x)    __builtin_expect((x), 0)

struct vendor_cpuid {
    unsigned int eax; /** thread **/
    char vendorIDString[255];
    char vendorName[255];
};

typedef struct vendor_cpuid *VendorCPUID;

/** Cpp **/
void get_cpu_id_cpp(void);

#ifdef __cplusplus
}
#endif

#endif /** __UTILS_RK_H__ **/