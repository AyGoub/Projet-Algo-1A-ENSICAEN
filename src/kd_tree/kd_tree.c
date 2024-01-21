#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kd_tree.h"

/**
 * @struct kdtree
 * @brief A structure where to store the data of a kd tree.
 */
struct kdtree{
    color_table table; /*!<Table containing the color table to represent the kdtree */
    struct kdtree *left_son; /*!<Pointer on the left son of the kdtree */
    struct kdtree *right_son; /*!<Pointer on the right son of the kdtree */
    axis split_axis; /*!<Axis on which the kdtree is split */
    float split_plan; /*!<Value of the split plan */
};

int size_table_tree(kdtree tree) {

    assert(tree != NULL);

    return size_color_table(tree->table);
}

color data_table_tree(kdtree tree, int index) {

    assert(tree != NULL);
    assert(index >= 0);
    assert(index < size_table_tree(tree)*3);

    return data_color_table(tree->table, index);
}

kdtree left_son_tree(kdtree tree) {

    assert(tree != NULL);

    return tree->left_son;
}

kdtree right_son_tree(kdtree tree) {

    assert(tree != NULL);

    return tree->right_son;
}
/**
 * @fn static axis choose_axis(color_table table)
 * @brief Chooses the axis on which the table will be split.
 * @param table The table to split.
 * @return The axis on which the table will be split.
 */
static axis choose_axis(color_table table) {

    assert(table != NULL);

    color max_r;
    color max_g;
    color max_b;
    color min_r;
    color min_g;
    color min_b;

    color_table table_r = (color_table)malloc(sizeof(color_table));
    color_table table_g = (color_table)malloc(sizeof(color_table));
    color_table table_b = (color_table)malloc(sizeof(color_table));

    /*We create 3 tables, one for each color, and we sort them*/

    table_r = table;
    table_g = table;
    table_b = table;
    
    color_table_sort(table_r, red);
    color_table_sort(table_g, green);
    color_table_sort(table_b, blue);

    /*We initialize the max and the min of each component*/

    max_r = data_color_table(table_r, size_color_table(table_r)*3 - 3);
    min_r = data_color_table(table_r, 0);

    max_g = data_color_table(table_g, size_color_table(table_g)*3 - 2);
    min_g = data_color_table(table_g, 1);

    max_b = data_color_table(table_b,size_color_table(table_b)*3 - 1);
    min_b = data_color_table(table_b, 2);

    /*we return the component which has the greatest variance between its max and min component*/

    if (max_r - min_r > max_g - min_g && max_r - min_r > max_b - min_b) {
        return red;
    }
    else if (max_g - min_g > max_r - min_r && max_g - min_g > max_b - min_b) {
        return green;
    }
    else {
        return blue;
    }
}

/**
 * @fn static float choose_plan(color_table table_sorted , axis sorting_axis, int* number_color)
 * @brief Chooses the plan on which the table will be split.
 * @param table_sorted The table to split.
 * @param sorting_axis The axis on which the table is sorted.
 * @param number_color The number of colors in the table after split.
 * @return The plan on which the table will be split.
 */
static float choose_plan(color_table table_sorted , axis sorting_axis, int* number_color) {

    assert(table_sorted != NULL);

    int size;
    color color1[3];
    color color2[3];

    size = size_color_table(table_sorted);

    /*We compare the parity of the  table size*/

    /*If the size is odd, we return the median of the table*/

    if (size %2 ==1 ) {
        *number_color = (size-1)/2;
        return (float) data_color_table(table_sorted, (size-1)/2);
    }

    /*If the size is even, we return the average of the two middle values*/

    else {
        color_table_get_color(table_sorted, (size/2) , color1);
        color_table_get_color(table_sorted, ((size)/2) - 1, color2);
        *number_color = size/2;
        return ((float) color1[sorting_axis] + color2[sorting_axis])/2;
    }
}


