#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

namespace Renderer {

enum class ShaderType {
    Vertex,
    Fragment,
    Compute
};

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    Shader(const std::string& computePath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform1i(const std::string& name, const int32_t value);
    void setUniform1f(const std::string& name, const float value);
    void setUniformVec2f(const std::string& name, const float v0, const float v1);
    void setUniformVec3f(const std::string& name, const float v0, const float v1, const float v2);
    void setUniformVec4f(const std::string& name, const float v0, const float v1, const float v2, const float v3);
    void setUniformMat4f(const std::string& name, const float* matrix);

private:
    uint32_t m_Handle;
    std::unordered_map<std::string, int32_t> m_UniformLocationCache;

    int32_t getUniformLocation(const std::string& name);
    uint32_t createShader(const std::string& vertexPath, const std::string& fragmentPath);
    uint32_t createComputeShader(const std::string& computePath);
    uint32_t compileShader(const std::string& filePath, const uint32_t type);
};

} // namespace Renderer
