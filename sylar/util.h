#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__


#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

namespace sylar
{
    pid_t GetThreadId();
    u_int32_t GetFiberId();
}
#endif