kdtree create_kdtree(color_table table , int max) {
    int size;
    int number_color;
    kdtree tree;
    color_table table_right;
    color_table table_left;

    tree = (kdtree)malloc(sizeof(struct kdtree));
    tree->table = (color_table)malloc(sizeof(color_table));
    tree->table = table;
    size = size_color_table(table);
    

    /*If the size of the table is greater than the max, we split the table*/

    if (size>max) {
        tree->split_axis=choose_axis(table); /*We choose the axis on which we split the table*/
        color_table_sort(tree->table, tree->split_axis); /*We sort the table on the chosen axis*/
        tree->split_plan=choose_plan(tree->table, tree->split_axis, &number_color); /*We choose the plan on which we split the table*/

        table_left = (color_table)malloc(sizeof(color_table));
        table_right = (color_table)malloc(sizeof(color_table));

        /*We create two tables, one for the left son and one for the right son*/

        table_left = color_table_duplicate(tree->table, 0, number_color);
        table_right = color_table_duplicate(tree->table, number_color , size-number_color);

        /*We create the left and right sons*/

        tree->left_son = create_kdtree(table_left, max);
        tree->right_son = create_kdtree(table_right, max);
    }

    /*If the size of the table is smaller than the max, we create a leaf*/

    else {
        tree->left_son = NULL;
        tree->right_son = NULL;
    }

    /*We return the tree*/

    return tree;

}

void destroy_kdtree(kdtree tree) {

    assert(tree != NULL);

    /*We destroy the tree recursively*/
    
    if (tree->left_son != NULL) {
        destroy_kdtree(tree->left_son);
    }
    if (tree->right_son != NULL) {
        destroy_kdtree(tree->right_son);
    }

    /*We destroy the table*/
    
    destroy_color_table(tree->table);
    free(tree);
}

float distance(color* color1, color* color2) {

    assert(color1 != NULL);
    assert(color2 != NULL);
    
    /*We calculate the distance between two colors using euclidien formula*/

    return sqrt(pow((color1[0] - color2[0]),2) + pow((color1[1] - color2[1]),2) + pow((color1[2] - color2[2]),2));
}

void closest_color(color_table table,color* reference_color, color* nearest_color) {

    assert(table != NULL); /*we check if the table is not null*/
    assert(reference_color != NULL); /*we check if the reference color is not null*/
    assert(nearest_color != NULL); /*we check if the nearest color is not null*/

    int i;
    int size;
    float dist;
    float temp;
    color temp_color[3];
    
    size = size_color_table(table); /*we get the size of the table*/

    color_table_get_color(table, 0, nearest_color); /*we get the first color of the table*/
    dist = distance(reference_color, nearest_color); /*we calculate the distance between the reference color and the first color of the table*/

    /*we go through the table and we calculate the distance between the reference color and each color of the table*/

    for (i=1; i<size; i++) {
        color_table_get_color(table, i, temp_color);
        temp = distance(reference_color, temp_color);

        /*if the distance is smaller than the previous one, we change the nearest color*/

        if (temp < dist) {
            dist = temp;
            nearest_color[0] = temp_color[0];
            nearest_color[1] = temp_color[1];
            nearest_color[2] = temp_color[2];
        }
    }
}

void kdtree_get_nearest_color(kdtree tree, color* reference_color, color* nearest_color){

    assert(tree != NULL); /*we check if the tree is not null*/
    assert(reference_color != NULL); /*we check if the reference color is not null*/
    assert(nearest_color != NULL); /*we check if the nearest color is not null*/

    kdtree leaf;
    kdtree other_leaf;
    float dist;
    
    color* temp_color = (color*)malloc(3*sizeof(color));

    /*if the tree is a leaf, we calculate the nearest color*/

    if(tree->left_son == NULL && tree->right_son == NULL) {
        closest_color(tree->table, reference_color, nearest_color);
        return;
    }

    /*if the reference color is smaller than the split plan, we go to the left son*/

    else if (reference_color[tree->split_axis] < tree->split_plan) {
        leaf = tree->left_son;
        other_leaf = tree->right_son;
    }

    /*if the reference color is bigger than the split plan, we go to the right son*/

    else {
        leaf = tree->right_son;
        other_leaf = tree->left_son;
    }

    /*we calculate the nearest color in the leaf recursively*/

    kdtree_get_nearest_color(leaf, reference_color, nearest_color);

    /*we calculate the distance between the reference color and the nearest color*/

    dist = distance(reference_color, nearest_color);

    /*if the distance between the reference color and the split plan is smaller than the distance between the reference color and the nearest color, we go to the other leaf*/

    if(dist > fabs(reference_color[leaf->split_axis] - leaf->split_plan)) {
        
        /*we calculate the nearest color in the other leaf*/

        closest_color(other_leaf->table, reference_color, temp_color);
        
        /*we calculate the distance between the reference color and the nearest color in the other leaf and we compare it to the previous distance*/

        if (distance(reference_color, temp_color) < dist) {
            nearest_color[0] = temp_color[0];
            nearest_color[1] = temp_color[1];
            nearest_color[2] = temp_color[2];
        }
        
    }   
}























