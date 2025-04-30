#include "Application.h"

#include <iostream>
#include <vector>

#include "renderer/VertexArray.h"
#include "renderer/Buffer.h"
#include "renderer/Shader.h"

#include "input/Input.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class TriangleApp : public Core::Application {
public:
    TriangleApp(int width, int height, const std::string& title)
        : Core::Application(width, height, title) {}
    ~TriangleApp() override = default;

private:
    void onCreate() override {
        // --- Test triangle ---
        const std::vector<float> vertices = {
            // positions         // colors
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, // bottom Left
            0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, // bottom Right
            0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, // middle
        };

        Renderer::BufferLayout layout = {
            {0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)0},
            {1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)(3 * sizeof(float))}
        };

        m_VAO = std::make_unique<Renderer::VertexArray>();
        auto vertexBuffer = std::make_unique<Renderer::Buffer>(vertices.data(), vertices.size() * sizeof(float), Renderer::BufferType::Vertex);
        m_VAO->addBuffer(std::move(vertexBuffer), layout);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        m_Shader.load("basic.vert", "basic.frag");
    }

    void onUpdate(float deltaTime) override {
        if (Input::isKeyPressed(m_Window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(m_Window, true);
        }

        // imgui state
        static const ImGuiIO& io = ImGui::GetIO();
        static bool show_demo_window = true;
        static bool show_another_window = false;
        static ImVec4 clear_color = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

        glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Shader.bind();
        m_VAO->bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 1. Show the big demo window (ImGui::ShowDemoWindow() calls all the ImGui::Show* functions
        //    e.g., ImGui::ShowSimpleWindow(), ImGui::ShowExampleAppConsole(), ImGui::ShowAppMetrics(), etc.).
        //    You can use the "show_demo_window" global to toggle visibility.
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");

            ImGui::Text("This is some useful text.");
            ImGui::Checkbox("Demo Window", &show_demo_window);
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);

            if (ImGui::Button("Button"))
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

    }

private:
    std::unique_ptr<Renderer::VertexArray> m_VAO;
    Renderer::Shader m_Shader;
};

int main() {
    TriangleApp app(800, 600, "TriangleApp");
    if (!app.initialize()) return EXIT_FAILURE;
    app.run();
    return 0;
}
