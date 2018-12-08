//
//  controls.h
//  Assignment1
//
//  Created by Lucas Le Faucheur on 2018-05-14.
//  Copyright © 2018 Lucas Le Faucheur. All rights reserved.
//

#ifndef controls_h
#define controls_h

GLfloat spaceBetween = 2.0;
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

using namespace std;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    const GLfloat rotationSpeed = 10;
    
    if (action == GLFW_PRESS || action == GLFW_REPEAT) { // If a key is pressed/repeated
        switch (key) {
            case GLFW_KEY_UP:
                rotationX -= rotationSpeed; // rotate the mesh up
                cout << "up" << endl;
                break;
            case GLFW_KEY_DOWN:
                rotationX += rotationSpeed; // rotate the mesh down
                cout << "down" << endl;
                break;
            case GLFW_KEY_RIGHT:
                rotationY += rotationSpeed; // rotate the mesh to right
                cout << "right" << endl;
                break;
            case GLFW_KEY_LEFT:
                rotationY -= rotationSpeed; // rotate the mesh to left
                cout << "left" << endl;
                break;
            case GLFW_KEY_P:
                glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // change rendering mode to GL_POINT
                cout << "P" << endl;
                break;
            case GLFW_KEY_L:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // change rendering mode to GL_LINE
                cout << "L" << endl;
                break;
            case GLFW_KEY_T:
                glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES); // change rendering mode to GL_TRIANGLES
                cout << "T" << endl;
                break;
        }
    }
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    if (yoffset > 0) {
        spaceBetween+=0.1; // move into the scene
        cout << "scroll down" << endl;
    }
    else if (spaceBetween > 0.1) {
        spaceBetween-=0.1; // move out of the scene
        cout << "scroll up" << endl;
    }
}

#endif /* controls_h */
