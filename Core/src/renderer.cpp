#include "renderer.h"

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

void Renderer::Clear()const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const {
    shader.Bind();
    vao.Bind();
    ibo.Bind();
    glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, 0);
}
