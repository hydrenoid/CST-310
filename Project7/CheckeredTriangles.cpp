// This application is a trivial illustration of texture mapping.  It draws
// several triangles, each with a texture mapped on to it.  The same texture
// is used for each triangle, but the mappings vary quite a bit so it looks as
// if each triangle has a different texture.


// spin triangles 360 degrees
// p to stop rotation
// c to continue rotation
// u move object up
// d move object down
// l move object left
// r move object right
// + zoom in
// - zoom out
// g++ -o check CheckeredTriangles.cpp -lglut -lGL -lGLU

// Setup variables for rotating the image
float angle = 0.0f;
bool rotating = false;


#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>

// Define a 2 x 2 red and yellow checkered pattern using RGB colors.
#define red {0xff, 0x00, 0x00}
#define yellow {0xff, 0xff, 0x00}
#define magenta {0xff, 0, 0xff}
GLubyte texture[][3] = {
    red, yellow,
    yellow, red,
};

// Fixes up camera and remaps texture when window reshaped.
void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(80, GLfloat(width)/height, 1, 40);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2, -1, 5, 0, 0, 0, 0, 1, 0);
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D,
               0,                    // level 0
               3,                    // use only R, G, and B components
               2, 2,                 // texture has 2x2 texels
               0,                    // no border
               GL_RGB,               // texels are in RGB format
               GL_UNSIGNED_BYTE,     // color components are unsigned bytes
               texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Draws three textured triangles.  Each triangle uses the same texture,
// but the mappings of texture coordinates to vertex coordinates is
// different in each triangle.
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  if (rotating) {
        glMatrixMode(GL_MODELVIEW);
        glRotatef(angle, 0.0, 0.0, 1.0); // Rotate around z-axis
    }

  glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5, 1.0);    glVertex2f(-3, 3);
    glTexCoord2f(0.0, 0.0);    glVertex2f(-3, 0);
    glTexCoord2f(1.0, 0.0);    glVertex2f(0, 0);

    glTexCoord2f(4, 8);        glVertex2f(3, 3);
    glTexCoord2f(0.0, 0.0);    glVertex2f(0, 0);
    glTexCoord2f(8, 0.0);      glVertex2f(3, 0);

    glTexCoord2f(5, 5);        glVertex2f(0, 0);
    glTexCoord2f(0.0, 0.0);    glVertex2f(-1.5, -3);
    glTexCoord2f(4, 0.0);      glVertex2f(1.5, -3);
  glEnd();
  glFlush();
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'c':
        rotating = true;
        glutPostRedisplay();
        break;
    case 'p':
        rotating = false;
        glutPostRedisplay();
        break;
    case 'u':
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(0, 0.1, 0); // Move object up
        glutPostRedisplay();
        break;
    case 'd':
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(0, -0.1, 0); // Move object down
        glutPostRedisplay();
        break;
    case 'l':
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(-0.1, 0, 0); // Move object left
        glutPostRedisplay();
        break;
    case 'r':
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(0.1, 0, 0); // Move object right
        glutPostRedisplay();
        break;
    case '-':
        glMatrixMode(GL_PROJECTION);
        glScaled(0.9, 0.9, 1.0); // Zoom out
        glutPostRedisplay();
        break;
    case '+':
        glMatrixMode(GL_PROJECTION);
        glScaled(1.1, 1.1, 1.0); // Zoom in
        glutPostRedisplay();
        break;
    case 27: // ESC key
        exit(0);
        break;
    default:
        break;
    }
}

void timer(int v) {
    if (rotating) {
        // Calculate the change in angle per frame
        float deltaAngle = 0.5f; // Adjust this value to control the rotation speed

        // Update the angle
        angle += deltaAngle;

        // Ensure the angle stays within the range [0, 360)
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(100, timer, v); // Set up the next timer callback (60 frames per second)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(520, 390);
    glutCreateWindow("Textured Triangles");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyInput);
    glutTimerFunc(100, timer, 0); // Set up the timer function to update every 16 milliseconds (about 60 frames per second)
    glutMainLoop();
    return 0;
}
