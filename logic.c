#include <stdlib.h>
#include <stdio.h>
#include "logic.h"
#include "pos.h"
#include "board.h"


//allocates memory and makes  a new game
game* new_game(unsigned int run, unsigned int width, unsigned int height,
               enum type type){
	if(run < 2){
		fprintf(stderr, "run size not possible");
		exit(1);
	}
	if(type == MATRIX){
        	game* new = (game*) malloc(sizeof(game));
		if(new == NULL){
			fprintf(stderr, "error");
			exit(1);
		}

        	new->run = run;
		new->b = board_new(width, height, type);
		new->next = BLACK_NEXT;
		return new;
	} else {
		game* new = (game*) malloc(sizeof(game));
		if(new == NULL){
			fprintf(stderr,"error");
			exit(1);
		}
		new->run = run;
		new->b = board_new(width,height,type);
		new->next = BLACK_NEXT;
		return new;
	}
}
//frees the game
void game_free(game* g){
	board_free(g->b);
	free(g);
}
//gives me the number of the row where the checker should de dropped
int full_row_number(game* g,unsigned int col){
	unsigned int height = g->b->height;
	unsigned int r=0;
	///iterate down the row
	for (int i = height - 1; i >= 0; i--) {
		struct pos p = {i,col};
		if (board_get(g->b,p) == EMPTY){  //g->b->u.matrix[i][col] == EMPTY) {
			r = i;
			break;
		}
	}
		return r;
	
}	

//makes sure the right character is dropped given who's turn it is
cell drop_right_character(game* g){
	
	cell cell_res; 
	if(g->next == BLACK_NEXT){
		cell_res = BLACK;
	}
	if(g->next == WHITE_NEXT){
		cell_res = WHITE; 
	}
	return cell_res;


}

//drops the piece in the board and returns true or false
int drop_piece(game* g, unsigned int col){
	
	int row_number = full_row_number(g,col);
	struct pos p = {0,col};
	if(board_get(g->b,p) /*g->b->u.matrix[0][col]*/ != EMPTY){
	return 0;
	}
	pos pos_curr = make_pos(row_number, col);
	board_set(g->b,pos_curr,drop_right_character(g));
	return 1;
	


}

//rotates the board CW or CCW and simulates gravity
void twist(game* g, direction d){
	printf("do");
	unsigned int width = g->b->width;
	unsigned int height = g->b->height;

	board* new = board_new(height,g->b->width,MATRIX);

	for(int i = 0; i < height;i++){
		for(int j = 0; j < width; j++){
			if(d == CW){
			struct pos p1 = {j,height-i-1};
			struct pos p2 = {i,j};
			cell c = board_get(g->b,p2);
			board_set(new,p1,c);
			//board_get(new,p1) = board_get(g->b,p2);
			//new->u.matrix[j][height-i-1] = g->b->u.matrix[i][j];
			}
			else if (d== CCW) {
				struct pos p3 = {width-j-1,i};
				struct pos p4 = {i,j};
				cell c1 = board_get(g->b,p4);
				board_set(new,p3,c1);
				//board_get(new,p3) = board_get(g->b,p4);
				//new->u.matrix[g->b->width-j-1][i] = g->b->u.matrix[i][j];
			}
		}
	}

	board_free(g->b);
	g->b = new;
	gravity(g->b);
}

//pushes everything down to its lowest point
void gravity(board* b){
	int height = b->height;
	int width = b->width;
	for(int i = height - 2; i>=0;i--){
		for(int j = 0; j<b->width;j++){
			struct pos p1 = {i,j};
			struct pos p2 = {i+1,j};
			if(board_get(b,p1) /*b->u.matrix[i][j]*/ != EMPTY && board_get(b,p2) /*b->u.matrix[i+1][j]*/ == EMPTY){
				unsigned k = i;
				struct pos p3 = {k,j};
				struct pos p4 = {k-1,j};
				do {
					k++;
				} while (k <= height - 1 && board_get(b,p3)/*b->u.matrix[k][j]*/ == EMPTY);
					cell c1 = board_get(b,p1);
					board_set(b,p4,c1);
				/*b->u.matrix[k-1][j]*///board_get(b,p4) = board_get(b,p1);/*b->u.matrix[i][j];*/
				/*b->u.matrix[i][j]*/
				 c1 = EMPTY;
			}
		}	
	}
}



