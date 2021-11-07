#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "pos.h"
#include "logic.h"
#include "board.h"

//valid input
// returns 1 for true and false 0
int valid_ch(char ch){
	if(ch == '<' || ch == '>' ){
		return 1;
	}
	else if(ch >= 0 && ch <= 9){
		return 1;
	}
	else if((char)ch >= 65 && (char)ch <= 90){
		return 1;
	}
	else if((char)ch >= 97 && (char)ch <= 122){
		return 1;
	}else {
		return 0;
	}
}
//makes sure the right action is performed given the character
//entered
int right_action(char ch, game* g){
	int i=0;
	if(ch == '<'){
	twist(g, CCW);
	i=1;
	}
	if(ch == '>'){
	twist(g, CW);
	i=1;
	}
	if(ch >= 0 && ch <= 9)
	 i = drop_piece(g,ch);
	if((char)ch >= 65 && (char)ch <= 90)
	i = drop_piece(g,(char)ch-55);
	if((char)ch >= 97 && (char)ch <= 122)
	i = drop_piece(g,(char)ch-61);
	
	return i;
}
//convert the turn into its string form	
void turn_to_string(turn t){
	if(t == BLACK_NEXT){
		printf("Black\n");
	}
	if(t == WHITE_NEXT){
		printf("While\n");
	}
}
//switches the turn
turn switch_turn(turn t){
	if(t==BLACK_NEXT){
		t=WHITE_NEXT;
	}	else{
			t=BLACK_NEXT;
		}
	return t;
}
	

int main(int argc, char* argv[]){
	//set default values
	unsigned int width = 10;
	unsigned int height = 10;
	unsigned int run = 4;
	enum type type = MATRIX;
	int type_set = 0;
	//create an error if the type already specified
		for(int i = 0; i < argc; i++){
			if(strcmp(argv[i], "-w") == 0){
				width = atof(argv[i+1]);
			}else if(strcmp(argv[i], "-h") == 0){
				height = atof(argv[i+1]);
			}else if(strcmp(argv[i], "-r") == 0){
				run = atof(argv[i+1]);
			}else if(strcmp(argv[i], "-m")==0){
				if(type_set != 0){
					fprintf(stderr, "main: types already set\n");
					exit(1);
				}
				type = MATRIX;
				type_set = 1;
			}else if(strcmp(argv[i], "-b")==0){
				if(type_set != 0){
					fprintf(stderr,"main: type already specified\n");
					exit(1);
				}
				type = BITS;
				type_set = 1;
				}
				
		}
	game* g = new_game(run,width,height,type);

	printf("Welcome to Marie's fabulous game\n");
	printf("pick the width,height and run of the game\n");
	printf("follow the following syntax to put in you values \n");
	printf(" -w value -h value -r value\n");
	board_show(g->b);	
	while(game_outcome(g) == IN_PROGRESS){
		printf("??\n");
		board_show(g->b);
	 	printf("turn: ");
		turn_to_string(g->next);
		
		printf("enter either the column or rotate character");
		char ch;
		scanf("%c%*c", &ch);
		if(valid_ch(ch)==1){
			int i = right_action(ch,g);
				if(i == 0){
					printf("column is full");
				} else{
				g->next = switch_turn(g->next);
				printf("turns over\n");
				}
			
		}else if(valid_ch(ch) != 1){
				printf("character entered was invalid\n");
			}
		
	}
	if(game_outcome(g) == BLACK_WIN){
		board_show(g->b);
		printf("Black player won\n");
	}
	else if(game_outcome(g) == WHITE_WIN){
		printf("White player won \n");
	} else {
		printf("Draw");
	}
	printf("\n");
	return 0;
}
