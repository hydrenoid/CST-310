///////////////////////////////////////////////////////////////
// Livingroom.cpp
//
// This program is for project4 where we will be modeling the given
// scene (my livingroom).
//
// Interaction:
// Use w,a,s,d to rotate the screne.
// Press r to reset.
//
// COMPILE: g++ -o Livingroom Livingroom.cpp -lGLEW -lGL -lGLU -lglut
//
// RUN: ./Livingroom
//
// Jonathon Moore.
///////////////////////////////////////////////////////////////

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>

#define PI 3.14159265358979323846

// Globals
static float HorizontalAngle = 340.0; // Horizontal rotation angle (left/right)
static float VerticalAngle = 20.0;   // Vertical rotation angle (up/down)


// Function to create a rectangular prism with given dimensions and position
void drawRectangularPrism(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat depth) {
    // Enable depth
    glEnable(GL_DEPTH_TEST);

    // Calculate half dimensions for centering the prism at (x, y, z)
    GLfloat halfWidth = width / 2.0f;
    GLfloat halfHeight = height / 2.0f;
    GLfloat halfDepth = depth / 2.0f;

    glBegin(GL_QUADS);  // Start drawing the prism using quads

    // Front face
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x - halfWidth, y - halfHeight, z + halfDepth);
    glVertex3f(x + halfWidth, y - halfHeight, z + halfDepth);
    glVertex3f(x + halfWidth, y + halfHeight, z + halfDepth);
    glVertex3f(x - halfWidth, y + halfHeight, z + halfDepth);

    // Back face
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(x - halfWidth, y - halfHeight, z - halfDepth);
    glVertex3f(x + halfWidth, y - halfHeight, z - halfDepth);
    glVertex3f(x + halfWidth, y + halfHeight, z - halfDepth);
    glVertex3f(x - halfWidth, y + halfHeight, z - halfDepth);

    // Top face
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(x - halfWidth, y + halfHeight, z - halfDepth);
    glVertex3f(x + halfWidth, y + halfHeight, z - halfDepth);
    glVertex3f(x + halfWidth, y + halfHeight, z + halfDepth);
    glVertex3f(x - halfWidth, y + halfHeight, z + halfDepth);

    // Bottom face
    glColor3f(0.0, 0.5, 1.0);
    glVertex3f(x - halfWidth, y - halfHeight, z - halfDepth);
    glVertex3f(x + halfWidth, y - halfHeight, z - halfDepth);
    glVertex3f(x + halfWidth, y - halfHeight, z + halfDepth);
    glVertex3f(x - halfWidth, y - halfHeight, z + halfDepth);

    // Right face
    glColor3f(0.5, 0.0, 1.0);
    glVertex3f(x + halfWidth, y - halfHeight, z - halfDepth);
    glVertex3f(x + halfWidth, y - halfHeight, z + halfDepth);
    glVertex3f(x + halfWidth, y + halfHeight, z + halfDepth);
    glVertex3f(x + halfWidth, y + halfHeight, z - halfDepth);

    // Left face
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(x - halfWidth, y - halfHeight, z - halfDepth);
    glVertex3f(x - halfWidth, y - halfHeight, z + halfDepth);
    glVertex3f(x - halfWidth, y + halfHeight, z + halfDepth);
    glVertex3f(x - halfWidth, y + halfHeight, z - halfDepth);

    glEnd();  // End drawing the prism
    glDisable(GL_DEPTH_TEST);   // Disable depth drawing
}


// Function to draw a cylinder at a specified position
void drawStraightCylinder(float x, float y, float z, float radius, float height, int slices) {
    glPushMatrix(); // Save the current transformation matrix

    // Move the cylinder to its designated location
    glTranslatef(x, y, z);

    // Enable depth
    glEnable(GL_DEPTH_TEST);

    // Top circle
    // Set the color
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, height);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 0.0);
    for (int i = 0; i <= slices; i++) {
        float angle = 2 * PI * i / slices;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0.0);
    }
    glEnd();
    glPopMatrix();

    // Bottom circle
    glColor3f(0.0, 1.0, 1.0);
    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 0.0);
    for (int i = 0; i <= slices; i++) {
        float angle = 2 * PI * i / slices;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0.0);
    }
    glEnd();
    glPopMatrix();

    // Cylinder's side
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = 2 * PI * i / slices;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, height);
        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0.0);
    }
    glDisable(GL_DEPTH_TEST);   // Disable depth drawing
    glEnd();

    glPopMatrix(); // Restore the original transformation matrix

}


