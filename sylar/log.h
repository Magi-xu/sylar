#ifndef __SYLAR_LOG_H_
#define __SYLAR_LOG_H_

#include <string>
#include <list>
#include <vector>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

namespace sylar {

class LogLevel;
class LogEvent;
class Logger;
class LogFormatter;
class LogAppender;

//日志级别
class LogLevel
{
public:
    enum Level {
            UNKNOW = 0,
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };

    static const char* ToString(LogLevel::Level Level);
};

// 日志事件
class LogEvent
{
private:
    /* data */
    const char* m_file = nullptr;   //文件名
    int32_t m_line = 0;             //行号
    uint32_t m_elapse = 0;          //程序启动到现在的毫秒数
    uint32_t m_threadId = 0;        //线程号
    uint32_t m_fiberId = 0;         //协程号
    uint64_t m_time;                //时间戳
    std::string m_content;
public:
    typedef std::shared_ptr<LogEvent> ptr;

    LogEvent();

    const char* getFile() const { return m_file;}
    int32_t getline() const { return m_line;}
    uint32_t getElapse() const { return m_elapse;}
    uint32_t getThreadId() const { return m_threadId;}
    uint32_t getFiberId() const { return m_fiberId;}
    uint64_t getTime() const { return m_time;}
    const std::string& getContent() const { return m_content;}

    
};

//日志器
class Logger : public std::enable_shared_from_this<Logger>
{
private:
    /* data */
    std::string m_name;                         //日志名称
    LogLevel::Level m_level;                    //日志级别
    std::list<std::shared_ptr<LogAppender>> m_appenders;    //Appender集合
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger (const std::string& name);
    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(std::shared_ptr<LogAppender> appender);
    void delAppender(std::shared_ptr<LogAppender> appender);
    
    const std::string getName(){ return m_name;}
    LogLevel::Level getLevel() const { return m_level;}
    void setLevel(LogLevel::Level val) { m_level = val;}
};

//日志格式器
class LogFormatter
{
public:
    class FormatItem
    {
    public:
        typedef std::shared_ptr<FormatItem> ptr;

        virtual ~FormatItem() {}
        virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr evrnt) = 0;
    };

    void init();
private:
    /* data */
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;
public:
    typedef std::shared_ptr<LogFormatter> ptr;

    LogFormatter(const std::string& pattern);
    std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
};

//日志输出地
class LogAppender
{
protected:
    /* data */
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
public:
    typedef std::shared_ptr<LogAppender> ptr;

    virtual ~LogAppender() {}

    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;

    void setFormatter(LogFormatter::ptr val) { m_formatter = val;}
    LogFormatter::ptr getFormatter() const { return m_formatter;}
};

//输出到控制台
class StdoutLogAppender : public LogAppender
{
private:
    /* data */
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;

    void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;

};

//输出到文件
class FileLogAppender : public LogAppender
{
private:
    /* data */
    std::string m_filename;
    std::ofstream m_filestream;
public:
    typedef std::shared_ptr<FileLogAppender> ptr;

    FileLogAppender(const std::string filename);
    void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;
    bool reopen();
};



}

#endif