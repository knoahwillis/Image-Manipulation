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
    std::cout << "Please enter the path of the image you would like to maniulate:\n";
    std::cin >> f;
    unsigned char* ret = stbi_load(f.c_str(), x, y, n, 3);
    return ret;
}

// blur the image (part a)
void blur_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    for (int i = 0; i < x * y * n; i++) {
        *temp &= 0xF0;
        temp++;
    }
    stbi_write_jpg("./images/blurred.jpg", x, y, n, data, 100);
}

// replace each green with blue, blue with red, red with green (part b)
void color_swap(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    unsigned char r, g, b;
    for (int i = 0; i < x * y; i++) {
        r = *temp;
        g = *(temp + 1);
        b = *(temp + 2);
        *temp = g;
        temp++;
        *temp = b;
        temp++;
        *temp = r;
        temp++;
    }
    stbi_write_jpg("./images/color_swap.jpg", x, y, n, data, 100);
}

void randomize_image(unsigned char* data, int x, int y, int n) {
    srand(time(NULL));

    iSecret = rand() % 10 + 1;
}

// divide the color of each pixel in half (part e)
void divide_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    for (int i = 0; i < x * y * n; i++) {
        *temp = *temp >> 1;
        temp++;
    }
    stbi_write_jpg("./images/divided.jpg", x, y, n, data, 100);
}

// create the negative of the image (part i)
void invert_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    for (int i = 0; i < x * y * n; i++) {
        *temp = ~(*temp);
        temp++;
    }
    stbi_write_jpg("./images/replaced.jpg", x, y, n, data, 100);
}

int main() {
    int x, y, n;
    unsigned char* data = stbi_load("./images/slug.jpg", &x, &y, &n, 3);
    // unsigned char* data = load_image(&x, &y, &n);
    // blur_image(data, x, y, n);
    // divide_image(data, x, y, n);
    // invert_image(data, x, y, n);
    // color_swap(data, x, y, n);
    stbi_image_free(data);
    return 0;
}
