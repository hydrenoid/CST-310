///////////////////////////////////////////////////////////////
// LorenzAttractor.cpp
//
// This program is for project8 and is a representation of a lorenz attractor
// in three dimensional space.
//
// Interaction:
// Use arrow keys to rotate the scene.
// Press r to reset.
//
// COMPILE: g++ -o lorenz_attractor LorenzAttractor.cpp -lglfw -lGLEW -lGL -lGLU
//
// RUN: ./lorenz_attractor
//
// Jonathon Moore.
///////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <iostream>

// Constants for the Lorenz system
const float dt = 0.01f;
const float sigma = 10.0f, rho = 28.0f, beta = 8.0f / 3.0f;

// Variables for two sets of Lorenz attractors
float x_1 = 0.01f, y_1 = 0.0f, z_1 = 0.0f;
float x_2 = -0.01f, y_2 = 0.0f, z_2 = 0.0f;
std::vector<float> vertices1, vertices2;

// Variables for rotating the scene
float angleX = 0.0f, angleY = 0.0f;

// Function to update the Lorenz system
void updateLorenz(float &x, float &y, float &z, float dt, float sigma, float rho, float beta, std::vector<float> &vertices) {
    float dx = sigma * (y - x) * dt;
    float dy = (x * (rho - z) - y) * dt;
    float dz = (x * y - beta * z) * dt;
    x += dx; y += dy; z += dz;
    vertices.push_back(x); vertices.push_back(y); vertices.push_back(z);
}

// Function to check for OpenGL errors
void checkGLError() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}

// Function to reset the animation
void resetAnimation() {
    x_1 = 0.01f; y_1 = 0.0f; z_1 = 0.0f;
    x_2 = -0.01f; y_2 = 0.0f; z_2 = 0.0f;
    vertices1.clear();
    vertices2.clear();
}

// Function to process user input
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        resetAnimation();
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        angleX -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        angleX += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        angleY -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        angleY += 1.0f;
    }
}

// Function to apply color based on position
void applyColor(float x, float y, float z) {
    float r = fabs(x) / 30.0f;
    float g = fabs(y) / 30.0f;
    float b = fabs(z) / 30.0f;
    glColor3f(r, g, b);
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    std::cout << "Interaction:" << std::endl;
    std::cout << "Use arrow keys to rotate the scene." << std::endl;
    std::cout << "Press r to reset." << std::endl;
}

int main() {

    printInteraction();

    // Initialize GLFW
    if (!glfwInit()) return -1;

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Lorenz Attractor", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewInit();

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Set up the viewport
    glViewport(0, 0, 800, 600);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 500.0);

    // Set up the modelview matrix
    glMatrixMode(GL_MODELVIEW);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        updateLorenz(x_1, y_1, z_1, dt, sigma, rho, beta, vertices1);
        updateLorenz(x_2, y_2, z_2, dt, sigma, rho, beta, vertices2);

        // Clear the color buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Load the identity matrix
        glLoadIdentity();

        // Set the camera position and orientation
        gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);

        // Apply rotations
        glRotatef(angleX, 1.0f, 0.0f, 0.0f);
        glRotatef(angleY, 0.0f, 1.0f, 0.0f);

        // Draw the first Lorenz attractor
        glBegin(GL_LINE_STRIP);
        for (size_t i = 0; i < vertices1.size(); i += 3) {
            applyColor(vertices1[i], vertices1[i + 1], vertices1[i + 2]);
            glVertex3f(vertices1[i], vertices1[i + 1], vertices1[i + 2]);
        }
        glEnd();

        // Draw the second Lorenz attractor
        glBegin(GL_LINE_STRIP);
        for (size_t i = 0; i < vertices2.size(); i += 3) {
            applyColor(vertices2[i], vertices2[i + 1], vertices2[i + 2]);
            glVertex3f(vertices2[i], vertices2[i + 1], vertices2[i + 2]);
        }
        glEnd();

        // Check for OpenGL errors
        checkGLError();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
