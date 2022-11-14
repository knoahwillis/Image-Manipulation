#include "Functions.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    TTF_Init();
    
    int x, y, n;
    unsigned char* data = load_image(&x, &y, &n);

    SDL_Window* window = SDL_CreateWindow("Image Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, 0);
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* Sans = TTF_OpenFont("./Sans.ttf", 24);

    SDL_Color White = {225, 225, 225};

    SDL_Surface* original_image_surface = IMG_Load("./image.jpg");
    SDL_Surface* original_text = TTF_RenderText_Solid(Sans, "Original Image", White);

    SDL_Surface* new_image_surface = IMG_Load("./image.jpg");
    SDL_Surface* new_text = TTF_RenderText_Solid(Sans, "New Image", White);

    bool closed = false;

    swap_quadrants(data, x, y, n);
    new_image_surface->pixels = data;

    SDL_Texture* original_texture = SDL_CreateTextureFromSurface(rend, original_image_surface);
    SDL_Texture* new_texture = SDL_CreateTextureFromSurface(rend, new_image_surface);

    SDL_Rect original_image = {0, original_text->h, x / 2, y / 2};
    SDL_Rect new_image = {700, original_text->h, x / 2, y / 2};

    SDL_Texture* original_text_texture = SDL_CreateTextureFromSurface(rend, original_text);
    SDL_Texture* new_text_texture = SDL_CreateTextureFromSurface(rend, new_text);

    SDL_Rect original_message_rect = {0, 0, original_text->w, original_text->h};
    SDL_Rect new_message_rect = {700, 0, new_text->w, original_text->h};

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

        SDL_RenderCopy(rend, original_texture, NULL, &original_image);
        SDL_RenderCopy(rend, new_texture, NULL, &new_image);
        SDL_RenderCopy(rend, original_text_texture, NULL, &original_message_rect);
        SDL_RenderCopy(rend, new_text_texture, NULL, &new_message_rect);

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }

    SDL_FreeSurface(original_image_surface);
    SDL_FreeSurface(new_image_surface);
    SDL_FreeSurface(original_text);
    SDL_FreeSurface(new_text);

    SDL_DestroyTexture(original_texture);
    SDL_DestroyTexture(new_texture);
    SDL_DestroyTexture(original_text_texture);
    SDL_DestroyTexture(new_text_texture);

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
