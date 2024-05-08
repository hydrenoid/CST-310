///////////////////////////////////////////////////////////////
// 3DGasket.cpp
//
// This program allows the user to visualize
// sierpinski's gasket in 3D.
//
// Interaction:
// Press the up arrow key to increase the number of fractals.
// Press the down arrow key to decrease the number of fractals.
// Press space bar to rotate object.
// Press r to reset.
//
// Jonathon Moore.
///////////////////////////////////////////////////////////////

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
static int fractals = 1; // Holds value for number of fractals.
static float Angle = 0.0; // Angle to rotate the sphere.

// Function to draw a tetrahedron given four vertices
void drawTetrahedron(float* a, float* b, float* c, float* d)
{
	glEnable(GL_DEPTH_TEST); // Make sure to enable the depth test otherwise it will not display correctly.
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(d);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3fv(a);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
	glDisable(GL_DEPTH_TEST);
}

// Function to divide the tetrahedron
void divideTetrahedron(float* a, float* b, float* c, float* d, int m)
{
	// Base case: if m is zero, draw the tetrahedron using the vertices.
	if (m > 0)
	{
		// Initialize midpoint vertices for the next level of tetrahedron.
		float v0[3], v1[3], v2[3], v3[3], v4[3], v5[3];
		// Midpoints for all edges of the tetrahedron
		for (int i = 0; i < 3; i++)
		{
			v0[i] = (a[i] + b[i]) / 2;
			v1[i] = (a[i] + c[i]) / 2;
			v2[i] = (a[i] + d[i]) / 2;
			v3[i] = (b[i] + c[i]) / 2;
			v4[i] = (b[i] + d[i]) / 2;
			v5[i] = (c[i] + d[i]) / 2;
		}

		// Recursively divide into smaller tetrahedra
		divideTetrahedron(a, v0, v1, v2, m - 1);
		divideTetrahedron(v0, b, v3, v4, m - 1);
		divideTetrahedron(v1, v3, c, v5, m - 1);
		divideTetrahedron(v2, v4, v5, d, m - 1);
	}
	else
	{
		// Draw the tetrahedron using given vertices when no further subdivision is needed
		drawTetrahedron(a, b, c, d);
	}
}

// Drawing routine.
void drawScene(void)
{

	float vertices[4][3] =
	{
		{0.0, 1.0, 0.0},  // Top vertex
		{-1.0, -0.5, -0.5},  // Bottom left vertex
		{1.0, -0.5, -0.5},  // Bottom right vertex
		{0.0, -0.5, 1.0}  // Front vertex
	};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotatef(Angle, 1.0, 1.0, 0.5);

	divideTetrahedron(vertices[0], vertices[1], vertices[2], vertices[3], fractals); // first call to initiate recursive calls where n = fractals

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

	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
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
		Angle = 0;
		glutPostRedisplay();
		break;
	case ' ':
		Angle += 10.0;
		if (Angle > 360.0)
		{
			Angle -= 360.0;
		}
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
		<< "Press the space bar to rotate the fractal." << std::endl
		<< "Press r to reset." << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);

	// glutInitContextVersion(4, 3);
	// glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Triangles 3-D");
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
