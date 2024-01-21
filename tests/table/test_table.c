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
 * @file test_table.c
 * @brief Test of table functions.
*/

/**
 * @author Ayoub Goubraim <ayoub.goubraim@ecole.ensicaen.fr>
 * @author Mohamed Ben lboukht <mohamed.ben-lboukht@ecole.ensicaen.fr>
 * @version 1.0.0
 * @date 29-12-2023
 */


#include <stdio.h>
#include <stdlib.h>
#include <table.h>
#include <image.h>



int main(int argc, char* argv[]) {

    assert(argc==2);

    image input;
    color_table table;
    color_table newtable;
    color color[3];

    int i;
    char *fichier=argv[1];
    int size;
    int newsize;


    /*Image creation*/

    input = FAIRE_image();
    image_charger(input,fichier);
    assert(input!=NULL);

    /*Table creation*/

    table=create_color_table(input);
    assert(table!=NULL);
    
    size=size_color_table(table);
    
    /*Printing Table data*/

    for (i = 0; i < size*3; i+=3) {
        printf("%d %d %d\n",data_color_table(table,i),data_color_table(table,i+1),data_color_table(table,i+2));
    }
    printf("table.owner=%d\ttable.size=%d\n",owner_color_table(table),size); 
    printf("-----------------------------\n");

    /*Table duplication*/

    newtable=color_table_duplicate(table,7,15);
    newsize=size_color_table(newtable);
    /*Printing newtable data*/

    for (i = 0; i < newsize*3; i+=3) {
        printf("%d %d %d\n",data_color_table(newtable,i),data_color_table(newtable,i+1),data_color_table(newtable,i+2));
    }
    printf("newtable.owner=%d\tnewtable.size=%d\n",owner_color_table(newtable),newsize);
    printf("-----------------------------\n");

    /*Store the pixel 2 of newtable in color variable*/

    color_table_get_color(newtable,2,color);

    /*Printing the color of the pixel 2*/

    printf("%d %d %d\n",color[0],color[1],color[2]);
    printf("--------------------------\n");

    /*Table Sorting with blue axis*/

    color_table_sort(newtable,blue);

    /*Printing the sorted data of newtable*/

    for (i = 0; i < newsize*3; i+=3) {
        printf("%d %d %d\n",data_color_table(newtable,i),data_color_table(newtable,i+1),data_color_table(newtable,i+2));
    }
    printf("\n");
    
    destroy_color_table(newtable);
    destroy_color_table(table);


return 0;
}
