// O SEGUINTE VÍDEO FOI USADO PARA MELHOR COMPREENSÃO DO FILTRO SOBEL: https://www.youtube.com/watch?v=1Ad6cH_7DQ8

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "lib_ppm.h"

struct image_s data;
struct image_s *image = &data;


void gray_filter() {
    struct image_s gray_image;
    new_ppm(&gray_image, image->width, image->height);

    for (int j = 0; j < image->height; j++) {
        for (int i = 0; i < image->width; i++) {
            int r_value = image->pix[j * image->width + i].r;
            int g_value = image->pix[j * image->width + i].g;
            int b_value = image->pix[j * image->width + i].b;

            int gray_value = r_value * 0.299 + g_value * 0.587 + b_value * 0.114;

            gray_image.pix[j * image->width + i].r = gray_value;
            gray_image.pix[j * image->width + i].g = gray_value;
            gray_image.pix[j * image->width + i].b = gray_value;
        }
    }

    write_ppm("image_with_gray_filter.ppm", &gray_image);
    free_ppm(&gray_image);
}

void threshold_operation(int threshold) {
    struct image_s threshold_image;
    new_ppm(&threshold_image, image->width, image->height);

    for (int j = 0; j < image->height; j++) {
        for (int i = 0; i < image->width; i++) {
            int r_value = image->pix[j * image->width + i].r;
            int g_value = image->pix[j * image->width + i].g;
            int b_value = image->pix[j * image->width + i].b;
            int gray_value = r_value * 0.299 + g_value * 0.587 + b_value * 0.114;

            if (gray_value < threshold) {
                threshold_image.pix[j * image->width + i].r = 0;
                threshold_image.pix[j * image->width + i].g = 0;
                threshold_image.pix[j * image->width + i].b = 0;
            } else {
                threshold_image.pix[j * image->width + i].r = 255;
                threshold_image.pix[j * image->width + i].g = 255;
                threshold_image.pix[j * image->width + i].b = 255;
            }
        }
    }

    write_ppm("image_with_threshold.ppm", &threshold_image);
    free_ppm(&threshold_image);
}

void sobel_filter() {
    struct image_s sobel_image;
    new_ppm(&sobel_image, image->width, image->height);
    
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

    for (int j = 1; j < image->height - 1; j++) {
        for (int i = 1; i < image->width - 1; i++) {
            int sum_r_x = 0, sum_g_x = 0, sum_b_x = 0;
            int sum_r_y = 0, sum_g_y = 0, sum_b_y = 0;

            for (int y = -1; y <= 1; y++) {
                for (int x = -1; x <= 1; x++) {
                    sum_r_x += image->pix[(j + y) * image->width + (i + x)].r * Gx[y + 1][x + 1];
                    sum_g_x += image->pix[(j + y) * image->width + (i + x)].g * Gx[y + 1][x + 1];
                    sum_b_x += image->pix[(j + y) * image->width + (i + x)].b * Gx[y + 1][x + 1];

                    sum_r_y += image->pix[(j + y) * image->width + (i + x)].r * Gy[y + 1][x + 1];
                    sum_g_y += image->pix[(j + y) * image->width + (i + x)].g * Gy[y + 1][x + 1];
                    sum_b_y += image->pix[(j + y) * image->width + (i + x)].b * Gy[y + 1][x + 1];
                }
            }
            
            sobel_image.pix[j * image->width + i].r = sqrt(pow(sum_r_x, 2) + pow(sum_r_y, 2));
            sobel_image.pix[j * image->width + i].g = sqrt(pow(sum_g_x, 2) + pow(sum_g_y, 2));
            sobel_image.pix[j * image->width + i].b = sqrt(pow(sum_b_x, 2) + pow(sum_b_y, 2));
        }

    }
    
    write_ppm("image_with_sobel_filter.ppm", &sobel_image);
    free_ppm(&sobel_image);
}

int main(void) {

    int r = read_ppm("images/lena.ppm", image);

    if (r == 0)
    {
        printf("width: %d, height: %d\n", image->width, image->height);

        gray_filter();
        threshold_operation(120);
        sobel_filter();

        free_ppm(image);
    }
}
