#ifndef FORMA_LOG_LOGGER_HPP_
#define FORMA_LOG_LOGGER_HPP_

#include <array>
#include <chrono>
#include <string>
#include <string_view>

namespace forma {
  namespace logging {
    enum Logger { LOG_FILE = 1u << 0, DAILY_FILE = 1u << 1, CONSOLE = 1u << 2 };
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

    void Log(unsigned logger, LogType type, std::string_view file,
             std::string_view scope, std::string_view fmt, va_list args);
    void Log(unsigned logger, LogType type, std::string_view file,
             std::string_view scope, std::string_view fmt, ...);

    void Console(LogType type, std::string_view file, std::string_view scope,
                 std::string_view fmt, va_list args);
    void Console(LogType type, std::string_view file, std::string_view scope,
                 std::string_view fmt, ...);

    void Daily(LogType type, std::string_view file, std::string_view scope,
               std::string_view fmt, va_list args);
    void Daily(LogType type, std::string_view file, std::string_view scope,
               std::string_view fmt, ...);

    void File(LogType type, std::string_view file, std::string_view scope,
              std::string_view fmt, va_list args);
    void File(LogType type, std::string_view file, std::string_view scope,
              std::string_view fmt, ...);

    void Fatal(std::string_view file, std::string_view scope,
               std::string_view fmt, ...);
    void Error(std::string_view file, std::string_view scope,
               std::string_view fmt, ...);
    void Warning(std::string_view file, std::string_view scope,
                 std::string_view fmt, ...);
    void Trace(std::string_view file, std::string_view scope,
               std::string_view fmt, ...);
    void Debug(std::string_view file, std::string_view scope,
               std::string_view fmt, ...);
    void Success(std::string_view file, std::string_view scope,
                 std::string_view fmt, ...);
    void Info(std::string_view file, std::string_view scope,
              std::string_view fmt, ...);
    void Data(std::string_view file, std::string_view scope,
              std::string_view fmt, ...);
    void Version(std::string_view file, std::string_view scope,
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

    void DailyFatal(std::string_view file, std::string_view scope,
                    std::string_view fmt, ...);
    void DailyError(std::string_view file, std::string_view scope,
                    std::string_view fmt, ...);
    void DailyWarning(std::string_view file, std::string_view scope,
                      std::string_view fmt, ...);
    void DailyTrace(std::string_view file, std::string_view scope,
                    std::string_view fmt, ...);
    void DailyDebug(std::string_view file, std::string_view scope,
                    std::string_view fmt, ...);
    void DailySuccess(std::string_view file, std::string_view scope,
                      std::string_view fmt, ...);
    void DailyInfo(std::string_view file, std::string_view scope,
                   std::string_view fmt, ...);
    void DailyData(std::string_view file, std::string_view scope,
                   std::string_view fmt, ...);
    void DailyVersion(std::string_view file, std::string_view scope,
                      std::string_view fmt, ...);

    void FileFatal(std::string_view file, std::string_view scope,
                   std::string_view fmt, ...);
    void FileError(std::string_view file, std::string_view scope,
                   std::string_view fmt, ...);
    void FileWarning(std::string_view file, std::string_view scope,
                     std::string_view fmt, ...);
    void FileTrace(std::string_view file, std::string_view scope,
                   std::string_view fmt, ...);
    void FileDebug(std::string_view file, std::string_view scope,
                   std::string_view fmt, ...);
    void FileSuccess(std::string_view file, std::string_view scope,
                     std::string_view fmt, ...);
    void FileInfo(std::string_view file, std::string_view scope,
                  std::string_view fmt, ...);
    void FileData(std::string_view file, std::string_view scope,
                  std::string_view fmt, ...);
    void FileVersion(std::string_view file, std::string_view scope,
                     std::string_view fmt, ...);

    void PrintConsoleLog(std::string_view msg, LogType type);
    void PrintDailyLog(std::string_view msg, LogType type);
    void PrintFileLog(std::string_view msg, LogType type);

    std::string GetLogTypeString(LogType type, bool abbrev);
    std::array<std::string, 7> GetDateTimeString();
    void SetDefaultLogger(unsigned logger);
    void SetLogFmt(std::string fmt);
    void SetLogPath(std::string path);
    void SetLogName(std::string name);

  }  // namespace logging
}  // namespace forma

#endif  // FORMA_LOG_LOGGER_HPP_
