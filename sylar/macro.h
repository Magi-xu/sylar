//
// Created by root on 23-12-7.
//

#ifndef __SYLAR_MACRO_H__
#define __SYLAR_MACRO_H__

#include <string>
#include <cassert>
#include "util.h"

#define SYLAR_ASSERT(x) \
    if (!(x)) {         \
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ASSERTION: " #x \
        << "\nbacktrace:\n"                                   \
        << sylar::BacktraceToString(100, 2, "    ");          \
        assert(x);      \
    }

#define SYLAR_ASSERT2(x, w) \
    if (!(x)) {         \
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ASSERTION: " #x \
        << "\n" << w                                          \
        << "\nbacktrace:\n"                                   \
        << sylar::BacktraceToString(100, 2, "    ");          \
        assert(x);      \
    }

#endif
