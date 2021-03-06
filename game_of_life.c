#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "std_const.h"
#include "biotope.h"
#include "fast_biotope.h"

int debug = FALSE;
int verbose = FALSE;

int main(int argc, char **argv) {

	int x = 0;
	int y = 0;
	int generations = DEFAULT_MAX_GENERATION;
	char* filename=NULL;
	int frames = 1;
  // Parse Opts
  int c;
  // TODO fix output for non existing options and not given argument vor options like -b without file
  while ((c = getopt(argc, argv, "/*:*/vdx:y:hb:g:f:")) != -1) {
    switch (c){
    case 'h':
      printf("-h            : print this help\n");
      printf("-x <width>    : max width of the biotope\n");
      printf("-y <heigth>   : max heigth of the biotope\n");
      printf("-g <count>    : how many generations to simuate\n");
      printf("-v            : verbose mode\n");
      printf("-d            : debug mode\n");
      printf("-b <filename> : biotope filename\n");
      printf("-f <frames>   : set framerate");
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
      } 
      break;
    case 'f':
      frames = atoi(optarg);
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
	printf("\tFrames: %i\n", frames);
	}


  /* biotope *board = NULL; */
  /* board = read_biotopefile(filename); */

  /* // after set up board */
  /* if (verbose) switch_on_verbose_mode(board); */
  /* if (debug) switch_on_debug_mode(board); */

  /* set_max_generation(board, generations); */
  /* start_living(board); */
  /* destroy_biotope(&board); */

  /*
  fast_biotope *fast_board = fb_create_biotope(303,303);
  fb_set_life_point_value(fast_board, 151, 150, LIFE);
  fb_set_life_point_value(fast_board, 152, 150, LIFE);
  fb_set_life_point_value(fast_board, 150, 151, LIFE);
  fb_set_life_point_value(fast_board, 151, 151, LIFE);
  fb_set_life_point_value(fast_board, 151, 152, LIFE);
  */

  fast_biotope *fast_board =  read_biotopefile(filename);

  fb_set_max_generation(fast_board, generations);
  if (frames)
    fb_set_framerate(fast_board, frames);
  if (verbose)
    fb_switch_on_verbose_mode(fast_board);
  fb_start_living(fast_board);
  fb_destroy_biotope(&fast_board);


  /* biotope *board = init_biotope(303,303); */
  /* set_life_point_value(board, 151, 150, LIFE); */
  /* set_life_point_value(board, 152, 150, LIFE); */
  /* set_life_point_value(board, 150, 151, LIFE); */
  /* set_life_point_value(board, 151, 151, LIFE); */
  /* set_life_point_value(board, 151, 152, LIFE); */
  
  /* set_max_generation(board, generations); */
  /* start_living(board); */
  /* destroy_biotope(&board); */

  return (EXIT_SUCCESS);
}
