//
// Created by faker on 2022/1/8.
//

#ifndef RUBY_LOG_H
#define RUBY_LOG_H

#include "memory"
#include "stdint.h"
#include "string"

namespace ruby {
    class LogEvent {
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
    class LogFormatter{
    public:
        typedef ::std::shared_ptr<LogFormatter> ptr;
        std::string format(LogEvent::ptr event);
    };
    //日志级别
    class LogLevel {
    public:
        enum Level {
            DEBUG = 0,
            INFO = 1,
            WARN = 2,
            ERROR = 3,
            FATAL = 4
        };
    };
    //日志输出器
    class LogAppender {
    public:
        typedef std::shared_ptr<LogAppender> ptr;

        virtual ~LogAppender() {};

        void log(LogLevel::Level, LogEvent::ptr event);

    private:
        LogLevel::Level = _level;
    };
    //日志器
    class Logger{
    public:
        typedef std::shared_ptr<Log> ptr;
        Logger(const std::string& name="root");
        void log(LogLevel::Level,LogEvent::ptr event);

    private:
        LogLevel::Level =_level;
        std::string m_name;
        LogAppender::ptr;
    };
}

#endif //RUBY_LOG_H
