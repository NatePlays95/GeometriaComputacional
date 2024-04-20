#include <GLFW/glfw3.h>
#include <iostream>
#include "vmath.h"

using namespace std;

void drawTriangle() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);  // Red
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0, 1.0, 0.0);  // Green
    glVertex2f(0.5f, -0.5f);
    glColor3f(0.0, 0.0, 1.0);  // Blue
    glVertex2f(0.0f, 0.5f);
    glEnd();
}

int programLoop() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Set up the projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Draw the triangle
        drawTriangle();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up GLFW and exit
    glfwTerminate();
    return 0;
}

int main() {
    //test
    cout << "hello world" << endl;
    vec2 vecA(1.5, 2.0/3.0);
    cout << vecA << endl;
}