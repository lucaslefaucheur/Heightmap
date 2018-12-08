3 FILES 
- main.cpp	
	int main()

- controls.h
	void keyCallback()

- mesh.h
	void DrawMesh()
	vector <GLfloat> loadImage()

----------------------------------------------------------------------------------------

- load an image and stores the intensity of each pixel in a vector 
	vector <GLfloat> pixels

- create a 2D array: one set of vertices per columns containing the x, y, z parameters, linked using GL_TRIANLE_STRIP
x determines the length
y determines the height
z determines the width
	GLfloat vertices[width-1][length * 2 * 3]

- every point is placed relatively to a central position using 4 for loops 
1 for the points with x < 0 and z < 0
1 for the points with x < 0 and z > 0
1 for the points with x > 0 and z < 0
1 for the points with x > 0 and z > 0
	GLfloat centerPosX
	GLfloat centerPosY
	GLfloat centerPosZ

- zoom in/out by increasing/decreasing the initial space between every points
	GLfloat spaceBetween = 2.0

- rotate the mesh by modifying the initial x or y rotation
	GLfloat rotationX = 0.0f
	GLfloat rotationY = 0.0f

----------------------------------------------------------------------------------------

CONTROLS 
- left 	rotate the mesh to left 
- right rotate the mesh to the left
- up 	rotate the mesh up 
- down	rotate the mesh down 
- T	change rendering mode to GL_TRIANGLES
- P	change rendering mode to GL_POINT
- L	change rendering mode to GL_LINES
- scroll up to move into the scene
- scroll down to move out of the scene