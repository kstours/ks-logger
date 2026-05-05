#pragma once
#include <GLFW/glfw3.h>
#include <string>

class WindowFrame {

public:
    static WindowFrame& get() {
        static WindowFrame instance;
        return instance;
    }

    bool init(int width, int height, std::string title);
    void close();
    bool shouldClose() const;
    void startFrame();
    void endFrame();

    WindowFrame(const WindowFrame&) = delete;
    WindowFrame& operator=(const WindowFrame&) = delete;

private:
    WindowFrame();

    GLFWwindow* m_GLFWWindow;
    bool m_Initialized;
};