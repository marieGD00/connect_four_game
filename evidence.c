#include <stdlib.h>
#include <stdio.h>
#include "pos.h"
#include "logic.h"
#include "board.h"


void evidence_make_pos(){

	printf("** testing make pos\n");
	//test1
	pos pos_new = make_pos(3,4);
	printf("expecting r: 3 c: 4 \n");
	printf(" r: %d, c: %d \n",pos_new.r,pos_new.c);
	printf("\n");

	//test 2
	pos pos_two = make_pos(10,11);
	printf(" r: %d c: %d \n",pos_two.r,pos_two.c);
	printf("\n");
	printf("------------------end make pos test-------------\n");
}

//void evidence_print_right_character()

void evidence_board_set(){
	printf("** testing board set\n");

	//test one
	board *board_one = board_new(3,4,MATRIX);
	pos pos_one = make_pos(0,0);
	board_set(board_one,pos_one,BLACK);
	printf("tasting board one\n");
	board_show(board_one);
	printf("\n");

	//test two
	board *board_two = board_new(5,4,MATRIX);
	pos pos_two = make_pos(2,1);
	printf("testing board two \n");
	board_set(board_two,pos_two,WHITE);
	board_show(board_two);
	printf("\n");

	//test three out of bounds
	printf("testing board out of bounds\n");
	board *board_three = board_new(2,2,MATRIX);
	pos pos_three = make_pos(4,5);
	//board_set(board_three,pos_three,WHITE);
	//board_show(board_three);
	printf("\n");

	//test four
	printf("testing with bits");
	board* board_four = board_new(5,5,BITS);
	pos pos_four = make_pos(0,0);
	board_set(board_four,pos_four,WHITE);
	board_show(board_four);
	printf("\n");

	printf("----------------end board set test------------\n");

}

//turns the value of a cell in a string for testing purposes
void cell_to_string(cell test){
	if(test == BLACK){
		printf("black");
	}
	if(test == WHITE){
		printf("white");
	}
	if(test == EMPTY){
		printf("empty");
	}
}

void evidence_board_get(){
	printf("** testing board get \n");

	//test one
	board *board_one = board_new(3,5,MATRIX);
	pos pos_one = make_pos(0,1);
	cell res_one = board_get(board_one,pos_one);
	printf(" expecting empty:\n");
	cell_to_string(res_one);	
	printf("\n");

	//test two
	board *board_two = board_new(5,6,MATRIX);
	pos pos_two = make_pos(3,4);
	board_set(board_two,pos_two,BLACK);
	cell res_two = board_get(board_two,pos_two);
	printf("expecting black: \n");
	cell_to_string(res_two);
	printf("\n");

	//test three out of bounds
	board *board_three = board_new(5,6,MATRIX);	
	pos pos_three = make_pos(10,12);
	//board_set(board_three,pos_three,BLACK);
	//cell res_three = board_get(board_three,pos_three);
	printf("expecting out of bounds: \n");
        //cell_to_string(res_three);
        printf("\n");

	printf("--------------end board get----------------\n");
}

void evidence_board_show(){
	printf("*** testing board_show\n");
	int width = 20;
	int height = 20;
	board *board_test = board_new(width, height, MATRIX);
	board_show(board_test);
	// do I have to board free after this?

	printf("-----------------end board show test------------\n");
}

void evidence_full_row_number(){
	printf("*** testing full row number\n");
	
	//test one
	game *game_one = new_game(4,10,11,MATRIX);
	int num_one = full_row_number(game_one,3);
	printf("expecting row number 10: %d \n",num_one);

	//test two
	game *game_two = new_game(4,12,20,MATRIX);
        int num_two = full_row_number(game_two,11);
        printf("expecting row number 19: %d \n",num_two);

	//test three
	game *game_three = new_game(3,5,5,MATRIX);
	pos pos_three = make_pos(4,2);
	board_set(game_three->b,pos_three,BLACK);
	int num_three = full_row_number(game_three,2);
	printf("expecting row 3: %d \n",num_three);

	
	printf("---------------end full row number test----------------\n");
}

