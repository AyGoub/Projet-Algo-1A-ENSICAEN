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
 * @file table.h
 * @brief Prototypes of functions used in table.c.
*/

/**
 * @author Ayoub Goubraim <ayoub.goubraim@ecole.ensicaen.fr>
 * @author Mohamed Ben lboukht <mohamed.ben-lboukht@ecole.ensicaen.fr>
 * @version 1.0.0
 * @date 27-12-2023
 */

#ifndef __TABLE_HH__
#define __TABLE_HH__
#include "image.h"


#define DIM 3 /*!< Definition of the dimension of the table*/

/**
 * @typedef boolean
 * @brief A boolean is a type that can take two values: true or false.
 */
typedef enum {false,true} boolean; 

/**
 * @typedef axis
 * @brief An axis is a RGB component of a color. 
 * 0 for red axis, 1 for green axis, and 2 for the blue one.
 */
typedef enum {red,green,blue} axis; 

/**
 * @typedef color
 * @brief A color is a RGB component of a color.
 */
typedef unsigned char color; /* ou int*/

/**
 * @typedef color_table
 * @brief A variable pointing on struct color_table.
 */
typedef struct color_table *color_table;

/**
 * @fn int size_color_table(color_table table)
 * @brief Gets the size of a color table.
 * @param table The color table from which we want to get the size.
 * @return The size of the color table.
 */
int size_color_table(color_table);

/**
 * @fn color data_color_table(color_table table, int index)
 * @brief Gets the data of a color table.
 * @param table The color table from which we want to get the data.
 * @param index The index of the data.
 * @return The data of the color table.
 */
color data_color_table(color_table table, int index);

/**
 * @fn boolean owner_color_table(color_table table)
 * @brief Gets the owner of a color table.
 * @param table The color table from which we want to get the owner.
 * @return The owner of the color table.
 */
boolean owner_color_table(color_table table);

/**
 * @fn color_table create_color_table(image image)
 * @brief Creates a color table from an image.
 * @param image The image from which we want to create a color table.
 * @return The color table created.
 */
color_table   create_color_table(image);

/**
 * @fn boolean destroy_color_table(color_table table)
 * @brief Destroys a color table.
 * @param table The color table to destroy.
 * @return true if the table is the owner of the data, false otherwise.
 */
boolean       destroy_color_table(color_table);

/**
 * @fn color_table color_table_duplicate(color_table table, int offset, int size)
 * @brief Creates a color table from a part of another color table.
 * @param table The color table from which we want to create a new color table.
 * @param offset The offset of the new color table.
 * @param size The size of the new color table.
 * @return The new color table created.
 */
color_table   color_table_duplicate(color_table,int,int);

/**
 * @fn void color_table_get_color(color_table table, int index,color* color)
 * @brief Gets the color of a pixel in a color table.
 * @param table The color table from which we want to get the color.
 * @param index The index of the pixel.
 * @param color The color of the pixel.
 */
void          color_table_get_color(color_table,int,color*);

/**
 * @fn int color_table_get_nb_color(color_table table)
 * @brief Gets the number of colors in a color table.
 * @param table The color table from which we want to get the number of colors.
 * @return The number of colors in the color table.
 */
int           color_table_get_nb_color(color_table);

/**
 * @fn void color_table_sort(color_table table,axis axis)
 * @brief Sorts a color table.
 * @param table The color table to sort.
 * @param axis The axis on which we want to sort the color table.
 */
void          color_table_sort(color_table,axis);

#endif