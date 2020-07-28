#pragma once
#define SPDLOG_TRACE_ON
#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>



namespace far {
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
	class Logger {

	private:
		static std::shared_ptr<spdlog::logger> _coreLogger;
	public:
		Logger(const Logger&) = delete;
		static void init();
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return _coreLogger; };
	};



}


//#ifdef FAR_DEBUG_BUILD

#define FAR_TRACE(...) ::FAR::Logger::getCoreLogger()->trace(__VA_ARGS__)
#define FAR_DEBUG(...) ::FAR::Logger::getCoreLogger()->debug(__VA_ARGS__)
#define FAR_LOG(...) ::FAR::Logger::getCoreLogger()->info(__VA_ARGS__)
#define FAR_WARN(...) ::FAR::Logger::getCoreLogger()->warn(__VA_ARGS__)
#define FAR_ERROR(...) ::FAR::Logger::getCoreLogger()->error(__VA_ARGS__)
//#define FAR_FATAL(...) ::FAR::Logger::getCoreLogger()->critical(__VA_ARGS__)


#define FAR_FATAL(...) { \
	::FAR::Logger::getCoreLogger()->critical(__VA_ARGS__); \
	DebugBreak();\
}\

//#define FAR_FATAL(...); { \
//	::FAR::Logger::getCoreLogger()->critical(__VA_ARGS__); \
//	DebugBreak();\
//}\


// #else 
// #define FAR_TRACE(...)
// #define FAR_DEBUG(...)
// #define FAR_LOG(...) 
// #define FAR_WARN(...)
// #define FAR_ERROR(...) 
// #define FAR_FATAL(...) 

//#endif

//#define FAR_TRACE(...) ::FAR::Logger::getClientLogger()->trace(__VA_ARGS__)
//#define FAR_DEBUG(...) ::FAR::Logger::getClientLogger()->debug(__VA_ARGS__)
//#define FAR_LOG(...) ::FAR::Logger::getClientLogger()->info(__VA_ARGS__)
//#define FAR_WARN(...) ::FAR::Logger::getClientLogger()->warn(__VA_ARGS__)
//#define FAR_ERROR(...) ::FAR::Logger::getClientLogger()->error(__VA_ARGS__)
//#define FAR_FATAL(...) ::FAR::Logger::getClientLogger()->critical(__VA_ARGS__)