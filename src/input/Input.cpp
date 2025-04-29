#include "input/Input.h"

#include "GLFW/glfw3.h"

namespace Input {

bool isKeyPressed(GLFWwindow* window, int32_t key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool isMouseButtonPressed(GLFWwindow* window, int32_t button) {
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

std::pair<double, double> getMousePosition(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {xpos, ypos};
}

} // namespace Input
