#include "renderer/VertexArray.h"

#include "glad/glad.h"
#include "renderer/Buffer.h"

namespace Renderer {

VertexArray::VertexArray()
    : m_Handle(0)
{
    glGenVertexArrays(1, &m_Handle);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_Handle);
}

void VertexArray::addBuffer(std::unique_ptr<Buffer> buffer, const BufferLayout& layout)
{
    glBindVertexArray(m_Handle);
    buffer->bind();
    for (const auto& element : layout) {
        glEnableVertexAttribArray(element.index);
        glVertexAttribPointer(element.index, element.size, element.type, element.normalized, element.stride, element.pointer);
    }
    m_VertexBuffers.push_back(std::move(buffer));
}

void VertexArray::setIndexBuffer(std::unique_ptr<Buffer> indexBuffer)
{
    glBindVertexArray(m_Handle);
    indexBuffer->bind();
    m_IndexBuffer = std::move(indexBuffer);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_Handle);
    /*
    if (m_IndexBuffer) {
        m_IndexBuffer->bind();
    }
    */
}

void VertexArray::unbind() const
{
    /*
    if (m_IndexBuffer) {
        m_IndexBuffer->unbind();
    }
    */
    glBindVertexArray(0);
}

} // namespace Renderer
