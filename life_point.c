#include "life_point.h"

#include <stdlib.h>
#include <stdio.h>


//--------------------------------------------------------------------------------
life_point *create_life_point(int life_value) {
  life_point *result = malloc(sizeof(life_point));
  if (result) {
    result->now = (life_value == 0) ? 0 : 1;
    result->then = -1;
  }
  return result;
}


//--------------------------------------------------------------------------------
void destroy_life_point(life_point **this) {
  if (this) {
    if (*this)
      free(*this);
    *this = 0;
  }
}


//--------------------------------------------------------------------------------
void calculate_next_generation(life_point *this, int living_neighbours) {
  if (living_neighbours == 3)
    this->then = 1;
  else if ((this->now == 1) && (living_neighbours == 2))
    this->then = 1;
  else
    this->then = 0;
}


//--------------------------------------------------------------------------------
void next_generation(life_point *this) {
  if (this->then == -1) {
    fprintf(stderr, "[FATAL]: cannot switch to next generation, because no value for next generation has been calculated\n");
    exit(EXIT_FAILURE);
  }
  this->now = this->then;
  this->then = -1;
}

//--------------------------------------------------------------------------------
int is_living(life_point *this) {
  return this->now;
}


//--------------------------------------------------------------------------------
void set_life_value(life_point *this, int life_value) {
  this->now = (life_value == 0) ? 0 : 1;
}
