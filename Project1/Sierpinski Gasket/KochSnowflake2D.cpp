///////////////////////////////////////////////////////////////
// KochSnowflake2D.cpp
//
// This program allows the user to visualize
// a snowflake fractal while zooming in.
//
// Interaction:
// Press the up arrow key to increase the number of fractals.
// Press the down arrow key to decrease the number of fractals.
// Press r to reset.
//
// Jonathon Moore.
///////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
static int fractals = 1; // initial fractal level
static float zoom = 1.0f;  // Initial zoom level

void drawKochSegment(float x1, float y1, float x2, float y2, int depth)
{
	// Base Case: depth = 0, If the depth of recursion reaches 0, simply draw a straight line segment from (x1, y1) to (x2, y2).
	if (depth == 0)
	{
		glVertex3f(x1, y1, 0.0); // first endpoint of line
		glVertex3f(x2, y2, 0.0); // second endpoint of line
	}
	else
	{
		// Step 1: Divide the line segment into three equal parts
		float dx = x2 - x1;
		float dy = y2 - y1;
		
		// Coordinates of the first division point (one-third of the way along the segment)
		float x3 = x1 + dx / 3;
		float y3 = y1 + dy / 3;

		// Coordinates of the second division point (two-thirds of the way along the segment)
		float x4 = x1 + 2 * dx / 3;
		float y4 = y1 + 2 * dy / 3;

		// Step 2: Calculate the peak of the equilateral triangle that should replace the middle third
		// The new vertex is at the midpoint of x3 and x4, shifted along the perpendicular bisector
		float mx = (x3 + x4 + sqrt(3) * (y3 - y4)) / 2;
		float my = (y3 + y4 + sqrt(3) * (x4 - x3)) / 2;

		// Step 3: Recursively apply the process to each of the four new line segments
		// Recurse for the segment from the start to the first division point
		drawKochSegment(x1, y1, x3, y3, depth - 1);
		// Recurse for the segment from the first division point to the new vertex (forming one side of the new triangle)
		drawKochSegment(x3, y3, mx, my, depth - 1);
		// Recurse for the segment from the new vertex to the second division point (forming the second side of the new triangle)
		drawKochSegment(mx, my, x4, y4, depth - 1);
		// Recurse for the segment from the second division point to the end of the original segment
		drawKochSegment(x4, y4, x2, y2, depth - 1);
	}
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glScalef(zoom, zoom, 1.0f);

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);

	// Initial triangle
	float x1 = -0.6, y1 = -0.35;
	float x2 = 0.6, y2 = -0.35;
	float x3 = 0.0, y3 = 0.65;

	// draw the segments, with fractals being the depth
	drawKochSegment(x1, y1, x2, y2, fractals);
	drawKochSegment(x2, y2, x3, y3, fractals);
	drawKochSegment(x3, y3, x1, y1, fractals);

	glEnd();

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
		zoom = 1;
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
		zoom *= 1.4;
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
			zoom /= 1.4;
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

	// glutInitContextVersion(4, 3);
	// glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Snowflake 2D");
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
