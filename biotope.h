
typedef struct _life_point_{
	int now;
	int then;
} life_point;

typedef struct _biotope_{
	int max_x;
	int max_y;
	life_point** field;
} biotope;

