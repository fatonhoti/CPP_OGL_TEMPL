#pragma once

#include <cstdint>
#include <string>

namespace Renderer {

class Texture {
public:
    Texture(const std::string& filePath);
    ~Texture();

    void bind(const uint32_t slot = 0) const;
    void unbind() const;

private:
    uint32_t m_Handle;
    int32_t m_Width;
    int32_t m_Height;
    int32_t m_BPP; // bits per pixel
};

} // namespace Renderer
