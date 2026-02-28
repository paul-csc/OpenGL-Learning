#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "index_buffer.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "vertex_array.h"
#include "texture.h"
#include "camera.h"

#include <iostream>

constexpr int WINDOW_WIDTH = 600;
constexpr int WINDOW_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool firstMouse = true;
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void MouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    static bool fullscreen = false;
    static bool f11PressedLastFrame = false;
    bool f11PressedNow = glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS;

    if (f11PressedNow && !f11PressedLastFrame) {
        fullscreen = !fullscreen;

        if (fullscreen) {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

            glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
            glfwSetWindowPos(window, 0, 0);
            glfwSetWindowSize(window, mode->width, mode->height);
        } else {
            glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
            glfwSetWindowSize(window, 800, 600);
            glfwSetWindowPos(window, 100, 100);
        }
    }

    f11PressedLastFrame = f11PressedNow;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
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
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(
        window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });
    glfwSwapInterval(1);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // clang-format off
    const float vertices[] = {
        // Front face
        -0.5f,-0.5f, 0.5f,   0.0f,0.0f,
         0.5f,-0.5f, 0.5f,   1.0f,0.0f,
         0.5f, 0.5f, 0.5f,   1.0f,1.0f,
        -0.5f, 0.5f, 0.5f,   0.0f,1.0f,

        // Back face
        -0.5f,-0.5f,-0.5f,   1.0f,0.0f,
         0.5f,-0.5f,-0.5f,   0.0f,0.0f,
         0.5f, 0.5f,-0.5f,   0.0f,1.0f,
        -0.5f, 0.5f,-0.5f,   1.0f,1.0f,

        // Left face
        -0.5f,-0.5f,-0.5f,   0.0f,0.0f,
        -0.5f,-0.5f, 0.5f,   1.0f,0.0f,
        -0.5f, 0.5f, 0.5f,   1.0f,1.0f,
        -0.5f, 0.5f,-0.5f,   0.0f,1.0f,

        // Right face
         0.5f,-0.5f,-0.5f,   1.0f,0.0f,
         0.5f,-0.5f, 0.5f,   0.0f,0.0f,
         0.5f, 0.5f, 0.5f,   0.0f,1.0f,
         0.5f, 0.5f,-0.5f,   1.0f,1.0f,

        // Top face
        -0.5f, 0.5f, 0.5f,   0.0f,0.0f,
         0.5f, 0.5f, 0.5f,   1.0f,0.0f,
         0.5f, 0.5f,-0.5f,   1.0f,1.0f,
        -0.5f, 0.5f,-0.5f,   0.0f,1.0f,

        // Bottom face
        -0.5f,-0.5f, 0.5f,   1.0f,1.0f,
         0.5f,-0.5f, 0.5f,   0.0f,1.0f,
         0.5f,-0.5f,-0.5f,   0.0f,0.0f,
        -0.5f,-0.5f,-0.5f,   1.0f,0.0f,
    };

    const unsigned int indices[] = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Left face
        8, 9,10,
       10,11, 8,

        // Right face
       12,13,14,
       14,15,12,

        // Top face
       16,17,18,
       18,19,16,

        // Bottom face
       20,21,22,
       22,23,20
    };
    // clang-format on

    const glm::vec3 cubePositions[] = {
        {  0.0f,  0.0f,   0.0f },
        {  2.0f,  5.0f, -15.0f },
        { -1.5f, -2.2f,  -2.5f },
        { -3.8f, -2.0f, -12.3f },
        {  2.4f, -0.4f,  -3.5f },
        { -1.7f,  3.0f,  -7.5f },
        {  1.3f, -2.0f,  -2.5f },
        {  1.5f,  2.0f,  -2.5f },
        {  1.5f,  0.2f,  -1.5f },
        { -1.3f,  1.0f,  -1.5f },
    };

    VertexArray vao;
    VertexBuffer vbo(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddBuffer(vbo, layout);

    IndexBuffer ibo(indices, 36);

    Shader shader("assets/shaders/vert.glsl", "assets/shaders/frag.glsl");

    Texture texture1("assets/textures/container.jpg");
    Texture texture2("assets/textures/awesomeface.png");

    shader.Bind();
    shader.SetUniform1i("uTexture1", 0);
    shader.SetUniform1i("uTexture2", 1);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture1.Bind(0);
        texture2.Bind(1);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glm::mat4 projection =
            glm::perspective(glm::radians(90.0f), (float)width / (float)height, 0.1f, 100.0f);
        shader.SetUniformMat4f("uProjection", projection);

        glm::mat4 view = camera.GetViewMatrix();
        shader.SetUniformMat4f("uView", view);

        shader.Bind();
        vao.Bind();
        ibo.Bind();

        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetUniformMat4f("uModel", model);

            glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}