#pragma once
#include <string>
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
	~Logger();

	private:
		Logger() = default;
		bool m_Initialized = false;
		std::atomic<bool> m_Running;
		std::thread m_LoggerThread;
	};
	
}
