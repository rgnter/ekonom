
#include "cfg/config_provider.hpp"
#include "EkonomApp.hpp"

#include <utility>
#include <thread>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <cxxopts.hpp>


int main(int argc, char **argv) {
    cxxopts::Options cliOptions("Ekonom", "Ekonom desc.");
    cliOptions.add_options()
            ("l,logFile", "Specifies log file location",
             cxxopts::value<std::string>()->default_value("Logs/log.log")
            )
            ("c,cfgFile", "Specifies config file location",
             cxxopts::value<std::string>()->default_value("Cfg/config.json")
            );

    const auto result = cliOptions.parse(argc, argv);

    const std::string logPath = result["logFile"].as<std::string>();
    const std::string cfgPath = result["cfgFile"].as<std::string>();

    const auto logConsoleSink =
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    logConsoleSink->set_level(spdlog::level::debug);
    const auto logFileSink =
            std::make_shared<spdlog::sinks::daily_file_sink_mt>(logPath, 0, 0);
    logFileSink->set_level(spdlog::level::debug);

    const auto logger =
            std::make_shared<spdlog::logger>(spdlog::logger("", {logConsoleSink, logFileSink}));
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Logging files saved to: {}", logPath.c_str());

    spdlog::set_default_logger(logger);

    ekonom::config_provider configProvider(cfgPath);

    std::thread thread([]() {
        spdlog::info("Begin lifetime of ekonom thread.");
        ekonom::EkonomApp app;
        app.Run();
        spdlog::info("End lifetime of ekonom thread.");
    });
    thread.join();
}