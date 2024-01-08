#ifndef __MEMORY_RKS_H__
#define __MEMORY_RKS_H__

#ifdef __cplusplus
extern "C"
{
#endif

    int clear_ram(void);
    long int size_ram(void);
    long int free_ram(void);
    long int shared_ram(void);
    long int buffer_ram(void);
    long int size_swap(void);

#ifdef __cplusplus
}
#endif
#endif // __MEMORY_RKS_H__