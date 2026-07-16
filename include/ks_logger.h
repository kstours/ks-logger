#pragma once
#include <thread>
#include <atomic>
#include <string>

namespace ks {

	class Logger {
	public:

	static Logger& Get() {
		static Logger instance;
		return instance;
	}


	bool registerChannel(const std::string& name);
	void log( const std::string& message, const std::string& name = "Main Channel");

	void init();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(Logger&&) = delete;
	

	private:
		~Logger();
		Logger() = default;
		bool m_Initialized = false;
		std::atomic<bool> m_Running;
		std::thread m_LoggerThread;
	};
	
}
