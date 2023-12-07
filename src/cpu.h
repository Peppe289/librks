#ifndef __CPU_STATS_RKS_H__
#define __CPU_STATS_RKS_H__

#ifdef __cplusplus
extern "C"
{
#endif

    extern char cpuid[126];
    extern unsigned int cpu_thread = 0;

    double get_cpu_temp(void);
    int max_Thread(void);

#ifdef __cplusplus
}
#endif
#endif // __CPU_STATS_RKS_H__