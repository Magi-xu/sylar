#include <iostream>
#include "../sylar/log.h"
#include "../sylar/util.h"
using namespace sylar;
using namespace std;

int main(int argc, char** argv) {
    Logger::ptr logger(new Logger);
    logger->addAppender(LogAppender::ptr(new StdoutLogAppender));

    FileLogAppender::ptr file_appender(new FileLogAppender("./log.txt"));
    logger->addAppender(file_appender);

    LogFormatter::ptr fmt(new LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);
    file_appender->setLevel(LogLevel::ERROR);

    // LogEvent::ptr event(new LogEvent(logger, level, __FILE__, __LINE__, 0, sylar::GetThreadId(), sylar::GetFiberId(), time(0)));
    // event->getSS() << "hello";

    // logger->log(level, event);
//     cout << "hello" << endl;
    SYLAR_LOG_INFO(logger) << "TEST MACRO";
    SYLAR_LOG_ERROR(logger) << "TEST MACRO ERROR";

    SYLAR_LOG_FMT_DEBUG(logger, "TEST MACRO FMT DEBUG %s", "aa");

    auto l = LoggerMgr::GetInstance()->getLogger("xx");
    SYLAR_LOG_INFO(l) << "xxx";
    return 0;
}