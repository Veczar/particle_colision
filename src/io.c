#include <SDL2/SDL.h>
#include <stdio.h>
#include "io.h"

// Real time graphics window

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

int init_window(int width, int height, const char *title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, 0);
    if (!window) {
        fprintf(stderr, "SDL window error: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "SDL renderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    return 1;
}

void draw_particles(ParticleArray *pa) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int i = 0; i < pa->count; i++) {
        Particle *p = &pa->array[i];
        SDL_SetRenderDrawColor(renderer, p->color, 0, 255 - p->color, 255);
        SDL_Rect rect = {(int)p->x * 10, (int)p->y * 10, 8, 8};
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

void handle_events(int *running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) *running = 0;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            *running = 0;
    }
}

void close_window(void) {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}


void save_frame_ppm(ParticleArray *pa, int frame_number) {
    char filename[64];
    snprintf(filename, sizeof(filename), "data/frame_%04d.ppm", frame_number);

    FILE *f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "P3\n%d %d\n255\n", WIDTH, HEIGHT);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int color = 0;
            for (int i = 0; i < pa->count; i++) {
                int px = (int)pa->array[i].x;
                int py = (int)pa->array[i].y;
                if (px == x && py == y) {
                    color = pa->array[i].color;
                    break;
                }
            }
            fprintf(f, "%d %d %d ", color, 0, 255 - color);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

void print_fps(double fps) {
    printf("FPS: %.2f\n", fps);
}