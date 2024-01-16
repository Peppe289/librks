#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>
#include <dirent.h>

#include "utils.h"

#define MAX_PATH_SIZE 255

char cpuid[126] = {'\0'};
char pthermal_ctl[MAX_PATH_SIZE] = {'\0'};

static int find_thermal_control(const char *path, const char *vendor)
{
    DIR *dir;
    struct dirent *entry;
    char buff[250];
    int fd;
    char tmp[50];

    if ((dir = opendir(path)) == NULL)
        return 0;

    while ((entry = readdir(dir)) != NULL)
    {
        if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
            continue;

        memset(buff, 0, sizeof(buff));
        sprintf(buff, "%s/%s", path, entry->d_name);


        if (entry->d_type == DT_DIR)
        {
            if (find_thermal_control(buff, vendor) == 1) {
                closedir(dir);
                return 1;
            }
        }
        else if (strcmp(entry->d_name, "name") == 0)
        {
            if ((fd = open(buff, O_RDONLY)) < 0) {
                perror("Error to open file");
                continue;
            }

            if (read(fd, tmp, sizeof(tmp)) < 0) {
                perror("Error to read file");
                close(fd);
                continue;
            }

            if (memcmp(tmp, vendor, strlen(vendor)) == 0) {
                memset(pthermal_ctl, 0, sizeof(pthermal_ctl));
                sprintf(pthermal_ctl, "%s/", path);
                close(fd);
                return 1;
            }
        }
    }

    closedir(dir);
    return 0;
}

static int __sysctl_thermal_CPU(void)
{
    char vendor[126];

    get_cpu_id_cpp();

    if (cpuid[0] == '\0' || (strcmp(cpuid, "Unknown") == 0))
        exit(-1);

    if (strcmp(cpuid, "AMD") == 0)
        memcpy(vendor, "k10temp", sizeof("k10temp"));
    else if (strcmp(cpuid, "Intel") == 0)
    {
        // do nothing for now
    }

    find_thermal_control("/sys/devices", vendor);
    return 0;
}

static double sysctl_thermal_CPU(void)
{
    int ret;
    int fd;
    char tpath[MAX_PATH_SIZE] = {'\0'};
    char data[6] = {'\0'};

    ret = __sysctl_thermal_CPU();
    if (ret < 0)
        exit(-1);

    strcpy(tpath, pthermal_ctl); // copy absolute path
    strcat(tpath, "temp1_input");

    fd = open(tpath, O_RDONLY);

    ret = read(fd, data, sizeof(data));
    if (ret < 0)
    {
        perror("Error to read node");
        exit(-1);
    }

    close(fd);

    return atoi(data) / 1000;
}

double get_cpu_temp(void)
{
    return sysctl_thermal_CPU();
}

int system_designed_cpu(void)
{
    return get_nprocs_conf();
}

int system_available_cpu(void)
{
    return get_nprocs();
}
