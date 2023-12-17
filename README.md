# librks

This library contains functions for system management and kernel control.

What can he do?
---

Public function:

- cpu.c: 
    - system_available_cpu(void) [x]
    - SingleThreadMaxFreq(thread)
    - get_cpu_temp() [x]
        - for now support AMD.
    - get_possible_governor()
- fan_service.c:
    - get_fan_speed()
        - for now only for asus motherboard
- meminfo.c:
    - memory_percentage()
    - clear_ram() [x]
- gpu.c:
    - get_gpu_usage()
    - get_gpu_thermal()

