#include <ks_logger.h>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <atomic>
#include "window_frame/window_frame.h"
#include "ks_logger_ui/ks_logger_ui.h"
#include "window_menu/window_menu.h"
#include "log_channel/log_channel.h"
#include "GLFW/glfw3.h"

namespace {
    void loggerMain() {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    void runLoggerWindow(int width, int height, std::string title, std::atomic<bool>* running_flag) {
        WindowFrame& windowframe = WindowFrame::get();

        if (!windowframe.init(width, height, title)) return;

        bool show_logger = true;

        while (!windowframe.shouldClose() && *running_flag) {
            windowframe.startFrame();

            if (show_logger) {
                logger_ui::renderLoggerUI(width, height, &show_logger);
            }
            else {
                windowframe.close();
            }

            windowframe.endFrame();
        }

        *running_flag = false;
    }
}

namespace ks {

    bool Logger::registerChannel(const std::string& name) {
        std::lock_guard<std::mutex> lock(logger_mutex);

        for (const auto& channel : active_channels) {
            if (channel.name == name) {
                return false;
            }
        }

        Log_Channel new_channel;
        new_channel.name = name;
        new_channel.is_open = true;
        active_channels.push_back(new_channel);
        return true;
    }

    void Logger::log(const std::string& message, const std::string& name) {
        std::lock_guard<std::mutex> lock(logger_mutex);
        bool found = false;

        for (auto& channel : active_channels) {
            if (channel.name == "Main Channel") {
                std::string modifiedMessage = "[" + name + "] " + message;
                if (name != "Main Channel") {
                     channel.messages.emplace_back(modifiedMessage);
                }
                else {
                    channel.messages.emplace_back(message);

                }
            
            }

            if (channel.name == name) {
                channel.messages.emplace_back(message);
                found = true;
                break;
            }
        }

        if (!found) {
            Log_Channel new_channel;
            new_channel.name = name;
            new_channel.is_open = true;
            new_channel.messages.emplace_back(message);
            active_channels.push_back(new_channel);
        }
    }

    void Logger::init() {
        int width = 960;
        int height = 480;
        std::string title = "KS Logger";

        window_menu::initWindowMenu();

        if (m_Initialized) return;
        m_Initialized = true;
        m_Running = true;

        m_LoggerThread = std::thread([this, width, height, title]() {
            runLoggerWindow(width, height, title, &this->m_Running);
            });

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    Logger::~Logger() {
        m_Running = false;
        if (m_LoggerThread.joinable()) {
            m_LoggerThread.join();
        }
    }
}