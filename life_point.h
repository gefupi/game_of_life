
typedef struct _life_point_{
	int now;
	int then;
} life_point;



life_point *init_life_point(int life_value);

void destroy_life_point(life_point **this);



