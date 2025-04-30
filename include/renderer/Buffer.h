#pragma once

#include <cstdint>

#include "glad/glad.h"

namespace Renderer {

enum class BufferType {
    Vertex,
    Index
};

class Buffer {
public:
    Buffer(const void* data, const uint32_t size, const BufferType type);
    ~Buffer();

    [[nodiscard]] const GLuint handle() const { return m_Handle; }
    void bind() const;
    void unbind() const;

private:
    GLuint m_Handle;
    GLenum m_Type;
};

} // namespace Renderer
