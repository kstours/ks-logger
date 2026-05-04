#include <ks_logger.h>
#include "ui/window_frame/window_frame.h"

namespace {


    void loggerMain() {
        
    }


    void runLoggerWindow(int width, int height, std::string title) {
   
        WindowFrame& windowframe = WindowFrame::get();

        if (!windowframe.init(width, height, title)) return;

        bool show_logger = true;
        while (!windowframe.shouldClose()) {
            windowframe.startFrame();

            if (show_logger) {

                // Centers the logger window
                const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                float posX = (mode->width / 2.0f) - (width / 2.0f);
                float posY = (mode->height / 2.0f) - (height / 2.0f);
                ImGui::SetNextWindowPos(ImVec2(posX, posY), ImGuiCond_FirstUseEver);
                ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);


                if (ImGui::Begin("KSLogger", &show_logger, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse)) {

                    ImGui::Text("Hello World");

                }

                ImGui::End();
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