#include "renderer/Shader.h"

#include "glad/glad.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace fs = std::filesystem;

namespace Renderer {

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    : m_Handle(createShader(vertexPath, fragmentPath)) {}

Shader::Shader(const std::string& computePath)
    : m_Handle(createComputeShader(computePath)) {}

Shader::~Shader() {
    glDeleteProgram(m_Handle);
}

void Shader::bind() const {
    glUseProgram(m_Handle);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, const int32_t value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string& name, const float value) {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniformVec2f(const std::string& name, const float v0, const float v1) {
    glUniform2f(getUniformLocation(name), v0, v1);
}

void Shader::setUniformVec3f(const std::string& name, const float v0, const float v1, const float v2) {
    glUniform3f(getUniformLocation(name), v0, v1, v2);
}

void Shader::setUniformVec4f(const std::string& name, const float v0, const float v1, const float v2, const float v3) {
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniformMat4f(const std::string& name, const float* matrix) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix);
}

int Shader::getUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }
    const int32_t location = glGetUniformLocation(m_Handle, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' doesn't exist!\n";
    }
    m_UniformLocationCache[name] = location;
    return location;
}

uint32_t Shader::createShader(const std::string& vertexPath, const std::string& fragmentPath) {

    auto cwd = fs::current_path();
    const std::string cwd_str = cwd.string();
    // if program is ran from the build folder, we step out once to
    // end up in the root folder so we can navigate to 'assets/shaders'.
    // Not ideal way of handling this, but this is meant to be a rudimentary setup.
    if (cwd_str.find("build_") != std::string::npos || 
        cwd.filename().string().find("build") == 0) {
        cwd = cwd.parent_path();
    }

    const auto path_vertexShader = cwd / "assets" / "shaders" / vertexPath;
    const auto path_fragShader = cwd / "assets" / "shaders" / fragmentPath;

    const uint32_t program = glCreateProgram();
    const uint32_t vs = compileShader(path_vertexShader, GL_VERTEX_SHADER);
    const uint32_t fs = compileShader(path_fragShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

uint32_t Shader::createComputeShader(const std::string& computePath) {
    unsigned int program = glCreateProgram();
    unsigned int cs = compileShader(computePath, GL_COMPUTE_SHADER);

    glAttachShader(program, cs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(cs);

    return program;
}

uint32_t Shader::compileShader(const std::string& filePath, const uint32_t type) {
    std::ifstream file(filePath);
    std::stringstream ss;
    std::string line;
    while (getline(file, line)) {
        ss << line << '\n';
    }
    const std::string shaderSource = ss.str();
    const char* src = shaderSource.c_str();

    const uint32_t id = glCreateShader(type);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int32_t result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int32_t length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cerr << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : (type == GL_FRAGMENT_SHADER ? "fragment" : "compute"))
                  << " shader!\n";
        std::cerr << message << "\n";
        glDeleteShader(id);
        return 0;
    }

    return id;
}

} // namespace Renderer
