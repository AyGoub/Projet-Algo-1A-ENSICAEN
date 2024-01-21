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
 * @file test_kd_tree.c
 * @brief Test of  functions.
*/

/**
 * @author Ayoub Goubraim <ayoub.goubraim@ecole.ensicaen.fr>
 * @author Mohamed Ben lboukht <mohamed.ben-lboukht@ecole.ensicaen.fr>
 * @version 1.0.0
 * @date 30-12-2023
 */

#include <stdio.h>
#include <stdlib.h>
#include "kd_tree.h"


/**
 * @fn void print_kdtree(kdtree,color*)
 * @brief Print the kdtree using recursive method and also the distance between each color and the reference color.
 * @param kdtree to print.
 * @param color* reference color.
 */
void print_kdtree(kdtree tree,color* color_reference) {
    color* color1;
    color1=malloc(sizeof(color)*3);
    if (tree==NULL){
        return;
    }
    for (int i = 0; i < size_table_tree(tree); i+=1) {
        color1[0]=data_table_tree(tree,i*3);
        color1[1]=data_table_tree(tree,i*3+1);
        color1[2]=data_table_tree(tree,i*3+2);
        printf("%d %d %d----- %f\n",data_table_tree(tree,i*3),data_table_tree(tree,i*3+1),data_table_tree(tree,i*3+2),distance(color_reference,color1));
    }
    printf("--------------------------------------\n");
    print_kdtree(left_son_tree(tree),color_reference);
    print_kdtree(right_son_tree(tree),color_reference);
}


int main(int argc, char* argv[]) {

    assert(argc==2);

    image input;
    color_table table;
    color color1[3]={100,145,86};
    kdtree tree;

    color* color2;

    color2=malloc(sizeof(color)*3);

    assert(color2!=NULL);

    char *fichier=argv[1];

    /*Image creation*/

    input = FAIRE_image();
    image_charger(input,fichier);

    assert(input!=NULL);

    /*Color table Creation*/

    table=create_color_table(input);

    assert(table!=NULL);

    /*Kd tree creation*/

    tree = create_kdtree(table, 30);

    assert(tree!=NULL);

    /*Print the kdtree*/

    print_kdtree(tree,color1);

    /*Get the nearest color to color1 and store it in color2*/

    kdtree_get_nearest_color(tree, color1, color2);

    /*Print the nearest color and the distance between it and color1*/

    printf("%d %d %d----%f\n",color2[0],color2[1],color2[2],distance(color1,color2));
    
    free(color2);
    destroy_kdtree(tree);
    



}
