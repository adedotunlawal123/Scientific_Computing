#ifndef CANNON_H
#define CANNON_H

extern const double dt;

struct ball_t
{
   double mass;
   double radius;
   double x;
   double y;
   double vx;
   double vy;
};

extern ball_t cannon_ball;
extern ball_t dropped_ball;

extern bool fire;
extern bool collision;

void initialize(double);

void update(void);

void exit_gracefully(void);

#endif // CANNON_H

