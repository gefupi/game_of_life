#include "life_point.h"

typedef struct _biotope_{
	int max_x;
	int max_y;
	struct _life_point_ **field;
} biotope;

/* Constuctor for the "biotop onject"
 * @input:
 *		max_x - max. width of biotope. if zero given determined by file
 *		max_y - max. heigth of biotope. if zero given determined by file
 *		filename - char pointer to biotope-filename
 * @return:
 		pointer to biotope 
*/
biotope* init_biotope(int max_x,int max_y,char* filename);
