//
// Created by root on 23-12-7.
//
#include "../sylar/sylar.h"
#include <cassert>

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_assert() {
    SYLAR_LOG_INFO(g_logger) << sylar::BacktraceToString(10);
    SYLAR_ASSERT2(0 == 1, "abcdeg xx");
}

 int main() {
     test_assert();
     return 0;
}