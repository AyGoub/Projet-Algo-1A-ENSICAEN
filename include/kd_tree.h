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
 * @file kd_tree.h
 * @brief Prototypes of functions used in kd_tree.c.
*/

/**
 * @author Ayoub Goubraim <ayoub.goubraim@ecole.ensicaen.fr>
 * @author Mohamed Ben lboukht <mohamed.ben-lboukht@ecole.ensicaen.fr>
 * @version 1.0.0
 * @date 29-12-2023
 */

#ifndef __KDTREE_HH__
#define __KDTREE_HH__

#include "table.h"

/**
 * @typedef kdtree
 * @brief A variable pointing on struct kdtree.
 */
typedef struct kdtree *kdtree;

/**
 * @fn int size_table_tree(kdtree)
 * @brief Get the size of the table of a kdtree.
 * @param kdtree.
 * @return int.
 */
int size_table_tree(kdtree tree);

/**
 * @fn color data_table_tree(kdtree, int)
 * @brief Get the data of the table of a kdtree.
 * @param kdtree.
 * @param int index of the color.
 * @return color.
 */
color data_table_tree(kdtree tree, int index);

/**
 * @fn kdtree left_son_tree(kdtree)
 * @brief Get the left son of a kdtree.
 * @param kdtree.
 * @return kdtree.
 */
kdtree left_son_tree(kdtree tree);

/**
 * @fn kdtree right_son_tree(kdtree)
 * @brief Get the right son of a kdtree.
 * @param kdtree.
 * @return kdtree.
 */
kdtree right_son_tree(kdtree tree);

/**
 * @fn kdtree create_kdtree(color_table,int)
 * @brief Create a kd tree from a color table.
 * @param color_table table to represent the kdtree.
 * @param int the limit of the number of colors in a leaf.
 * @return kdtree.
 */
kdtree create_kdtree(color_table,int);

/**
 * @fn destroy_kdtree(kdtree)
 * @brief Destroy a kd tree.
 * @param kdtree to destroy.
 */
void destroy_kdtree(kdtree);

/**
 * @fn float distance(color*, color*)
 * @brief Calculate the distance between two colors.
 * @param color* the first color.
 * @param color* the second color.
 */
float distance(color* , color* );

/**
 * @fn void kdtree_get_nearest_color(kdtree, color*, color*)
 * @brief Get the nearest color from a kdtree.
 * @param kdtree.
 * @param color* the color to compare.
 * @param color* the nearest color.
 */
void kdtree_get_nearest_color(kdtree, color*, color*);

#endif
