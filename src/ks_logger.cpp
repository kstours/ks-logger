#include <ks_logger.h>
#include "imgui.h"
#include "window_frame/window_frame.h"
#include "ks_logger_ui/ks_logger_ui.h"
namespace {


    void loggerMain() {
        
    }


    void runLoggerWindow(int width, int height, std::string title) {
   
        WindowFrame& windowframe = WindowFrame::get();
        LoggerUI& loggerui = LoggerUI::get();

        if (!windowframe.init(width, height, title)) return;

        bool show_logger = true;
        


        while (!windowframe.shouldClose()) {
            windowframe.startFrame();

            if (show_logger) {
                    loggerui.renderLoggerUI(width,  height,  show_logger);
            }

            else {
                windowframe.close();
            }

            windowframe.endFrame();
        }
    }

}
    

namespace ks {

    void Logger::init() {
        int width = 960;
        int height = 480;
        std::string title = "KSLogger";
		if (m_Initialized) return;

		m_Initialized = true;

        m_LoggerThread = std::thread([this](){
            while (this->m_Initialized){
                loggerMain();
            }
        });
        runLoggerWindow(width, height, title);
    }

    Logger::~Logger() {
        m_Running.store(false);
        if (m_LoggerThread.joinable()) {
            m_LoggerThread.join();
        }
    }

}