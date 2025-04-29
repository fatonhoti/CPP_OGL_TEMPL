#include "renderer/Buffer.h"

#include "glad/glad.h"

static GLenum BufferTypeToGLenum(const Renderer::BufferType type) {
    switch (type) {
        case Renderer::BufferType::Vertex: return GL_ARRAY_BUFFER;
        case Renderer::BufferType::Index: return GL_ELEMENT_ARRAY_BUFFER;
        default: return 0;
    }
}

namespace Renderer {

Buffer::Buffer(const void* data, const unsigned int size, BufferType type)
    : m_Handle(0), m_Type(BufferTypeToGLenum(type))
{
    glGenBuffers(1, &m_Handle);
    glBindBuffer(m_Type, m_Handle);
    glBufferData(m_Type, size, data, GL_STATIC_DRAW);
}

Buffer::Buffer(const void* data, const unsigned int size, const std::vector<VertexBufferConfig>& layout)
    : m_Handle(0), m_Type(GL_ARRAY_BUFFER), m_VertexBufferLayout(layout)
{
    glGenBuffers(1, &m_Handle);
    glBindBuffer(m_Type, m_Handle);
    glBufferData(m_Type, size, data, GL_STATIC_DRAW);

    for (const auto& config : m_VertexBufferLayout) {
        glEnableVertexAttribArray(config.index);
        glVertexAttribPointer(config.index, config.size, config.type, config.normalized, config.stride, config.pointer);
    }
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &m_Handle);
}

const uint32_t Buffer::handle() const {
    return m_Handle;
}

void Buffer::bind() const {
    glBindBuffer(m_Type, m_Handle);
}

void Buffer::unbind() const {
    glBindBuffer(m_Type, 0);
}

} // namespace Renderer
