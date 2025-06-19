#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "features.h"
#include "utils.h"

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
    int R, G, B;
    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        unsigned int position = (y * width + x) * nbChannels;
        R = data[position];
        G = data[position + 1];
        B = data[position + 2];
        printf("print_pixel (%d, %d): %d, %d, %d \n", x, y, R, G, B);
    }
    else {
        printf("ERROR\n");
    }

}

void max_pixel(char *source_path){
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

void min_pixel(char *source_path){
    int width;
    int height;
    int nbChannels;
    unsigned char * data;
    int R,G,B;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        int min_sum = 3 * 255;
        int min_x = 0;
        int min_y = 0;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                unsigned int position = (y * width + x) * nbChannels;

                R = data[position];
                G = data[position + 1];
                B = data[position + 2];

                int sum = R + G + B;

                if (sum < min_sum) {
                    min_sum = sum;
                    min_x = x;
                    min_y = y;
                }
            }
        }

        unsigned int min_position = (min_y * width + min_x) * nbChannels;
        R = data[min_position];
        G = data[min_position + 1];
        B = data[min_position + 2];

        printf("min_pixel (%d, %d): %d, %d, %d\n", min_x, min_y, R, G, B);
    }
    else {
        printf("ERROR\n");
    }
}

#include <ctype.h> 

void max_component(char *source_path, char component) {
    int width;
    int height;
    int nbChannels;
    unsigned char *data;
    int max_value = -1;
    int max_x = 0, max_y = 0;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        int comp_index = -1;
        component = toupper((unsigned char)component);
        if (component == 'R') comp_index = 0;
        else if (component == 'G') comp_index = 1;
        else if (component == 'B') comp_index = 2;
        else {
            printf("ERROR: Invalid component\n");
            return;
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                unsigned int position = (y * width + x) * nbChannels;
                int value = data[position + comp_index];
                if (value > max_value) {
                    max_value = value;
                    max_x = x;
                    max_y = y;
                }
            }
        }
        printf("max_component %c (%d, %d): %d\n", component, max_x, max_y, max_value);
    } else {
        printf("ERROR\n");
    }
}
void min_component(char *source_path, char component) {
    int width;
    int height;
    int nbChannels;
    unsigned char *data;
    int min_value = 256;
    int min_x = 0, min_y = 0;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        int comp_index = -1;
        component = toupper((unsigned char)component);
        if (component == 'R') comp_index = 0;
        else if (component == 'G') comp_index = 1;
        else if (component == 'B') comp_index = 2;
        else {
            printf("ERROR: Invalid component\n");
            return;
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                unsigned int position = (y * width + x) * nbChannels;
                int value = data[position + comp_index];
                if (value < min_value) {
                    min_value = value;
                    min_x = x;
                    min_y = y;
                }
            }
        }
        printf("min_component %c (%d, %d): %d\n", component, min_x, min_y, min_value);
    } else {
        printf("ERROR\n");
    }
}

void color_red(char *source_path){
    unsigned char *data;
    int height;
    int width;
    int channel_count;
    int statut;
    int etat;
    etat = read_image_data(source_path, &data, &width, &height, &channel_count);

    if(etat!=0){
        int position = 0;
        for(int i=0; i<width*height;i++){
            position = i*channel_count;
            data[position+1]=0;
            data[position+2]=0;
        }
    }
    statut = write_image_data("image_out.bmp",data,width,height);
    if (statut == 0){
        printf("Erreur de generation de l'image");
    }
}
void color_green (char *source_path){
    unsigned char *data;
    int height;
    int width;
    int channel_count;
    int statut;
    int etat;

    etat = read_image_data(source_path, &data, &width, &height, &channel_count);

    if(etat!=0){
        int position = 0;
        for(int i=0;i<width*height;i++){
            position = i*channel_count;
            data[position]=0;
            data[position+2]=0;
        }
    }

    statut = write_image_data("image_out.bmp",data,width, height);

    if (statut == 0)
    {
        printf("Erreur de generation de l'image");
    }

}
void color_blue (char *source_path){
    unsigned char *data;
    int height;
    int width;
    int channel_count;
    int statut;
    int etat;

    etat = read_image_data(source_path, &data, &width, &height, &channel_count);

    if(etat!=0){
        int position = 0;
        for(int i=0;i<width*height;i++){
            position = i*channel_count;
            data[position]=0;
            data[position+1]=0;
        }
    }

    statut = write_image_data("image_out.bmp",data,width, height);

    if (statut == 0)
    {
        printf("Erreur de generation de l'image");
    }
}
void color_gray (char *source_path){
     unsigned char *data;
    int height;
    int width;
    int channel_count;
    int statut;
    int etat;
    int value;

    etat = read_image_data(source_path, &data, &width, &height, &channel_count);

    if(etat!=0){
        int position = 0;
        for(int i=0;i<width*height;i++){
            position = i*channel_count;
            value = (data[position]+data[position+1]+data[position+2])/3;
            data[position]=value;
            data[position+1]=value;
            data[position+2]=value;
        }
    }

    statut = write_image_data("image_out.bmp",data,width, height);

    if (statut == 0)
    {
        printf("Erreur de generation de l'image");
    }
}
void color_gray_luminance(char *source_path){
    unsigned char *data;
    int height;
    int width;
    int channel_count;
    int statut;
    int etat;
    int value;

    etat = read_image_data(source_path, &data, &width, &height, &channel_count);

    if(etat!=0){
        /*for(int y=0; y<height; y++){
            for(int x=0; x<width; x++ ){
                value = (get_pixel(data, width, height, channel_count, x, y)->R + get_pixel(data, width, height, channel_count, x, y)->G + get_pixel(data, width, height, channel_count, x, y)->B)/3;
                data[x*y*channel_count] = value;
                data[x*y*channel_count+1] = value;
                data[x*y*channel_count+2] = value;
            }
        }*/
        int position = 0;
        for(int i=0;i<width*height;i++){
            position = i*channel_count;
            value = (0.21*data[position]+0.72*data[position+1]+0.07*data[position+2]);
            data[position]=value;
            data[position+1]=value;
            data[position+2]=value;
        }
    }

    statut = write_image_data("image_out.bmp",data,width, height);

    if (statut == 0)
    {
        printf("Erreur de generation de l'image");
    }
}

