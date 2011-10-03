#include "fast_biotope.h"
#include "std_const.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int fb_init_fields(fast_biotope *this);
int fb_get_living_neighbours_count(fast_biotope *this, int x, int y);
void fb_calculate_next_generation_step(fast_biotope *this);
void fb_switch_to_next_gereation(fast_biotope *this);
void fb_update_population(fast_biotope *this);
void fb_print_result(fast_biotope *this);
void fb_print_debug_info(fast_biotope *this);
void fb_print_verbose_info(fast_biotope *this);
void fb_print_biotope(fast_biotope *this);


//--------------------------------------------------------------------------------
fast_biotope* fb_create_biotope(int max_x, int max_y) {
  if ((max_x <= 0) || (max_y <= 0)) {
    fprintf(stdout, "cannot create biotope of size %d X %d (x X y)", max_x, max_y);
    return NULL;  
  }
  fast_biotope* result = (fast_biotope*)malloc(sizeof(fast_biotope));
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
  result->framerate = 0;
  // init field and next_field
  if (fb_init_fields(result) == EXIT_FAILURE) {
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
    this->max_generation = max_generation;
}

//--------------------------------------------------------------------------------
void fb_switch_on_debug_mode(fast_biotope *this) {
  this->debug_mode = TRUE;
}

//--------------------------------------------------------------------------------
void fb_switch_on_verbose_mode(fast_biotope *this) {
  this->verbose_mode = TRUE;
}

void fb_set_framerate(fast_biotope *this, int framerate) {
  this->framerate = framerate;
}


//--------------------------------------------------------------------------------
void fb_set_life_point_value(fast_biotope *this, int x, int y, int life_value) {
  int index = (x * y) + x;
  if ((this->field[index] == DEAD) && (life_value == LIVE))
    this->population++;
  else
    this->population--;
  this->field[index] = life_value;
}

//--------------------------------------------------------------------------------
void fb_start_living(fast_biotope *this) {
  fprintf(stdout, "start living until generation %d is reached:\n", this->max_generation);
  do {
    /* calculate_next_generation_step(this); */
    /* switch_to_next_gereation(this); */
    if ((this->generation) < 5 && (this->debug_mode))
      /* print_debug_info(this); */
    if (this->generation % 100 /* 1000000 */ == 0) {
      if (this->verbose_mode) {
	/* print_verbose_info(this); */
      } else {
	fprintf(stderr, ".");
	fflush(stderr);
      }
    }
    if ((this->framerate) && (this->generation % this->framerate == 0)) {
      /* print_biotope(); */
    }
  } while ((this->generation < this->max_generation) && (this->population > 0));
  fprintf(stderr, "\n");
  /* print_result(this); */
}



/*
 *     private functions
 */


//--------------------------------------------------------------------------------
int fb_init_fields(fast_biotope *this) {
    this->field = malloc(this->max_x * this->max_y *sizeof(int));
    this->next_field = malloc(this->max_x * this->max_y *sizeof(int));
    if (!(this->field) || !(this->next_field)) {
      return (EXIT_FAILURE);
    }
    memset(this->field, DEAD, (this->max_x * this->max_y *sizeof(int)));
    memset(this->next_field, INVALID, this->max_x * this->max_y *sizeof(int));
    return (EXIT_SUCCESS);
}


//--------------------------------------------------------------------------------
int fb_get_living_neighbours_count(fast_biotope *this, int x, int y) {
  int result = 0;
  // TODO: implement this function
  return result;
}


//--------------------------------------------------------------------------------
void fb_calculate_next_generation_step(fast_biotope *this) {
  
}


//--------------------------------------------------------------------------------
void fb_switch_to_next_gereation(fast_biotope *this) {

}


//--------------------------------------------------------------------------------
void fb_update_population(fast_biotope *this) {
  
}


//--------------------------------------------------------------------------------
void fb_print_result(fast_biotope *this) {

}


//--------------------------------------------------------------------------------
void fb_print_debug_info(fast_biotope *this) {

}


//--------------------------------------------------------------------------------
void fb_print_verbose_info(fast_biotope *this) {

}

//--------------------------------------------------------------------------------
void fb_print_biotope(fast_biotope *this) {

}
