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
using std::cout;
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
using std::cos;
using std::sin;

#include "cannon.h"

#include "mtrand.hpp"
mtrand R;

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

float angle = 0.3;
int hits = 0;
bool falling = false;
const double len = 0.3;
const double a = 0.08*len;
const double b = 0.75*len;

double v = 0.0;
const double vmax = 3.0;

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// velocity bar

   const double edge1 = right*(-1.0F+50.8F/width);
   //const double edge2 = top*(-1.0F+115.F/height);
   glBegin(GL_POLYGON);
      glColor3f(0.9,0.05,0.05);
      const double bar_height = (1.9-2*len)*min(vmax,v)/vmax-0.95+len;
      glVertex2f(edge1+0.1,bar_height);
      glVertex2f(edge1,bar_height);
      glVertex2f(edge1,-0.95+len);
      glVertex2f(edge1+0.1,-0.95+len);
   glEnd();
   glBegin(GL_LINE_LOOP);
      glColor3f(1.0,1.0,1.0);
      glVertex2f(edge1+0.1,0.95-len);
      glVertex2f(edge1,0.95-len);
      glVertex2f(edge1,-0.95+len);
      glVertex2f(edge1+0.1,-0.95+len);
   glEnd();
   const double s = sin(angle);
   const double c = cos(angle);

   // cannon_ball
   glBegin(GL_POLYGON);
   glColor3f(0.55,0.55,0.6);
   if (!fire)
   {
      cannon_ball.x = -right+(b+0.1*a)*c;
      cannon_ball.y = -top+(b+0.1*a)*s;
   }
   for (int i = 0; i < 360; ++i)
      glVertex2f(cannon_ball.x + cannon_ball.radius*cos(i*1.5707963267949/90), cannon_ball.y + cannon_ball.radius*sin(i*1.5707963267949/90) );
   glEnd();

   // dropped_ball
   glBegin(GL_POLYGON);
   glColor3f(0.3,0.5,0.9);
   for (int i = 0; i < 360; ++i)
      glVertex2f(dropped_ball.x + dropped_ball.radius*cos(i*1.5707963267949/90), dropped_ball.y + dropped_ball.radius*sin(i*1.5707963267949/90) );
   glEnd();

   // cannon
   glBegin(GL_POLYGON);
   glColor3f(0.35,0.35,0.4);
   glVertex2f(-right-a*c+a*s,-top-a*c-a*s);
   glVertex2f(-right+b*c+a*s,-top-a*c+b*s);
   glVertex2f(-right+b*c-a*s,-top+a*c+b*s);
   glVertex2f(-right-a*c-a*s,-top+a*c-a*s);
   glEnd();

   stringstream ss;
   ss << "Hits: " << hits;
   glutPrint(right*(-1.0F+76.8F/width), top*(1.0F-76.8F/height),ss.str().c_str(), 1.0f, 1.0f, 1.0f, 0.5f);
      
   glFlush();
   glutSwapBuffers();
}

bool moving = false;
int startj;

bool is_button_down;

void mouse(int button, int state, int i, int j)
{
   if (button == GLUT_LEFT_BUTTON)
   {
      if (state == GLUT_UP)
      {
         is_button_down = false;
         if (!fire)
         {
            fire = true;
            cannon_ball.vx = cos(angle)*v;
            cannon_ball.vy = sin(angle)*v;
         }
      }
      else if (state == GLUT_DOWN)
      {
         is_button_down = true;
         moving = true;
         startj = j;
      }
   }
}

void motion(int i, int j)
{
   if (moving)
   {
      angle += 0.01*(startj-j);
      if (angle < 0.0) angle = 0.0;
      else if (angle > 1.5707963267949) angle = 1.5707963267949;
      startj = j;
   }
   glutPostRedisplay();
}

void keyboard(unsigned char key, int i, int j)
{
   if (key == 'n')
      initialize(a);
   if (key == 'q')
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

const int delay = 1; // milliseconds
void animate(int)
{
   if (!fire and is_button_down)
   {
      v += 0.5*dt;
      if (v > vmax) v = vmax;
   }
   if (fire)
   {
      if (cannon_ball.y < -top-2*cannon_ball.radius 
       or cannon_ball.y > top+2*cannon_ball.radius 
       or cannon_ball.x > right+2*cannon_ball.radius 
       or cannon_ball.x < -right-2*cannon_ball.radius) 
      {
         fire = false;
         v = 0.0;
      }
   }
   if (!falling)
   {
      if (R() < 0.6)
      {
         dropped_ball.x = right*(R()-0.75);
         dropped_ball.y = top+dropped_ball.radius;
         dropped_ball.vx = 0.1*R();
         dropped_ball.vy = 0.0;
      }
      else
      {
         dropped_ball.x = right+dropped_ball.radius;
         dropped_ball.y = top*R();
         dropped_ball.vx = -0.35*R();
         dropped_ball.vy = 0.1*(R()-0.05);      
      }
      falling = true;
   }
   else if (dropped_ball.y < -top-2*dropped_ball.radius 
         or dropped_ball.y > top+3*dropped_ball.radius 
         or dropped_ball.x > right+2*dropped_ball.radius 
         or dropped_ball.x < -right-2*dropped_ball.radius) 
      falling = false;

   update();

   if (collision) { ++hits; collision = false; }
   
   glutPostRedisplay();
   glutTimerFunc(delay,animate,0);
}

int main(int argc, char **argv)
{
   initialize(a);
   glutInit(&argc,argv);
   glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize (640, 640);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Cannon");
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);   
   glutKeyboardFunc(keyboard);
   glutTimerFunc(delay,animate,0);
   glutReshapeFunc(changeSize);   
   glutMainLoop();
}
