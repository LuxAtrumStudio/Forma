#ifndef FORMA_LOG_HPP_
#define FORMA_LOG_HPP_

#ifdef DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include <string_view>

#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#define LTRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define LDEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define LINFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LWARN(...) SPDLOG_WARN(__VA_ARGS__)
#define LERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define LCRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)

namespace forma {
  /**
   * @brief Log handler
   */
  namespace logger {
    /**
     * @brief Initalizes SPDLOG loggers
     *
     * Initalizes the SPDLOG loggers, to output both to the terminal, and a file "forma.log".
     *
     * @param verbosity Enables the console logger (primarily for debuging)
     *
     * @return ``true`` if the logger has been successfully initalized, ``false`` otherwise.
     */
    bool initalize_logger(const bool& console_logger);
    /**
     * @brief Determins if the logger is already initalized
     *
     * @return ``true`` if the logger has been initalized, ``false`` otherwise.
     */
    bool is_initalized();
    /**
     * @brief Logs a trace message
     *
     * @tparam _ARGS Type of additional arguments
     * @param fmt Log message and format string
     * @param args Optional additonal arguments
     */
    template <typename... _ARGS>
    inline void trace(const std::string_view& fmt, const _ARGS&... args) {
      spdlog::trace(fmt, args...);
    }
    /**
     * @brief Logs a debug message
     *
     * @tparam _ARGS Type of additional arguments
     * @param fmt Log message and format string
     * @param args Optional additonal arguments
     */
    template <typename... _ARGS>
    inline void debug(const std::string_view& fmt, const _ARGS&... args) {
      spdlog::debug(fmt, args...);
    }
    /**
     * @brief Logs a info message
     *
     * @tparam _ARGS Type of additional arguments
     * @param fmt Log message and format string
     * @param args Optional additonal arguments
     */
    template <typename... _ARGS>
    inline void info(const std::string_view& fmt, const _ARGS&... args) {
      spdlog::info(fmt, args...);
    }
    /**
     * @brief Logs a warning message
     *
     * @tparam _ARGS Type of additional arguments
     * @param fmt Log message and format string
     * @param args Optional additonal arguments
     */
    template <typename... _ARGS>
    inline void warn(const std::string_view& fmt, const _ARGS&... args) {
      spdlog::warn(fmt, args...);
    }
    /**
     * @brief Logs a error message
     *
     * @tparam _ARGS Type of additional arguments
     * @param fmt Log message and format string
     * @param args Optional additonal arguments
     */
    template <typename... _ARGS>
    inline void error(const std::string_view& fmt, const _ARGS&... args) {
      spdlog::error(fmt, args...);
    }
    /**
     * @brief Logs a critical message
     *
     * @tparam _ARGS Type of additional arguments
     * @param fmt Log message and format string
     * @param args Optional additonal arguments
     */
    template <typename... _ARGS>
    inline void critical(const std::string_view& fmt, const _ARGS&... args) {
      spdlog::critical(fmt, args...);
    }
  }  // namespace logger
}  // namespace forma

#endif  // FORMA_LOG_HPP_
