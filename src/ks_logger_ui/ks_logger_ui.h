#pragma once
#include <GLFW/glfw3.h>
#include <string>

class LoggerUI {

public:
    static LoggerUI& get() {
        static LoggerUI instance;
        return instance;
    }

    bool init(int width, int height, std::string title);
    void renderLoggerUI(int width, int height, bool show_logger);

    LoggerUI(const LoggerUI&) = delete;
    LoggerUI& operator=(const LoggerUI&) = delete;

private:
    LoggerUI();
    bool m_ShowLogger;
    GLFWwindow* m_GLFWWindow;
    bool m_Initialized;
};