#pragma once
#include <thread>
#include <atomic>

namespace ks {

	class Logger {
	public:

	static Logger& Get() {
		static Logger instance;
		return instance;
	}

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