//iterates horizontaly to check for a horizontal win
int helper_row(game* g,int j, int i, cell compare_cell)
{	
	int count = 0;
	for(int m = j+1; m < g->b->width; m++){
		struct pos p = {i,m};
		cell curr_cell = board_get(g->b,p); /*g->b->u.matrix[i][m]*/;
		if (curr_cell == compare_cell){
			count++;
			
		}
	}

	return count + 1;
}
//iterates verticaly to check for a vertical win
int helper_column(game* g, int j, int i, cell compare_cell){
	int count = 0;
	for(int m = i + 1; m < g->b->height; m++){
		struct pos p = {m,j};
		cell curr_cell = board_get(g->b,p); /*g->b->u.matrix[m][j]*/ 
		if(curr_cell == compare_cell){
			count++;
		}
	}
	return count + 1;
}

//iterates diagonally from top left to bottom right for a diagonal win
int helper_diagonal_down(game* g, int j, int i, cell compare_cell){
	//printf("start\n");
	int count = 0;
	int count_add = 1; 
	int width = g->b->width;
	int height = g->b->height;

		for(int m = j + 1; m < g->b->width; m++){
			if(j+1 < width && (i+count_add) < height){
			struct pos p = {i+ count_add,m};
                	 cell curr_cell = board_get(g->b,p); /*g->b->u.matrix[i+count_add][m];*/
			count_add++;
                 	if(curr_cell == compare_cell){
                         count++;
                 	}
         	}
	}
	return count + 1;
}
//iterates diagonally from bottom left to top right for a diagonal win
int helper_diagonal_up(game* g, int j, int i,cell compare_cell){
         int count = 0;
	int count_sub = 1;
	int width = g->b->width;
	int height = g->b->height;

                 for(int m = j + 1; m < g->b->width; m++){
			if(j+1 < width && (i-count_sub) >= 0){
			struct pos p = {i-count_sub,m};
                          cell curr_cell = board_get(g->b,p); /*g->b->u.matrix[i-count_sub][m];*/
			  count_sub++;
                         if(curr_cell == compare_cell){
                         count++;
                         }
          	}
	}
	return count+1;
}      
                

//convert into the right outcome given a cell value
outcome right_outcome(cell compare_cell){
	
	outcome outcome_game;
	if(compare_cell == BLACK){
		outcome_game = BLACK_WIN;
	}
	if(compare_cell == WHITE){
		outcome_game = WHITE_WIN;
	}
	if(compare_cell == EMPTY){
		outcome_game = IN_PROGRESS;
	}
	return outcome_game;
}
//checks for a horizontal win in the game
//this function also checks for a draw within its own type
outcome horizontal_win(game* g){
	int arr_len = g->b->width * g->b->height;
	outcome arr[arr_len];
	arr[0] = IN_PROGRESS;
	int arr_pos = 0;
	int diff_win = 0;
	for(int i = 0; i < g->b->height; i++){
		for(int j =0; j < g->b->width;j++){
			struct pos p = {i,j};
			cell compare_cell = board_get(g->b,p); /*g->b->u.matrix[i][j];*/
			if(j + g->run <= g->b->width){
			int count = helper_row(g,j,i,compare_cell);
				if(count >= g->run && compare_cell != EMPTY){
					arr[arr_pos] = right_outcome(compare_cell);
					arr_pos++;
				}
				
			}
			
		}
	}
//checks array
	
	if(arr[0] == BLACK_WIN || arr[0] == WHITE_WIN){
		for(int i = 1; i < arr_pos; i++){
			if(arr[i] != arr[i-1]){
				diff_win++;
			}
		}
	}
	
	if(diff_win != 0){
			return DRAW;
		}
	
	return arr[0];
	
}

