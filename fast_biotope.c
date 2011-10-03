#include "fast_biotope.h"
#include "std_const.h"

#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------
fast_biotope* fb_create_biotope(int max_x, int max_y) {
  if ((max_x <= 0) || (max_y <= 0)) {
    fprintf(stdout, "cannot create biotope of size %d X %d (x X y)", max_x, max_y);
    return NULL;  
  }
  biotope* result = (fast_biotope*)malloc(sizeof(fast_biotope));
  if (!result)
    return NULL;
  result->field = NULL;
  result->next_field = NULL;
  result->max_x = max_x;
  result->max_y = max_y;
  result->generation = 0;
  result->population = 0;
  result->max_generation = DEFAULT_MAX_GENERATION;
  result->population_maximum = 0;
  result->generation_of_population_maximum = 0;
  result->debug_mode = FALSE;
  result->verbose_mode = FALSE;
  result->boarder_collision = 0;
  // init field and next_field
  if (init_fields(result) == EXIT_FAILURE) {
    fb_destroy_biotope(&result);
  }
  return result;
}


//--------------------------------------------------------------------------------
void fb_destroy_biotope(fast_biotope **this) {
  if ((this) && (*this)) {
    if ((*this)->field)
      free((*this)->field);
    if ((*this)->next_field)
      free((*this)->next_field);
    (*this)->field = NULL;
    (*this)->next_field = NULL;
    free(*this);
    *this = NULL;
  }
}

//--------------------------------------------------------------------------------
void fb_set_max_generation(fast_biotope *this, int max_generation) {

}

//--------------------------------------------------------------------------------
void fb_switch_on_debug_mode(fast_biotope *this) {

}

//--------------------------------------------------------------------------------
void fb_switch_on_verbose_mode(fast_biotope *this) {

}

//--------------------------------------------------------------------------------
void fb_set_life_point_value(fast_biotope *this, int x, int y, int life_value) {

}

//--------------------------------------------------------------------------------
void fb_start_living(fast_biotope *this) {

}



/*
 *     private functions
 */


//--------------------------------------------------------------------------------
int init_fields(fast_biotope *this) {
    this->field = malloc(this->max_x * this->max_y *sizeof(int));
    this->next_field = malloc(this->max_x * this->max_y *sizeof(int));
    if (!(this-field) || !(this->next_field)) {
      return (EXIT_FAILURE);
    }
    memset(this->field, 0, this->max_x * this->max_y *sizeof(int));
    memset(this->next_field, 0, this->max_x * this->max_y *sizeof(int));
    return (EXIT_SUCCESS);
}
