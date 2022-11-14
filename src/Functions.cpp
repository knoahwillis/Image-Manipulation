#include "Functions.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// loading a file into the program
unsigned char* load_image(int* x, int* y, int* n) {
    // std::string f;
    // // std::cout << "Please enter the path of the image (.jpg) you would like to manipulate:\n";
    // std::cin >> f;
    unsigned char* ret = stbi_load("./slug.jpg", x, y, n, 3);
    return ret;
}

// blur the image (part a)
void blur_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    for (int i = 0; i < x * y * n; i++) {
        *temp = *temp & 0xF0;
        temp++;
    }
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
}

// (part c)
void recolor_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    for(int i = 0; i < x * y; i++) {
        unsigned char r = *temp;
        temp++;
        unsigned char g = *temp;
        temp++;
        unsigned char b = *temp;
        temp++;
        float y = ((static_cast<float>(r) / 255) + (static_cast<float>(g) / 255)) / 2;
        float o = ((static_cast<float>(r) / 255) + ((static_cast<float>(g) / 2) / 255)) / 2;
        float p = ((static_cast<float>(b) / 255) + (static_cast<float>(r) / 255)) / 2;
        y *= 255;
        o *= 255;
        p *= 255;
        temp -= 3;
        *temp = static_cast<unsigned char>(o);
        temp++;
        *temp = static_cast<unsigned char>(y);
        temp++;
        *temp = static_cast<unsigned char>(p);
        temp++;
    }
}

// randomize the intensity of each pixel (part d)
void randomize_image(unsigned char* data, int x, int y, int n) {
    srand(time(NULL));
    unsigned char* temp = data;
    for (int i = 0; i < x * y * n; i++) {
        *temp = rand() % 255 + 1;
        temp++;
    }
}

// divide the color of each pixel in half (part e)
void divide_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data; 
    for (int i = 0; i < x * y * n; i++) {
        *temp = *temp >> 1;
        temp++;
    }
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

    temp = data;
    tq1 = q1;
    tq2 = q2;
    tq3 = q3;
    tq4 = q4;
    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            // q2
            if (i >= 0 && i < half_x && j >= 0 && j < half_y) {
                for (int k = 0; k < 3; k++) {
                    *temp = *tq4;
                    temp++;
                    tq4++;
                }
            }
            // q1
            else if (i >= half_x && j >= 0 && j < half_y) {
                for (int k = 0; k < 3; k++) {
                    *temp = *tq3;
                    temp++;
                    tq3++;
                }
            }
            // q3
            else if (i >= 0 && i < half_x && j >= half_y) {
                for (int k = 0; k < 3; k++) {
                    *temp = *tq1;
                    temp++;
                    tq1++;
                }
            }
            // q4
            else {
                for (int k = 0; k < 3; k++) {
                    *temp = *tq2;
                    temp++;
                    tq2++;
                }
            }
        }
    }

    delete[] q1;
    delete[] q2;
    delete[] q3;
    delete[] q4;
}


// I DONT THINK THIS WILL WORK -- dosent, acts weird ??
// rotate the image by pi/2 radians (part g)
void flip_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    for (int i = 0; i < x * y * n; i++) {
        temp++;
    }
    unsigned char r, g, b;
    for (int i = 0; i < x * y; i++) {
        r = *(temp - 2);
        g = *(temp - 1);
        b = *(temp);
        *temp = b;
        temp--;
        *temp = r;
        temp--;
        *temp = g;
        temp--;
    }
}

// draw the image in shades of ruby (part h)
void shade_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    // these values can be replaced with the RGB values of any color, ruby is used here
    unsigned char ruby_r = 0xE0;
    unsigned char ruby_g = 0x11;
    unsigned char ruby_b = 0x5F;
    for (int i = 0; i < x * y; i++) {
        for (int j = 0; j < 3; j++) {
            switch (j) {
            case 0:
                *temp = *temp & ruby_r;
                break;
            case 1:
                *temp = *temp & ruby_g;
                break;
            case 2:
                *temp = *temp & ruby_b;
                break;
            }
            temp++;
        }
    }
}

// create the negative of the image (part i)
void invert_image(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    for (int i = 0; i < x * y * n; i++) {
        *temp = ~(*temp);
        temp++;
    }
}

// create a random char, then bitwise and the pixel and that char (part j)
void and_randomize_image(unsigned char* data, int x, int y, int n) {
    srand(time(NULL));
    unsigned char* temp = data;
    for (int i = 0; i < x * y * n; i++) {
        *temp = *temp & (rand() % 255 + 1);
        temp++;
    }
}

// xor each color with the char 'B' for my favorite computer science professor
// who taught me all about xor (part k)
void b_xor(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    for (int i = 0; i < x * y * n; i++) {
        *temp = *temp ^ 'B';
        temp++;
    }
}

// THIS ONE ALSO WONT WORK -- dosent
// reflect the image over the vertical axis (part l)
void reflect(unsigned char* data, int x, int y, int n) {
    unsigned char* temp = data;
    for (int j = 0; j < y; j++) {
        temp += x * 3;
        for (int i = 0; i < x; i++) {
            temp += 2;
            temp--;
            *temp = *temp;
            temp--;
            temp--;
            *temp = *temp;
            temp--;
            temp--;
            *temp = *temp;
            temp += 3;
        }
        temp += x * 3;
    }
}

void del_image_data(unsigned char* data) {
  stbi_image_free(data);
}
