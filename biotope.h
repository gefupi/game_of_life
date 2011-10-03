#ifndef _BIOTOPE_H_
#define _BIOTOPE_H_

#include "life_point.h"
#include "std_const.h"

typedef struct _biotope_{
  int max_x;
  int max_y;
  life_point ***field;
  unsigned int generation;
  unsigned int population;
  unsigned int max_generation;
  unsigned int population_maximum;
  unsigned int generation_of_population_maximum;
  int debug_mode;
  int verbose_mode;
  int boarder_collision;
} biotope;




/* Constuctor for the "biotop onject"
 * @input:
 *		max_x - max. width of biotope. if zero given determined by file
 *		max_y - max. heigth of biotope. if zero given determined by file
 *		filename - char pointer to biotope-filename
 * @return:
 		pointer to biotope 
*/
biotope* init_biotope(int max_x, int max_y);

/*
 * This functiondestroys the biotope object wich is pointed to, which means 
 * the allocated memory will be freed and the pointer value will be set to zero
 * @input: this - the pointer to the pointer to biotope object which will be 
 *                destroyed and the pointer will be set to NULL
 */
void destroy_biotope(biotope **this);

/*
 * this function sets the member wich is used as termination condition for living.
 * At creation all biotope objects have set this member to DEFAULT_MAX_GENERATION.
 * @input: this - pointer to the biotope object which member should be set
 *         max_generation
 */
void set_max_generation(biotope *this, int max_generation);


/*
 * This function switches on the debug mode of the biotope object which will result 
 * in printing out debug information during execution of start_living().
 * @input: this - pointer to the biotope object which member should be set 
 */
void switch_on_debug_mode(biotope *this);


/*
 * This function switches on the verbose mode of the biotope object which will result
 * in printing out more information during execution of start_living().
 * @input: this - pointer to the biotope object which member should be set 
 */
void switch_on_verbose_mode(biotope *this);


/*
 * This function is used to set life value of the life point at position (x,y).
 * A new biotpoe is created with all life values set to 0 (no life).
 * @input: this - pointer to the biotope object which is used
 *         x - x-coordinate of the position of the affected life point
 *         y - x-coordinate of the position of the affected life point
 *         
 */
void set_life_point_value(biotope *this, int x, int y, int life_value);

/*
 * This function starts the calculation process. It will race until max generation
 * or extinction is reached wathever happens first. After calculation the result 
 * will be print to stdout.
 * @input: this - pointer to the biotope object which is used
 */
//--------------------------------------------------------------------------------
void start_living(biotope *this);

#endif
