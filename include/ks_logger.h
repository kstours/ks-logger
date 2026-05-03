#pragma once
#include <string>

namespace ks {

	class Logger {
	public:

	static Logger& Get() {
		static Logger instance;
		return instance;
	}

	void init();

	private:
		Logger() = default;
		bool m_Initialized = false;
	};
	
}
