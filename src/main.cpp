#include "Functions.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[]) {
    int x, y, n;
    unsigned char* data = load_image(&x, &y, &n);
    SDL_Window* window = SDL_CreateWindow("Image Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_surface_h_

    bool closed = false;

    reflect(data, x, y, n); // part a

    while (!closed) {
        unsigned char* image_data = data;
        SDL_Event e;

        SDL_RenderClear(rend);

        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                closed = true;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    closed = true;
                    break;
                }
                break;
            }
        }
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                unsigned char red = *image_data;
                image_data++;
                unsigned char green = *image_data;
                image_data++;
                unsigned char blue = *image_data;
                image_data++;
                SDL_SetRenderDrawColor(rend, red, green, blue, 0);
                SDL_RenderDrawPoint(rend, j, i);
            }
        }

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
