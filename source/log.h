//
// Created by faker on 2022/1/8.
//

#ifndef CPP_LOG_H
#define CPP_LOG_H

#include "memory"
#include "stdint.h"
#include "string"
#include "list"

namespace cpp2log
{
    class LogEvent
    {
    public:
        typedef std::shared_ptr<LogEvent> ptr;

        LogEvent();

    private:
        const char *m_file = nullptr;
        int32_t m_line = 0;
        uint32_t m_elapse = 0;
        uint32_t m_coroutineId = 0;
        uint32_t m_time = 0;
        ::std::string m_content;
    };
    //日志格式器
    class LogFormatter
    {
    public:
        typedef ::std::shared_ptr<LogFormatter> ptr;
        std::string format(LogEvent::ptr event);
    };
    //日志级别
    class LogLevel
    {
    public:
        enum Level
        {
            DEBUG = 0,
            INFO = 1,
            WARN = 2,
            ERROR = 3,
            FATAL = 4
        };
    };
    //日志输出器
    class LogAppender
    {
    public:
        typedef std::shared_ptr<LogAppender> ptr;

        virtual ~LogAppender(){};

        virtual void log(LogLevel::Level, LogEvent::ptr event) = 0;

    private:
        LogLevel::Level m_level;
    };
    //日志器
    class Logger
    {
    public:
        typedef std::shared_ptr<Logger> ptr;
        Logger(const std::string &name = "root");
        void log(LogLevel::Level level, LogEvent::ptr event);

        void debug(LogEvent::ptr event);
        void info(LogEvent::ptr event);
        void warn(LogEvent::ptr event);
        void error(LogEvent::ptr event);
        void fatal(LogEvent::ptr event);
        void addAppender(LogAppender::ptr appender);
        void delAppender(LogAppender::ptr appender);
        LogLevel::Level getLevel() const { return m_level; };
        void setLevel(LogLevel::Level level) { m_level = level; };

    private:
        LogLevel::Level m_level;                 //日志级别
        std::string m_name;                      //日志级别
        std::list<LogAppender::ptr> m_appenders; // Appender集合
    };
}

#endif // RUBY_LOG_H
