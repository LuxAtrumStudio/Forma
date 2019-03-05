#ifndef FORMA_LOGGER_HPP_
#define FORMA_LOGGER_HPP_

#include <array>
#include <cstdarg>
#include <ctime>
#include <string>

namespace forma {
  namespace log {
#define Default() Logger::Get()->GetLogger()

    enum LogType {
      FATAL = (1u << 0),
      ERROR = (1u << 1),
      WARNING = (1u << 2),
      SUCCESS = (1u << 3),
      DEBUG = (1u << 4),
      TRACE = (1u << 5),
      INFO = (1u << 6),
      VERSION = (1u << 7)
    };

    class LoggerBase {
     public:
      LoggerBase() {}
      virtual ~LoggerBase() {}
      void _log(LogType type, std::string_view message, std::string_view file,
                std::string_view func, unsigned long line, va_list args) {
        if ((activation_mask_ & type) != type) return;
        char fmt[255];
        std::time_t raw_time;
        std::time(&raw_time);
        std::tm* current_tm = std::localtime(&raw_time);
        vsnprintf(fmt, 255, message.data(), args);
        std::string body_str(fmt);
        if (body_str.size() < padding_[3])
          body_str = std::string(padding_[3] - body_str.size(), ' ') + body_str;
        std::string file_str(file);
        if (file_str.size() < padding_[0])
          file_str = std::string(padding_[0] - file_str.size(), ' ') + file_str;
        std::string func_str(func);
        if (func_str.size() < padding_[1])
          func_str = std::string(padding_[1] - func_str.size(), ' ') + func_str;
        std::string type_str = type_string(type);
        std::string fmt_str = log_fmt_[get_index(type)];
        if (line_pad_zero_)
          snprintf(fmt, 255, "%0*lu", padding_[2], line);
        else
          snprintf(fmt, 255, "%*lu", padding_[2], line);
        std::string line_str(fmt);
        std::strftime(fmt, 255, "%Y-%m-%d", current_tm);
        std::string date_str(fmt);
        std::strftime(fmt, 255, "%H:%M:%S", current_tm);
        std::string time_str(fmt);
        std::strftime(fmt, 255, "%Y-%m-%d %H:%M:%S", current_tm);
        std::string date_time_str(fmt);
        replace_substr(fmt_str, "__TYPE__", type_str);
        replace_substr(fmt_str, "__FILE__", file_str);
        replace_substr(fmt_str, "__FUNC__", func_str);
        replace_substr(fmt_str, "__LINE__", line_str);
        replace_substr(fmt_str, "__BODY__", body_str);
        replace_substr(fmt_str, "__DATE__", date_str);
        replace_substr(fmt_str, "__TIME__", time_str);
        replace_substr(fmt_str, "__DATE_TIME__", date_time_str);
        handle_log(type, fmt_str);
      }
      void _log(LogType type, std::string_view message, std::string_view file,
                std::string_view func, unsigned long line, ...) {
        if ((activation_mask_ & type) != type) return;
        va_list args;
        va_start(args, line);
        char fmt[255];
        std::time_t raw_time;
        std::time(&raw_time);
        std::tm* current_tm = std::localtime(&raw_time);
        vsnprintf(fmt, 255, message.data(), args);
        std::string body_str(fmt);
        if (body_str.size() < padding_[3])
          body_str = std::string(padding_[3] - body_str.size(), ' ') + body_str;
        std::string file_str(file);
        if (file_str.size() < padding_[0])
          file_str = std::string(padding_[0] - file_str.size(), ' ') + file_str;
        std::string func_str(func);
        if (func_str.size() < padding_[1])
          func_str = std::string(padding_[1] - func_str.size(), ' ') + func_str;
        std::string type_str = type_string(type);
        std::string fmt_str = log_fmt_[get_index(type)];
        if (line_pad_zero_)
          snprintf(fmt, 255, "%0*lu", padding_[2], line);
        else
          snprintf(fmt, 255, "%*lu", padding_[2], line);
        std::string line_str(fmt);
        std::strftime(fmt, 255, "%Y-%m-%d", current_tm);
        std::string date_str(fmt);
        std::strftime(fmt, 255, "%H:%M:%S", current_tm);
        std::string time_str(fmt);
        std::strftime(fmt, 255, "%Y-%m-%d %H:%M:%S", current_tm);
        std::string date_time_str(fmt);
        replace_substr(fmt_str, "__TYPE__", type_str);
        replace_substr(fmt_str, "__FILE__", file_str);
        replace_substr(fmt_str, "__FUNC__", func_str);
        replace_substr(fmt_str, "__LINE__", line_str);
        replace_substr(fmt_str, "__BODY__", body_str);
        replace_substr(fmt_str, "__DATE__", date_str);
        replace_substr(fmt_str, "__TIME__", time_str);
        replace_substr(fmt_str, "__DATE_TIME__", date_time_str);
        handle_log(type, fmt_str);
        va_end(args);
      }

