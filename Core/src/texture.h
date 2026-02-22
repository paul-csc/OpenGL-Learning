#pragma once

#include <string>

class Texture {
  public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

  private:
    unsigned int m_rendererID;
    std::string m_filePath;
    unsigned char* m_localBuffer;
    int m_width;
    int m_height;
    int m_bpp;
};