//check for a vertical win in the game
//this function also checks for a draw within its own type
outcome vertical_win(game* g){
	int arr_len = g->b->width * g->b->height;
	outcome arr[arr_len];
	arr[0] = IN_PROGRESS;
	int arr_pos = 0;
	int diff_win = 0;
		for(int i = 0; i < g->b->height;i++){
			for(int j = 0; j < g->b->width;j++){
				struct pos p = {i,j};
				cell compare_cell = board_get(g->b,p);/*g->b->u.matrix[i][j];*/
				if(i + g->run <= g->b->height){
				
				int count = helper_column(g,j,i,compare_cell);
					if(count >= g->run && compare_cell != EMPTY){
						arr[arr_pos] = right_outcome(compare_cell);
						arr_pos++;
					}
				}
			}
		}
//check the array
	if(arr[0] == BLACK_WIN || arr[0] == WHITE_WIN){
			for(int i = 1; i < arr_pos; i++){
				if(arr[i] != arr[i-1]){
				diff_win++;
			}
		}
	}

	if(diff_win != 0){
			return DRAW;
	}
	 

	return arr[0];	
	
}
//checks for a diagonal going from top left to bottom right	
//this function also checks for a draw within its own type
outcome diagonal_down_win(game* g) {
	int arr_len = g->b->width * g->b->height;
	outcome arr[arr_len];
	arr[0] = IN_PROGRESS;
	int arr_pos = 0;
	int diff_win = 0;
	for(int i = 0; i < g->b->height;i++){
		for(int j = 0; j < g->b->width;j++){
		struct pos p = {i,j};
		cell compare_cell = board_get(g->b,p); /*g->b->u.matrix[i][j];*/
		int count = helper_diagonal_down(g,j,i,compare_cell);
			//printf("count: %d \n",count);
			if(count >= g->run && compare_cell != EMPTY){
				arr[arr_pos] = right_outcome(compare_cell);
				arr_pos++;
			}
		}
	}
//checks the array
	if(arr[0] == BLACK_WIN || arr[0] == WHITE_WIN){
			for(int i = 1; i < arr_pos; i++){
				if(arr[i] != arr[i-1]){
				diff_win++;
				}
			}
		}
		if(diff_win != 0){
			return DRAW;
		}
	return arr[0];
}

//checks for a diagonal going from bottom left to top right
//this function also checks for a draw within its own type
outcome diagonal_up_win(game* g){
	int arr_len = g->b->width * g->b->height;
	outcome arr[arr_len];
	arr[0] = IN_PROGRESS;
	int arr_pos = 0;
	int diff_win = 0;
	for(int i = 0; i < g->b->height;i++){
		for(int j = 0; j < g->b->width;j++){
		struct pos p = {i,j};
		cell compare_cell = board_get(g->b,p); /*g->b->u.matrix[i][j];*/
		int count = helper_diagonal_up(g,j,i,compare_cell);
			if(count >= g->run && compare_cell != EMPTY){
				arr[arr_pos] = right_outcome(compare_cell);
				arr_pos++;
			}
		}
	}
//checks array
	if(arr[0] == BLACK_WIN || arr[0] == WHITE_WIN){
			for(int i = 1; i < arr_pos; i++){
				if(arr[i] != arr[i-1]){
				diff_win++;
				}
			}
		}
		if(diff_win != 0){
			return DRAW;
		}

	return arr[0];
}

//converts an outcome to string- used for testing purposes			
void outcome_to_stringl(outcome outcome_t){
         if(outcome_t == BLACK_WIN){
                 printf("Black_win\n");
         }
         else if(outcome_t == WHITE_WIN){
                 printf("White_win\n");
         }
         else if(outcome_t == DRAW){
                 printf("Draw\n");
         }
         else if(outcome_t == IN_PROGRESS){
                 printf("in progress\n");
         } else {
                 printf("ERROR");
         }
 
 }	

//checks if all the game positions are full but theres been no win
int game_full(game* g){
	int width = g->b->width;
	int num_full_col = 0;
	for(int i = 0; i < width;i++){
		if(drop_piece(g,i)==0){
			num_full_col++;
		}
	}
	if(num_full_col == width){
		return 1;
	}
	return 0;
}

//returns the outcome of a game given a game input
outcome game_outcome(game* g){

	outcome curr_outcome = IN_PROGRESS;
	outcome hw = horizontal_win(g);
	outcome vw = vertical_win(g);
	outcome dd = diagonal_down_win(g);
	outcome du = diagonal_up_win(g); 

//test
	if(hw == DRAW || vw == DRAW || dd == DRAW || du == DRAW){
	
		return  DRAW;
	}
 
	if (hw != IN_PROGRESS){

		curr_outcome = hw;
	}
	
	if (vw != IN_PROGRESS){
	
		if(curr_outcome != IN_PROGRESS && vw != curr_outcome){
			return DRAW;
		} else {
			curr_outcome = vw;
			}
	}
	if (dd != IN_PROGRESS){
		if(curr_outcome != IN_PROGRESS && dd != curr_outcome){
			return DRAW;
		} else {
			curr_outcome = dd;
			}
	} 
	if (du != IN_PROGRESS){
		if(curr_outcome != IN_PROGRESS && du != curr_outcome){
			return DRAW;
		} else {
			curr_outcome = du;
		}
	} 
	if (game_full(g) == 1){
		return DRAW;
	}

	return curr_outcome;
}	

	
 	







