#include "ks_logger_ui/ks_logger_ui.h"
#include "imgui.h"

// 1. ADD THIS CONSTRUCTOR DEFINITION
LoggerUI::LoggerUI() 
    : m_ShowLogger(true), m_GLFWWindow(nullptr), m_Initialized(false) 
{
    // You can initialize your member variables here
}
 void LoggerUI::renderLoggerUI(int width, int height, bool show_logger){
                // Centers the logger window
                const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                float posX = (mode->width / 2.0f) - (width / 2.0f);
                float posY = (mode->height / 2.0f) - (height / 2.0f);
                ImGui::SetNextWindowPos(ImVec2(posX, posY), ImGuiCond_FirstUseEver);
                ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);

                if (ImGui::Begin("KSLogger", &show_logger, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse)) {

                    ImGui::Text("it works");

                }

                ImGui::End();
}
