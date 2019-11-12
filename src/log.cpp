#include "forma/log.hpp"

#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <cstdio>
#include <memory>
#include <string_view>

bool forma::logger::initalize_logger(const bool& console_logger) {
  try {
    auto file_sink =
        std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/forma", 0, 0);
    file_sink->set_level(spdlog::level::trace);
    if (console_logger) {
      auto console_sink =
          std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
      console_sink->set_level(spdlog::level::trace);
      spdlog::set_default_logger(std::make_shared<spdlog::logger>(
          "", spdlog::sinks_init_list({console_sink, file_sink})));
    } else {
      spdlog::set_default_logger(std::make_shared<spdlog::logger>(
          "", spdlog::sinks_init_list({file_sink})));
    }
    spdlog::set_level(spdlog::level::trace);
    return true;
  } catch (const spdlog::spdlog_ex& ex) {
    fprintf(stderr, "Failed to initalize logging %s\n", ex.what());
    return false;
  }
}
