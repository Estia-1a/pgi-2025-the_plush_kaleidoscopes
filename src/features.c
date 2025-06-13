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