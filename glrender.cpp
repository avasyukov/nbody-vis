#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#include "GLBall.hpp"
#include "NBodyScene.hpp"

// Global var, not nice,
NBodyScene* sceneToRender;

// Will be provided in separate source,
// not nice, but allows to create separate debug main without GL
NBodyScene* getScene();

static void animateScene()
{
    sceneToRender->doTimeStep();
    glutPostRedisplay();
}

static void cleanupScene()
{
    delete sceneToRender;
    // TODO: cleanup GL and GLUT resources as well
}

static void reshapeScene(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / height, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

static void renderBall(const GLBall& b) {
    double r = b.getR();
    double cx = b.getX();
    double cy = b.getY();
    glColor3f(1.0, 1.0, 0.0);

    int num_segments = 20;
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)   {
        double theta = 2 * M_PI * float(ii) / float(num_segments);
        double x = r * cosf(theta);
        double y = r * sinf(theta);
        glVertex2d(x + cx, y + cy);
    }
    glEnd();
}

static void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    for(unsigned int i = 0; i < sceneToRender->getNumberOfBodies(); ++i)
        renderBall(sceneToRender->getBody(i));

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("N body problem");

    sceneToRender = getScene();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshapeScene);
    glutIdleFunc(animateScene);
    glutCloseFunc(&cleanupScene);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutMainLoop();

    return 0;
}