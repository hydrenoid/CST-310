///////////////////////////////////////////////////////////////
// 2DGasket.cpp
//
// This program allows the user to visualize
// sierpinski's gasket in 2D.
//
// Interaction:
// Press the up arrow key to increase the number of fractals.
// Press the down arrow key to decrease the number of fractals.
// Press r to reset.
//
// Jonathon Moore.
///////////////////////////////////////////////////////////////

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
static int fractals = 1;

// Draws a triangle on screen with the three given vertices.
void drawTriangle(float* a, float* b, float* c)
{
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2fv(a);
	glVertex2fv(b);
	glVertex2fv(c);
	glEnd();
}

void divideTriangle(float* a, float* b, float* c, int m)
{
	// Base case: if m is zero, draw the triangle using the vertices a, b, and c.
	if (m > 0)
	{
		// Initialize midpoint vertices for the next level of triangles.
		float v0[2], v1[2], v2[2];

		// Calculate midpoints between vertices a-b, a-c, and b-c.
		for (int i = 0; i < 2; i++)
		{
			v0[i] = (a[i] + b[i]) / 2; // v0 is the midpoint between a and b
			v1[i] = (a[i] + c[i]) / 2; // v1 is the midpoint between a and c
			v2[i] = (b[i] + c[i]) / 2; // v2 is the midpoint between b and c
		}
		// Recursively divide the triangle formed by vertices a, v0, and v1
		divideTriangle(a, v0, v1, m - 1);
		// Recursively divide the triangle formed by vertices c, v1, and v2
		divideTriangle(c, v1, v2, m - 1);
		// Recursively divide the triangle formed by vertices b, v2, and v0
		divideTriangle(b, v2, v0, m - 1);
	}
	else
	{
		// Draw the triangle using vertices a, b, and c when no further subdivision is needed
		drawTriangle(a, b, c);
	}
}

// Drawing routine.
void drawScene(void)
{
	float vertices[3][2] = { {-1.0, -1.0}, {0.0, 1.0}, {1.0, -1.0} }; // set initial vertices to bottom left, top middle, and bottom left
	glClear(GL_COLOR_BUFFER_BIT);

	divideTriangle(vertices[0], vertices[1], vertices[2], fractals);  // first call to initiate recursive calls where n = fractals

	glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r': // reset to original number of fractals.
		fractals = 1;
		glutPostRedisplay();
		break;
	case 27: // escape will leave the program
		exit(0);
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		fractals += 1; // increase number of fractals by 1
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (fractals == 0)
		{
			fractals = 0; // if fractals is zero do not decrease it
		}
		else
		{
			fractals -= 1; // decrease number of fractals by 1
		}
	}
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press the up arrow key to increase number of fractals." << std::endl
		<< "Press the down arrow key to decrease number of fractals." << std::endl
		<< "Press r to reset." << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Triangles 2-D");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	// Register the callback function for non-ASCII key entry.
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
