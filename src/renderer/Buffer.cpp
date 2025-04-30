#include "renderer/Buffer.h"

#include "glad/glad.h"

namespace Renderer {

static GLenum BufferTypeToGLenum(const BufferType type) {
    switch (type) {
        case BufferType::Vertex: return GL_ARRAY_BUFFER;
        case BufferType::Index: return GL_ELEMENT_ARRAY_BUFFER;
        default: return 0;
    }
}

Buffer::Buffer(const void* data, const uint32_t size, const BufferType type)
    : m_Handle(0), m_Type(BufferTypeToGLenum(type))
{
    glGenBuffers(1, &m_Handle);
    glBindBuffer(m_Type, m_Handle);
    glBufferData(m_Type, size, data, GL_STATIC_DRAW);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &m_Handle);
}

void Buffer::bind() const {
    glBindBuffer(m_Type, m_Handle);
}

void Buffer::unbind() const {
    glBindBuffer(m_Type, 0);
}

} // namespace Renderer