      inline void format(LogType type, std::string fmt) {
        log_fmt_[get_index(type)] = fmt;
      }
      inline void format_all(std::string fmt) {
        log_fmt_ = {{fmt, fmt, fmt, fmt, fmt, fmt, fmt, fmt}};
      }
      inline void format_fatal(std::string fmt) { log_fmt_[0] = fmt; }
      inline void format_error(std::string fmt) { log_fmt_[1] = fmt; }
      inline void format_warning(std::string fmt) { log_fmt_[2] = fmt; }
      inline void format_success(std::string fmt) { log_fmt_[3] = fmt; }
      inline void format_debug(std::string fmt) { log_fmt_[4] = fmt; }
      inline void format_trace(std::string fmt) { log_fmt_[5] = fmt; }
      inline void format_info(std::string fmt) { log_fmt_[6] = fmt; }
      inline void format_version(std::string fmt) { log_fmt_[7] = fmt; }

      inline void set_fatal(bool val) {
        val ? activation_mask_ |= FATAL : activation_mask_ &= ~FATAL;
      }
      inline void set_error(bool val) {
        val ? activation_mask_ |= ERROR : activation_mask_ &= ~ERROR;
      }
      inline void set_warning(bool val) {
        val ? activation_mask_ |= WARNING : activation_mask_ &= ~WARNING;
      }
      inline void set_success(bool val) {
        val ? activation_mask_ |= SUCCESS : activation_mask_ &= ~SUCCESS;
      }
      inline void set_debug(bool val) {
        val ? activation_mask_ |= DEBUG : activation_mask_ &= ~DEBUG;
      }
      inline void set_trace(bool val) {
        val ? activation_mask_ |= TRACE : activation_mask_ &= ~TRACE;
      }
      inline void set_info(bool val) {
        val ? activation_mask_ |= INFO : activation_mask_ &= ~INFO;
      }
      inline void set_version(bool val) {
        val ? activation_mask_ |= VERSION : activation_mask_ &= ~VERSION;
      }
      inline void set_activation(unsigned mask) { activation_mask_ = mask; }

      inline void set_line_zero_pad(bool val) { line_pad_zero_ = val; }
      inline void set_file_pad(unsigned val) { padding_[0] = val; }
      inline void set_func_pad(unsigned val) { padding_[1] = val; }
      inline void set_line_pad(unsigned val) { padding_[2] = val; }
      inline void set_body_pad(unsigned val) { padding_[3] = val; }

     protected:
      virtual void handle_log(const LogType&, const std::string&) {}
      unsigned activation_mask_ =
          FATAL | ERROR | WARNING | SUCCESS | DEBUG | TRACE | INFO | VERSION;
      bool line_pad_zero_ = false;
      std::array<unsigned, 4> padding_ = {{0, 0, 3, 0}};
      std::array<std::string, 8> log_fmt_ = {
          {"[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) __BODY__",
           "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) __BODY__",
           "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) __BODY__",
           "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) __BODY__",
           "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) __BODY__",
           "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) __BODY__",
           "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) __BODY__",
           "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) __BODY__"}};

     private:
      inline unsigned get_index(const LogType& type) const {
        switch (type) {
          case FATAL:
            return 0;
          case ERROR:
            return 1;
          case WARNING:
            return 2;
          case SUCCESS:
            return 3;
          case DEBUG:
            return 4;
          case TRACE:
            return 5;
          case INFO:
            return 6;
          case VERSION:
            return 7;
          default:
            return 0;
        };
      }
      std::string& replace_substr(std::string& src, std::string pat,
                                  std::string_view rep) {
        while (true) {
          std::size_t index = 0;
          index = src.find(pat);
          if (index == std::string::npos) break;
          src.replace(index, pat.size(), rep);
        }
        return src;
      }

