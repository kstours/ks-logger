#include "window_frame.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

WindowFrame::WindowFrame() {
    m_GLFWWindow = nullptr;
    m_Initialized = false;
}


bool WindowFrame::init(int width, int height, std::string title) {
    if (m_Initialized) return false;

    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    m_GLFWWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_GLFWWindow) return false;

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
 
    glfwMakeContextCurrent(m_GLFWWindow);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().IniFilename = nullptr;
    ImGui_ImplGlfw_InitForOpenGL(m_GLFWWindow, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    m_Initialized = true;
    return true;
}

void WindowFrame::close() {
    glfwSetWindowShouldClose(m_GLFWWindow, true);
}

bool WindowFrame::shouldClose() const {
    return glfwWindowShouldClose(m_GLFWWindow);
}

void WindowFrame::startFrame() {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void WindowFrame::endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* currentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(currentContext);
    }

    glfwSwapBuffers(m_GLFWWindow);
}