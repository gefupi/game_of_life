
typdef struct _life_point_{
	int now;
	int then;
} life_point;

struct _biotope_{
	int x;
	int y;
	life_point* field;
} biotope;

