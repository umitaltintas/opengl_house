#include "../include/imageloader.h"
#include <GL/glut.h>
#include <stdlib.h>

float _angle = 0.0f;
float x = 0.0f;
float y = 0.0f;
float z = 0.0f;
float ax = 1.0f, ay = 1.0f, az = 1.0f;
float sx = 1.0f, sy = 1.0f, sz = 1.0f;
GLuint _textureRoof;
GLuint _textureSky;
GLuint _textureWindow;
GLuint _textureGrass;
GLuint _textureDoor;
GLuint _textureBrick;
void NormalKeyHandler(unsigned char key, int a, int b) {
  switch (key) {
  case 'q':
  case 'Q':
    _angle += 4;
    if (_angle > 360)
      _angle = 0.0;
    break;
  case 'r':
  case 'R':
    _angle -= 4;
    if (_angle > 360)
      _angle = 0.0;
    break;
  case 'w':
  case 'W':
    sx *= 1.1;
    sy *= 1.1;
    sz *= 1.1;

    break;
  case 's':
  case 'S':
    sx *= 0.9;
    sy *= 0.9;
    sz *= 0.9;

    break;
  case 'x':
  case 'X':
    ax = 1.0f;
    ay = 0.0f;
    az = 0.0f;
    _angle=0.0f;
    break;
  case 'y':
  case 'Y':
    ax = 0.0f;
    ay = 1.0f;
    az = 0.0f;
    _angle=0.0f;

    break;
  case 'Z':
  case 'z':
    ax = 0.0f;
    ay = 0.0f;
    az = 1.0f;
    _angle=0.0f;

    break;
  case 'e':
  case 'E':
    ax = 1.0f;
    ay = 1.0f;
    ay = 1.0f;
    _angle=0.0f;

    break;

  default:
    break;
  }
  glutPostRedisplay();
}
static void resize(int width, int height) {
  const float ar = (float)width / (float)height;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void renderScene(void) {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);

  // Sky
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, _textureSky);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTranslatef(x + 0, y + 0, z + -10);
  glBegin(GL_QUADS);
  glTexCoord3f(0.0, 1.0, 0.1f);
  glVertex3f(-10, 10, 0);
  glTexCoord3f(1.0, 1.0, 0.1f);
  glVertex3f(10, 10, 0);
  glTexCoord3f(1.0, 0.0, 0.1f);
  glVertex3f(10, -10, 0);
  glTexCoord3f(0.0, 0.0, 0.1f);
  glVertex3f(-10, -10, 0);
  glEnd();

  glPopMatrix();

  // Grass
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, _textureGrass);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTranslatef(x + 0, y + 0, z - 6);
  glScalef(sx, sy, sz);

  glRotatef(_angle, ax, ay, az);
  glBegin(GL_QUADS);
  glTexCoord3f(0.0, 70.0, 1);
  glVertex3f(-50, -1.5, 50);
  glTexCoord3f(0.0, 0.0, -1);
  glVertex3f(-50, -1.5, -50);
  glTexCoord3f(70.0, 0.0, -1);
  glVertex3f(50, -1.5, -50);
  glTexCoord3f(70.0, 70.0, 1);
  glVertex3f(50, -1.5, 50);
  glEnd();
  glPopMatrix();

  // Front side
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, _textureBrick);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTranslatef(x + 0, y + 0, z - 6);
  glScalef(sx, sy, sz);

  glRotatef(_angle, ax, ay, az);

  glBegin(GL_QUADS); // Wall
  glTexCoord3f(0.0, 2.0, 0.1f);
  glVertex3f(-2, 0, 1);
  glTexCoord3f(4.0, 2.0, 0.1f);
  glVertex3f(2, 0, 1);
  glTexCoord3f(4.0, 0.0, 0.1f);
  glVertex3f(2, -1.5, 1);
  glTexCoord3f(0.0, 0.0, 0.1f);
  glVertex3f(-2, -1.5, 1);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, _textureRoof);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBegin(GL_QUADS); // Roof
  glTexCoord3f(0.0, 2.0, 0);
  glVertex3f(-2.2f, 0.5, 0);
  glTexCoord3f(4.0, 2.0, 0);
  glVertex3f(2.2f, 0.5, 0);
  glTexCoord3f(4.0, 0.0, 1.25);
  glVertex3f(2.2f, -0.1f, 1.25);
  glTexCoord3f(0.0, 0.0, 1.25);
  glVertex3f(-2.2f, -0.1f, 1.25);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, _textureDoor);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBegin(GL_QUADS); // Door
  glTexCoord3f(0.0, 1.0, 1.0001f);
  glVertex3f(-0.3f, -0.4f, 1.0001f);
  glTexCoord3f(1.0, 1.0, 1.0001f);
  glVertex3f(0.3f, -0.4f, 1.0001f);
  glTexCoord3f(1.0, 0.0, 1.0001f);
  glVertex3f(0.3f, -1.5, 1.0001f);
  glTexCoord3f(0.0, 0.0, 1.0001f);
  glVertex3f(-0.3f, -1.5, 1.0001f);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, _textureWindow);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBegin(GL_QUADS); // Window Left
  glTexCoord3f(0.0, 1.0, 1.0001f);
  glVertex3f(-1.5, -0.3f, 1.0001f);
  glTexCoord3f(1.0, 1.0, 1.0001f);
  glVertex3f(-0.75, -0.3f, 1.0001f);
  glTexCoord3f(1.0, 0.0, 1.0001f);
  glVertex3f(-0.75, -0.8f, 1.0001f);
  glTexCoord3f(0.0, 0.0, 1.0001f);
  glVertex3f(-1.5, -0.8f, 1.0001f);
  glEnd();

  glBegin(GL_QUADS); // Window Right
  glTexCoord3f(0.0, 1.0, 1.0001f);
  glVertex3f(1.5, -0.3f, 1.0001f);
  glTexCoord3f(1.0, 1.0, 1.0001f);
  glVertex3f(0.75, -0.3f, 1.0001f);
  glTexCoord3f(1.0, 0.0, 1.0001f);
  glVertex3f(0.75, -0.8f, 1.0001f);
  glTexCoord3f(0.0, 0.0, 1.0001f);
  glVertex3f(1.5, -0.8f, 1.0001f);
  glEnd();
  glPopMatrix();

  // Back side
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, _textureBrick);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTranslatef(x + 0, y + 0, z - 6);
  glScalef(sx, sy, sz);
  glRotatef(_angle, ax, ay, az);

  glBegin(GL_QUADS); // Wall
  glTexCoord3f(0.0, 2.0, -1);
  glVertex3f(-2, 0, -1);
  glTexCoord3f(4.0, 2.0, -1);
  glVertex3f(2, 0, -1);
  glTexCoord3f(4.0, 0.0, -1);
  glVertex3f(2, -1.5, -1);
  glTexCoord3f(0.0, 0.0, -1);
  glVertex3f(-2, -1.5, -1);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, _textureRoof);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBegin(GL_QUADS); // Roof
  glTexCoord3f(0.0, 2.0, 0);
  glVertex3f(-2.2f, 0.5, 0);
  glTexCoord3f(4.0, 2.0, 0);
  glVertex3f(2.2f, 0.5, 0);
  glTexCoord3f(4.0, 0.0, -1.25);
  glVertex3f(2.2f, -0.1f, -1.25);
  glTexCoord3f(0.0, 0.0, -1.25);
  glVertex3f(-2.2f, -0.1f, -1.25);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, _textureWindow);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBegin(GL_QUADS); // Window Left
  glTexCoord3f(0.0, 1.0f, -1.0001f);
  glVertex3f(-1.5, -0.3f, -1.0001f);
  glTexCoord3f(1.0, 1.0f, -1.0001f);
  glVertex3f(-0.75, -0.3f, -1.0001f);
  glTexCoord3f(1.0, 0.0, -1.0001f);
  glVertex3f(-0.75, -0.8f, -1.0001f);
  glTexCoord3f(0.0, 0.0f, -1.0001f);
  glVertex3f(-1.5, -0.8f, -1.0001f);
  glEnd();

  glBegin(GL_QUADS); // Window Right
  glTexCoord3f(0.0, 1.0, 1.0001f);
  glVertex3f(1.5f, -0.3f, -1.0001f);
  glTexCoord3f(1.0f, 1.0, 1.0001f);
  glVertex3f(0.75f, -0.3f, -1.0001f);
  glTexCoord3f(1.0, 0.0, 1.0001f);
  glVertex3f(0.75f, -0.8f, -1.0001f);
  glTexCoord3f(0.0f, 0.0, 1.0001f);
  glVertex3f(1.5f, -0.8f, -1.0001f);
  glEnd();
  glPopMatrix();
  // Right side
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, _textureBrick);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTranslatef(x + 0, y + 0, z - 6);
  glScalef(sx, sy, sz);
  glRotatef(_angle, ax, ay, az);

  glBegin(GL_QUADS); // Wall
  glTexCoord3f(0.0, 2.0, 1);
  glVertex3f(2, 0, 1);
  glTexCoord3f(2.0, 2.0, -1);
  glVertex3f(2, 0, -1);
  glTexCoord3f(2.0, 0.0, -1);
  glVertex3f(2, -1.5, -1);
  glTexCoord3f(0.0, 0.0, 1);
  glVertex3f(2, -1.5, 1);
  glEnd();

  glBegin(GL_TRIANGLES); // Wall Upper
  glTexCoord3f(0.0, 1.0, 0);
  glVertex3f(2, 0.5, 0);
  glTexCoord3f(1.0, 0.0, 1);
  glVertex3f(2, 0, 1);
  glTexCoord3f(-1.0, 0.0, -1);
  glVertex3f(2, 0, -1);
  glEnd();
  glPopMatrix();

  // Left side
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, _textureBrick);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTranslatef(x + 0, y + 0, z - 6);
  glScalef(sx, sy, sz);

  glRotatef(_angle, ax, ay, az);

  glBegin(GL_QUADS); // Wall
  glTexCoord3f(0.0, 2.0, 1);
  glVertex3f(-2, 0, 1);
  glTexCoord3f(2.0, 2.0, -1);
  glVertex3f(-2, 0, -1);
  glTexCoord3f(2.0, 0.0, -1);
  glVertex3f(-2, -1.5, -1);
  glTexCoord3f(0.0, 0.0, 1);
  glVertex3f(-2, -1.5, 1);
  glEnd();

  glBegin(GL_TRIANGLES); // Wall Upper
  glTexCoord3f(0.0, 1.0, 0);
  glVertex3f(-2, 0.5, 0);
  glTexCoord3f(1.0, 0.0, 1);
  glVertex3f(-2, 0, 1);
  glTexCoord3f(-1.0, 0.0, -1);
  glVertex3f(-2, 0, -1);
  glEnd();

  glPopMatrix();

  glutSwapBuffers();
}