void evidence_drop_right_character(){
	printf("**** testing drop right character\n");

	//test one
	game* game_one = new_game(4,8,5,MATRIX);
	game_one->next = BLACK_NEXT;
	cell res_one = drop_right_character(game_one);
	printf("expecting black\n");
	cell_to_string(res_one);
	printf("\n");

	//test two
	game_one->next = WHITE_NEXT;
	cell res_two = drop_right_character(game_one);
	printf("expecting white\n");
	cell_to_string(res_two);
	printf("\n");

	//test three
	game_one->next = BLACK_NEXT;
	cell res_three = drop_right_character(game_one);
	printf("expecting black\n");
	cell_to_string(res_three);
	printf("\n");

	printf("-------------------end drop right character test-------\n");

}
void evidence_drop_piece(){
	printf("*** testing drop piece\n");
	//test one
	game* game_one = new_game(4,5,5,MATRIX);
	int res_one = drop_piece(game_one,2);
	printf("expecting number 1: %d\n",res_one);
	board_show(game_one->b);

	//test two
	drop_piece(game_one,2);
	drop_piece(game_one,0);
	drop_piece(game_one,0);
	board_show(game_one->b);

	//test three fill the whole row
	drop_piece(game_one,0);
	drop_piece(game_one,0);
	int num_four = drop_piece(game_one,0);
	printf("expecing 1 :%d\n",num_four);

	drop_piece(game_one,0);
	int num_five = drop_piece(game_one,0);
	printf("expecting 0: %d\n",num_five);
	board_show(game_one->b);

}

void evidence_twist(){
	printf("*** testing twist \n");

	//test one
	game* game_one = new_game(4,4,5,MATRIX);
	
	//set up the game
 	int num_one = drop_piece(game_one,0); //black piece
	//board_show(game_one->b);
	int num_two = drop_piece(game_one,0); //black piece
	 //board_show(game_one->b);
	game_one->next = BLACK_NEXT;
	int num_three = drop_piece(game_one,0); // whitepiece
 	//board_show(game_one->b);
	int num_four = drop_piece(game_one,2); //whitepiece
	board_show(game_one->b);
	twist(game_one,CW);
	board_show(game_one->b);

	//test two
	game* game_two = new_game(3,4,4,MATRIX);
	drop_piece(game_two,1);
	drop_piece(game_two,1);
	drop_piece(game_two,1);

	game_two->next = BLACK_NEXT;
	drop_piece(game_two,3);
	drop_piece(game_two,3);
	printf("board 2 before twist\n");
	board_show(game_two->b);

	printf("board 3 after twist \n");
	twist(game_two,CCW);
	board_show(game_two->b);

	printf("-------end twist test-------------\n");
}

void evidence_gravity(){
	printf("***testing gravity\n");

	//test one
	game* game_one = new_game(4,5,5,MATRIX);
        pos pos_one = make_pos(0,0);
        board_set(game_one->b,pos_one,BLACK);
        printf("testing board one\n");
	printf("board before gravity");
	board_show(game_one->b);
	printf("\n");
        gravity(game_one->b);
	board_show(game_one->b);
        printf("\n");

	printf("---------end gravity test------------\n");
  

}

void evidence_helper_row(){
	printf("*** testing helper row\n");
	//test 1
	game* game_one = new_game(4,5,5,MATRIX);
	drop_piece(game_one,0);
	drop_piece(game_one,1);
	drop_piece(game_one,2);
	board_show(game_one->b);

	int count = helper_row(game_one,0,4,BLACK);
	printf("expecting count 3 :%d\n",count);

	//add a test 2

	printf("---------------end helper row-------------\n");
}

void evidence_helper_column(){
	printf("*** testing helper column\n");
	//test 1
	game* game_one = new_game(4,5,5,MATRIX);
	drop_piece(game_one,1);
	drop_piece(game_one,1);
	drop_piece(game_one,1);
	drop_piece(game_one,1);
	drop_piece(game_one,1);
	board_show(game_one->b);

	int count = helper_column(game_one,1,0,BLACK);
	printf("expecting count 5: %d\n",count);

	//test 2
	//drop_piece(game_one,2)
	printf("-----------end helper column test-----------\n");

}

