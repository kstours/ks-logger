#include "ks_logger_ui/ks_logger_ui.h"
#include "window_menu/window_menu.h"
#include "log_channel/log_channel.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_internal.h" 
#include <string>
#include <vector>

void renderWindowMenu() {
    if (ImGui::BeginMenuBar()) {
        for (const auto& item : window_menu::menu) {
            if (ImGui::BeginMenu(item.name.c_str())) {
                for (const auto& options : item.options) {
                    const char* keybind = options.keybind.empty() ? nullptr : options.keybind.c_str();
                    if (ImGui::MenuItem(options.name.c_str(), keybind)) {
                        if (options.callback) {
                            options.callback();
                        }
                    }
                }
                ImGui::EndMenu();
            }
        }
        ImGui::EndMenuBar();
    }
}

void logger_ui::renderLoggerUI(int width, int height, bool* show_logger) {
    std::lock_guard<std::mutex> lock(logger_mutex);

    if (active_channels.empty()) {
        Log_Channel main_channel;
        main_channel.name = "Main Channel";
        main_channel.is_open = true;
        active_channels.push_back(main_channel);
    }

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    float posX = (mode->width / 2.0f) - (width / 2.0f);
    float posY = (mode->height / 2.0f) - (height / 2.0f);
    ImGui::SetNextWindowPos(ImVec2(posX, posY), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar;
    ImGuiID dockspace_id = 0;

    if (ImGui::Begin("KS Logger", show_logger, flags)) {
        renderWindowMenu();

        dockspace_id = ImGui::GetID("KSLoggerDockSpace");

        ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_TabUnfocusedActive, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_TabBarBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_TabBorderSize, 0.0f);

        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_PassthruCentralNode;
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        ImGui::PopStyleColor(3);
        ImGui::PopStyleVar(2);

        static bool first_time = true;
        if (first_time) {
            first_time = false;

            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, ImVec2(width, height));

            for (size_t i = 0; i < active_channels.size(); i++) {
                ImGui::DockBuilderDockWindow(active_channels[i].name.c_str(), dockspace_id);
            }

            ImGui::DockBuilderFinish(dockspace_id);
        }
    }
    ImGui::End();

    ImGuiWindowFlags tab_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;

    for (size_t i = 0; i < active_channels.size(); i++) {
        if (!active_channels[i].is_open) {
            continue;
        }

      
        ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_Appearing);

   
        bool* open_flag_ptr = (i == 0) ? nullptr : &active_channels[i].is_open;

        if (ImGui::Begin(active_channels[i].name.c_str(), open_flag_ptr, tab_flags)) {
            for (const auto& message : active_channels[i].messages) {
                ImGui::TextDisabled("%s", message.timestamp.c_str());
                ImGui::SameLine();
                ImGui::TextUnformatted(message.text.c_str());
                ImGui::Separator();
            }
        }
        ImGui::End();
    }
}