#include "ks_logger_ui/ks_logger_ui.h"
#include "window_menu/window_menu.h"
#include "GLFW/glfw3.h"
#include "imgui.h"


void renderWindowMenu() {
    if (ImGui::BeginMenuBar()) {
        for (const auto & item : window_menu::menu) {
        if (ImGui::BeginMenu(item.name.c_str())) { 
            for (const auto & options : item.options) {
                const char* keybind = options.keybind.empty() ? nullptr : options.keybind.c_str();
                if (ImGui::MenuItem(options.name.c_str(),keybind)) { 
                    if (options.callback) {
                        options.callback();
                     }
                    }
                }
                ImGui::EndMenu();
            }
        }
    }ImGui::EndMenuBar();
}
         

 void logger_ui::renderLoggerUI(int width, int height, bool* show_logger){
                // Centers the logger ui
                const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                float posX = (mode->width / 2.0f) - (width / 2.0f);
                float posY = (mode->height / 2.0f) - (height / 2.0f);
                ImGui::SetNextWindowPos(ImVec2(posX, posY), ImGuiCond_FirstUseEver);
                ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);
                ImGuiWindowFlags flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar;
                if (ImGui::Begin("KS Logger", show_logger, flags)) {
                    //Menu Bar 
                       
                            renderWindowMenu();
                         


                    ImGui::Text("Hello World");

                }

                ImGui::End();
}
