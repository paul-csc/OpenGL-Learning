#pragma once

#include <glad/gl.h>
#include <glm/mat4x4.hpp>
#include <unordered_map>
#include <string>

class Shader {
  public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string& name, const glm::mat4& mat);

  private:
    static std::string ReadFileAsString(const std::string& filepath);
    static unsigned int CompileShader(unsigned int type, const std::string& source);
    static unsigned int CreateShader(const std::string& vertSource, const std::string& fragSource);
    int GetUniformLocation(const std::string& name);

    unsigned int m_rendererID;
    std::unordered_map<std::string, int> m_uniformLocationCache;
};