#include <stdio.h>
#include <stdlib.h>
#include "biotope.h"
#include "std_const.h"


extern int debug;
extern int verbose;


int eval_x_size(char* filename){
	FILE* fh = fopen(filename, "r");	
	char c;
	int x=0;
	while(TRUE){
		c=fgetc(fh);
		if ((c==EOF)||(c=='\n'))
			break;
		x++;
	}
	close(fh);
	return x;
}


int eval_y_size(char* filename){
	FILE* fh = fopen(filename, "r");	
	char c;
	int y=0;
	while(TRUE){
		c=fgetc(fh);
		if ((c==EOF))
			break;	
		if (c=='\n')
			y++;		
	}
	close(fh);
	return y;
}


/*
 * Function reads a file and returns a Biotope
 * File example: (1 - live / 0 - not live)
 *    1001
 *		0101
 *		1001
 *		0101
 *
 * @inpute:
 * 		max_x - will set the max. width of bitope. if zero given determined by file
 *		max_y - max. heigth of biotope. if zero given determined by file 
 *		filename - charpointer to biotope-filename
 * @return:
 *		pointer to biotope
*/
biotope* read_biotopefile(char* filename){
	if(debug) printf("Parsing %s\n", filename);

	FILE* fh = fopen(filename, "r");
	if(fh==NULL){
		printf("File read error\n");
		exit(EXIT_FAILURE);
	}

	int bt_x = eval_x_size(filename);
	int bt_y = eval_y_size(filename);
	if(debug) printf("Eval of File (x/y):(%i/%i)\n",bt_x,bt_y);

	biotope* my_biotope = init_biotope(bt_x,bt_y);

	int x = 0;
	int y = 0;
	char c;
	while((c=fgetc(fh))!=EOF){
		if(c=='\n'){
			y++;
			x=0;
			continue;
		}
		if ('1'==c){
			if(debug) printf("Found live at Pos.:(%i/%i)\n",x,y);
			set_life_point_value(my_biotope,x,y,LIVE);
		}
		x++;		
	}
	fclose(fh);
	return my_biotope;
}







//	char c;
//	int x_max_count = 1;
//	int x = 0;
//	int y = 1;
//	while((c=fgetc(datei)) != EOF){
//		if (c=='\n'){
//			y++;
//			if (x>x_max_count)
//				x_max_count = x;
//			x=0;
//			break;
//		}
//		x++;
//	}