// Function to draw a cylinder at a specified position
void drawHorizontalCylinder(float x, float y, float z, float radius, float height, int slices) {
    glPushMatrix(); // Save the current transformation matrix

    // Move the cylinder to its designated location
    glTranslatef(x, y, z);

    // Rotate the cylinder to make it horizontal (90 degrees around the x-axis)
    glRotatef(90, 0.0, 1.0, 0.0);

    // Enable depth
    glEnable(GL_DEPTH_TEST);

    // Top circle
    // Set the color
    glColor3f(0.5, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, height);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 0.0);
    for (int i = 0; i <= slices; i++) {
        float angle = 2 * PI * i / slices;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0.0);
    }
    glEnd();
    glPopMatrix();

    // Bottom circle
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 0.0);
    for (int i = 0; i <= slices; i++) {
        float angle = 2 * PI * i / slices;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0.0);
    }
    glEnd();
    glPopMatrix();

    // Cylinder's side
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = 2 * PI * i / slices;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, height);
        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0.0);
    }
    glDisable(GL_DEPTH_TEST);   // Disable depth drawing
    glEnd();

    glPopMatrix(); // Restore the original transformation matrix

}


// Function to draw a cylinder at a specified position
void drawVerticalCylinder(float x, float y, float z, float radius, float height, int slices) {
    glPushMatrix(); // Save the current transformation matrix

    // Move the cylinder to its designated location
    glTranslatef(x, y, z);

    // Rotate the cylinder to make it horizontal (90 degrees around the x-axis)
    glRotatef(90, 1.0, 0.0, 0.0);

    // Enable depth
    glEnable(GL_DEPTH_TEST);

    // Top circle
    // Set the color
    glColor3f(0.5, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, height);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 0.0);
    for (int i = 0; i <= slices; i++) {
        float angle = 2 * PI * i / slices;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0.0);
    }
    glEnd();
    glPopMatrix();

    // Bottom circle
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 0.0);
    for (int i = 0; i <= slices; i++) {
        float angle = 2 * PI * i / slices;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0.0);
    }
    glEnd();
    glPopMatrix();

    // Cylinder's side
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = 2 * PI * i / slices;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, height);
        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0.0);
    }
    glDisable(GL_DEPTH_TEST);   // Disable depth drawing
    glEnd();

    glPopMatrix(); // Restore the original transformation matrix

}


void drawHemisphere(float x, float y, float z, float radius, int slices, int stacks) {
    // Enable depth
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
    glTranslatef(x, y, z);  // Move the sphere to the desired location

    // Rotate to make the flat part on top
    glRotatef(270.0, 1.0, 0.0, 0.0);

    for (int i = 0; i < stacks / 2; i++) { // Iterate only over half the stacks for a hemisphere
        float lat0 = PI * (-0.5 + (float) i / stacks);
        float z0  = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = PI * (-0.5 + (float) (i+1) / stacks);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= slices; j++) {
            float lng = 2 * PI * (float) j / slices;
            float x = cos(lng);
            float y = sin(lng);

            glColor3f(0.0, 0.0, 1.0); // Color can be adjusted or made a parameter
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0 * radius, y * zr0 * radius, z0 * radius);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1 * radius, y * zr1 * radius, z1 * radius);
        }
        glEnd();
    }

    glPopMatrix();
    glDisable(GL_DEPTH_TEST);
}


