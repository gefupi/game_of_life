#ifndef _BIOTOPE_H_
#define _BIOTOPE_H_

#include "life_point.h"

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


void destroy_biotope(biotope **this);

void set_max_generation(biotope *this, int max_generations);

void switch_on_debug_mode(biotope *this);

void set_life_point_value(biotope *this, int x, int y, int life_value);

void start_living(biotope *this);

#endif
