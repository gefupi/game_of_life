#include "biotope.h"
#include "life_point.h"
#include <stdio.h>
#include <stdlib.h>


biotope* init_biotope(int max_x,int max_y){
	biotope* this = (biotope*)malloc(sizeof(biotope));
	if ((max_x <=0)||(max_y<=0)){
		free(this);
		fprintf(stderr, "X or Y fucked up in init_biotope\n");
		exit(EXIT_FAILURE);
	}
	this->max_x=max_x;
	this->max_y=max_y;
}
