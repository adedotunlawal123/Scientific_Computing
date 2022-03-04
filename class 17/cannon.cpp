#include <cassert>

#include <cstddef>
using std::size_t;

#include <cstdlib>
using std::exit;

#include <cmath>
using std::sqrt;
using std::fabs;

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

#include "cannon.h"

ball_t cannon_ball;
ball_t dropped_ball;

bool fire;
bool collision;

void initialize(double R)
{
   fire = false;
   collision = false;

   cannon_ball.radius = R;
   cannon_ball.mass = 1.0;

   dropped_ball.radius = 5.0*R;
   dropped_ball.mass = 1.5;
}

const double dt = 0.02;
const double g = 0.1;

void advance(ball_t &B, double t)
{
   B.x += t*B.vx;
   B.y += t*B.vy - 0.5*g*t*t;
   B.vy -= g*t;
}

void verify(void)
{
   // check that the balls are indeed touching
   const double dx = cannon_ball.x - dropped_ball.x;
   const double dy = cannon_ball.y - dropped_ball.y;
   const double sep = sqrt(dx*dx+dy*dy);
   const double R = cannon_ball.radius + dropped_ball.radius;
   assert(fabs(sep-R) < 1E-6);
}

void elastic_scatter()
{
   const double dx = cannon_ball.x - dropped_ball.x;
   const double dy = cannon_ball.y - dropped_ball.y;
   const double R = cannon_ball.radius + dropped_ball.radius;
   const double M = cannon_ball.mass + dropped_ball.mass;
   const double c = dx/R;
   const double s = dy/R;

   const double cb_u = c*cannon_ball.vx + s*cannon_ball.vy;
   const double cb_w = -s*cannon_ball.vx + c*cannon_ball.vy;
   const double db_u = c*dropped_ball.vx + s*dropped_ball.vy;
   const double db_w = -s*dropped_ball.vx + c*dropped_ball.vy;

   const double cb_uprime = (cb_u*(cannon_ball.mass-dropped_ball.mass) + 2.0*dropped_ball.mass*db_u)/M;
   const double db_uprime = (db_u*(dropped_ball.mass-cannon_ball.mass) + 2.0*cannon_ball.mass*cb_u)/M;

   cannon_ball.vx = c*cb_uprime - s*cb_w;
   cannon_ball.vy = s*cb_uprime + c*cb_w;
   dropped_ball.vx = c*db_uprime - s*db_w;
   dropped_ball.vy = s*db_uprime + c*db_w;   
}

void inelastic_scatter()
{
   const double M = cannon_ball.mass + dropped_ball.mass;
   const double vx = (cannon_ball.mass*cannon_ball.vx + dropped_ball.mass*dropped_ball.vx) / M;
   const double vy = (cannon_ball.mass*cannon_ball.vy + dropped_ball.mass*dropped_ball.vy) / M;
   
   cannon_ball.vx = vx;
   cannon_ball.vy = vy;

   dropped_ball.vx = vx;
   dropped_ball.vy = vy;
}

double energy(void)
{
   return 0.5*(  cannon_ball.mass*(cannon_ball.vx*cannon_ball.vx + cannon_ball.vy*cannon_ball.vy)
            + dropped_ball.mass*(dropped_ball.vx*dropped_ball.vx + dropped_ball.vy*dropped_ball.vy) );
}

bool in_time_step(double t) { return 0.0 < t and t < dt; }

void update(void)
{
   const double dx = cannon_ball.x - dropped_ball.x;
   const double dy = cannon_ball.y - dropped_ball.y;
   const double dvx = cannon_ball.vx - dropped_ball.vx;
   const double dvy = cannon_ball.vy - dropped_ball.vy;
   const double R = cannon_ball.radius + dropped_ball.radius;
   
   const double drdv = dx*dvx + dy*dvy;
   const double dr2 = dx*dx + dy*dy;
   const double dv2 = dvx*dvx + dvy*dvy;
   
   const double radical = sqrt(drdv*drdv - dv2*(dr2-R*R));
   const double t1 = (-drdv + radical)/dv2;
   const double t2 = (-drdv - radical)/dv2;
   
   double tc = -1.0;
   if (in_time_step(t1) and !in_time_step(t2)) tc = t1;
   else if (!in_time_step(t1) and in_time_step(t2)) tc = t2;
   else if (in_time_step(t1) and in_time_step(t2)) tc = (t1 < t2 ? t1 : t2);
   if (tc > 0.0)
   {
      collision = true;
      advance(cannon_ball,tc);
      advance(dropped_ball,tc);
      verify();

      const double oldE = energy();
      //inelastic_scatter();
      elastic_scatter();

      cout << "Energy change: " << energy() - oldE << endl;

      advance(cannon_ball,dt-tc);
      advance(dropped_ball,dt-tc);
   }
   else
   {   
      advance(cannon_ball,dt);
      advance(dropped_ball,dt);
   }
}

void exit_gracefully(void)
{
   exit(0);
}
