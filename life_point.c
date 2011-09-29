#include "life_point.h"

#include <stdlib.h>

life_point *init_life_point(int life_value) {
  life_point *result = malloc(sizeof(life_point));
  if (result) {
    result->now = (life_value == 0) ? 0 : 1;
    result->then = -1;
  }
  return result;
}

void destroy_life_point(life_point **this) {
  if (this) {
    if (*this)
      free(*this);
    *this = 0;
  }
}


