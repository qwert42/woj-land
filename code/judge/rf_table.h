#ifndef __RF_TABLE__
#define __RF_TABLE__

#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include "logger.h"

/*
 * RF_table 每个值对应的是该syscall可被调用的次数
 *    取值有3种:
 *      正值: 表示可被调用的次数, 每次调用后会减一(比如fork)
 *      零值: 表示禁止调用(比如open)
 *      负值: 表示不限制该syscall(比如write)
 * 
 * RF_table的初始化由init_RF_table函数完成
 */
short RF_table[1024] = {0};

/*
 * RF_* 数组对是用于初始化RF_table的数据来源, 
 * 每两个数字为一组k/v: syscall_id:次数
 *   次数 < 0 表示不限制
 *   次数 > 0 表示可调用次数, 运行时每调用一次减一
 *   次数 = 0 (运行时达到) 不再允许调用该syscall
 * 最后一个syscall_id存放的是非正值，表示结束
 * 未指定的syscall_id的次数将被自动初始化为0
 */
#if __WORDSIZE == 32    //x86_32
//c or c++
int RF_C[512] =
{
    SYS_access,         -1,
    SYS_brk,            -1,
    SYS_close,          -1,
    SYS_execve,         1,
    SYS_exit_group,     -1,
    SYS_fstat64,        -1,
    SYS_futex,          -1,
    SYS_gettimeofday,   -1,
    SYS_mmap2,          -1,
    SYS_mremap,         -1,
    SYS_mprotect,       -1,
    SYS_munmap,         -1,
    SYS_lseek,          -1,
    SYS_read,           -1,
    SYS_set_thread_area,-1,
    SYS_uname,          -1,
    SYS_write,          -1,
    SYS_writev,         -1,
    -1
};

int RF_CPP[512] =
{
    SYS_access,         -1,
    SYS_brk,            -1,
    SYS_close,          -1,
    SYS_execve,         1,
    SYS_exit_group,     -1,
    SYS_fstat64,        -1,
    SYS_futex,          -1,
    SYS_gettimeofday,   -1,
    SYS_mmap2,          -1,
    SYS_mremap,         -1,
    SYS_mprotect,       -1,
    SYS_munmap,         -1,
    SYS_lseek,          -1,
    SYS_read,           -1,
    SYS_set_thread_area,-1,
    SYS_uname,          -1,
    SYS_write,          -1,
    SYS_writev,         -1,
    -1
};

//Pascal
int RF_PASCAL[512] = 
{
    SYS_close,          -1,
    SYS_execve,         1,
    SYS_exit_group,     -1,
    SYS_futex,          -1,
    SYS_gettimeofday,   -1,
    SYS_ioctl,          -1,
    SYS_mmap,           -1,
    SYS_mremap,         -1,
    SYS_munmap,         -1,
    SYS_lseek,          -1,
    SYS_read,           -1,
    SYS_readlink,       -1,
    SYS_rt_sigaction,   -1,
    SYS_ugetrlimit,     -1,
    SYS_uname,          -1,
    SYS_write,          -1,
    SYS_writev,         -1,
    -1
};

//Java (TODO暂未测试)
int RF_JAVA[512] = 
{
    SYS_access,         -1,
    SYS_brk,            -1,
    SYS_clone,          -1,
    SYS_close,          -1,
    SYS_execve,         -1,
    SYS_exit,           -1,
    SYS_exit_group,     -1,
    SYS_fcntl64,        -1,
    SYS_fstat64,        -1,
    SYS_futex,          -1,
    SYS_getdents64,     -1,
    SYS_getegid32,      -1,
    SYS_geteuid32,      -1,
    SYS_getgid32,       -1,
    SYS_getrlimit,      -1,
    SYS_gettimeofday,   -1,
    SYS_getuid32,       -1,
    SYS_mmap,           -1,
    SYS_mmap2,          -1,
    SYS_mremap,         -1,
    SYS_mprotect,       -1,
    SYS_munmap,         -1,
    SYS_lseek,          -1,
    SYS_open,           -1,
    SYS_read,           -1,
    SYS_readlink,       -1,
    SYS_rt_sigaction,   -1,
    SYS_rt_sigprocmask, -1,
    SYS_set_robust_list,-1,
    SYS_set_thread_area,-1,
    SYS_set_tid_address,-1,
    SYS_sigprocmask,    -1,
    SYS_stat64,         -1,
    SYS_ugetrlimit,     -1,
    SYS_uname,          -1,
    -1
};

#elif defined __x86_64__
int RF_C[512] =
{
    SYS_access,         -1,
    SYS_arch_prctl,     -1,
    SYS_brk,            -1,
    SYS_close,          -1,
    SYS_execve,          1,
    SYS_exit_group,     -1,
    SYS_fstat,          -1,
    SYS_futex,          -1,
    SYS_gettimeofday,   -1,
    SYS_mmap,           -1,
    SYS_mremap,         -1,
    SYS_mprotect,       -1,
    SYS_munmap,         -1,
    SYS_lseek,          -1,
    SYS_read,           -1,
    SYS_set_thread_area,-1,
    SYS_uname,          -1,
    SYS_write,          -1,
    SYS_writev,         -1,
    SYS_readlink,       -1,
    -1
};
/**
 * Under gcc x86_64-linux-gnu, 4.8.2 (Ubuntu 4.8.2-19ubuntu1),
 * following clearances are added:
 * + SYS_access,
 * + SYS_readlink
 */

