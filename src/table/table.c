/**
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

/**
 * @file table.c
 * @brief Functions of the table.
*/

/**
 * @author Ayoub Goubraim <ayoub.goubraim@ecole.ensicaen.fr>
 * @author Mohamed Ben lboukht <mohamed.ben-lboukht@ecole.ensicaen.fr>
 * @version 1.0.0
 * @date 27-12-2023
 */

#include <stdio.h>
#include <stdlib.h>

#include "table.h"
#include "image.h"

/**
 * @struct color_table
 * @brief A structure where to store the data of a color table image.
 */
struct color_table{
    color* data; /*!< table which contains the rgb components of each color*/
    int size; /*!< number of colors in the table*/
    boolean owner; /*!< true if the table is the owner of the data, false otherwise*/
};

int size_color_table(color_table table) {

    assert(table != NULL); /*we check if the table is not null*/

    return table->size;
}

color data_color_table(color_table table, int index) {

    assert(table != NULL); /*we check if the table is not null*/
    assert(index >= 0); /*we check if the index is not negative*/
    assert(index < table->size*3); /*we check if the index is not bigger than the table size*/

    return table->data[index];
}

boolean owner_color_table(color_table table) {

    assert(table != NULL); /*we check if the table is not null*/

    return table->owner;
}

color_table create_color_table(image image) {
    color_table table; /*creation of a color table*/
    int longueur;  /*length of the table*/
    int i;
    int j;

    assert(image != NULL); /*we check if the image is not null*/
    assert(image_give_largeur(image) > 0); /*we check if the image size is not null*/

    table=(color_table)malloc(sizeof(struct color_table)); /*allocation of the table*/

    table->size=image_give_largeur(image); /*initialisation of the table size*/

    longueur=table->size*3; /*initialisation of the table length*/

    table->data = (color *)malloc(sizeof(color) * longueur); /*allocation of the table data*/

    i=0;

    image_debut(image); /*we go to the beginning of the image*/
    
    do {
        for(j=0;j<DIM;j++){                                   
            table->data[i*DIM +j]=image_lire_pixel(image)[j];  /*we put the pixel in the table*/
        }                                                       
        i++;
    } while(image_pixel_suivant(image)); /*we go to the next pixel*/
    	
        
    table->owner= true; 
    return table; 
}

boolean destroy_color_table(color_table table) {

    assert(table != NULL); /*we check if the table is not null*/

    boolean resultat = table->owner; 
    if (table->owner) {            /*we check if the table is the owner of the data*/
        free(table->data);         /*we free the data*/
    }
    free(table);                  /*we free the table*/
    return resultat;
}

color_table color_table_duplicate(color_table table, int offset, int size) {

    assert(table != NULL); /*we check if the table is not null*/
    assert(offset >= 0); /*we check if the offset is not negative*/
    assert(size >= 0); /*we check if the size is not negative*/
    assert(offset + size <= table->size); /*we check if the offset + size is not bigger than the table size*/

    color_table new_table; /*Creation a new color table*/
    new_table = (color_table)malloc(sizeof(color_table)); /*allocation of the table*/
    new_table->data = &(table->data[DIM*offset]); /*we put the data of the table in the new table*/
    new_table->size = size; /*we initialise the new table size*/
    new_table->owner = 0; /*we initialise the new table owner*/
    return new_table;
}

void color_table_get_color(color_table table, int index,color* color) {

    assert(table != NULL); /*we check if the table is not null*/
    assert(index >= 0); /*we check if the index is not negative*/
    assert(index < table->size); /*we check if the index is not bigger than the table size*/
    assert(color != NULL); /*we check if the color is not null*/

    int i;
    for ( i = 0; i < DIM ; i++) { 
        color[i] = table->data[DIM*index + i];
    }
}

int color_table_get_nb_color(color_table table) {

    assert(table != NULL); /*we check if the table is not null*/

    return table->size;
}

void color_table_sort(color_table table,axis axis)
{
    assert(table != NULL); /*we check if the table is not null*/
    assert(axis >= 0); /*we check if the axis is not negative*/
    assert(axis < 3); /*we check if the axis is not bigger than 3*/
    
    int i;
    int j;
    int k;
    color temp;
    switch (axis) /*Check the axis of sorting*/
    {
    case 0:
    for(i=0;i<table->size*3;i+=3) /*we go through the table*/
    {
        for(j=table->size*3;j>i;j-=3) /*we go through the table in the other direction*/
        {
            if(table->data[j]<table->data[j-3]){ /*we check if the pixel is smaller than the next one*/
                for(k=0;k<3;k++){ /*we swap the pixels*/
                    temp=table->data[j+k];
                    table->data[j+k]=table->data[k+j-3];
                    table->data[k+j-3]=temp;

                }
            }
        }
    }
    break;
    case 1:
    for(i=1;i<table->size*3;i+=3)
    {
        for(j=table->size*3-2;j>i;j-=3)
        {
            if(table->data[j]<table->data[j-3]){
                for(k=-1;k<2;k++){
                    temp=table->data[j+k];
                    table->data[j+k]=table->data[k+j-3];
                    table->data[k+j-3]=temp;

                }
            }
        }
    }
    break;
    case 2:
    for(i=2;i<table->size*3;i+=3)
    {
        for(j=table->size*3-1;j>i;j-=3)
        {
            if(table->data[j]<table->data[j-3]){
                for(k=-2;k<1;k++){
                    temp=table->data[j+k];
                    table->data[j+k]=table->data[k+j-3];
                    table->data[k+j-3]=temp;

                }
            }
        }
    }
    break;
    }
}
