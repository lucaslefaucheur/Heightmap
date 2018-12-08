#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <vector>

#include "controls.h"
#include "mesh.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

int main() {
    vector<GLfloat> pixels = loadImage("/Users/lucaslefaucheur/Desktop/Assignment1/Assignment1/test1.bmp");
    
    // Create a window and its OpenGL context
    GLFWwindow *window;
    
    // Initialize the library
    if (!glfwInit())
        return -1;
    
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Assignment1", NULL, NULL);
    
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    glfwSetScrollCallback(window, scrollCallback);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window); // Make the window's context current
    glViewport(0.0f, 0.0f, screenWidth, screenHeight); // Part of the window to which OpenGL will draw
    
    // Projection matrix: define the properties of the camera that views the objects in the world coordinate frame
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Modelview matrix: define how objects are transformed (translation, rotation; scaling) in the world coordinate frame
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 20000); // Set coordinate system
    
    // Loop until user closes the window
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Render OpenGL
        glPushMatrix();
        glTranslatef(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, -500);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glTranslatef(-SCREEN_WIDTH/2, -SCREEN_HEIGHT/2, 500);
        
        DrawMesh(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, -500, pixels);
        
        glPopMatrix();
        glfwSwapBuffers(window); // Swap front and back buffers
        glfwPollEvents(); // Poll for and process events
    }
    glfwTerminate();
    return 0;
}
