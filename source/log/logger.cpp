#include "log/logger.hpp"

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <chrono>
#include <cstdarg>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

static std::string log_fmt = "[%Y-%m-%d %H:%M:%S.%e] [%f@%s] [%o] %i";
static unsigned default_logger = forma::logging::Logger::CONSOLE;
static std::string log_path = "", log_name = "log";
static bool console_color = true;
static std::ofstream daily_file, file_file;

void forma::logging::Log(unsigned logger, LogType type, std::string_view file,
                         std::string_view scope, std::string_view fmt,
                         va_list args) {
  std::string type_string = GetLogTypeString(type, false);
  std::array<std::string, 7> time_data = GetDateTimeString();
  char buffer[255];
  int len = vsprintf(buffer, fmt.data(), args);
  std::string msg(buffer, len);
  std::string result;
  for (std::size_t i = 0; i < log_fmt.size(); i++) {
    if (log_fmt.at(i) == '%') {
      i++;
      switch (log_fmt.at(i)) {
        case 'Y':
          result += time_data.at(0);
          break;
        case 'm':
          result += time_data.at(1);
          break;
        case 'd':
          result += time_data.at(2);
          break;
        case 'H':
          result += time_data.at(3);
          break;
        case 'M':
          result += time_data.at(4);
          break;
        case 'S':
          result += time_data.at(5);
          break;
        case 'e':
          result += time_data.at(6);
          break;
        case 'f':
          result += file;
          break;
        case 's':
          result += scope;
          break;
        case 'o':
          result += type_string;
          break;
        case 'i':
          result += msg;
          break;
        case '%':
          result += '%';
          break;
        default:
          result += '%';
          result += log_fmt.at(i);
          break;
      }
    } else {
      result += log_fmt.at(i);
    }
  }
  if ((logger & CONSOLE) == CONSOLE) {
    PrintConsoleLog(result, type);
  }
  if ((logger & DAILY_FILE) == DAILY_FILE) {
    PrintDailyLog(result, type);
  }
  if ((logger & LOG_FILE) == LOG_FILE) {
    PrintFileLog(result, type);
  }
}

void forma::logging::Log(unsigned logger, LogType type, std::string_view file,
                         std::string_view scope, std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(logger, type, file, scope, fmt, args);
  va_end(args);
}

