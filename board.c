#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "pos.h"
#include "logic.h"

//prints the header
unsigned char header(int i){
	if(i < 10){
		return i + '0';
	}
	else if ( i >= 10 && i < 36){
		return (i + 55);
	}
	else if( i >= 36 && i < 62){
		return (i + 61);
	}
	else{
		return '?';

	}
}

  
//allocates memory and creates a board
board* board_new(unsigned int width, unsigned int height, enum type type){

	if( width == 0 || height == 0){
		fprintf(stderr, " not enough room to play the game");
		exit(1);
	}

		if(type == MATRIX){
			board* new = (board*) malloc(sizeof(board));
			if (new == NULL){
				fprintf(stderr, "error");
				exit(1);
			}
		new->width = width;
		new->height = height;
		new->type = type;
		new->u.matrix = (cell**) malloc(sizeof(cell*)*height);
		for(int i = 0; i < height; i++){
			new->u.matrix[i]  = (cell*) malloc(sizeof(cell)*width);
		}

			for (int r = 0; r < height; r++) {
		  		for (int c = 0; c < width; c++) {
		    			new->u.matrix[r][c] = EMPTY;
		  		}
			}
			return new;
		}
			else {
			board* new = (board*) malloc(sizeof(board));
			if(new == NULL){
				fprintf(stderr, "error");
				exit(1);
			}
			new->width = width;
			new->height = height;
			new->type = type;
			unsigned int arr_size = 0;
			if(arr_size%16 == 0)
				arr_size = (width*height)/16;
			else
				arr_size = (width*height)+1;
			//create the array
			new->u.bits = (unsigned int*) malloc(sizeof(unsigned int) * arr_size);
			for(int i = 0; i < arr_size;i++){
				new->u.bits[i] = 0;
			}
			return new;
		}	
		

}

//frees the board
void board_free(board* b){
	if(b->type == MATRIX){
	for(int i = 0;i < b->height; i++){
		free(b->u.matrix[i]);
	}
	free(b->u.matrix);
	free(b);
	} else {
		free(b->u.bits);
		free(b);
	}
}

//prints the right character given the cell value
void print_right_character(board* b, unsigned int r, unsigned int c){

		struct pos p = {r,c};
		if(/*b->u.matrix[r][c]*/board_get(b,p) == EMPTY){
			printf(".");
		}
		if(/*b->u.matrix[r][c]*/board_get(b,p) == BLACK){
			printf("*");
		}
		if(/*b->u.matrix[r][c]*/board_get(b,p) == WHITE){
			printf("o");
		}


	
}

//shows the board
void board_show(board* b){
	printf(" ");
	for(int i = 0; i < b->width;i++){
		printf("%c",header(i));
	}
  	printf("\n");
  		for(unsigned int r = 0; r < b->height; r++){
    			printf("%c",header(r));
    			for(unsigned int c = 0; c < b->width; c++){
      				print_right_character(b, r, c);
    			}
    		printf("\n");
  	}
}

//retrieves a cell from the board
cell board_get(board* b, pos p){

	if(b->type == MATRIX){

	if(p.r < b->height && p.c < b->width){
		return b->u.matrix[p.r][p.c];
	} else {
		fprintf(stderr, "out of bounds");
		exit(1);
		}
	} else {
		
	//positioning starts from 0 top left?
	unsigned int num_pos = p.c + (p.r *b->width);//not sure
	unsigned int index_array = num_pos/16;
	unsigned int index_array_within = num_pos % 16;
	unsigned int pull = (b->u.bits[index_array] >> (index_array_within*2)) & 3;
	if(pull == 2)
		return WHITE;
	else if(pull == 1)
		return BLACK;
	else
		return EMPTY;
	}

}

//overwrites cell values
void board_set(board* b, pos p, cell c){
	
	if(b->type == MATRIX){
		if(p.r < b->height && p.c < b->width){
			b->u.matrix[p.r][p.c] = c;
			return;
		} else {
			fprintf(stderr, " out of bounds");
			exit(1);
		}
	} else {
	unsigned int num_pos = p.c + (p.r * b->width); // not sure
	unsigned int index_array = num_pos / 16;
	unsigned int index_array_within = num_pos % 16;
	unsigned int set;
	if(c == WHITE)
		set = 2;
	else
		set = 1;

	b->u.bits[index_array] = (set << (index_array_within*2)) | b->u.bits[index_array];
	}	
}
			



