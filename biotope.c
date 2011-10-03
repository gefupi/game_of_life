#include "biotope.h"
#include "std_const.h"

#include <stdio.h>
#include <stdlib.h>

int init_field(biotope *this);
int get_living_neighbours_count(biotope *this, int x, int y);
void calculate_next_generation_step(biotope *this);
void switch_to_next_gereation(biotope *this);
void update_population(biotope *this);
void print_result(biotope *this);
void print_debug_info(biotope *this);
void print_verbose_info(biotope *this);


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
    this->field = NULL;
    this->max_x = max_x;
    this->max_y = max_y;
    this->generation = 0;
    this->population = 0;
    this->max_generation = DEFAULT_MAX_GENERATION;
    this->population_maximum = 0;
    this->generation_of_population_maximum = 0;
    this->debug_mode = FALSE;
    this->verbose_mode = FALSE;
    this->boarder_collision = 0;
    // init field
    if (init_field(this) == EXIT_FAILURE) {
      destroy_biotope(&this);
    }
  } // if (this)
  return this;
}


//--------------------------------------------------------------------------------
void destroy_biotope(biotope **this) {
  int x = 0;
  int y = 0;
  if (this && *this) {
    if ((*this)->field) {
      for (x = 0; x < (*this)->max_x; x++) {
      	if ((*this)->field[x]) {
	  for (y = 0; y < (*this)->max_y; y++) {
      	    if ((*this)->field[x][y])
      	      destroy_life_point(&((*this)->field[x][y]));
      	  } // for y
      	  free((*this)->field[x]);
      	  (*this)->field[x] = NULL;
      	}
      } // for x
      free((*this)->field);
      (*this)->field = NULL;
    }
    free(*this);
    this = 0;
  }
}


//--------------------------------------------------------------------------------
void set_max_generation(biotope *this, int max_generation) {
  this->max_generation = max_generation;
}


//--------------------------------------------------------------------------------
void switch_on_debug_mode(biotope *this) {
  this->debug_mode = TRUE;
}


//--------------------------------------------------------------------------------
void switch_on_verbose_mode(biotope *this) {
  this->verbose_mode = TRUE;
}


//--------------------------------------------------------------------------------
void set_life_point_value(biotope *this, int x, int y, int life_value) {
  if ((is_living(this->field[x][y]) == 0) && (life_value == 1))
    this->max_generation++;
  else if ((is_living(this->field[x][y]) == 1) && (life_value == 0))
    this->max_generation--;
  set_life_value(this->field[x][y], life_value);
}


//--------------------------------------------------------------------------------
void start_living(biotope *this) {
  fprintf(stdout, "start living until generation %d is reached:\n", this->max_generation);
  if (this->debug_mode)
      print_debug_info(this);    
  do {
    calculate_next_generation_step(this);
    switch_to_next_gereation(this);
    if ((this->generation) < 5 && (this->debug_mode))
      print_debug_info(this);
    if (this->generation % 100 /* 1000000 */ == 0) {
      if (this->verbose_mode) {
	print_verbose_info(this);
      } else {
	fprintf(stdout, ".");
	fflush(stdout);
      }
    }
  } while ((this->generation < this->max_generation) && (this->population > 0));
  fprintf(stdout, "\n");
  print_result(this);
}




/*
 *     private functions
 */


/*
 * This function is used to initialise the field and all the life points in this 
 * field.
 * @input: this - pointer to the biotope object which field should be initialized
 * @return: EXIT_SUCCESS - if no error occured during field initialization
 *          EXIT_FAILURE - an error occured, field is not initialized correctly
 *                         (e.g. out of memory, ...)
 */
//--------------------------------------------------------------------------------
int init_field(biotope *this) {
  int out_of_mem_error = FALSE;
  int x = 0;
  int y = 0;
  this->field = malloc((this->max_x)*(sizeof(life_point **)));
  if (!this->field)
    out_of_mem_error = TRUE;
  for (x = 0; x < this->max_x; x++) {
    this->field[x] = malloc((this->max_y)*(sizeof(life_point *)));
    if (!this->field[x])
      out_of_mem_error = TRUE;
  }
  if (out_of_mem_error == FALSE) {
    for (x = 0; x < this->max_x; x++) {
      for (y = 0; y < this->max_y; y++) {
  	this->field[x][y] = create_life_point(0);
	if (!this->field[x][y])
	  out_of_mem_error == TRUE;
      } // for y
    } // for x
  } // if (out_of_memory == FALSE)
  return (out_of_mem_error == TRUE) ? (EXIT_FAILURE) : (EXIT_SUCCESS);
}


/*
 * This function calculates how many living neigbours the life point at 
 * position (x,y) has.
 * @input: this - pointer to the biotope object which is used
 *         x - x-coordinate of the position of the life point
 *         y - x-coordinate of the position of the life point
 * @return: number of living neighbours, which will be in interval [0,8]
 */
