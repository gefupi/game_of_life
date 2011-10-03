#ifndef _BIOTOPE_H_
#define _BIOTOPE_H_

#include "life_point.h"
#include "std_const.h"

typedef struct _fast_biotope_{
  int max_x;
  int max_y;
  int *field;
  int *next_field;
  unsigned int generation;
  unsigned int population;
  unsigned int max_generation;
  unsigned int population_maximum;
  unsigned int generation_of_population_maximum;
  int debug_mode;
  int verbose_mode;
  int boarder_collision;
} fast_biotope;




/* Constuctor for the "biotop onject"
 * @input:
 *		max_x - max. width of biotope. if zero given determined by file
 *		max_y - max. heigth of biotope. if zero given determined by file
 *		filename - char pointer to biotope-filename
 * @return:
 		pointer to biotope 
*/
fast_biotope* fb_create_biotope(int max_x, int max_y);

/*
 * This functiondestroys the biotope object wich is pointed to, which means 
 * the allocated memory will be freed and the pointer value will be set to zero
 * @input: this - the pointer to the pointer to biotope object which will be 
 *                destroyed and the pointer will be set to NULL
 */
void fb_destroy_biotope(fast_biotope **this);

/*
 * this function sets the member wich is used as termination condition for living.
 * At creation all biotope objects have set this member to DEFAULT_MAX_GENERATION.
 * @input: this - pointer to the biotope object which member should be set
 *         max_generation
 */
void fb_set_max_generation(fast_biotope *this, int max_generation);


/*
 * This function switches on the debug mode of the biotope object which will result 
 * in printing out debug information during execution of start_living().
 * @input: this - pointer to the biotope object which member should be set 
 */
void fb_switch_on_debug_mode(fast_biotope *this);


/*
 * This function switches on the verbose mode of the biotope object which will result
 * in printing out more information during execution of start_living().
 * @input: this - pointer to the biotope object which member should be set 
 */
void fb_switch_on_verbose_mode(fast_biotope *this);


/*
 * This function is used to set life value of the life point at position (x,y).
 * A new biotpoe is created with all life values set to 0 (no life).
 * @input: this - pointer to the biotope object which is used
 *         x - x-coordinate of the position of the affected life point
 *         y - x-coordinate of the position of the affected life point
 *         life_value - TODO
 */
void fb_set_life_point_value(fast_biotope *this, int x, int y, int life_value);

/*
 * This function starts the calculation process. It will race until max generation
 * or extinction is reached wathever happens first. After calculation the result 
 * will be print to stdout.
 * @input: this - pointer to the biotope object which is used
 */
//--------------------------------------------------------------------------------
void fb_start_living(fast_biotope *this);

#endif
