#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_rendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_rendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) {
    Bind();
    vbo.Bind();

    const auto& elements = layout.GetElements();
    uintptr_t offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];

        glVertexAttribPointer(
            i, element.count, element.type, element.normalized, layout.GetStride(), (void*)offset);
        glEnableVertexAttribArray(i);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const {
    glBindVertexArray(m_rendererID);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}
