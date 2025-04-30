#pragma once

#include <vector>
#include <memory>

#include "glad/glad.h"
#include "renderer/Buffer.h"

namespace Renderer {

struct BufferLayoutElement {
    GLuint index;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    const void* pointer;
};

using BufferLayout = std::vector<BufferLayoutElement>;

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(std::unique_ptr<Buffer> buffer, const BufferLayout& layout);
    void setIndexBuffer(std::unique_ptr<Buffer> indexBuffer);

    void bind() const;
    void unbind() const;

    [[nodiscard]] const GLuint handle() const { return m_Handle; }

private:
    GLuint m_Handle;
    std::vector<std::unique_ptr<Buffer>> m_VertexBuffers;
    std::unique_ptr<Buffer> m_IndexBuffer;
};

} // namespace Renderer
