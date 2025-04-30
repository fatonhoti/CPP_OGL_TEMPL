#pragma once

#include <string>
#include <cstdint>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Core {

class Application {
public:
    Application(int width, int height, const std::string& title);
    virtual ~Application();

    [[nodiscard]] bool initialize();
    void run();
    void shutdown();

    [[nodiscard]] const GLFWwindow* getWindow() const { return m_Window; }
    [[nodiscard]] int32_t getWidth() const { return m_Width; }
    [[nodiscard]] int32_t getHeight() const { return m_Height; }

protected:
    GLFWwindow* m_Window = nullptr;

    virtual void onCreate() = 0;
    virtual void onUpdate(float deltaTime) = 0;

    int32_t m_Width;
    int32_t m_Height;
    std::string m_Title;
    bool m_IsRunning = false;
    double m_LastFrameTime = 0.0;
};

} // namespace Core
