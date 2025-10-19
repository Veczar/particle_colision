#ifndef IO_H
#define IO_H

#include "particles.h"

int init_window(int width, int height, const char *title);
void draw_particles(ParticleArray *pa);
void handle_events(int *running);
void close_window(void);

void save_frame_ppm(ParticleArray *pa, int frame_number);
void print_fps(double fps);

#endif