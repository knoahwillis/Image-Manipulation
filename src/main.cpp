#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <stdio.h>
#include <string>

// loading a file into the program
unsigned char* load_image(int* x, int* y, int* n) {
    std::string f;
    std::cout << "Please enter the path of the image (.jpg) you would like to manipulate:\n";
    std::cin >> f;
    unsigned char* ret = stbi_load(f.c_str(), x, y, n, 3);
    return ret;
}

// blur the image (part a)
void blur_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    unsigned char* new_image = new unsigned char[x * y * n];
    unsigned char* ret = new_image;
    for (int i = 0; i < x * y * n; i++) {
        *new_image = *temp & 0xF0;
        temp++;
        new_image++;
    }
    stbi_write_jpg("./images/blurred.jpg", x, y, n, ret, 100);
    delete[] ret;
}

// replace each green with blue, blue with red, red with green (part b)
void color_swap(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    unsigned char* new_image = new unsigned char[x * y * n];
    unsigned char* ret = new_image;
    unsigned char r, g, b;
    for (int i = 0; i < x * y; i++) {
        r = *temp;
        g = *(temp + 1);
        b = *(temp + 2);
        *new_image = g;
        temp++;
        new_image++;
        *new_image = b;
        temp++;
        new_image++;
        *new_image = r;
        temp++;
        new_image++;
    }
    stbi_write_jpg("./images/color_swap.jpg", x, y, n, ret, 100);
    delete[] ret;
}

// (part c)
void recolor_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    unsigned char* new_image = new unsigned char[x * y * n];
    unsigned char* ret = new_image;
    // these values can be replaced with the RGB values of any color, ruby is used here
    unsigned char ruby_r = 0xE0;
    unsigned char ruby_g = 0x11;
    unsigned char ruby_b = 0x5F;
    for (int i = 0; i < x * y; i++) {
        for (int j = 0; j < 3; j++) {
            switch (j) {
            case 0:
                *new_image = *temp & ruby_r;
                break;
            case 1:
                *new_image = *temp & ruby_g;
                break;
            case 2:
                *new_image = *temp & ruby_b;
                break;
            }
            temp++;
            new_image++;
        }
    }
    stbi_write_jpg("./images/shaded.jpg", x, y, n, ret, 100);
    delete[] ret;
}

// randomize the intensity of each pixel (part d)
void randomize_image(unsigned char* data, int x, int y, int n) {
    srand(time(NULL));
    unsigned char* new_image = new unsigned char[x * y * n];
    unsigned char* ret = new_image;
    for (int i = 0; i < x * y * n; i++) {
        *new_image = rand() % 255 + 1;
        new_image++;
    }
    stbi_write_jpg("./images/randomized.jpg", x, y, n, ret, 100);
    delete[] ret;
}

// divide the color of each pixel in half (part e)
void divide_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    unsigned char* new_image = new unsigned char[x * y * n];
    unsigned char* ret = new_image;
    for (int i = 0; i < x * y * n; i++) {
        *new_image = *temp >> 1;
        temp++;
        new_image++;
    }
    stbi_write_jpg("./images/divided.jpg", x, y, n, ret, 100);
    delete[] ret;
}

// swap quadrans I and III, II and IV (part f)
void swap_quadrants(unsigned char* data, int x, int y, int n) {
    unsigned char* q1 = new unsigned char[(x * y * n) / 4];
    unsigned char* q2 = new unsigned char[(x * y * n) / 4];
    unsigned char* q3 = new unsigned char[(x * y * n) / 4];
    unsigned char* q4 = new unsigned char[(x * y * n) / 4];
    int half_x = x / 2;
    int half_y = y / 2;

    // initial loop to divide the quadrants
    unsigned char* temp = data;
    unsigned char* tq1 = q1;
    unsigned char* tq2 = q2;
    unsigned char* tq3 = q3;
    unsigned char* tq4 = q4;
    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            // q2
            if (i >= 0 && i < half_x && j >= 0 && j < half_y) {
                for (int k = 0; k < 3; k++) {
                    *tq2 = *temp;
                    temp++;
                    tq2++;
                }
            }
            // q1
            else if (i >= half_x && j >= 0 && j < half_y) {
                for (int k = 0; k < 3; k++) {
                    *tq1 = *temp;
                    temp++;
                    tq1++;
                }
            }
            // q3
            else if (i >= 0 && i < half_x && j >= half_y) {
                for (int k = 0; k < 3; k++) {
                    *tq3 = *temp;
                    temp++;
                    tq3++;
                }
            }
            // q4
            else {
                for (int k = 0; k < 3; k++) {
                    *tq4 = *temp;
                    temp++;
                    tq4++;
                }
            }
        }
    }

    // second loop to swap them

    unsigned char* new_image = new unsigned char[x * y * n];
    unsigned char* ret = new_image;
    tq1 = q1;
    tq2 = q2;
    tq3 = q3;
    tq4 = q4;
    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            // q2
            if (i >= 0 && i < half_x && j >= 0 && j < half_y) {
                for (int k = 0; k < 3; k++) {
                    *new_image = *tq4;
                    new_image++;
                    tq4++;
                }
            }
            // q1
            else if (i >= half_x && j >= 0 && j < half_y) {
                for (int k = 0; k < 3; k++) {
                    *new_image = *tq3;
                    new_image++;
                    tq3++;
                }
            }
            // q3
            else if (i >= 0 && i < half_x && j >= half_y) {
                for (int k = 0; k < 3; k++) {
                    *new_image = *tq1;
                    new_image++;
                    tq1++;
                }
            }
            // q4
            else {
                for (int k = 0; k < 3; k++) {
                    *new_image = *tq2;
                    new_image++;
                    tq2++;
                }
            }
        }
    }

    delete[] q1;
    delete[] q2;
    delete[] q3;
    delete[] q4;
    stbi_write_jpg("./images/swapped.jpg", x, y, n, ret, 100);
    delete[] ret;
}

