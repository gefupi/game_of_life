#include "biotope.h"
//#include "life_point.h" // already included in biotope.h
#include "std_const.h"

#include <stdio.h>
#include <stdlib.h>

int init_field(biotope *this);

//--------------------------------------------------------------------------------
biotope* init_biotope(int max_x,int max_y){
  biotope* this = (biotope*)malloc(sizeof(biotope));
  if (this) {
    if ((max_x <=0)||(max_y<=0)){
      free(this);
      fprintf(stderr, "X or Y fucked up in init_biotope\n");
      exit(EXIT_FAILURE);
    }
    // init members
    this->max_x = max_x;
    this->max_y = max_y;
    this->generation = 0;
    this->population = 0;
    this->max_generation = DEFAULT_MAX_GENERATION;
    this->population_maximum = 0;
    this->generation_of_population_maximum = 0;

    // init field
    if (init_field(this) == EXIT_FAILURE) {
      // TODO: some failure occered during field init (e.g. out of memory)
      //         deinitialize field and this biotope
      //         this= 0;
    }
  } // if (this)
  return this;
}


//--------------------------------------------------------------------------------
void destroy_biotope(biotope **this) {
  // TODO: implement this function
}


//--------------------------------------------------------------------------------
void set_max_generation(biotope *this, int max_generations) {
  this->max_generation = max_generations;
}


//--------------------------------------------------------------------------------
void set_life_point_value(biotope *this, int x, int y, int life_value) {
  if ((is_living(this->field[y][x]) == 0) && (life_value == 1))
    this->max_generation++;
  else if ((is_living(this->field[y][x]) == 1) && (life_value == 0))
    this->max_generation--;
  set_life_value(this->field[y][x], life_value);
}


//--------------------------------------------------------------------------------
void start_living(biotope *this) {
  // TODO: implement this function
}


/*
 *     private functions
 */



//--------------------------------------------------------------------------------
int init_field(biotope *this) {
  int out_of_mem_error = FALSE;
  int x = 0;
  int y = 0;
  this->field = malloc((this->max_y)*(sizeof(life_point **)));
  if (!this->field)
    out_of_mem_error = TRUE;
  for (y = 0; y < this->max_y; y++) {
    this->field[y] = malloc((this->max_x)*(sizeof(life_point *)));
    if (!this->field[y])
      out_of_mem_error = TRUE;
  }
  if (out_of_mem_error == FALSE) {
    for (y = 0; y < this->max_y; y++) {
      for (x = 0; x < this->max_x; x++) {
	this->field[y][x] = create_life_point(0);
      } // for x
    } // for y
  } // if (out_of_memory == FALSE)
  return (EXIT_FAILURE);
}