//--------------------------------------------------------------------------------
int get_living_neighbours_count(biotope *this, int x, int y) {
  // ASSERT: biotope (this) was initialized correctly and is not NULL
  int result = 0;
  // checking ...
  // ... left ...
  if (x-1 >= 0) {
    if (is_living(this->field[x-1][y]))
      result++;
  }
  // ... left & up ...
  if ((x-1 >= 0) && (y-1 >= 0)) {
    if (is_living(this->field[x-1][y-1]))
      result++;
  }
  // ... up ...
  if (y-1 >= 0) {
    if (is_living(this->field[x][y-1]))
      result++;
  }
  // ... up & right ...
  if ((y-1 >= 0) && (x+1 < this->max_x)) {
    if (is_living(this->field[x+1][y-1]))
      result++;
  }
  // ... right ...
  if (x+1 < this->max_x) {
    if (is_living(this->field[x+1][y]))
      result++;
  }
  // ... right & down ...
  if ((x+1 < this->max_x) && (y+1 < this->max_y)) {
    if (is_living(this->field[x+1][y+1]))
      result++;
  }
  // ... down ...
  if (y+1 < this->max_y) {
    if (is_living(this->field[x][y+1]))
      result++;
  }
  // ... down & left
  if ((y+1 < this->max_y) && (x-1 >= 0)) {
    if (is_living(this->field[x-1][y+1]))
      result++;
  }
  return result;
}


/*
 * This function calls the function to calculate life value of next generation for 
 * each life point in field.
 * @input: this - pointer to the biotope object which is used 
 */
//--------------------------------------------------------------------------------
void calculate_next_generation_step(biotope *this) {
  // ASSERT: biotope (this) was initialized correctly and is not NULL
  // ENHANCEMENT TODO: use threads to speed up this calculations
  int x = 0;
  int y = 0;
  for (x = 0; x < this->max_x; x++) {
    for (y = 0; y < this->max_y; y++) {
      // this will print out some neighbour calculations, only useful for debuging small boards at fisrt states
      /* if ((this->debug_mode) && (this->generation < 3)) */
      /* 	fprintf(stdout, "x=%d, y=%d, neighbours=%d\t\t", x, y, get_living_neighbours_count(this, x, y)); */
      calculate_next_generation(this->field[x][y], get_living_neighbours_count(this, x, y));
    }
  }
}


/*
 * This function calls the function to switch a life point to the next generation 
 * for each life point in field. Afterwards generation counter is increased and 
 * update_population is called.
 * @input: this - pointer to the biotope object which is used 
 */
//--------------------------------------------------------------------------------
void switch_to_next_gereation(biotope *this) {
  // ASSERT: biotope (this) was initialized correctly and is not NULL
  int x = 0;
  int y = 0;
  for (x = 0; x < this->max_x; x++) {
    for (y = 0; y < this->max_y; y++) {
      next_generation(this->field[x][y]);
      if ((this->boarder_collision == FALSE) 
	  && ((x == 0) || (x == this->max_x) || (y == 0) || (y == this->max_y))
	  && (is_living(this->field[x][y]))) {
	this->boarder_collision = TRUE;
	fprintf(stdout, "[WARNING]: boarder collision detected!\n");
      }
    }
  }
  this->generation++;
  update_population(this);
}


/*
 * This function updates the local members population and its maximum. It is 
 * called at the end of each step to next generation.
 * @input: this - pointer to the biotope object which will be affected
 */
//--------------------------------------------------------------------------------
void update_population(biotope *this) {
  // ASSERT: biotope (this) was initialized correctly and is not NULL
  this->population = 0;
  int x = 0;
  int y = 0;
  for (x = 0; x < this->max_x; x++) {
    for (y = 0; y < this->max_y; y++) {
      this->population += is_living(this->field[x][y]);
    }
  }
  if (this->population > this->population_maximum) {
    this->population_maximum = this->population;
    this->generation_of_population_maximum = this->generation;
  } 
}


/*
 * This function prints the result of the biotope calculation, e.g. population, 
 * population maximum, generation of population maximum, ...
 * @input: this - pointer to the biotope object which is used  
 */
//--------------------------------------------------------------------------------
void print_result(biotope *this) {
  // ASSERT: biotope (this) was initialized correctly and is not NULL
  if (this->boarder_collision)
    fprintf(stdout, "[WARNING]: boarder collision detected!\n           Calculated result may be incorrect!\n");
  if (this->population) {
    fprintf(stdout, "reached generation %5d\n", this->generation);
    fprintf(stdout, "actual population: %5d\n", this->population);
  } else {
    fprintf(stdout, "extinction!\nlast life has been in generation: %5d\n", this->generation-1);
  }
  fprintf(stdout, "maximum population has been: %8d\n", this->population_maximum);
  fprintf(stdout, "the population maximum has been reached in generation %5d for the firs time\n", 
	  this->generation_of_population_maximum);
}


/*
 * This function prints out the board, wich only is useful for small boards
 * @input: this - pointer to the biotope object which is used 
 */
//--------------------------------------------------------------------------------
void print_debug_info(biotope *this) {
  // ASSERT: biotope (this) was initialized correctly and is not NULL
  int x = 0;
  int y = 0;
  fprintf(stdout, "[DEBUG]: generation: %d\n", this->generation);
  for (y = 0; y < this->max_y; y++) {
    for (x = 0; x < this->max_x; x++) {
      fprintf(stdout, "%d", is_living(this->field[x][y]));
    }
    fprintf(stdout, "\n");
  }
  fprintf(stdout, "\n\n");
}


/* 
 * This function prints out some information like actual generation, population
 * maximum, ...
 * @input: this - pointer to the biotope object which is used 
 */
//--------------------------------------------------------------------------------
void print_verbose_info(biotope *this) {
  fprintf(stdout, "generation: %d\n", this->generation);
  fprintf(stdout, "population maximum (generation of max, max): %d,%d", this->generation_of_population_maximum, this->population_maximum);
  fprintf(stdout, "\n\n");
}
