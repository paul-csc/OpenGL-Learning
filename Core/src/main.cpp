#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "index_buffer.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "vertex_array.h"
#include "renderer.h"
#include "texture.h"

#include <iostream>

constexpr int WINDOW_WIDTH = 600;
constexpr int WINDOW_HEIGHT = 600;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
        glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSwapInterval(1);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // clang-format off
    float vertices[] = {
         0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,   0.0f, 1.0f, // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
    };
    // clang-format on

    VertexArray vao;
    VertexBuffer vbo(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddBuffer(vbo, layout);

    IndexBuffer ibo(indices, 6);

    Shader shader("assets/shaders/vert.glsl", "assets/shaders/frag.glsl");
    shader.Bind();

    Renderer renderer;

    Texture texture1("assets/textures/bear.png");
    Texture texture2("assets/textures/snowman.png");

    shader.SetUniform1i("uTexture1", 0);
    shader.SetUniform1i("uTexture2", 1);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        ProcessInput(window);
        renderer.Clear();

        texture1.Bind(0);
        texture2.Bind(1);

        renderer.Draw(vao, ibo, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}