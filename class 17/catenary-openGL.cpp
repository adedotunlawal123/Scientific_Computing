#include <cstddef>
using std::size_t;

#include <cassert>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using std::ostream;
using std::endl;
using std::fixed;

#include <vector>
using std::vector;

#include <utility>
using std::pair;
using std::make_pair;

#include <sstream>
using std::stringstream;

#include <algorithm>
using std::min;

#include <cmath>
using std::cosh;
using std::sinh;

#include "catenary.h"

vector< pair<float, float> > coord;

int width, height;
float right = 1.0F;
float top = 1.0F;

float rescale_x(int i) { return right*(-1.0F+2.0F/width*i); }
float rescale_y(int j) { return top*(1.0F-2.0F*top/height*j); }

void glutPrint(float x, float y, const char* text, float r, float g, float b, float a) 
{ 
    if(!text || !strlen(text)) return; 
    bool blending = false; 
    if(glIsEnabled(GL_BLEND)) blending = true; 
    glEnable(GL_BLEND); 
    glColor4f(r,g,b,a); 
    glRasterPos2f(x,y); 
    while (*text) { 
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *text); 
        text++; 
    } 
    if(!blending) glDisable(GL_BLEND); 
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   if (coord.size() != 0)
   {
      glPointSize(5.0); 
      glBegin(GL_POINTS);
      glColor3f(1,0.8,0.5);
      for (auto c : coord)
         glVertex2f(c.first,c.second);
      glEnd();
   }
   glBegin(GL_LINE_STRIP);
   glColor3f(0.2,0.7,0.75);
   for (int i = 0; i < width; i += 4)
   {
      const float x = rescale_x(i);
      glVertex2f(x,catenary(x));
   }
   glEnd();
   glFlush();

   stringstream s;
   s << "Number of measurements: " << fixed << coord.size();
   glutPrint(right*(-1.0F+76.8F/width), top*(-1.0F+76.8F/height),s.str().c_str(), 1.0f, 1.0f, 1.0f, 0.5f);
   glFlush();
   glutSwapBuffers();
}

void mouse(int button, int state, int i, int j)
{
   if (button == GLUT_LEFT_BUTTON) 
      if (state == GLUT_UP)
      {
         const float x = rescale_x(i);
         const float y = rescale_y(j);
         add_measurement(x,y);
         coord.push_back(make_pair(x,y));
      }
}

void keyboard(unsigned char key, int x, int y)
{
   if (key == 'n')
   {
      start_new_data_set();
      coord.resize(0);
   }
   else if (key == 'q')
      exit_gracefully();
}

void changeSize(int w, int h) 
{
   width = w;
   height = h;
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w < h)
   {
      const double ratio = double(h)/double(w);
      right = 1.0F;
      top = ratio;
   }
   else
   {
      const double ratio = double(w)/double(h);
      right = ratio;
      top = 1.0F;
   }
   gluOrtho2D(-right,right,-top,top);
}

const int delay = 0; // milliseconds
void animate(int)
{
   if (coord.size() > 0)
   {
   float chi2 = 0.0;
   float grad_x_0 = 0.0;
   float grad_y_0 = 0.0;
   float grad_a = 0.0;
   for (auto c : coord)
   {
      const float x_i = c.first; 
      const float y_i = c.second;
      const float dx = (x_i-x_0)/a;
      const float C = a*(cosh(dx)-1.0F)+y_0-y_i;
      chi2 += C*C;
      grad_x_0 -= C*sinh(dx);
      grad_y_0 += C;
      grad_a += C*(cosh(dx)-1.0F-dx*sinh(dx));
   }
   x_0 -= 0.01*grad_x_0/coord.size();
   y_0 -= 0.01*grad_y_0/coord.size();
   a -= 0.01*grad_a/coord.size();
   }
   glutPostRedisplay();
   glutTimerFunc(delay,animate,0);
}

int main(int argc, char **argv)
{
   initialize();
   glutInit(&argc,argv);
   glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize (640, 640);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Catenary");
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(delay,animate,0);
   glutReshapeFunc(changeSize);  
   glutMainLoop();
}
