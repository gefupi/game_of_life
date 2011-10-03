#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "std_const.h"
#include "biotope.h"

int debug = FALSE;
int verbose = FALSE;

int main(int argc, char **argv) {

	int x = 0;
	int y = 0;
	int generations = DEFAULT_MAX_GENERATION;
	char* filename=NULL;
  // Parse Opts
  int c;
  // TODO fix output for non existing options and not given argument vor options like -b without file
  while ((c = getopt(argc, argv, "/*:*/vdx:y:hb:g:")) != -1) {
  	switch (c){
	  	case 'h':
	  		printf("-h            : print this help\n");
	  		printf("-x <width>    : max width of the biotope\n");
	  		printf("-y <heigth>   : max heigth of the biotope\n");
	  		printf("-g <count>    : how many generations to simuate\n");
	  		printf("-v            : verbose mode\n");
	  		printf("-d            : debug mode\n");
	  		printf("-b <filename> : biotope filename\n");
	  		exit(EXIT_SUCCESS);
	  		break;
	  	case 'v':
	  		verbose = TRUE;
	  		break;
	  	case 'd':
	  		debug = TRUE;
	  		break;
	  	case 'x':
	  		x = atoi(optarg);
	  		if (x<=0){
	  			printf("width should be larger then zero\n");
	  			exit(EXIT_FAILURE);
	  		}
	  		break;
	  	case 'y':
	  		y = atoi(optarg);
	  		if (y<=0){	
	  			printf("heigth should be larger then zero\n");
	  			exit(EXIT_FAILURE);
	  		}
	  		break;
	  	case 'g':
	  		generations = atoi(optarg);
	  		if (generations<=0){	
	  			printf("generations should be larger then zero\n");
	  			exit(EXIT_FAILURE);
	  		}
	  		break;
	  	case 'b':
	  		filename=optarg;
	  		if (filename==NULL) {
	  			printf("Whats the filename???\n");
	  			exit(EXIT_FAILURE);
	  		} else 
	  			fprintf(stdout, "filename: %s\n", filename);
	  		break;
  	}
  }

  //Print the flags
  if (debug){
  	printf("Flags:\n \tdebug on\n");
  	if(verbose) 
  		printf("\tverbose on\n");
  	else 
  		printf("\tverbose off\n");
  	if (filename!=NULL)
  		printf("\tFilename: %s\n",filename);
  	else
  		printf("\tFilename: ;-(\n");
  	printf("\tBiotope: %ix%i\n",x,y);
  	printf("\tGenerations: %i\n",generations);
	}


  // FIXXXXME - gefupi 20111001 - implemented two boards of different 
  //                              size with F-pentomino on them for testing 
  //                              and debuging purposes
  // small board
  /* biotope *board = init_biotope(147,147); */
  /* set_life_point_value(board, 73, 72, 1); */
  /* set_life_point_value(board, 74, 72, 1); */
  /* set_life_point_value(board, 72, 73, 1); */
  /* set_life_point_value(board, 73, 73, 1); */
  /* set_life_point_value(board, 73, 74, 1); */

  // big board
  //biotope *board = init_biotope(1147,1147);
  //set_life_point_value(board, 573, 572, 1);
  //set_life_point_value(board, 574, 572, 1);
  //set_life_point_value(board, 572, 573, 1);
  //set_life_point_value(board, 573, 573, 1);
  //set_life_point_value(board, 573, 574, 1);

  biotope *board = NULL;
  board = read_biotopefile(filename);



  // after set up board
  switch_on_verbose_mode(board);
    switch_on_debug_mode(board);

  set_max_generation(board, generations);
  start_living(board);
  destroy_biotope(&board);

  // end fixxxxme - gefupi 20111001

  return (EXIT_SUCCESS);
}
