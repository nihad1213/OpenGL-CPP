#include <GLFW/glfw3.h>
#include <iostream>

int main() {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw!" << std::endl;
        return -1; 
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Colorful Screen", NULL, NULL);

    if (!window) {
        std::cerr << "Failed to create window!" << std::endl; 
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}