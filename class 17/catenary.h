#ifndef CATENARY_H
#define CATENARY_H

void initialize(void);

void start_new_data_set(void);

void add_measurement(float, float);

void exit_gracefully(void);

extern float a, x_0, y_0;
float catenary(float);

#endif