void evidence_helper_diagonal_down(){
	printf("*** testing helper diagonal down\n");
	
	//test 1
	game* game_one = new_game(3,3,3,MATRIX);
	drop_piece(game_one,0);
	drop_piece(game_one,0);
	drop_piece(game_one,0);
	drop_piece(game_one,1);
	drop_piece(game_one,1);
	drop_piece(game_one,2);
	board_show(game_one->b);
	
	printf("break\n");
	int count = helper_diagonal_down(game_one,0,0,BLACK);
	printf("expecting count 3: %d\n",count);

	//test 2
	game* game_two = new_game(3,4,4,MATRIX);
	//first column
	//game_two->next = BLACK_NEXT;
	drop_piece(game_two,0);
	drop_piece(game_two,0);
	game_two->next = BLACK_NEXT;
	drop_piece(game_two,0);
	drop_piece(game_two,0);

	//second column
	drop_piece(game_two,1);
	drop_piece(game_two,1);
	drop_piece(game_two,1);

	//third column
	drop_piece(game_two,2);
	drop_piece(game_two,2);
	drop_piece(game_two,3);
	board_show(game_two->b);

	int count_two = helper_diagonal_down(game_two,1,1,WHITE);
	printf("expecting count 3: %d\n",count_two);

	game* game_three = new_game(3,3,3,MATRIX);
	drop_piece(game_three,1);
	drop_piece(game_three,1);
	game_three->next = WHITE_NEXT;
	drop_piece(game_three,0);
	drop_piece(game_three,0);
	game_three->next = BLACK_NEXT;
	drop_piece(game_three,0);
	drop_piece(game_three,2);
	game_three->next = WHITE_NEXT;
	drop_piece(game_three,1);
	drop_piece(game_three,2);
	drop_piece(game_three,2);
	board_show(game_three->b);
	int count_three = helper_diagonal_down(game_three,0,0,BLACK);
	printf("%d",count_three);

	printf("------------end helper diagonal down test -------------\n");

	
}

void evidence_helper_diagonal_up(){
	printf("*** testing helper diagonal down \n");
	
	//test 1
	game* game_one = new_game(3,5,5,MATRIX);
	drop_piece(game_one,0);
	drop_piece(game_one,1);
	drop_piece(game_one,1);
	drop_piece(game_one,2);
	drop_piece(game_one,2);
	drop_piece(game_one,2);
	drop_piece(game_one,3);
	drop_piece(game_one,3);
	drop_piece(game_one,3);
	drop_piece(game_one,3);
	drop_piece(game_one,3);
	
	board_show(game_one->b);
	int count_one = helper_diagonal_up(game_one,0,4,BLACK);
	printf("expecting count 4: %d\n",count_one);

	int count_two = helper_diagonal_up(game_one,1,4,BLACK);
	printf("expecting count 3: %d\n",count_two);
	printf("---------------------end helper diagonal up test---------\n");

}


