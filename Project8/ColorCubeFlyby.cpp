// This program is a flyby around the RGB color cube.  One intersting note
// is that because the cube is a convex polyhedron and it is the only thing
// in the scene, we can render it using backface culling only. i.e., there
// is no need for a depth buffer.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

// The cube has opposite corners at (0,0,0) and (1,1,1), which are black and
// white respectively.  The x-axis is the red gradient, the y-axis is the
// green gradient, and the z-axis is the blue gradient.  The cube's position
// and colors are fixed.

// r to rotate the whole image
// s to stop the animation
// c to continue the animation
// u move scene up
// d to move scene down
// + zoom in
// - zoom out
// add two cubes
// add a plane on the left and right
// make two new cubes bounce between the planes
// g++ -o cube ColorCubeFlyby.cpp -lglut -lGL -lGLU

float angle = 0.0f;
float cube1x = 0.0f;
float cube2x = 0.0f;


namespace Cube {

const int NUM_VERTICES = 8;
const int NUM_FACES = 6;

GLint vertices1[NUM_VERTICES][3] = {
  {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
  {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

GLint faces1[NUM_FACES][4] = {
  {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
  {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

GLfloat vertexColors1[NUM_VERTICES][3] = {
  {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
  {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};

void draw1() {
  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors1[faces1[i][j]]);
      glVertex3iv((GLint*)&vertices1[faces1[i][j]]);
    }
  }
  glEnd();
}

GLint vertices2[NUM_VERTICES][3] = {
  {0, 3, 5}, {0, 3, 6}, {0, 4, 5}, {0, 4, 6},
  {1, 3, 5}, {1, 3, 6}, {1, 4, 5}, {1, 4, 6}};

GLint faces2[NUM_FACES][4] = {
  {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
  {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

GLfloat vertexColors2[NUM_VERTICES][3] = {
  {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0},
  {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}};

void draw2() {
  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors2[faces2[i][j]]);
      glVertex3iv((GLint*)&vertices2[faces2[i][j]]);
    }
  }
  glEnd();
}


GLint vertices3[NUM_VERTICES][3] = {
  {0, -3, -5}, {0, -3, -4}, {0, -2, -5}, {0, -2, -4},
  {1, -3, -5}, {1, -3, -4}, {1, -2, -5}, {1, -2, -4}};

GLint faces3[NUM_FACES][4] = {
  {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
  {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

GLfloat vertexColors3[NUM_VERTICES][3] = {
  {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
  {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}};

void draw3() {
  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors3[faces3[i][j]]);
      glVertex3iv((GLint*)&vertices3[faces3[i][j]]);
    }
  }
  glEnd();
}

}



bool animationRunning = true;
bool forward = true;
float MOVE_SPEED = 0.2f;
GLfloat zoom = 2.0;



void drawVerticalPlanes() {
  // Draw two vertical planes at different positions
    // Set the color for the planes
    glDisable(GL_CULL_FACE);
    glColor3f(0.5f, 0.5f, 0.5f); // Grey color

    // Left plane
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, -10.0f, -10.0f);  // Bottom left
    glVertex3f(-10.0f, -10.0f, 10.0f);  // Bottom Right
    glVertex3f(-10.0f, 10.0f, 10.0f);  // Top right
    glVertex3f(-10.0f, 10.0f, -10.0f);  // Top Left
    glEnd();

    // Right plane
    glColor3f(1.0f, 0.5f, 0.5f); // Grey color
    glBegin(GL_QUADS);
    glVertex3f(10.0f, -10.0f, -10.0f);  // Bottom left
    glVertex3f(10.0f, -10.0f, 10.0f);  // Bottom Right
    glVertex3f(10.0f, 10.0f, 10.0f);  // Top right
    glVertex3f(10.0f, 10.0f, -10.0f);  // Top Left
    glEnd();
    glEnable(GL_CULL_FACE);
}

// Display and Animation. To draw we just clear the window and draw the cube.
// Because our main window is double buffered we have to swap the buffers to
// make the drawing visible. Animation is achieved by successively moving our
// camera and drawing. The function nextAnimationFrame() moves the camera to
// the next point and draws. The way that we get animation in OpenGL is to
// register nextFrame as the idle function; this is done in main().
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glRotatef(angle, 1.0, 1.0, 1.0); // Rotate around z-axis

  Cube::draw1();

  // add the bouncing
  glPushMatrix();
  glTranslatef(cube1x, 0.0f, 0.0f);
  Cube::draw2();
  glPopMatrix();

  // add the bouncing
  glPushMatrix();
  glTranslatef(cube1x, 0.0f, 0.0f);
  Cube::draw3();
  glPopMatrix();


  drawVerticalPlanes();
  glDisable(GL_DEPTH_TEST);
  glFlush();
  glutSwapBuffers();
}

// We'll be flying around the cube by moving the camera along the orbit of the
// curve u->(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2).  We keep the camera looking
// at the center of the cube (0.5, 0.5, 0.5) and vary the up vector to achieve
// a weird tumbling effect.

void timer(int v) {
  static GLfloat u = 0.0;

  if (animationRunning) {
    u += 0.01;
    glLoadIdentity();
    gluLookAt(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2, .5, .5, .5, cos(u), 1, 0);
    glutPostRedisplay();
  }

  if (cube1x > 5.0)
  {
      forward = false;
  }

  if (cube1x < -5.0)
  {
      forward = true;
  }

  if (forward)
  {
      cube1x += MOVE_SPEED;
  }
  else
  {
      cube1x -= MOVE_SPEED;
  }

  cube2x += 0.01;
  glutTimerFunc(1000/60.0, timer, v);
}

// When the window is reshaped we have to recompute the camera settings to
// match the new window shape.  Set the viewport to (0,0)-(w,h).  Set the
// camera to have a 60 degree vertical field of view, aspect ratio w/h, near
// clipping plane distance 0.5 and far clipping plane distance 40.
void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

// Application specific initialization:  The only thing we really need to do
// is enable back face culling because the only thing in the scene is a cube
// which is a convex polyhedron.
void init() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'r':
      // Rotate the whole image
      angle += 5.0;
      break;
    case 's':
      // Stop the animation
      animationRunning = false;
      break;
    case 'c':
      // Continue the animation
      animationRunning = true;
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
    case '-':
        glMatrixMode(GL_PROJECTION);
        glScaled(0.9, 0.9, 0.0); // Zoom out
        glutPostRedisplay();
        break;
    case '+':
        glMatrixMode(GL_PROJECTION);
        glScaled(1.1, 1.1, 1.0); // Zoom in
        glutPostRedisplay();
        break;
    default:
      break;
  }
  glutPostRedisplay();
}

// The usual main for a GLUT application.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("The RGB Color Cube");
  glutReshapeFunc(reshape);
  glutTimerFunc(100, timer, 0);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
}
