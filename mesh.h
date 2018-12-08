//
//  mesh.h
//  Assignment1
//
//  Created by Lucas Le Faucheur on 2018-05-14.
//  Copyright © 2018 Lucas Le Faucheur. All rights reserved.
//

#ifndef mesh_h
#define mesh_h

#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;

int length, width;

vector<GLfloat> loadImage(char* name) {
    CImg<unsigned char> image(name); // Load the image using CImg librairy
    
    cout << "image: " << name << "\nsize = " << image.height() << " * " << image.width() << endl;
    if (image.height() < 256 || image.width() < 256 || image.height() > 1024 || image.width() > 1024) {
        cout << "The application handles only images of minimum size 256 × 256 and maximum size of 1024 × 1024" << endl;
        exit(0);
    }
    
    width = image.height()/2;
    length = image.width()/2;
    
    vector<GLfloat> pixels; // Vector containing the intensity of each pixels
    for (int r = 0; r < image.height() - 1; r+=2)
        for (int c = 0; c < image.width() - 1; c+=2)
            pixels.push_back(((int)image(c,r,0,0) + (int)image(c,r,0,1) + (int)image(c,r,0,2)) / 3); // Creates an average (in case it is not black & white)
    
    return pixels;
}

void DrawMesh(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, vector<GLfloat> pixels) {
    GLfloat vertices[width-1][length * 2 * 3];
    
    int tempI, tempJ;
    tempI = 0;
    
    // z < centerPosZ
    for (int i = 0; i < (width/2); i++) {
        // x < centerPosX
        tempJ = 0;
        for (int j = 0; j < (length * 3); j+=6) {
            vertices[i][j+0] = centerPosX - (length/2 * spaceBetween) + (tempJ * spaceBetween); // x
            vertices[i][j+1] = (centerPosY - 20) + (pixels[tempI]/2) * spaceBetween; // y
            vertices[i][j+2] = centerPosZ - (width/2 * spaceBetween) + (i * spaceBetween); // z
            
            vertices[i][j+3] = centerPosX - (length/2 * spaceBetween) + (tempJ * spaceBetween); // x
            vertices[i][j+4] = (centerPosY - 20) + (pixels[tempI+length]/2) * spaceBetween; // y
            vertices[i][j+5] = centerPosZ - (width/2 * spaceBetween) + ((i+1) * spaceBetween); // z
            
            tempI++;
            tempJ++;
        }
        
        // x > centerPosX
        tempJ = 0;
        for (int j = (length * 3); j < (length * 2 * 3); j+=6) {
            vertices[i][j+0] = centerPosX + (tempJ * spaceBetween); // x
            vertices[i][j+1] = (centerPosY - 20) + (pixels[tempI]/2) * spaceBetween; // y
            vertices[i][j+2] = centerPosZ - (width/2 * spaceBetween) + (i * spaceBetween); // z
            
            vertices[i][j+3] = centerPosX + (tempJ * spaceBetween); // x
            vertices[i][j+4] = (centerPosY - 20) + (pixels[tempI+length]/2) * spaceBetween; // y
            vertices[i][j+5] = centerPosZ - (width/2 * spaceBetween) + ((i+1) * spaceBetween); // z
            
            tempI++;
            tempJ++;
        }
    }
    
    // z > centerPosZ
    for (int i = width/2; i < width-1; i++) {
        // x < centerPosX
        tempJ = 0;
        for (int j = 0; j < (length * 3); j+=6) {
            vertices[i][j+0] = centerPosX - (length/2 * spaceBetween) + (tempJ * spaceBetween); // x
            vertices[i][j+1] = (centerPosY - 20) + (pixels[tempI]/2) * spaceBetween; // y
            vertices[i][j+2] = centerPosZ + ((i-width/2) * spaceBetween); // z
            
            vertices[i][j+3] = centerPosX - (length/2 * spaceBetween) + (tempJ * spaceBetween); // x
            vertices[i][j+4] = (centerPosY - 20) + (pixels[tempI+length]/2) * spaceBetween; // y
            vertices[i][j+5] = centerPosZ + (((i-width/2)+1) * spaceBetween); // z
            
            tempI++;
            tempJ++;
        }
        
        // x > centerPosX
        tempJ = 0;
        for (int j = (length * 3); j < (length * 2 * 3); j+=6) {
            vertices[i][j+0] = centerPosX + (tempJ * spaceBetween); // x
            vertices[i][j+1] = (centerPosY - 20) + (pixels[tempI]/2) * spaceBetween; // y
            vertices[i][j+2] = centerPosZ + ((i-width/2) * spaceBetween); // z
            
            vertices[i][j+3] = centerPosX + (tempJ * spaceBetween); // x
            vertices[i][j+4] = (centerPosY - 20) + (pixels[tempI+length]/2) * spaceBetween; // y
            vertices[i][j+5] = centerPosZ + (((i-width/2)+1) * spaceBetween); // z
            
            tempI++;
            tempJ++;
        }
    }

    // Attribute colors to every vertices
    GLfloat colors[width-1][length*2*3];
    tempI = 0;
    for (int i = 0; i < width-1; i++) {
        for(int j = 0; j < length * 2 * 3; j+=6) {
            colors[i][j] = pixels[tempI] * 0.004;
            colors[i][j+1] = pixels[tempI] * 0.004;
            colors[i][j+2] = pixels[tempI] * 0.004;
            
            colors[i][j+3] = pixels[tempI+(length)] * 0.004;
            colors[i][j+4] = pixels[tempI+(length)] * 0.004;
            colors[i][j+5] = pixels[tempI+(length)] * 0.004;
            
            tempI++;
        }
    }
    
    // Draw every vertices on the screen
    for (int i = 0; i < width-1; i++) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices[i]);
        glColorPointer(3, GL_FLOAT, 0, colors[i]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, (length * 2));
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

#endif /* mesh_h */
