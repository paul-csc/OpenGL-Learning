#pragma once

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer {
  public:
    void Clear() const;
    void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;

  private:
};