void scale_crop(char *source_path, int center_x, int center_y, int crop_width, int crop_height) {
    int width, height, nbChannels;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) == 0) {
        printf("ERROR\n");
        return;
    }
    unsigned char *out_data = malloc(crop_width * crop_height * nbChannels);
    if (!out_data) {
        printf("ERROR\n");
        free(data);
        return;
    }

    int half_w = crop_width / 2;
    int half_h = crop_height / 2;

    for (int y = 0; y < crop_height; ++y) {
        for (int x = 0; x < crop_width; ++x) {
            int src_x = center_x - half_w + x;
            int src_y = center_y - half_h + y;
            unsigned char *dst_pixel = out_data + (y * crop_width + x) * nbChannels;

            if (src_x >= 0 && src_x < width && src_y >= 0 && src_y < height) {
                unsigned char *src_pixel = data + (src_y * width + src_x) * nbChannels;
                memcpy(dst_pixel, src_pixel, nbChannels);
            } else {
                memset(dst_pixel, 0, nbChannels);
            }
        }
    }
    write_image_data("image_crop_out.bmp", out_data, crop_width, crop_height);

    free(data);
    free(out_data);
}

void rotate_cw(char *source_path) {
    int width, height, nbChannels;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) == 0) {
        printf("ERROR\n");
        return;
    }

    unsigned char *rotated = malloc(width * height * nbChannels);
    if (!rotated) {
        printf("ERROR\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int src_idx = (y * width + x) * nbChannels;
            int dst_x = height - 1 - y;
            int dst_y = x;
            int dst_idx = (dst_y * height + dst_x) * nbChannels;
            memcpy(rotated + dst_idx, data + src_idx, nbChannels);
        }
    }

    write_image_data("image_out.bmp", rotated, height, width);
    free(data);
    free(rotated);
}

void rotate_acw(char *source_path) {
    int width, height, nbChannels;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) == 0) {
        printf("ERROR\n");
        return;
    }

    unsigned char *rotated = malloc(width * height * nbChannels);
    if (!rotated) {
        printf("ERROR\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int src_idx = (y * width + x) * nbChannels;
            int dst_x = y;
            int dst_y = width - 1 - x;
            int dst_idx = (dst_y * height + dst_x) * nbChannels;
            memcpy(rotated + dst_idx, data + src_idx, nbChannels);
        }
    }

    write_image_data("image_out.bmp", rotated, height, width);
    free(data);
    free(rotated);
}

void mirror_horizontal(char *source_path) {
    int width, height, nbChannels;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) == 0) {
        printf("ERROR\n");
        return;
    }

    unsigned char *mirrored = malloc(width * height * nbChannels);
    if (!mirrored) {
        printf("ERROR\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int src_idx = (y * width + x) * nbChannels;
            int dst_x = width - 1 - x;
            int dst_idx = (y * width + dst_x) * nbChannels;
            memcpy(mirrored + dst_idx, data + src_idx, nbChannels);
        }
    }

    write_image_data("image_out.bmp", mirrored, width, height);
    free(data);
    free(mirrored);
}

void mirror_vertical(char *source_path) {
    int width, height, nbChannels;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) == 0) {
        printf("ERROR\n");
        return;
    }

    unsigned char *mirrored = malloc(width * height * nbChannels);
    if (!mirrored) {
        printf("ERROR\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int src_idx = (y * width + x) * nbChannels;
            int dst_y = height - 1 - y;
            int dst_idx = (dst_y * width + x) * nbChannels;
            memcpy(mirrored + dst_idx, data + src_idx, nbChannels);
        }
    }

    write_image_data("image_out.bmp", mirrored, width, height);
    free(data);
    free(mirrored);
}

void mirror_total(char *source_path) {
    int width, height, nbChannels;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) == 0) {
        printf("ERROR\n");
        return;
    }

    unsigned char *mirrored = malloc(width * height * nbChannels);
    if (!mirrored) {
        printf("ERROR\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int src_idx = (y * width + x) * nbChannels;
            int dst_x = width - 1 - x;
            int dst_y = height - 1 - y;
            int dst_idx = (dst_y * width + dst_x) * nbChannels;
            memcpy(mirrored + dst_idx, data + src_idx, nbChannels);
        }
    }

    write_image_data("image_out.bmp", mirrored, width, height);
    free(data);
    free(mirrored);
}

void scale_nearest(char *source_path, int scale_factor) {
    int width, height, nbChannels;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) == 0) {
        printf("ERROR\n");
        return;
    }

    int new_width = width * scale_factor;
    int new_height = height * scale_factor;
    unsigned char *scaled = malloc(new_width * new_height * nbChannels);
    if (!scaled) {
        printf("ERROR\n");
        free(data);
        return;
    }

    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            int src_x = x / scale_factor;
            int src_y = y / scale_factor;
            unsigned char *src_pixel = data + (src_y * width + src_x) * nbChannels;
            unsigned char *dst_pixel = scaled + (y * new_width + x) * nbChannels;
            memcpy(dst_pixel, src_pixel, nbChannels);
        }
    }

    write_image_data("image_out.bmp", scaled, new_width, new_height);
    free(data);
    free(scaled);
}