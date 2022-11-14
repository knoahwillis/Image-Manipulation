#include "Functions.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <array>
#include <iostream>

int main(int argc, char* argv[]) {
    TTF_Init();

    int x, y, n;
    unsigned char* data = load_image(&x, &y, &n);

    SDL_Window* window = SDL_CreateWindow("Image Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, 0);
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* Titles = TTF_OpenFont("./Sans.ttf", 24);
    TTF_Font* Buttons = TTF_OpenFont("./Sans.ttf", 12);

    SDL_Color White = {225, 225, 225};

    SDL_Surface* original_image_surface = IMG_Load("./image.jpg");
    SDL_Surface* original_text = TTF_RenderText_Solid(Titles, "Original Image", White);

    SDL_Surface* new_image_surface = IMG_Load("./image.jpg");
    new_image_surface->pixels = data;
    SDL_Surface* new_text = TTF_RenderText_Solid(Titles, "New Image", White);

    std::array<SDL_Surface*, 12> button_surfaces = {
        TTF_RenderText_Solid(Buttons, "Blur", White),        TTF_RenderText_Solid(Buttons, "Swap Colors", White),
        TTF_RenderText_Solid(Buttons, "Recolor", White),     TTF_RenderText_Solid(Buttons, "Randomize", White),
        TTF_RenderText_Solid(Buttons, "Darken", White),      TTF_RenderText_Solid(Buttons, "Swap Quadrants", White),
        TTF_RenderText_Solid(Buttons, "Flip", White),        TTF_RenderText_Solid(Buttons, "Shade", White),
        TTF_RenderText_Solid(Buttons, "Invert", White),      TTF_RenderText_Solid(Buttons, "Add Noise", White),
        TTF_RenderText_Solid(Buttons, "Special XOR", White), TTF_RenderText_Solid(Buttons, "Reflect", White),
    };

    bool closed = false;

    SDL_Texture* original_texture = SDL_CreateTextureFromSurface(rend, original_image_surface);

    SDL_Rect original_image = {0, original_text->h, x / 2, y / 2};

    SDL_Texture* original_text_texture = SDL_CreateTextureFromSurface(rend, original_text);
    SDL_Texture* new_text_texture = SDL_CreateTextureFromSurface(rend, new_text);

    SDL_Rect original_message_rect = {0, 0, original_text->w, original_text->h};
    SDL_Rect new_message_rect = {700, 0, new_text->w, original_text->h};

    std::array<SDL_Texture*, 12> button_textures;
    for (int i = 0; i < 12; i++) {
        button_textures[i] = SDL_CreateTextureFromSurface(rend, button_surfaces[i]);
    }

    const int button_width = 100;
    const int button_height = 100;
    std::array<SDL_Rect, 12> button_rects;
    int count = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            button_rects[count] = SDL_Rect{50 * j + j * button_width, 300 + 2 * button_height * i, button_width, button_height};
            count++;
        }
    }

    while (!closed) {
        SDL_Event e;

        SDL_RenderClear(rend);

        SDL_Texture* new_texture = SDL_CreateTextureFromSurface(rend, new_image_surface);
        SDL_Rect new_image = {700, original_text->h, x / 2, y / 2};

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
            case SDL_MOUSEBUTTONDOWN:
                switch (e.button.button) {
                case SDL_BUTTON_LEFT:
                    if (e.button.y >= button_rects[0].y && e.button.y <= button_rects[0].y + button_rects[0].h) {
                        if (e.button.x >= button_rects[0].x && e.button.x <= button_rects[0].x + button_rects[0].w) {
                            blur_image(data, x, y, n);
                        } else if (e.button.x >= button_rects[1].x && e.button.x <= button_rects[1].x + button_rects[1].w) {
                            color_swap(data, x, y, n);
                        } else if (e.button.x >= button_rects[2].x && e.button.x <= button_rects[2].x + button_rects[2].w) {
                            recolor_image(data, x, y, n);

                        } else if (e.button.x >= button_rects[3].x && e.button.x <= button_rects[3].x + button_rects[3].w) {
                            randomize_image(data, x, y, n);

                        } else if (e.button.x >= button_rects[4].x && e.button.x <= button_rects[4].x + button_rects[4].w) {
                            divide_image(data, x, y, n);

                        } else if (e.button.x >= button_rects[5].x && e.button.x <= button_rects[5].x + button_rects[5].w) {
                            swap_quadrants(data, x, y, n);
                        }
                    } else if (e.button.y >= button_rects[6].y && e.button.y <= button_rects[6].y + button_rects[6].h) {
                        if (e.button.x >= button_rects[6].x && e.button.x <= button_rects[6].x + button_rects[6].w) {
                            data = flip_image(data, x, y, n);

                        } else if (e.button.x >= button_rects[7].x && e.button.x <= button_rects[7].x + button_rects[7].w) {
                            shade_image(data, x, y, n);

                        } else if (e.button.x >= button_rects[8].x && e.button.x <= button_rects[8].x + button_rects[8].w) {
                            invert_image(data, x, y, n);

                        } else if (e.button.x >= button_rects[9].x && e.button.x <= button_rects[9].x + button_rects[9].w) {
                            and_randomize_image(data, x, y, n);

                        } else if (e.button.x >= button_rects[10].x && e.button.x <= button_rects[10].x + button_rects[10].w) {
                            b_xor(data, x, y, n);

                        } else if (e.button.x >= button_rects[11].x && e.button.x <= button_rects[11].x + button_rects[11].w) {
                            data = reflect(data, x, y, n);
                        }
                    }
                    break;
                }
                break;
            }
        }
        new_image_surface->pixels = data;

        SDL_RenderCopy(rend, original_texture, NULL, &original_image);
        SDL_RenderCopy(rend, new_texture, NULL, &new_image);
        SDL_RenderCopy(rend, original_text_texture, NULL, &original_message_rect);
        SDL_RenderCopy(rend, new_text_texture, NULL, &new_message_rect);

        for (int i = 0; i < 12; i++) {
            SDL_RenderCopy(rend, button_textures[i], NULL, &button_rects[i]);
        }

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }

    SDL_FreeSurface(original_image_surface);
    SDL_FreeSurface(new_image_surface);
    SDL_FreeSurface(original_text);
    SDL_FreeSurface(new_text);

    SDL_DestroyTexture(original_texture);
    // SDL_DestroyTexture(new_texture);
    SDL_DestroyTexture(original_text_texture);
    SDL_DestroyTexture(new_text_texture);

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    del_image_data(data);

    return 0;
}
