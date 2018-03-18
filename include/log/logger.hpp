#ifndef FORMA_LOG_LOGGER_HPP_
#define FORMA_LOG_LOGGER_HPP_

#include <array>
#include <chrono>
#include <string>
#include <string_view>

namespace forma {
  namespace logging {
    enum Logger { ROTATING_FILE, DAILY_FILE, CONSOLE };
    enum LogType {
      FATAL,
      ERROR,
      WARNING,
      TRACE,
      DEBUG,
      SUCCESS,
      INFO,
      DATA,
      VERSION,
      NONE
    };

    void Log(Logger logger, LogType type, std::string_view file,
             std::string_view scope, std::string_view fmt, va_list args);
    void Log(Logger logger, LogType type, std::string_view file,
             std::string_view scope, std::string_view fmt, ...);

    void Console(LogType type, std::string_view file, std::string_view scope,
                 std::string_view fmt, va_list args);
    void Console(LogType type, std::string_view file, std::string_view scope,
                 std::string_view fmt, ...);

    void ConsoleFatal(std::string_view file, std::string_view scope,
                      std::string_view fmt, ...);
    void ConsoleError(std::string_view file, std::string_view scope,
                      std::string_view fmt, ...);
    void ConsoleWarning(std::string_view file, std::string_view scope,
                        std::string_view fmt, ...);
    void ConsoleTrace(std::string_view file, std::string_view scope,
                      std::string_view fmt, ...);
    void ConsoleDebug(std::string_view file, std::string_view scope,
                      std::string_view fmt, ...);
    void ConsoleSuccess(std::string_view file, std::string_view scope,
                        std::string_view fmt, ...);
    void ConsoleInfo(std::string_view file, std::string_view scope,
                     std::string_view fmt, ...);
    void ConsoleData(std::string_view file, std::string_view scope,
                     std::string_view fmt, ...);
    void ConsoleVersion(std::string_view file, std::string_view scope,
                        std::string_view fmt, ...);

    void PrintConsoleLog(std::string_view msg, LogType type);

    std::string GetLogTypeString(LogType type, bool abbrev);
    std::array<std::string, 7> GetDateTimeString();
    void SetLogFmt(std::string fmt);

  }  // namespace logging
}  // namespace forma

#endif  // FORMA_LOG_LOGGER_HPP_
