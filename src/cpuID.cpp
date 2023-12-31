#include <cpuid.h>
#include <iostream>
#include <map>
#include <string>
#include <cstring>

#include "utils.h"
#include "cpu.h"

using namespace std;

/**
 * Thx https://stackoverflow.com/a/15557347 for this 
 */
struct CPUVendorID {
    unsigned int ebx;
    unsigned int edx;
    unsigned int ecx;

    string toString() const {
        return string(reinterpret_cast<const char *>(this), 12);
    }
};

void get_cpu_id_cpp() {
    unsigned int level = 0;
    unsigned int eax = 0, ebx, ecx, edx;

    // already loaded
    if (cpuid[0] != '\0')
        return;

    __get_cpuid(level, &eax, &ebx, &ecx, &edx);

    CPUVendorID vendorID { .ebx = ebx, .edx = edx, .ecx = ecx };

    map<string, string> vendorIdToName;
    vendorIdToName["GenuineIntel"] = "Intel";
    vendorIdToName["AuthenticAMD"] = "AMD";
    vendorIdToName["CyrixInstead"] = "Cyrix";
    vendorIdToName["CentaurHauls"] = "Centaur";
    vendorIdToName["SiS SiS SiS "] = "SiS";
    vendorIdToName["NexGenDriven"] = "NexGen";
    vendorIdToName["GenuineTMx86"] = "Transmeta";
    vendorIdToName["RiseRiseRise"] = "Rise";
    vendorIdToName["UMC UMC UMC "] = "UMC";
    vendorIdToName["Geode by NSC"] = "National Semiconductor";

    string vendorIDString = vendorID.toString();

    auto it = vendorIdToName.find(vendorIDString);
    string vendorName = (it == vendorIdToName.end()) ? "Unknown" : it->second;

    strcpy(cpuid, &vendorName[0]);
}