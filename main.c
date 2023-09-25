#include <stdio.h>
#include <stdint.h>
#include "lib_ppm.h"


struct image_s data;
struct image_s *image = &data;


void display_pixel(uint16_t x0, uint16_t y0, uint32_t color)
{
	image->pix[y0 * image->width + x0].r = (color & 0xff0000) >> 16;
	image->pix[y0 * image->width + x0].g = (color & 0x00ff00) >> 8;
	image->pix[y0 * image->width + x0].b = (color & 0x0000ff);
}


int main(void)
{
	int i, j, r;
	
	r = read_ppm("images/lena.ppm", image);
	
	if (r == 0) {
		printf("width: %d, height: %d\n", image->width, image->height);
		for (j = 0; j < image->height; j++) {
			for (i = 0; i < image->width; i++) {
				printf("(%d %d) %02x %02x %02x\n", i, j,
					image->pix[j * image->width + i].r,
					image->pix[j * image->width + i].g,
					image->pix[j * image->width + i].b);
					
			}
		}
		
		image->pix[50 * image->width + 20].r = 255;
		image->pix[50 * image->width + 20].g = 255;
		image->pix[50 * image->width + 20].b = 255;
		
		write_ppm("lena_copy.ppm", image);
		
		free_ppm(image);
	}
	
	r = new_ppm(image, 675, 428);
	
	if (r == 0) {
		for (j = 0; j < 15; j++) {
			for (i = 0; i < 25; i++) {
				image->pix[(100 + j) * image->width + 125 + i].r = 255;
				image->pix[(27 + j) * image->width + 440 + i].g = 255;
		
				image->pix[(371 + j) * image->width + 10 + i].r = 192;
				image->pix[(371 + j) * image->width + 10 + i].g = 192;
				image->pix[(371 + j) * image->width + 10 + i].b = 192;
			}
		}
		
		write_ppm("test.ppm", image);
		free_ppm(image);
	}
	
	return 0;
}
