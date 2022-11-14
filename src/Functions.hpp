#pragma once
#include <iostream>
#include <stdio.h>
#include <string>

unsigned char* load_image(int* x, int* y, int* n);

void blur_image(unsigned char* data, int x, int y, int n);

void color_swap(unsigned char* data, int x, int y, int n);

void recolor_image(unsigned char* data, int x, int y, int n);

void randomize_image(unsigned char* data, int x, int y, int n);

void divide_image(unsigned char* data, int x, int y, int n);

void swap_quadrants(unsigned char* data, int x, int y, int n);

unsigned char* flip_image(unsigned char* data, int x, int y, int n);

void shade_image(unsigned char* data, int x, int y, int n);

void invert_image(unsigned char* data, int x, int y, int n);

void and_randomize_image(unsigned char* data, int x, int y, int n);

void b_xor(unsigned char* data, int x, int y, int n);

unsigned char* reflect(unsigned char* data, int x, int y, int n);

void del_image_data(unsigned char* data);