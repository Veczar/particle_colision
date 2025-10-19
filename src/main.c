#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "particles.h"
#include "physics.h"
#include "io.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int N = 10;
    ParticleArray pa;
    init_particle_array(&pa, N);

    if (!init_window(WIDTH * 10, HEIGHT * 10, "Particle Simulation")) {
        fprintf(stderr, "Could not initialize SDL window!\n");
        return 1;
    }

    int running = 1;

    while (running)
    {
        handle_events(&running);
        update_positions(&pa);
        handle_collisions(&pa);
        draw_particles(&pa);
        SDL_Delay(16); // ~60 FPS
    }
    
    close_window();
    /*
    clock_t start = clock();

    for (int step = 0; step < steps; step++) {
        update_positions(&pa);
        handle_collisions(&pa);
        if (step % 10 == 0)
            save_frame_ppm(&pa, step);
    }

    double time_spent = (double)(clock() - start) / CLOCKS_PER_SEC;
    print_fps(steps / time_spent); 
    */

    free_particle_array(&pa);
    return 0;
}