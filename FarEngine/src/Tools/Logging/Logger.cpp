#include "Logger.h"

namespace far {
	std::shared_ptr<spdlog::logger> Logger::_coreLogger(spdlog::stdout_color_mt("Far"));
	void Logger::init() {
		_coreLogger->set_pattern("%^[%T]%@ %n: %v%$");
		spdlog::set_pattern("%^[%T]%@ %n: %v%$");
		auto colorSink = std::make_shared < spdlog::sinks::stdout_color_sink_mt>();
		_coreLogger->set_level(spdlog::level::trace);
		_coreLogger->set_level(spdlog::level::trace);
	}




}