#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

struct Vec2 {
    float x, y;
};

bool intersect(Vec2 A, Vec2 B, Vec2 C, Vec2 D, Vec2 &out) {
    float a1 = B.y - A.y;
    float b1 = A.x - B.x;
    float c1 = a1 * A.x + b1 * A.y;

    float a2 = D.y - C.y;
    float b2 = C.x - D.x;
    float c2 = a2 * C.x + b2 * C.y;

    float det = a1 * b2 - a2 * b1;

    if (det == 0) {
        return false; // Lines are parallel
    } else {
        out.x = (b2 * c1 - b1 * c2) / det;
        out.y = (a1 * c2 - a2 * c1) / det;
        return true; // Lines intersect
    }
}

const char* vertexShaderSrc = R"(
#version 330 core
layout (location = 0) in vec2 aPos;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

const char* fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
)";

GLuint compileShader(GLenum type, const char* src)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Shader compile error:\n" << log << std::endl;
    }

    return shader;
}

GLuint createProgram()
{
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main() {

 glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Line Intersection", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Window creation failed\n";
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, 800, 600);

    GLuint program = createProgram();

    // Two lines
    Vec2 A = {-0.8f, -0.5f};
    Vec2 B = { 0.8f,  0.5f};

    Vec2 C = {-0.8f,  0.5f};
    Vec2 D = { 0.8f, -0.5f};

    Vec2 I;
    bool hasIntersection = intersect(A, B, C, D, I);

    float vertices[] = {
        // line 1
        A.x, A.y,
        B.x, B.y,

        // line 2
        C.x, C.y,
        D.x, D.y
    };

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint pointVBO;
    glGenBuffers(1, &pointVBO);

    GLuint pointVAO;
    glGenVertexArrays(1, &pointVAO);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        // Draw lines
        glBindVertexArray(vao);
        glDrawArrays(GL_LINES, 0, 4);

        // Draw intersection point
        if (hasIntersection)
        {
            float p[] = { I.x, I.y };

            glBindVertexArray(pointVAO);
            glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(p), p, GL_DYNAMIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glPointSize(10.0f);
            glDrawArrays(GL_POINTS, 0, 1);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}