void mySpecialFunc(int key, int a, int b) {
  switch (key) {

  case GLUT_KEY_RIGHT:
    x += 0.3f;
    break;
  case GLUT_KEY_LEFT:
    x -= 0.3f;
    break;
  case GLUT_KEY_UP:
    y += 0.3f;
    break;
  case GLUT_KEY_DOWN:
    y -= 0.3f;
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

GLuint loadTexture(const Image *image) {
  GLuint textureId;
  glGenTextures(1, &textureId);            // Make room for our texture
  glBindTexture(GL_TEXTURE_2D, textureId); // Tell OpenGL which texture to edit
  // Map the image to the texture
  glTexImage2D(GL_TEXTURE_2D,               // Always GL_TEXTURE_2D
               0,                           // 0 for now
               GL_RGB,                      // Format OpenGL uses for image
               image->width, image->height, // Width and height
               0,                           // The border of the image
               GL_RGB, // GL_RGB, because pixels are stored in RGB format
               GL_UNSIGNED_BYTE, // GL_UNSIGNED_BYTE, because pixels are stored
                                 // as unsigned numbers
               image->pixels);   // The actual pixel data
  return textureId;              // Returns the id of the texture
}

void Initialize() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

  Image *image = loadBMP("bricks.bmp");
  _textureBrick = loadTexture(image);
  image = loadBMP("door.bmp");
  _textureDoor = loadTexture(image);
  image = loadBMP("grass.bmp");
  _textureGrass = loadTexture(image);
  image = loadBMP("roof.bmp");
  _textureRoof = loadTexture(image);
  image = loadBMP("window.bmp");
  _textureWindow = loadTexture(image);
  image = loadBMP("sky.bmp");
  _textureSky = loadTexture(image);
  delete image;
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(600, 600);
  glutCreateWindow("3D House");
  glEnable(GL_DEPTH_TEST);

  glutReshapeFunc(resize);
  glutSpecialFunc(mySpecialFunc);
  glutKeyboardFunc(NormalKeyHandler);
  glutDisplayFunc(renderScene);
  Initialize();

  glutMainLoop();

  return 0;
}
