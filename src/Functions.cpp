#include "Functions.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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

void del_image_data(unsigned char* data) {
  stbi_image_free(data);
}
