#ifndef __CPU_STATS_RKS_H__
#define __CPU_STATS_RKS_H__

#ifdef __cplusplus
extern "C"
{
#endif

    extern char cpuid[126];

    double get_cpu_temp(void);
    int system_available_cpu(void);
    int system_designed_cpu(void);

#ifdef __cplusplus
}
#endif
#endif // __CPU_STATS_RKS_H__