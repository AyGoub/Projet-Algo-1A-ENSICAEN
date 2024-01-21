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
 * @file triviale.c
 * @brief Inversion of an image by a color table using the trivial method.
*/

/**
 * @author Ayoub Goubraim <ayoub.goubraim@ecole.ensicaen.fr>
 * @author Mohamed Ben lboukht <mohamed.ben-lboukht@ecole.ensicaen.fr>
 * @version 1.0.0
 * @date 29-12-2023
 */

#include "table.h"
#include <math.h>
#include <time.h>




int main(int argc, char *argv[]) {

    assert(argc == 3);

	image img;
    image table;
    color_table ctable;
    		
   	int i;
   	int dist;
   	int temp;
	float time;
   		
	color  *new_pixel = malloc(3*sizeof(color));

    assert(new_pixel != NULL);

	int * pixel;
	int closest_pixel[3];

	clock_t t1;
	clock_t t2;

    /*Image Creation*/
		
    img = FAIRE_image();
    image_charger(img, argv[1]);

    assert(img != NULL);

    /*Table Creation*/

	table = FAIRE_image();
	image_charger(table, argv[2]);

    assert(table != NULL);

    /*Color Table Creation*/

    ctable = create_color_table(table);

	/*Start the clock*/

    t1 = clock();
    		
    image_debut(img);

    /*In this loop we go through all the pixels of the image*/
	do
	{
        /*Get the pixel of the image*/

		pixel = image_lire_pixel(img);
    
        /*Store the first pixel of ctable in new_pixel*/

		color_table_get_color(ctable, 0, new_pixel);
            
        /*Calculate the distance between the pixel and the first pixel of ctable*/

		dist = sqrt(pow((new_pixel[0] - pixel[0]),2) + pow((new_pixel[1] - pixel[1]),2) + pow((new_pixel[2] - pixel[2]),2));

        /*Store the first pixel of ctable in closest_pixel*/

		closest_pixel[0] = (int) new_pixel[0];
		closest_pixel[1] = (int) new_pixel[1];
		closest_pixel[2] = (int) new_pixel[2];

        /*In this loop we compare the distances between the pixel of the image and every pixel of ctable and we choose the pixel with the lowest distance*/

		for (i = 1; i < color_table_get_nb_color(ctable); i++) {

			color_table_get_color(ctable, i, new_pixel);
			temp = sqrt(pow((new_pixel[0] - pixel[0]),2) + pow((new_pixel[1] - pixel[1]),2) + pow((new_pixel[2] - pixel[2]),2));
				
			if (temp < dist) {
				dist = temp;
				closest_pixel[0] = (int) new_pixel[0];
				closest_pixel[1] = (int) new_pixel[1];
				closest_pixel[2] = (int) new_pixel[2];
			}
		}
    
        /*We change the pixel of the image with the pixel of ctable with the lowest distance*/

		image_ecrire_pixel(img, closest_pixel);

    } while (image_pixel_suivant(img));

	/*Stop the clock*/

	t2 = clock();

	/*Calculate the time of execution in second*/

	time = (float)(t2 - t1) / CLOCKS_PER_SEC;

	/*Print the time of execution*/

	printf("Inversion colors of %s using trivial method takes %f seconds\n",argv[1], time);

	/*We save the new image*/
	
	image_sauvegarder(img, "image_trivial_method.ppm");
	
	free(new_pixel);
	destroy_color_table(ctable);
	

    return 0;

}