int RF_CPP[512] = 
{
    SYS_access,         -1,
    SYS_arch_prctl,     -1,
    SYS_brk,            -1,
    SYS_close,          -1,
    SYS_execve,          1,
    SYS_exit_group,     -1,
    SYS_fstat,          -1,
    SYS_futex,          -1,
    SYS_gettimeofday,   -1,
    SYS_mmap,           -1,
    SYS_mremap,         -1,
    SYS_mprotect,       -1,
    SYS_munmap,         -1,
    SYS_lseek,          -1,
    SYS_read,           -1,
    SYS_set_thread_area,-1,
    SYS_uname,          -1,
    SYS_write,          -1,
    SYS_writev,         -1,
    SYS_readlink,       -1,
    -1
};
/**
 * Under g++ x86_64-linux-gnu, 4.8.2 (Ubuntu 4.8.2-19ubuntu1),
 * following clearances are added:
 * + SYS_readlink
 */

int RF_PASCAL[512] = 
{
    SYS_close,          -1,
    SYS_execve,         1,
    SYS_exit_group,     -1,
    SYS_futex,          -1,
    SYS_getrlimit,      -1,
    SYS_gettimeofday,   -1,
    SYS_ioctl,          -1,
    SYS_mmap,           -1,
    SYS_mremap,         -1,
    SYS_munmap,         -1,
    SYS_lseek,          -1,
    SYS_read,           -1,
    SYS_readlink,       -1,
    SYS_rt_sigaction,   -1,
    SYS_uname,          -1,
    SYS_write,          -1,
    SYS_writev,         -1,
    -1
};

int RF_JAVA[512] = 
{
    SYS_access,         -1,
    SYS_arch_prctl,     -1,
    SYS_brk,            -1,
    SYS_clone,          -1,
    SYS_close,          -1,
    SYS_execve,         -1,
    SYS_exit_group,     -1,
    SYS_fstat,          -1,
    SYS_futex,          -1,
    SYS_getegid,        -1,
    SYS_geteuid,        -1,
    SYS_getgid,         -1,
    SYS_getrlimit,      -1,
    SYS_gettimeofday,   -1,
    SYS_getuid,         -1,
    SYS_mmap,           -1,
    SYS_mremap,         -1,
    SYS_mprotect,       -1,
    SYS_munmap,         -1,
    SYS_lseek,          -1,
    SYS_open,           -1,
    SYS_read,           -1,
    SYS_readlink,       -1,
    SYS_rt_sigaction,   -1,
    SYS_rt_sigprocmask, -1,
    SYS_set_robust_list,-1,
    SYS_set_tid_address,-1,
    SYS_stat,           -1,
    SYS_uname,          -1,
    SYS_write,          -1,
    SYS_writev,         -1,
    -1
};

int RF_PYTHON2_PYTHON3_RUBY[512] =
{
    SYS_access,         -1,
    SYS_arch_prctl,     -1,
    SYS_brk,            -1,
    SYS_clone,          -1,
    SYS_close,          -1,
    SYS_dup,            -1,
    SYS_execve,          6,
    SYS_exit_group,     -1,
    SYS_fcntl,          -1,
    SYS_fstat,          -1,
    SYS_futex,          -1,
    SYS_getcwd,         -1,
    SYS_getdents,       -1,
    SYS_geteuid,        -1,
    SYS_getegid,        -1,
    SYS_getgid,         -1,
    SYS_getrlimit,      -1,
    SYS_getrusage,      -1,
    SYS_gettimeofday,   -1,
    SYS_getuid,         -1,
    SYS_ioctl,          -1,
    SYS_lstat,          -1,
    SYS_mmap,           -1,
    SYS_mremap,         -1,
    SYS_mprotect,       -1,
    SYS_munmap,         -1,
    SYS_lseek,          -1,
    SYS_open,           -1,
    SYS_openat,         -1,
    SYS_stat,           -1,
    SYS_pipe,           -1,
    SYS_read,           -1,
    SYS_rt_sigaction,   -1,
    SYS_rt_sigprocmask, -1,
    SYS_sched_getaffinity,-1,
    SYS_sched_setaffinity,-1,
    SYS_set_robust_list,-1,
    SYS_set_thread_area,-1,
    SYS_set_tid_address,-1,
    SYS_sigaltstack,    -1,
    SYS_uname,          -1,
    SYS_write,          -1,
    SYS_writev,         -1,
    SYS_readlink,       -1,
    -1
};

#endif

//根据 RF_* 数组来初始化RF_table
void init_RF_table(char* lang_name)
{
    if (strlen(lang_name) > 100) {
        exit(3);
    }

    char rf_conf_path[256];
    sprintf(rf_conf_path, "%s/%s_rf.conf",
            problem::langs_conf_dir.c_str(),
            lang_name);

    FILE* f = fopen(rf_conf_path, "r");
    if (!f) {
        exit(9);
    }

    memset(RF_table, 0, sizeof(RF_table));

    short syscall_id, count;
    while (fscanf(f, "%hd %hd", &syscall_id, &count) == 2) {
        RF_table[syscall_id] = count;
    }

    if (feof(f)) {
        // Succeeded.
        fclose(f);
    } else {
        fclose(f);
        exit(9);
    }
}

#endif