// rotate the image by pi/2 radians (part g)
void flip_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    unsigned char* new_image = new unsigned char[x * y * n];
    unsigned char* ret = new_image;
    for (int i = 0; i < x * y * n; i++) {
        temp++;
    }
    unsigned char r, g, b;
    for (int i = 0; i < x * y; i++) {
        r = *(temp - 2);
        g = *(temp - 1);
        b = *(temp);
        *new_image = b;
        temp--;
        new_image++;
        *new_image = r;
        temp--;
        new_image++;
        *new_image = g;
        temp--;
        new_image++;
    }
    stbi_write_jpg("./images/flipped.jpg", x, y, n, ret, 100);
    delete[] ret;
}

// draw the image in shades of ruby (part h)
void shade_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    unsigned char* new_image = new unsigned char[x * y * n];
    unsigned char* ret = new_image;
    // these values can be replaced with the RGB values of any color, ruby is used here
    unsigned char ruby_r = 0xE0;
    unsigned char ruby_g = 0x11;
    unsigned char ruby_b = 0x5F;
    for (int i = 0; i < x * y; i++) {
        for (int j = 0; j < 3; j++) {
            switch (j) {
            case 0:
                *new_image = *temp & ruby_r;
                break;
            case 1:
                *new_image = *temp & ruby_g;
                break;
            case 2:
                *new_image = *temp & ruby_b;
                break;
            }
            temp++;
            new_image++;
        }
    }
    stbi_write_jpg("./images/shaded.jpg", x, y, n, ret, 100);
    delete[] ret;
}

// create the negative of the image (part i)
void invert_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    unsigned char* new_image = new unsigned char[x * y * n];
    unsigned char* ret = new_image;
    for (int i = 0; i < x * y * n; i++) {
        *new_image = ~(*temp);
        temp++;
        new_image++;
    }
    stbi_write_jpg("./images/inverted.jpg", x, y, n, ret, 100);
    delete[] ret;
}

// create a random char, then bitwise and the pixel and that char (part j)
void and_randomize_image(unsigned char* data, int x, int y, int n) {
    srand(time(NULL));
    unsigned char* temp = data;
    unsigned char* new_image = new unsigned char[x * y * n];
    unsigned char* ret = new_image;
    for (int i = 0; i < x * y * n; i++) {
        *new_image = *temp & (rand() % 255 + 1);
        temp++;
        new_image++;
    }
    stbi_write_jpg("./images/andrandomized.jpg", x, y, n, ret, 100);
    delete[] ret;
}

// xor each color with the char 'B' for my favorite computer science professor
// who taught me all about xor (part k)
void b_xor(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    unsigned char* new_image = new unsigned char[x * y * n];
    unsigned char* ret = new_image;
    for (int i = 0; i < x * y * n; i++) {
        *new_image = *temp ^ 'B';
        temp++;
        new_image++;
    }
    stbi_write_jpg("./images/b_xor.jpg", x, y, n, ret, 100);
    delete[] ret;
}

// reflect the image over the vertical axis (part l)
void reflect(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    unsigned char* new_image = new unsigned char[x * y * n];
    unsigned char* ret = new_image;
    for (int j = 0; j < y; j++) {
        temp += x * 3;
        for (int i = 0; i < x; i++) {
            new_image += 2;
            temp--;
            *new_image = *temp;
            temp--;
            new_image--;
            *new_image = *temp;
            new_image--;
            temp--;
            *new_image = *temp;
            new_image += 3;
        }
        temp += x * 3;
    }
    stbi_write_jpg("./images/reflected.jpg", x, y, n, ret, 100);
    delete[] ret;
}

int main() {
    int x, y, n;
    // unsigned char* data = stbi_load("./images/slug.jpg", &x, &y, &n, 3);
    unsigned char* data = load_image(&x, &y, &n);
    bool exit = false;
    char c;
    std::cout << "What would you like to do to your image? Please enter the corresponding letter, or enter e to escape:\n ";
    std::cout << "Blur image - a\n";
    std::cout << "Swap the colors - b\n";
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
    while (!exit) {
        std::cin >> c;
        switch (c) {
        case 'a':
            blur_image(data, x, y, n); // part a
            break;
        case 'b':
            color_swap(data, x, y, n); // part b
            break;
            // case 'c':
            //
            // break;
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
        std::cout << "If you would like continue manipulating your image, simply enter the above character, or enter e to exit.\n";
    }
    stbi_image_free(data);
    return 0;
}
