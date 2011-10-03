#include <stdio.h>
#include <stdlib.h>
#include "read_biotopefile.h"
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
biotope* read_biotopefile(int max_x,int max_y,char* filename){
	if(debug) printf("Parsing %s\n", filename);

	FILE* fh = fopen(filename, "r");
	if(fh==NULL){
		printf("File read error\n");
		exit(EXIT_FAILURE);
	}

	int x;
	if (max_x>0)
		x = max_x;
	else
		x = eval_x_size(filename);
	char* str	= (char*)malloc(x);	

	fclose(fh);
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
