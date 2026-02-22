#include "shader.h"

#include <iostream>
#include <vector>
#include <fstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) : m_rendererID(0) {
    const std::string& vertSrc = ReadFileAsString(vertexPath);
    const std::string& fragSrc = ReadFileAsString(fragmentPath);

    m_rendererID = CreateShader(vertSrc, fragSrc);
}

Shader::~Shader() {
    glDeleteProgram(m_rendererID);
}

void Shader::Bind() const {
    glUseProgram(m_rendererID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value) {
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

std::string Shader::ReadFileAsString(const std::string& filepath) {
    std::string result;
    std::ifstream in(filepath, std::ios::in | std::ios::binary | std::ios::ate);
    if (in) {
        result.resize((size_t)in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0], result.size());
        in.close();
    } else {
        std::cout << "Could not open file '" << filepath << "'\n";
    }

    return result;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);

    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, 0);
    glCompileShader(shader);

    int isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        int maxLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader\n";
        std::cout << infoLog.data() << "\n";

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

unsigned int Shader::CreateShader(const std::string& vertSource, const std::string& fragSource) {
    unsigned int program = glCreateProgram();

    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertSource);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragSource);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

int Shader::GetUniformLocation(const std::string& name) {
    if (m_uniformLocationCache.contains(name)) {
        return m_uniformLocationCache[name];
    }

    int location = glGetUniformLocation(m_rendererID, name.c_str());
    if (location == -1) {
        std::cout << "Uniform '" << name << "' does not exist\n";
    }

    m_uniformLocationCache[name] = location;
    return location;
}
