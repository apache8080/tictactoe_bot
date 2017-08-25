#import <stdio.h>
#define BOARD_SIZE 3

char board[3][3] = {{'1', '2', '3'},
		    {'4', '5', '6'},
		    {'7', '8', '9'}};

struct point{
  int row;
  int col;
};

int x_win_positions[8] = {0};
int o_win_positions[8] = {0};

int is_winner = 0;
int moves = 0;

void draw_board(int size){
  for(int i=0; i<size; i++){
    for(int n=0; n<size; n++){
      printf("%c ", board[i][n]);
    }
    printf("\n");
  }
  printf("----------------- \n");
}

struct point convert_pos_to_coord(int pos){
  //Works for Any N X N Square 
  int col;
  if(pos % BOARD_SIZE == 0){
    col = BOARD_SIZE-1;
  }else{
    col = (pos % BOARD_SIZE)-1;
  }
  
  int row;
  if(pos % BOARD_SIZE == 0){
    row = (pos / BOARD_SIZE)-1;
  }else{
    row = pos / BOARD_SIZE;
  }

  struct point temp;
  temp.row = row;
  temp.col = col;
  return temp;
}

int make_move(int pos, int is_user){  
  struct point p = convert_pos_to_coord(pos);
  int row = p.row;
  int col = p.col;
  
  if(board[row][col] == 'X' || board[row][col] == 'O'){
    return 0;
  }else{
    if(is_user == 1){
      board[row][col] = 'X';
    }else{ 
      board[row][col] = 'O';
    }
    moves++;
    
    int row_check = 0;
    int col_check = 0;
    int diag_check = 0;
    int anti_diag_check = 0;
    
    for(int i=0; i<BOARD_SIZE; i++){
      if(is_user == 1){
	if(board[i][col] == 'X'){
	  row_check++;
	}
      }else{
	if(board[i][col] == 'O'){
	  row_check++;
	}	
      }

      if(is_user == 1){
	if(board[row][i] == 'X'){
	  col_check++;
	}
      }else{
	if(board[row][i] == 'O'){
	  col_check++;
	}	
      }

      if(is_user == 1){
	if(board[i][i] == 'X'){
	  diag_check++;
	}
      }else{
	if(board[i][i] == 'O'){
	  diag_check++;
	}	
      }
      
      if(is_user == 1){
	if(board[i][BOARD_SIZE-i-1] == 'X'){
	  anti_diag_check++;
	}
      }else{
	if(board[i][BOARD_SIZE-i-1] == 'O'){
	  anti_diag_check++;
	}	
      }
      
    }
    
    if(col_check == 3 || row_check == 3 || diag_check == 3 || anti_diag_check == 3){
      if(is_user == 1){
	is_winner = 1;
      }else{
	is_winner = 2;
      }
    }else if(moves == 9){
      is_winner = 3;
    }else{
      is_winner = 0;
    }
    return 1;
  }
}

//Dumb Bot right now
void bot_make_move(){
  int n = BOARD_SIZE*BOARD_SIZE;
  for(int i=1; i<=n; i++){
    int result = make_move(i, 0);
    if(result == 1){
      break;
    }
  }
}

int main(){
  char ans;
  
  printf("Welcome to Tic-Tac-Toe Bot \n");
  printf("Do you want to play? y/n \n");
  
  scanf("%c", &ans);
  if(ans == 'y'){
    printf("Welcome to the Game! \n");
    draw_board(BOARD_SIZE);
    while(is_winner == 0){
      printf("Enter a position: \n");
      int pos;
      scanf("%d", &pos);
      if(pos>=1 || pos<=9){
	int move_result = make_move(pos, 1);
	if(move_result == 1 && is_winner == 0){
	  draw_board(BOARD_SIZE);
	  bot_make_move(); 
	  draw_board(BOARD_SIZE);
	}else{
	  if(is_winner == 0){
	    printf("This position has already been used. :( \n");
	  }
	}
      }else{
	printf("Enter a number between 1 and 9 \n");
      }
    }
  }
  
  draw_board(BOARD_SIZE);

  if(is_winner == 1){
    printf("You Won! :) \n");
  }else if(is_winner == 2){
    printf("You Lost! :( \n");
  }else{
    printf("Cat's game! :| \n");
  }
}
