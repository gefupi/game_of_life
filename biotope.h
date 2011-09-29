#include "life_point.h"

typedef struct _biotope_{
	int max_x;
	int max_y;
	struct _life_point_ **field;
} biotope;

