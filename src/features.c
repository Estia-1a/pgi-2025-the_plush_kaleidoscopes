#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !!!");
}

void dimension (char *source_path){
    int width;
    int height;
    int channel_count;
    unsigned char *data;
    int resultat = read_image_data(source_path, &data, &width, &height, &channel_count);

    if (resultat){
        printf("dimension: %d,%d", width,height);
    }
    else{
        printf("ERROR");
    }
}

void first_pixel (char *source_path){
    int width;
    int height;
    int channel_count;
    unsigned char *data;
    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    
    if (result){
        printf("first_pixel: %d, %d, %d", data[0], data[1], data[2]);
    }
    else{
        printf("ERROR");
    }
}

void tenth_pixel (char *source_path){
unsigned char *data;
    int width;
    int height;
    int nbChannels;
    if (read_image_data(source_path, &data, &width, &height, &nbChannels)) {
        int pixelIndex = (3 * (10-1));
 
        if (pixelIndex < width * height * nbChannels) {
            printf("tenth_pixel: %d, %d, %d\n", data[pixelIndex], data[pixelIndex + 1], data[pixelIndex + 2]);
        } else {
            printf(".\n");
        }
    }
    else {
        printf("ERROR");
    }
}

void second_line(char *source_path){
    unsigned char *data;
    int width;
    int height;
    int nbChannels;
    if (read_image_data(source_path, &data, &width, &height, &nbChannels)) {
        int pixelIndex = (width * nbChannels);
 
        if (pixelIndex < width * height * nbChannels) {
            printf("second_line: %d, %d, %d\n", data[pixelIndex], data[pixelIndex + 1], data[pixelIndex + 2]);
        } else {
            printf("The image does not have a second line with at least one pixel.\n");
        }
    }
    else {
        printf("ERROR\n");
    }
}

void print_pixel(char *source_path, int x, int y){
    int width;
    int height;
    int nbChannels;
    unsigned char * data;
    int R,G,B;
    if (read_image_data(source_path, &data, &width, &height, &nbChannels) !=0){
        unsigned int position = 3*(y*width+x);
        R = data[position];
        G = data[position+1];
        B = data[position+2];
        printf("print_pixel (%d, %d): %d, %d, %d \n", x, y, R, G, B);
    }
    else {
        printf("ERROR\n");
    }

}

void max_pixel(char *source_path, int x, int y){
    int width;
    int height;
    int nbChannels;
    unsigned char * data;
    int R,G,B;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        int max_sum = -1;
        int max_x = 0;
        int max_y = 0;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                unsigned int position = (y * width + x) * nbChannels;

                R = data[position];
                G = data[position + 1];
                B = data[position + 2];

                int sum = R + G + B;

                if (sum > max_sum) {
                    max_sum = sum;
                    max_x = x;
                    max_y = y;
                }
            }
        }

        unsigned int max_position = (max_y * width + max_x) * nbChannels;
        R = data[max_position];
        G = data[max_position + 1];
        B = data[max_position + 2];

        printf("max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, R, G, B);
    }
    else {
        printf("ERROR\n");
    }
}