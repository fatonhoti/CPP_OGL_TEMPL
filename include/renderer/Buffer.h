#pragma once

#include <cstdint>
#include <vector>

#include "glad/glad.h"

namespace Renderer {

enum class BufferType {
    Vertex,
    Index
};

struct VertexBufferConfig {
    GLuint index;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    const void* pointer;

    VertexBufferConfig(GLuint index_, GLint size_, GLenum type_, GLboolean normalized_, GLsizei stride_, const void* pointer_)
        : index(index_), size(size_), type(type_), normalized(normalized_), stride(stride_), pointer(pointer_) {}
};

class Buffer {
public:
    Buffer(const void* data, const unsigned int size, BufferType type);
    Buffer(const void* data, const unsigned int size, const std::vector<VertexBufferConfig>& layout);
    ~Buffer();

    const uint32_t handle() const;
    void bind() const;
    void unbind() const;

private:
    uint32_t m_Handle;
    uint32_t m_Type;
    std::vector<VertexBufferConfig> m_VertexBufferLayout;
};

} // namespace Renderer
