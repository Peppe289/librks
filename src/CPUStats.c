#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>

#include "utils.h"

#define MAX_PATH_SIZE 255

char cpuid[126] = {'\0'};
char pthermal_ctl[MAX_PATH_SIZE] = {'\0'};

static int __sysctl_thermal_CPU(void)
{
    char vendor[126];
    pid_t pid;
    int pipefd[2];
    char path[MAX_PATH_SIZE] = {'\0'};
    int devNUll = open("/dev/null", O_WRONLY);
    long rd;

    get_cpu_id_cpp();

    if (cpuid[0] == '\0' || (strcmp(cpuid, "Unknown") == 0))
        exit(-1);

    if (strcmp(cpuid, "AMD") == 0)
        memcpy(vendor, "^k10temp", sizeof("^k10temp"));
    else if (strcmp(cpuid, "Intel") == 0)
    {
        // do nothing for now
    }

    if (pipe(pipefd) < 0)
    {
        perror("Error to open pipe\n");
        exit(-1);
    }

    if ((pid = fork()) < 0)
    {
        perror("Error to fork\n");
    }
    else if (pid == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(devNUll, STDERR_FILENO);
        execlp("grep", "grep", "-r", "-E", vendor, "-l", "/sys", NULL);
        exit(-1); // wrong exec
    }
    else
    {
        close(pipefd[1]);
        if ((rd = read(pipefd[0], path, sizeof(path))) < 0)
        {
            perror("Error to read()");
        }

        close(pipefd[0]);
        close(devNUll);

        if (_unlikely(rd == 0)) {
            print_err("Not found");
            path[0] = '\0';
        }

        /* We don't need exit status. All exception are controlled */
        waitpid(pid, NULL, 0);

        // node not found
        if (rd == 0)
            return -1;
    }

    strncpy(pthermal_ctl, path, strlen(path) - sizeof("name"));
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
        perror("Error to read node\n");
        exit(-1);
    }

    close(fd);

    return atoi(data) / 1000;
}

double get_cpu_temp(void)
{
    return sysctl_thermal_CPU();
}

int system_designed_cpu(void) {
    return get_nprocs_conf();
}

int system_available_cpu(void)
{
    return get_nprocs();
}
