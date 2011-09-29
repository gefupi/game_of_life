
typedef struct _life_point_{
	int now;
	int then;
} life_point;


/* 
 * this function creates a new life point object, which means it will allocates 
 * the needed memory and initialises the new life_point object with the given value
 * @input: life_value - if zero is given no life exists at this this point now
 *                      else life exists on this point now
 * @return: pointer to the new life_point object
 *          OR zero if an error occured (e.g. out of memory, ...)
 */
life_point *init_life_point(int life_value);

/*
 * this function destroys the life_point object wich is pointed to, which means 
 * the allocated memory will be freed and the pointer value will be set to zero
 * @input: this - the pointer to the pointer to life_point object which will be 
 *                destroyed
 */
void destroy_life_point(life_point **this);

/*
 * this function calculates whether life will exist at this location in the 
 * next generation based on the game of life rules.
 * @input: this - the live_point which next genration state will be calculated
 *         living_neighbours - number of living neighbours
 */
void calculate_next_generation(life_point *this, int living_neighbours);

/*
 * this function switches to the next generation and reset the value for next 
 * generation to an invalid value. If function is called and value for next 
 * generation is invalid program execution will be terminated.
 * @input: this - the live_point which will be switched to the next generation
 * @error: if no value has been calculated befor this function is called 
 *         exit(EXIT_FAILURE) will be called
 */
//--------------------------------------------------------------------------------
void next_generation(life_point *this);

/*
 * this function returns the actual state of this live point
 * @input: this - the life_point which life value will be returned
 * @return: 0 - if no life at this point now
 *          1 - if life at this point exists now
 */
int is_living(life_point *this);