// Drawing routine
void drawScene(void)
{
    // Clear the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the TV
    float TV_X = 20.0;
    float TV_Y = 37.5;
    float TV_Z = -52.5;
    drawRectangularPrism(TV_X, TV_Y, TV_Z, 60.0, 25.0, 5.0); // Screen
    drawRectangularPrism(TV_X + 10, TV_Y - 15, TV_Z, 2.0, 5.0, 2.0); // Left leg
    drawRectangularPrism(TV_X - 10, TV_Y - 15, TV_Z, 2.0, 5.0, 2.0); // Right leg

    // Draw the entertainment center
    float EC_X = 10.0;
    float EC_Y = 19.0;
    float EC_Z = -50.0;

    drawRectangularPrism(EC_X, EC_Y, EC_Z, 80.0, 3.0, 20.0); // top plate
    drawRectangularPrism(EC_X, EC_Y - 25, EC_Z, 80.0, 3.0, 20.0); // bottom plate
    drawRectangularPrism(EC_X, EC_Y - 12.5, EC_Z - 10, 80.0, 28.0, 3.0); // back plate
    drawRectangularPrism(EC_X - 30, EC_Y - 12.5, EC_Z, 20.0, 25.0, 20.0); // left cupboard
    drawRectangularPrism(EC_X + 30, EC_Y - 12.5, EC_Z, 20.0, 25.0, 20.0); // left cupboard
    drawRectangularPrism(EC_X, EC_Y - 12.5, EC_Z, 80.0, 3.0, 20.0); // middle plate

    // Draw the coffee table
    float CT_X = 10.0;
    float CT_Y = 9.0;
    float CT_Z = 5.0;

    drawRectangularPrism(CT_X, CT_Y, CT_Z, 70.0, 7.0, 30.0); // top plate
    drawRectangularPrism(CT_X - 32.5, CT_Y - 6.5, CT_Z + 12.5, 5.0, 20.0, 5.0); // front left leg
    drawRectangularPrism(CT_X + 32.5, CT_Y - 6.5, CT_Z + 12.5, 5.0, 20.0, 5.0); // front right leg
    drawRectangularPrism(CT_X - 32.5, CT_Y - 6.5, CT_Z - 12.5, 5.0, 20.0, 5.0); // back left leg
    drawRectangularPrism(CT_X + 32.5, CT_Y - 6.5, CT_Z - 12.5, 5.0, 20.0, 5.0); // back right leg
    drawRectangularPrism(CT_X, CT_Y - 13, CT_Z, 70.0, 2.0, 30.0); // bottom plate

    // Draw the endtable
    float ET_X = -60.0;
    float ET_Y = 13.0;
    float ET_Z = 70.0;

    drawRectangularPrism(ET_X, ET_Y, ET_Z, 30.0, 3.0, 30.0); // top plate
    drawRectangularPrism(ET_X - 14, ET_Y - 8.5, ET_Z + 13, 2.0, 20.0, 4.0); // front left leg
    drawRectangularPrism(ET_X + 14, ET_Y - 8.5, ET_Z + 13, 2.0, 20.0, 4.0); // front right leg
    drawRectangularPrism(ET_X - 14, ET_Y - 8.5, ET_Z - 13, 2.0, 20.0, 4.0); // back left leg
    drawRectangularPrism(ET_X + 14, ET_Y - 8.5, ET_Z - 13, 2.0, 20.0, 4.0); // back right leg
    drawRectangularPrism(ET_X, ET_Y - 19, ET_Z + 13, 30.0, 2.0, 4.0); // front bottom leg plate
    drawRectangularPrism(ET_X, ET_Y - 19, ET_Z - 13, 30.0, 2.0, 4.0); // back bottom leg plate

    // Draw the chair
    float CH_X = 90.0;
    float CH_Y = 21.0;
    float CH_Z = 0.0;

    drawRectangularPrism(CH_X, CH_Y, CH_Z, 2.0, 30.0, 20.0); // back rest
    drawRectangularPrism(CH_X - 9, CH_Y - 14, CH_Z, 20.0, 2.0, 20.0); // sitting plate
    drawRectangularPrism(CH_X - 18, CH_Y - 21, CH_Z + 9, 2.0, 15.0, 2.0); // front left leg
    drawRectangularPrism(CH_X, CH_Y - 21, CH_Z + 9, 2.0, 15.0, 2.0); // front right leg
    drawRectangularPrism(CH_X - 18, CH_Y - 21, CH_Z - 9, 2.0, 15.0, 2.0); // back left leg
    drawRectangularPrism(CH_X, CH_Y - 21, CH_Z - 9, 2.0, 15.0, 2.0); // back right leg

    // Draw the left couch
    float LC_X = -60.0;
    float LC_Y = 0.0;
    float LC_Z = 10.0;

    drawRectangularPrism(LC_X, LC_Y, LC_Z, 40.0, 15.0, 60.0); // sitting plate
    drawRectangularPrism(LC_X - 15, LC_Y + 20, LC_Z, 10.0, 25.0, 60.0); // back plate
    drawStraightCylinder(LC_X - 15.0, LC_Y + 32, LC_Z - 30.0, 8.0, 60.0, 48); // back plate cushion
    drawHorizontalCylinder(LC_X - 10.0, LC_Y + 10, LC_Z + 30, 8.0, 30.0, 48); // front arm rest cushion
    drawHorizontalCylinder(LC_X - 10.0, LC_Y + 10, LC_Z - 30, 8.0, 30.0, 48); // back arm rest cushion

    // Draw the front couch
    float FC_X = 15.0;
    float FC_Y = 0.0;
    float FC_Z = 70.0;

    drawRectangularPrism(FC_X, FC_Y, FC_Z, 80.0, 15.0, 40.0); // sitting plate
    drawRectangularPrism(FC_X, FC_Y + 20, FC_Z + 15, 80.0, 25.0, 10.0); // back plate
    drawHorizontalCylinder(FC_X - 40.0, FC_Y + 32, FC_Z + 15.0, 8.0, 80.0, 48); // back plate cushion
    drawStraightCylinder(FC_X - 40.0, FC_Y + 10, FC_Z - 20.0, 8.0, 30.0, 48); // left arm rest cushion
    drawStraightCylinder(FC_X + 40.0, FC_Y + 10, FC_Z - 20.0, 8.0, 30.0, 48); // right arm rest cushion

    // Draw the ceiling fan
    float CF_X = 0.0;
    float CF_Y = 150.0;
    float CF_Z = 0.0;

    drawHemisphere(CF_X, CF_Y, CF_Z, 20.0, 50, 50); // top connector sphere
    drawRectangularPrism(CF_X, CF_Y - 25, CF_Z, 2.0, 10.0, 2.0); // connector to bottom sphere
    drawHemisphere(CF_X, CF_Y - 30, CF_Z, 15.0, 50, 50); // bottom hemisphere for light
    drawRectangularPrism(CF_X + 20, CF_Y - 25, CF_Z, 40.0, 2.0, 10.0); // right fan blade
    drawRectangularPrism(CF_X - 20, CF_Y - 25, CF_Z, 40.0, 2.0, 10.0); // left fan blade

    // Draw the endtable binder
    float EB_X = -60.0;
    float EB_Y = 15.0;
    float EB_Z = 70.0;

    drawRectangularPrism(EB_X, EB_Y, EB_Z, 10.0, 3.0, 15.0); // body
    drawStraightCylinder(EB_X - 5, EB_Y, EB_Z - 7.5, 2.0, 15.0, 24); // spine

    // Draw the coffee table binder
    float CB_X = 0.0;
    float CB_Y = 13.0;
    float CB_Z = 0.0;

    drawRectangularPrism(CB_X, CB_Y, CB_Z, 10.0, 3.0, 15.0); // body
    drawStraightCylinder(CB_X - 5, CB_Y, CB_Z - 7.5, 2.0, 15.0, 24); // spine

    // Draw the switch
    float SW_X = -20.0;
    float SW_Y = 28.0;
    float SW_Z = -55.0;

    drawRectangularPrism(SW_X, SW_Y, SW_Z, 20.0, 15.0, 2.0); // body
    drawVerticalCylinder(SW_X - 8.5, SW_Y + 7.5, SW_Z, 2.5, 15.0, 24); // left controller
    drawVerticalCylinder(SW_X + 8.5, SW_Y + 7.5, SW_Z, 2.5, 15.0, 24); // right controller

    // Draw the modem
    float MD_X = -14.0;
    float MD_Y = 35.0;
    float MD_Z = -47.5;

    drawVerticalCylinder(MD_X, MD_Y, MD_Z, 5, 15.0, 24); // body

    // Apply rotations
    glLoadIdentity();
    glRotatef(VerticalAngle, 1.0, 0.0, 0.0);   // Rotate up/down along the x-axis
    glRotatef(HorizontalAngle, 0.0, 1.0, 0.0);

    // Swap screen with buffer
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

    // Set the size of the scene
	glOrtho(-200.0, 200.0, -200.0, 200.0, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r':
        HorizontalAngle = 340.0;
        VerticalAngle = 20.0;
        glutPostRedisplay();
        break;
    case 'a':
        HorizontalAngle -= 5.0; // Rotate left
        if (HorizontalAngle < 0.0) HorizontalAngle += 360.0;
        glutPostRedisplay();
        break;
    case 'd':
        HorizontalAngle += 5.0; // Rotate right
        if (HorizontalAngle > 360.0) HorizontalAngle -= 360.0;
        glutPostRedisplay();
        break;
    case 'w':
        VerticalAngle += 5.0; // Rotate up
        if (VerticalAngle > 360.0) VerticalAngle -= 360.0;
        glutPostRedisplay();
        break;
    case 's':
        VerticalAngle -= 5.0; // Rotate down
        if (VerticalAngle < 0.0) VerticalAngle += 360.0;
        glutPostRedisplay();
        break;
    case 27: // ESC key
        exit(0);
        break;
    default:
        break;
    }
}


// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Use w,a,s,d to rotate the scene." << std::endl;
	std::cout << "Press r to reset." << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Livingroom");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);


	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
