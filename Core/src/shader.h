#pragma once

#include <glad/glad.h>
#include <unordered_map>
#include <string>

class Shader {
  public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniformi(const std::string& name, int value);
    void SetUniformf(const std::string& name, float value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

  private:
    std::string ReadFileAsString(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertSource, const std::string& fragSource);
    unsigned int GetUniformLocation(const std::string& name);

    unsigned int m_rendererID;
    std::unordered_map<std::string, int> m_uniformLocationCache;
};