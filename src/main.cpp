#include "Functions.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// int main(int argc, char* argv[]) {
//     int x, y, n;
//     unsigned char* data = load_image(&x, &y, &n);
//     SDL_Window* window = SDL_CreateWindow("Image Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, 0);
//     SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//     SDL_Surface* image = IMG_Load("./slug.jpg");
//     SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, image);

//     bool closed = false;

//     blur_image(data, x, y, n); // part a

//     while (!closed) {
//         SDL_Event e;

//         // SDL_RenderClear(rend);

//         while (SDL_PollEvent(&e)) {
//             switch (e.type) {
//             case SDL_QUIT:
//                 closed = true;
//                 break;
//             case SDL_KEYDOWN:
//                 switch (e.key.keysym.scancode) {
//                 case SDL_SCANCODE_ESCAPE:
//                     closed = true;
//                     break;
//                 }
//                 break;
//             }
//         }

//         // SDL_RenderCopy(rend, texture, NULL, NULL);
//         SDL_RenderPresent(rend);
//         SDL_Delay(1000 / 60);
//     }

//     SDL_DestroyTexture(texture);
//     SDL_FreeSurface(image);
//     SDL_DestroyRenderer(rend);
//     SDL_DestroyWindow(window);

//     SDL_Quit();

//     return 0;
// }

int main() {
    int x, y, n;
    // unsigned char* data = stbi_load("./images/slug.jpg", &x, &y, &n, 3);
    unsigned char* data = load_image(&x, &y, &n);
    bool exit = false;
    char c;
    std::cout << "What would you like to do to your image? Please enter the corresponding letter, or enter e to escape:\n ";
    std::cout << "Blur image - a\n";
    std::cout << "Swap the colors - b\n";
    std::cout << "Swap each color with it's compliment's intensity - c";
    std::cout << "Randomize the image - d\n";
    std::cout << "Darken the image - f\n";
    std::cout << "Swap the quadrants - g\n";
    std::cout << "Flip the image 180 degrees - h\n";
    std::cout << "Color the image in shades of ruby - i\n";
    std::cout << "Invert the image - j\n";
    std::cout << "Add 'noise' to the image - k\n";
    std::cout << "xor the pixels - l\n";
    std::cout << "Reflect the image over the horizontal axis - m\n";
    std::cout << "All 12 - n\n";
    int count = 0;
    while (!exit) {
        if (count > 0) {
            std::cout << "If you would like continue manipulating your image, simply enter the above character, or enter e to exit.\n";
        }
        std::cin >> c;
        switch (c) {
        case 'a':
            blur_image(data, x, y, n); // part a
            break;
        case 'b':
            color_swap(data, x, y, n); // part b
            break;
        case 'c':
            recolor_image(data, x, y, n);
            break;
        case 'd':
            randomize_image(data, x, y, n); // part d
            break;
        case 'f':
            divide_image(data, x, y, n); // part e
            break;
        case 'g':
            swap_quadrants(data, x, y, n); // part f
            break;
        case 'h':
            flip_image(data, x, y, n); // part g
            break;
        case 'i':
            shade_image(data, x, y, n); // part h
            break;
        case 'j':
            invert_image(data, x, y, n); // part i
            break;
        case 'k':
            and_randomize_image(data, x, y, n); // part j
            break;
        case 'l':
            b_xor(data, x, y, n); // part k
            break;
        case 'm':
            reflect(data, x, y, n); // park l
            break;
        case 'n':
            blur_image(data, x, y, n);          // part a
            color_swap(data, x, y, n);          // part b
            randomize_image(data, x, y, n);     // part d
            divide_image(data, x, y, n);        // part e
            swap_quadrants(data, x, y, n);      // part f
            flip_image(data, x, y, n);          // part g
            shade_image(data, x, y, n);         // part h
            invert_image(data, x, y, n);        // part i
            and_randomize_image(data, x, y, n); // part j
            b_xor(data, x, y, n);               // part k
            reflect(data, x, y, n);             // park l
            break;
        case 'e':
            exit = true;
            break;
        }
        count++;
    }
    del_image_data(data);
    return 0;
}
