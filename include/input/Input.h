#pragma once

#include "GLFW/glfw3.h"

#include <utility>

namespace Input {

bool isKeyPressed(GLFWwindow* window, int32_t key);
bool isMouseButtonPressed(GLFWwindow* window, int32_t button);
std::pair<double, double> getMousePosition(GLFWwindow* window);

} // namespace Input