void forma::logging::Console(LogType type, std::string_view file,
                             std::string_view scope, std::string_view fmt,
                             va_list args) {
  Log(CONSOLE, type, file, scope, fmt, args);
}
void forma::logging::Console(LogType type, std::string_view file,
                             std::string_view scope, std::string_view fmt,
                             ...) {
  va_list args;
  va_start(args, fmt);
  Log(DAILY_FILE, type, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::Daily(LogType type, std::string_view file,
                           std::string_view scope, std::string_view fmt,
                           va_list args) {
  Log(CONSOLE, type, file, scope, fmt, args);
}
void forma::logging::Daily(LogType type, std::string_view file,
                           std::string_view scope, std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(LOG_FILE, type, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::File(LogType type, std::string_view file,
                          std::string_view scope, std::string_view fmt,
                          va_list args) {
  Log(CONSOLE, type, file, scope, fmt, args);
}
void forma::logging::File(LogType type, std::string_view file,
                          std::string_view scope, std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(LOG_FILE, type, file, scope, fmt, args);
  va_end(args);
}

void forma::logging::Fatal(std::string_view file, std::string_view scope,
                           std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(default_logger, FATAL, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::Error(std::string_view file, std::string_view scope,
                           std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(default_logger, ERROR, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::Warning(std::string_view file, std::string_view scope,
                             std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(default_logger, WARNING, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::Trace(std::string_view file, std::string_view scope,
                           std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(default_logger, TRACE, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::Debug(std::string_view file, std::string_view scope,
                           std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(default_logger, DEBUG, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::Success(std::string_view file, std::string_view scope,
                             std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(default_logger, SUCCESS, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::Info(std::string_view file, std::string_view scope,
                          std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(default_logger, INFO, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::Data(std::string_view file, std::string_view scope,
                          std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(default_logger, DATA, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::Version(std::string_view file, std::string_view scope,
                             std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(default_logger, VERSION, file, scope, fmt, args);
  va_end(args);
}

void forma::logging::ConsoleFatal(std::string_view file, std::string_view scope,
                                  std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(CONSOLE, FATAL, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::ConsoleError(std::string_view file, std::string_view scope,
                                  std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(CONSOLE, ERROR, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::ConsoleWarning(std::string_view file,
                                    std::string_view scope,
                                    std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(CONSOLE, WARNING, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::ConsoleTrace(std::string_view file, std::string_view scope,
                                  std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(CONSOLE, TRACE, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::ConsoleDebug(std::string_view file, std::string_view scope,
                                  std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(CONSOLE, DEBUG, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::ConsoleSuccess(std::string_view file,
                                    std::string_view scope,
                                    std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(CONSOLE, SUCCESS, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::ConsoleInfo(std::string_view file, std::string_view scope,
                                 std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(CONSOLE, INFO, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::ConsoleData(std::string_view file, std::string_view scope,
                                 std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(CONSOLE, DATA, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::ConsoleVersion(std::string_view file,
                                    std::string_view scope,
                                    std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(CONSOLE, VERSION, file, scope, fmt, args);
  va_end(args);
}

void forma::logging::DailyFatal(std::string_view file, std::string_view scope,
                                std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(DAILY_FILE, FATAL, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::DailyError(std::string_view file, std::string_view scope,
                                std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(DAILY_FILE, ERROR, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::DailyWarning(std::string_view file, std::string_view scope,
                                  std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(DAILY_FILE, WARNING, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::DailyTrace(std::string_view file, std::string_view scope,
                                std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(DAILY_FILE, TRACE, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::DailyDebug(std::string_view file, std::string_view scope,
                                std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(DAILY_FILE, DEBUG, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::DailySuccess(std::string_view file, std::string_view scope,
                                  std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(DAILY_FILE, SUCCESS, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::DailyInfo(std::string_view file, std::string_view scope,
                               std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(DAILY_FILE, INFO, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::DailyData(std::string_view file, std::string_view scope,
                               std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(DAILY_FILE, DATA, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::DailyVersion(std::string_view file, std::string_view scope,
                                  std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(DAILY_FILE, VERSION, file, scope, fmt, args);
  va_end(args);
}

void forma::logging::FileFatal(std::string_view file, std::string_view scope,
                               std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(LOG_FILE, FATAL, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::FileError(std::string_view file, std::string_view scope,
                               std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(LOG_FILE, ERROR, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::FileWarning(std::string_view file, std::string_view scope,
                                 std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(LOG_FILE, WARNING, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::FileTrace(std::string_view file, std::string_view scope,
                               std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(LOG_FILE, TRACE, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::FileDebug(std::string_view file, std::string_view scope,
                               std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(LOG_FILE, DEBUG, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::FileSuccess(std::string_view file, std::string_view scope,
                                 std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(LOG_FILE, SUCCESS, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::FileInfo(std::string_view file, std::string_view scope,
                              std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(LOG_FILE, INFO, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::FileData(std::string_view file, std::string_view scope,
                              std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(LOG_FILE, DATA, file, scope, fmt, args);
  va_end(args);
}
void forma::logging::FileVersion(std::string_view file, std::string_view scope,
                                 std::string_view fmt, ...) {
  va_list args;
  va_start(args, fmt);
  Log(LOG_FILE, VERSION, file, scope, fmt, args);
  va_end(args);
}

void forma::logging::PrintConsoleLog(std::string_view msg, LogType type) {
  if (console_color == true) {
    if (type == FATAL) {
      std::cout << "\033[1;31m" << msg << "\033[0m\n";
    } else if (type == ERROR) {
      std::cout << "\033[31m" << msg << "\033[0m\n";
    } else if (type == WARNING) {
      std::cout << "\033[33m" << msg << "\033[0m\n";
    } else if (type == TRACE) {
      std::cout << "\033[34m" << msg << "\033[0m\n";
    } else if (type == DEBUG) {
      std::cout << "\033[94m" << msg << "\033[0m\n";
    } else if (type == SUCCESS) {
      std::cout << "\033[32m" << msg << "\033[0m\n";
    } else if (type == INFO) {
      std::cout << "\033[97m" << msg << "\033[0m\n";
    } else if (type == DATA) {
      std::cout << "\033[0m" << msg << "\033[0m\n";
    } else if (type == VERSION) {
      std::cout << "\033[33m" << msg << "\033[0m\n";
    } else if (type == NONE) {
      std::cout << "\033[0m" << msg << "\033[0m\n";
    }
  } else {
    std::cout << msg << "\n";
  }
}
void forma::logging::PrintDailyLog(std::string_view msg, LogType type) {
  if (daily_file.is_open() == false) {
    std::array<std::string, 7> date_time = GetDateTimeString();
    std::string file_path = log_path + date_time.at(0) + "-" + date_time.at(1) +
                            "-" + date_time.at(2) + ".log";
    struct stat st = {0};

    if (stat(log_path.c_str(), &st) == -1) {
      mkdir(log_path.c_str(), 0700);
    }
    daily_file.open(file_path);
  }
  daily_file << msg << std::endl;
}
void forma::logging::PrintFileLog(std::string_view msg, LogType type) {
  if (file_file.is_open() == false) {
    struct stat st = {0};

    if (stat(log_path.c_str(), &st) == -1) {
      mkdir(log_path.c_str(), 0700);
    }
    file_file.open(log_path + log_name);
  }
  file_file << msg << std::endl;
}

std::string forma::logging::GetLogTypeString(LogType type, bool abbrev) {
  std::string type_string;
  switch (type) {
    case FATAL:
      type_string = "FATAL";
      break;
    case ERROR:
      type_string = "ERROR";
      break;
    case WARNING:
      type_string = "WARNING";
      break;
    case TRACE:
      type_string = "TRACE";
      break;
    case DEBUG:
      type_string = "DEBUG";
      break;
    case SUCCESS:
      type_string = "SUCCESS";
      break;
    case INFO:
      type_string = "INFO";
      break;
    case DATA:
      type_string = "DATA";
      break;
    case VERSION:
      type_string = "VERSION";
      break;
    case NONE:
      type_string = "NONE";
      break;
  }
  if (abbrev) {
    type_string = type_string.front();
  }
  return type_string;
}

std::array<std::string, 7> forma::logging::GetDateTimeString() {
  std::chrono::system_clock::time_point current =
      std::chrono::system_clock::now();
  std::time_t date_time_t = std::chrono::system_clock::to_time_t(current);
  std::tm date_time = *std::localtime(&date_time_t);
  std::chrono::duration diff =
      current - std::chrono::time_point_cast<std::chrono::seconds>(current);
  std::chrono::duration milli_seconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(diff);
  return std::array<std::string, 7>{
      {std::to_string(date_time.tm_year + 1900),
       std::to_string(date_time.tm_mon), std::to_string(date_time.tm_mday),
       std::to_string(date_time.tm_hour), std::to_string(date_time.tm_min),
       std::to_string(date_time.tm_sec),
       std::to_string(milli_seconds.count())}};
}

void forma::logging::SetDefaultLogger(unsigned logger) {
  default_logger = logger;
}
void forma::logging::SetLogFmt(std::string fmt) { log_fmt = fmt; }
void forma::logging::SetLogPath(std::string path) { log_path = path; }
void forma::logging::SetLogName(std::string name) { log_name = name; }
