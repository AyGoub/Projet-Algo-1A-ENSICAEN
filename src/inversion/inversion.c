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
 * @file inversion.c
 * @brief Inversion of an image using a kd_tree.
*/

/**
 * @author Ayoub Goubraim <ayoub.goubraim@ecole.ensicaen.fr>
 * @author Mohamed Ben lboukht <mohamed.ben-lboukht@ecole.ensicaen.fr>
 * @version 1.0.0
 * @date 30-12-2023
 */

#include <time.h>
#include "kd_tree.h"
 	
int main(int argc, char *argv[]) {

    assert(argc == 3);

    image img;
    image table;
    color_table ctable;
    kdtree tree; 	

    int* pixel;
    int newpixel[3];
    color closest_pixel[3];
    color color_reference[3];

	float time;
	clock_t t1;
	clock_t t2;

    /*Image Creation*/
		
    img = FAIRE_image();
    image_charger(img, argv[1]);
	assert(img != NULL);
        
    /*Table Creation*/
	
	table=FAIRE_image();
	image_charger(table,argv[2]);
	assert(table!=NULL);
	
	/*Color table Creation*/

	ctable=create_color_table(table);
	assert(ctable!=NULL);	
	
	/*Kd_tree Creation*/

	tree=create_kdtree(ctable,10);
	assert(tree!=NULL);

	/*Start the clock*/

	t1 = clock();
	

	/*In this loop we go through all the pixels of the image*/

	image_debut(img);

	do
	{
		/*Get the pixel of the image*/

		pixel = image_lire_pixel(img);

		color_reference[0] = (color) pixel[0];
		color_reference[1] = (color) pixel[1];
		color_reference[2] = (color) pixel[2];

		/*Get the closest pixel of the image using the kd_tree*/

		kdtree_get_nearest_color(tree, color_reference, closest_pixel);

		newpixel[0] = (int) closest_pixel[0];
		newpixel[1] = (int) closest_pixel[1];
		newpixel[2] = (int) closest_pixel[2];

		/*Write the new pixel in the image*/

		image_ecrire_pixel(img, newpixel);

	} while (image_pixel_suivant(img));

	/*Stop the clock*/

	t2 = clock();

	/*Calculate the time of execution in second*/

	time = (float)(t2 - t1) / CLOCKS_PER_SEC;

	/*Print the time of execution*/

	printf("Inversion colors of %s using kdtree takes %f seconds\n",argv[1], time);

	/*Save the image*/

	image_sauvegarder(img, "Image_Inversion.ppm");

	destroy_kdtree(tree);
		




	return 0;
}
