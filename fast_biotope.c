#include "fast_biotope.h"
#include "std_const.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int fb_init_fields(fast_biotope *this);
int fb_get_living_neighbours_count(fast_biotope *this, int x, int y);
char fb_calculate_next_generation_step(fast_biotope *this);
void fb_calculate_next_generation(fast_biotope *this, int index, int living_neighbours);
void fb_switch_to_next_gereation(fast_biotope *this);
void fb_switch_to_next_gereation_and_resize_field(fast_biotope *this, char resize_info);
int resize_field(fast_biotope *this, char directions);
void fb_update_population(fast_biotope *this);
void fb_print_result(fast_biotope *this);
void fb_print_debug_info(fast_biotope *this);
void fb_print_verbose_info(fast_biotope *this);
void fb_print_biotope(fast_biotope *this);


/* typedef struct _next_gen_thread_args_ { */
/*   int start_x; */
/*   int end_x; */
/*   int start_y; */
/*   int end_y; */
/* } next_gen_thread_args; */


//--------------------------------------------------------------------------------
fast_biotope* fb_create_biotope(int max_x, int max_y) {
  if ((max_x <= 0) || (max_y <= 0)) {
    fprintf(stderr, "cannot create biotope of size %d X %d (x X y)", max_x, max_y);
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


//--------------------------------------------------------------------------------
void fb_set_framerate(fast_biotope *this, int framerate) {
  this->framerate = framerate;
}


//--------------------------------------------------------------------------------
void fb_set_life_point_value(fast_biotope *this, int x, int y, int life_value) {
  int index = (this->max_x * y) + x;
  if ((this->field[index] == DEAD) && (life_value == LIVE))
    this->population++;
  else
    this->population--;
  this->field[index] = life_value;
}


//--------------------------------------------------------------------------------
void fb_start_living(fast_biotope *this) {
  char resize_info = 0;
  fprintf(stderr, "start living until generation %d is reached:\n", this->max_generation);
  do {
    resize_info = 0;
    resize_info = fb_calculate_next_generation_step(this);
    if (resize_info == NO_RESIZE)
      fb_switch_to_next_gereation(this);
    else {
      fb_switch_to_next_gereation_and_resize_field(this, resize_info);
      /* fprintf(stderr, "field must be resized (%d)\n", resize_info); */
      /* fb_switch_to_next_gereation(this); */
    }    
    if ((this->generation) < 5 && (this->debug_mode))
      /* fb_print_debug_info(this); */
    if (this->generation % 100 /* 1000000 */ == 0) {
      if (this->verbose_mode) {
	/* fb_print_verbose_info(this); */
      } else {
	fprintf(stderr, ".");
	fflush(stderr);
      }
    }
    if ((this->framerate) && (this->generation % this->framerate == 0)) {
      fb_print_biotope(this);
    }
  } while ((this->generation < this->max_generation) && (this->population > 0));
  fprintf(stderr, "\n");
  fb_print_result(this);
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
  int index = (this->max_x * y) + x;
  if ((x > 0) && (x < this->max_x)) {
    if ((y > 0) && (y < this->max_y))
      result += this->field[(this->max_x*(y-1)) + (x-1)];
    if ((y+1 < this->max_y) && (y >= 0))
      result += this->field[(this->max_x*(y+1)) + (x-1)];
    result += this->field[(this->max_x*y) + (x-1)];
  }
  if ((x+1 < this->max_x) && (x >= 0)) {
    if ((y > 0) && (y < this->max_y))
      result += this->field[(this->max_x*(y-1)) + (x+1)];
    if ((y+1 < this->max_y) && (y >= 0))
      result += this->field[(this->max_x*(y+1)) + (x+1)];
    result += this->field[(this->max_x*y) + (x + 1)];
  }
  if ((y > 0) && (y < this->max_y))
    result += this->field[(this->max_x*(y-1)) + x];
  if ((y+1 < this->max_y) && (y >= 0))
    result += this->field[(this->max_x*(y+1)) + x];
  return result;
}


//--------------------------------------------------------------------------------
char fb_calculate_next_generation_step(fast_biotope *this) {
  char result = NO_RESIZE;
  /* int use_threads = FALSE; */
  /* if (MAX_THREADS > 1) { */
  /*   next_gen_thread_args **thread_args = NULL; */
  /*   pthrad_t **threads = NULL; */
  /*   if (init_threads(this, &thread_args, &threads) == EXIT_SUCCESS)  */
  /*     use_threads = TRUE; */
  /* } */
  /* if (use_threads == TRUE) { */
  /*   // TODO implement thread handling here */
  /* } else { */
  /*   if  */
    int x = 0;
    int y = 0;
    for (x = 0; x < this->max_x; x++) {
      for (y = 0; y < this->max_y; y++) {
	fb_calculate_next_generation(this, ((this->max_x * y) + x), fb_get_living_neighbours_count(this, x, y));
      }
    }
  /* } */
  // check for boarder collision
  for (x = 0; x < this->max_x; x++) {
    for (y = 0; y < this->max_y; y++) {
      if ((x == 0) && (this->next_field[(this->max_x*y) + x] == LIFE))
      	result |= LEFT;
      if ((x+1 == this->max_x) && (this->next_field[(this->max_x*y) + x] == LIFE))
      	result |= RIGHT;
      if ((y == 0) && (this->next_field[(this->max_x*y) + x] == LIFE))
      	result |= UP;
      if ((y+1 == this->max_y) && (this->next_field[(this->max_x*y) + x] == LIFE))
      	result |= DOWN;
    }  
  }
  // unset NO_RESIZE bit if boarder collision is detected
  if ((result & UP) || (result & RIGHT) || (result & DOWN) || (result & LEFT))
    result &= ~NO_RESIZE;
  return result;
}


//--------------------------------------------------------------------------------
void fb_calculate_next_generation(fast_biotope *this, int index, int living_neighbours) {
  if (living_neighbours == 3)
    this->next_field[index] = LIFE;
  else if ((living_neighbours == 2) && (this->field[index] == LIVE))
    this->next_field[index] = LIFE;
  else
    this->next_field[index] = DEAD;
}


//--------------------------------------------------------------------------------
void fb_switch_to_next_gereation(fast_biotope *this) {
  int *old_field = this->field;
  this->field = this->next_field;
  this->next_field = old_field;
  memset(this->next_field, INVALID, this->max_x * this->max_y *sizeof(int));
  this->generation++;
  fb_update_population(this);
}


//--------------------------------------------------------------------------------
void fb_switch_to_next_gereation_and_resize_field(fast_biotope *this, char resize_info) {
  int new_max_x = this->max_x;
  int new_max_y = this->max_y;
  int delta_x = 0;
  int delta_y = 0;
  if (resize_info & UP) {
    new_max_y += DEF_RESIZE_ADDITION;
    delta_y = DEF_RESIZE_ADDITION;
  }
  if (resize_info & DOWN)
    new_max_y += DEF_RESIZE_ADDITION;
  if (resize_info & LEFT) {
    new_max_x += DEF_RESIZE_ADDITION;
    delta_x = DEF_RESIZE_ADDITION;
  }
  if (resize_info & RIGHT)
    new_max_x += DEF_RESIZE_ADDITION;
  if (this->verbose_mode)
    fprintf(stderr, "resizing field %ix%i to %ix%i after generation %i\n", this->max_x, this->max_y, new_max_x, new_max_y, this->generation);
  // resize field
  free(this->field);
  this->field = malloc(new_max_x * new_max_y * sizeof(int));
  if (!this->field) {
    fprintf(stderr, "[ERROR]: Out of memory\n");
    fprintf(stderr, "[FATAL]: Cannot allocate memory for field. Exiting.\n\n");
    exit (EXIT_FAILURE);
  }
  memset(this->field, DEAD, (new_max_x * new_max_y * sizeof(int)));
  // copy next generation into field 
  int y = 0;
  for (y = 0; y < this->max_y; y++) {
    memcpy(&(this->field[((y+delta_y)*new_max_x) + delta_x]), &(this->next_field[y*this->max_x]), this->max_x*sizeof(int));
  }
  //resize next field
  free(this->next_field);
  this->next_field = malloc(new_max_x * new_max_y * sizeof(int));
  if (!this->next_field) {
    fprintf(stderr, "[ERROR]: Out of memory\n");
    fprintf(stderr, "[FATAL]: Cannot allocate memory for next_field. Exiting.\n\n");
    exit (EXIT_FAILURE);
  }
  memset(this->next_field, INVALID, (new_max_x * new_max_y * sizeof(int)));
  // set new x and y maxima
  this->max_x = new_max_x;
  this->max_y = new_max_y;
  // last steps to reach next generation
  this->generation++;
  fb_update_population(this);  
}


//--------------------------------------------------------------------------------
int resize_field(fast_biotope *this, char directions) {
  // TODO: implement this function ???
  return (EXIT_FAILURE);
}


//--------------------------------------------------------------------------------
void fb_update_population(fast_biotope *this) {
  int index = 0;
  int population = 0;
  for (index = 0; index < (this->max_x*this->max_y); index++) {
    if (this->field[index] == LIFE)
      population++;
  }
  this->population = population;
  if (this->population > this->population_maximum) {
    this->population_maximum = this->population;
    this->generation_of_population_maximum = this->generation;
  } 
}


//--------------------------------------------------------------------------------
void fb_print_result(fast_biotope *this) {
  if (this->boarder_collision)
    fprintf(stderr, "[WARNING]: boarder collision detected!\n           Calculated result may be incorrect!\n");
  if (this->population) {
    fprintf(stderr, "reached generation %5d\n", this->generation);
    fprintf(stderr, "actual population: %5d\n", this->population);
  } else {
    fprintf(stderr, "extinction!\nlast life has been in generation: %5d\n", this->generation-1);
  }
  fprintf(stderr, "maximum population has been: %5d\n", this->population_maximum);
  fprintf(stderr, "the population maximum has been reached in generation %5d for the firs time\n", 
	  this->generation_of_population_maximum);
}


//--------------------------------------------------------------------------------
void fb_print_debug_info(fast_biotope *this) {

}


//--------------------------------------------------------------------------------
void fb_print_verbose_info(fast_biotope *this) {

}


//--------------------------------------------------------------------------------
void fb_print_biotope(fast_biotope *this) {
  int x = 0;
  int y = 0;
  for (y = 0; y < this->max_y; y++) {
    for (x = 0; x < this->max_x; x++) {
      if (this->field[(this->max_x * y) + x] == LIVE)
	fprintf(stdout, "1");
      else
	fprintf(stdout, "0");
    }
    if (y+1 < this->max_y)
      fprintf(stdout, "#");
  }
  fprintf(stdout, "\n");
}