      std::string type_string(LogType type) {
        switch (type) {
          case FATAL:
            return "FATAL  ";
          case ERROR:
            return "ERROR  ";
          case WARNING:
            return "WARNING";
          case SUCCESS:
            return "SUCCESS";
          case DEBUG:
            return "DEBUG  ";
          case TRACE:
            return "TRACE  ";
          case INFO:
            return "INFO   ";
          case VERSION:
            return "VESION ";
        };
      }
    };

    class ConsoleLogger : public LoggerBase {
     public:
      ConsoleLogger() : LoggerBase() { set_color(true); }
      virtual ~ConsoleLogger() {}

      inline static ConsoleLogger* get() {
        static ConsoleLogger instance;
        return &instance;
      }

      void set_color(bool val) {
        if (val) {
          this->log_fmt_ = {
              {"\033[1;31m[__TYPE__] <__DATE_TIME__> "
               "(__FILE__:__FUNC__:__LINE__) __BODY__\033[0m",
               "\033[1;31m[__TYPE__] <__DATE_TIME__> "
               "(__FILE__:__FUNC__:__LINE__) "
               "__BODY__\033[0m",
               "\033[1;33m[__TYPE__] <__DATE_TIME__> "
               "(__FILE__:__FUNC__:__LINE__) "
               "__BODY__\033[0m",
               "\033[1;32m[__TYPE__] <__DATE_TIME__> "
               "(__FILE__:__FUNC__:__LINE__) "
               "__BODY__\033[0m",
               "\033[1;34m[__TYPE__] <__DATE_TIME__> "
               "(__FILE__:__FUNC__:__LINE__) "
               "__BODY__\033[0m",
               "\033[1;35m[__TYPE__] <__DATE_TIME__> "
               "(__FILE__:__FUNC__:__LINE__) "
               "__BODY__\033[0m",
               "\033[1;37m[__TYPE__] <__DATE_TIME__> "
               "(__FILE__:__FUNC__:__LINE__) "
               "__BODY__\033[0m",
               "\033[1;36m[__TYPE__] <__DATE_TIME__> "
               "(__FILE__:__FUNC__:__LINE__) __BODY__\033[0m"}};
        } else {
          this->log_fmt_ = {
              {"[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) "
               "__BODY__",
               "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) "
               "__BODY__",
               "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) "
               "__BODY__",
               "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) "
               "__BODY__",
               "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) "
               "__BODY__",
               "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) "
               "__BODY__",
               "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) "
               "__BODY__",
               "[__TYPE__] <__DATE_TIME__> (__FILE__:__FUNC__:__LINE__) "
               "__BODY__"}};
        }
      }

     protected:
      virtual void handle_log(const LogType& type, const std::string& log_msg) {
        printf("%s\n", log_msg.c_str());
      }
    };

    class Logger {
     public:
      enum LoggerType { CONSOLE = (1u << 0), OUT_FILE = (1u << 1) };
      Logger() {}
      virtual ~Logger() {}

      inline void _log(LogType type, std::string_view message,
                       std::string_view file, std::string_view func,
                       unsigned long line, ...) {
        va_list args;
        va_start(args, line);
        if ((logger_ & CONSOLE) == CONSOLE)
          ConsoleLogger::get()->_log(type, message, file, func, line, args);
        va_end(args);
      }

      inline static Logger* get() {
        static Logger instance;
        return &instance;
      }
      inline LoggerBase* get_logger(LoggerType logger) {
        switch (logger) {
          case CONSOLE:
            return ConsoleLogger::get();
          case OUT_FILE:
            return NULL;
        }
        return NULL;
      }

      inline void set_console(bool val) {
        val ? logger_ |= CONSOLE : logger_ &= ~CONSOLE;
      }
      inline void set_out_file(bool val) {
        val ? logger_ |= OUT_FILE : logger_ &= ~OUT_FILE;
      }

     protected:
      unsigned logger_ = CONSOLE | OUT_FILE;
    };

  }  // namespace log
}  // namespace forma

#endif  // FORMA_LOGGER_HPP_
