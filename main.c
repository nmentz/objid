/**
 * 
 */

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
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
 */
vec3 getRGB (const int x, const int y, const struct ImageData* img_d) {
    int width = img_d->width;
    int channels = img_d->channels;
    unsigned char* image = img_d->image;

    int red = ((y * width + x) * channels),
        green = ((y * width + x) * channels) + 1,
        blue = ((y * width + x) * channels) + 2;

    vec3 rgbColor = {
        .r = image[red],
        .g = image[green],
        .b = image[blue]
    };

    // debug line
    //printf("\npixel (%i, %i) has the rgb values %i %i %i respectively\n", x, y, rgbColor.r, rgbColor.g, rgbColor.b);

    return rgbColor;
}

vec3** dynamicallySized2dArray (const int width, const int height) {
    vec3 **array = malloc(width * sizeof(vec3 *));
    for (int i = 0; i < width; i++) {
        array[i] = malloc(height * sizeof(vec3));
    }
    return array;
}

void saveRGBToArray (vec3** array, const struct ImageData* img_d) {
    const int width = img_d->width;
    const int height = img_d->height;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            array[x][y] = getRGB (x, y, img_d);
        }
    }
}

void RGB2csv (vec3** rgb_screen_data, const struct ImageData* img_d) {
    const int width = img_d->width;
    const int height = img_d->height;

    FILE* csv = fopen("data.csv", "w");
    if (csv == NULL) {
        printf("Error creating data.csv\n");
        return;
    }

    // declare column headers
    fprintf(csv, "x,y,r,g,b\n");

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            fprintf(csv, "%i,%i,", x, y);
            fprintf(csv, "%i,", rgb_screen_data[x][y].r);
            fprintf(csv, "%i,", rgb_screen_data[x][y].g);
            fprintf(csv, "%i,", rgb_screen_data[x][y].b);
            fprintf(csv, "\n");
        }
    }

    fclose(csv);
}

int main (void) {

    struct ImageData img_d;
    img_d.image = stbi_load("tests/1200x1552.jpeg", &img_d.width, &img_d.height, &img_d.channels, 0);

    if (img_d.image == NULL) {
        printf("Error loading the image\n");
        return 0; // no need to tell the operating system something went wrong
    }

    vec3** rgb_screen_data = dynamicallySized2dArray(img_d.width, img_d.height);

    saveRGBToArray(rgb_screen_data, &img_d);

    RGB2csv(rgb_screen_data, &img_d);

    stbi_image_free(img_d.image);

    return 0;
}