//convert the outcome to a string
void outcome_to_string(outcome outcome_t){
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
	
void evidence_horizontal_win(){
	printf("***testing horizontal win \n");
	
	//test one
	game* game_one = new_game(3,4,5,MATRIX);
	game_one->next = BLACK_NEXT;
	drop_piece(game_one,0); // black piece
	drop_piece(game_one,1);
	drop_piece(game_one,2);
	//drop_piece(game_one,3);
	//game_one->next = BLACK_NEXT;
	drop_piece(game_one,0);
	drop_piece(game_one,1);
	drop_piece(game_one,2);

	board_show(game_one->b);
	printf("\n");
	outcome outcome_one = horizontal_win(game_one);
	printf("expecting Black_win: \n");
	outcome_to_string(outcome_one);
	printf("\n");

	printf("------------end test horizontal win----------\n");

}

void evidence_vertical_win(){
	printf("*** testing vertical win \n");
	
	//test one
	game* game_one = new_game(4,5,5,MATRIX);
	game_one->next = BLACK_NEXT;
	drop_piece(game_one,0);
	drop_piece(game_one,0);
	drop_piece(game_one,0);
	drop_piece(game_one,0);
	board_show(game_one->b);
	outcome outcome_one = vertical_win(game_one);
	outcome_to_string(outcome_one);
	printf("\n");
	printf("---------end vertical win test\n------------");
}

void evidence_diagonal_down_win(){
	printf("** testing diagonal down\n");

	//test one
	game* game_one = new_game(3,4,4,MATRIX);
	drop_piece(game_one,0);
	drop_piece(game_one,0);
	drop_piece(game_one,0);
	drop_piece(game_one,1);
	drop_piece(game_one,1);
	drop_piece(game_one,2);
	board_show(game_one->b);

	outcome outcome_one = diagonal_down_win(game_one);
	outcome_to_string(outcome_one);
	printf("\n");
	printf("----------- end diagonal down win test---------------\n");
}

void evidence_diagonal_up(){
	printf("*** testing diagonal up win \n");
	
	//test one
	game* game_one = new_game(3,4,4,MATRIX);
	game_one->next = BLACK_NEXT;
	drop_piece(game_one,1);
	drop_piece(game_one,2);
	drop_piece(game_one,2);
	drop_piece(game_one,3);
	drop_piece(game_one,3);
	 drop_piece(game_one,3);
	 drop_piece(game_one,3);
	board_show(game_one->b);
	printf("461\n");
	outcome outcome_one = diagonal_up_win(game_one);
	outcome_to_string(outcome_one);
	printf("\n");
	printf("-----------end diagonal up win  test -----------\n");
}

void evidence_outcome(){
	printf("*** testing outcome \n");

	//test one
	game* game_one = new_game(3,6,6,MATRIX);
	game_one->next = BLACK_NEXT;
	drop_piece(game_one,0);
	drop_piece(game_one,1);
	drop_piece(game_one,2);
	drop_piece(game_one,3);
	game_one->next = WHITE_NEXT;
	drop_piece(game_one,1);
	drop_piece(game_one,2);
	drop_piece(game_one,3);
	drop_piece(game_one,4);
	game_one->next = WHITE_NEXT;
	drop_piece(game_one,5);

	board_show(game_one->b);
	outcome outcome_one = game_outcome(game_one);
	outcome_to_string(outcome_one);
	printf("\n");

	//test two
	game* game_two = new_game(3,5,5,MATRIX);
	drop_piece(game_two,0);
	drop_piece(game_two,1);
	drop_piece(game_two,1);
	drop_piece(game_two,2);
	drop_piece(game_two,2);
	drop_piece(game_two,2);

	game_two->next = BLACK_NEXT;
	drop_piece(game_two,0);
	drop_piece(game_two,1);
	drop_piece(game_two,2);
	board_show(game_two->b);
	
	printf("test");
	//outcome outcome1 = horizontal_win(game_two);
	//outcome_to_string(outcome1);
	//outcome outcome2 = vertical_win(game_two);
	//outcome_to_string(outcome2);
	//outcome outcome3 = diagonal_down_win(game_two);
	//outcome_to_string(outcome3);
	//outcome outcome4 = diagonal_up_win(game_two);
	//outcome_to_string(outcome4);
	printf("end test");

	outcome outcome_two = game_outcome(game_two);
	outcome_to_string(outcome_two);

	//test three- test if game is full and now win
	game* game_three = new_game(3,3,3,MATRIX);
	game_three->next = WHITE_NEXT;
	drop_piece(game_three,1);
	drop_piece(game_three,1);
	game_three->next = BLACK_NEXT;
	drop_piece(game_three,0);
	drop_piece(game_three,0);
	game_three->next = WHITE_NEXT;
	drop_piece(game_three,0);
	drop_piece(game_three,2);
	game_three->next = BLACK_NEXT;
	drop_piece(game_three,1);
	drop_piece(game_three,2);
	drop_piece(game_three,2);
	board_show(game_three->b);

	printf("test2");
	 outcome outcome3 = diagonal_down_win(game_three);
         outcome_to_string(outcome3);
         outcome outcome4 = diagonal_up_win(game_three);
         outcome_to_string(outcome4);
	outcome outcome1 = horizontal_win(game_three);
        outcome_to_string(outcome1);
         outcome outcome2 = vertical_win(game_three);
         outcome_to_string(outcome2);
	outcome outcome_three = game_outcome(game_three);
	outcome_to_string(outcome_three);	
	printf("----------end outcome test------------\n");
}



int main(int argc , char *argv[]) {
	evidence_make_pos();
	evidence_board_set();
	evidence_board_get();
	evidence_board_show();
	evidence_full_row_number();
	evidence_drop_right_character();
	evidence_drop_piece();
	//evidence_twist();
	evidence_gravity();
	evidence_helper_row();
	evidence_helper_column();
	evidence_helper_diagonal_down();
	evidence_helper_diagonal_up();
	evidence_horizontal_win();
	evidence_vertical_win();
	evidence_diagonal_down_win();
	evidence_diagonal_up();
	evidence_outcome();
  return 0;
}

