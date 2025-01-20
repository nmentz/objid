/**
 * 
 */

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vec3 {
    int r, g, b;
} vec3;

struct ImageData {
    int width;
    int height;
    int channels;
    unsigned char* image;
};

/**
 * stbi_load(...) returns an unsigned char* array I named 'img_d'. This array stores the rgb data as follows...
 * img_d = [ R1, G1, B1, R2, G2, B2, R3, G3, B3, ..., Rn, Gn+1, Bn+2 ] where R = (y * image_width + x) * channels;
 * This is how stb_image wants things done and I'm not gonna fight it.
 */
//void get_rgbvec3 (int x, int y, unsigned char* img_d, int width, int channels) {
vec3 get_rgbvec3 (int x, int y, const struct ImageData* img_d) {
    int width = img_d->width;
    int channels = img_d->channels;
    unsigned char* image = img_d->image;

    int red = ((y * width + x) * channels),
        green = ((y * width + x) * channels) + 1,
        blue = ((y * width + x) * channels) + 2;

    // this is kind of nice for debugging so I'll leave it
    //printf("\npixel (%i, %i) has the rgb values respectively %i %i %i\n", x, y, image[red], image[green], image[blue]);

    vec3 rgbColor = {
        .r = image[red],
        .g = image[green],
        .b = image[blue]
    };

    return rgbColor;
}

int main (void) {

    struct ImageData img_d;
    img_d.image = stbi_load("1200x1552.jpeg", &img_d.width, &img_d.height, &img_d.channels, 0);

    if (img_d.image == NULL) {
        printf("Error loading the image\n");
        return 0; // no need to tell the operating system something went wrong
    }

    vec3 vector = get_rgbvec3(478, 332, &img_d);

    // Free the image data after use
    stbi_image_free(img_d.image);

    return 0;
}