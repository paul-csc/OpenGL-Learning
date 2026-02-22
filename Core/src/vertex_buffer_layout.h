#pragma once

#include <glad/glad.h>
#include <vector>
#include <cassert>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static constexpr unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        assert(false);
        return 0;
    }
};

class VertexBufferLayout {
  public:
    VertexBufferLayout() : m_stride(0) {}

    template <typename T>
    void Push(unsigned int count) {
        static_assert(false);
    }

    template <>
    void Push<float>(unsigned int count) {
        m_elements.emplace_back(GL_FLOAT, count, GL_FALSE);
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template <>
    void Push<unsigned int>(unsigned int count) {
        m_elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE);
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template <>
    void Push<unsigned char>(unsigned int count) {
        m_elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_TRUE);
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    unsigned int GetStride() const { return m_stride; }
    const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }

  private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;
};