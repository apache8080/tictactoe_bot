#include <stdio.h>
#include <string.h> 
#define BOARD_SIZE 3
#define EASY 2
#define MEDIUM 3
#define HARD 10


enum game_state {
    USER_WIN,
    BOT_WIN,
    CATSGAME,
    PLAYING
};

struct point {
    int row;
    int col;
};

int level;

struct point convert_pos_to_coord (int pos) {
    //Works for Any N X N Square 
    int col;
    if (pos % BOARD_SIZE == 0) {
	col = BOARD_SIZE-1;
    } else {
	col = (pos % BOARD_SIZE) - 1;
    }
  
    int row;
    if (pos % BOARD_SIZE == 0) {
	row = (pos / BOARD_SIZE) - 1;
    } else {
	row = pos / BOARD_SIZE;
    }

    struct point temp;
    temp.row = row;
    temp.col = col;
    return temp;
}

void draw_board (int board[][BOARD_SIZE]) {
    int n=1;
    for (int i = 0; i < BOARD_SIZE; i++) {
	for (int j = 0; j < BOARD_SIZE; j++) {
	    int square = board[i][j];
	    switch (square) {
	    case 1:
		printf("X ");
		break;
	    case -1:
		printf("O ");
		break;
	    default:
		printf("%d ", n);
		break;
	    }
	    n++;
	}
	printf("\n");
    }
    printf("----------------\n");
}

int get_winner (int board[][BOARD_SIZE]) {
    int row_check = 0;
    int col_check = 0;
    int diag_check = 0;
    int anti_diag_check = 0;
    int n_moves = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
	for (int j = 0; j < BOARD_SIZE; j++) {
	    if (board[i][j] != 0) {
		n_moves++;
	    }
	    row_check += board[i][j];
	    col_check += board[j][i];
	}
	if (row_check == 3 || row_check == -3) {
	    return row_check / 3;
	} else if(col_check == 3 || col_check == -3) {
	    return col_check / 3;
	} else {
	    row_check = 0;
	    col_check = 0;
	}
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
	diag_check += board[i][i];
	anti_diag_check += board[i][BOARD_SIZE-i-1]; 
    }
  
    if (n_moves == 9) {
	return 2;
    } else if(diag_check == 3 || diag_check == -3) {
	return diag_check / 3;
    } else if(anti_diag_check == 3 || anti_diag_check == -3) {
	return anti_diag_check / 3;
    } else {
	return 0;
    }
}

int make_move (int pos, int board[][BOARD_SIZE], int player) {
    struct point p = convert_pos_to_coord(pos);
    int row = p.row;
    int col = p.col;
    if (board[row][col] != -1 && board[row][col] != 1) {
	board[row][col] = player;
	return 1;
    } else {
	return 0;
    }
}

int minimax (int board[][BOARD_SIZE], int first_move, int depth, int player) {
    int winner = get_winner(board);
    int max_depth;
    switch (level) {
    case 1:
	max_depth = EASY;
	break;
    case 2:
	max_depth = MEDIUM;
	break;
    case 3:
	max_depth = HARD;
	break;
    default:
	max_depth = HARD;
    }
  
    if (winner == 1) {
	return 10 - depth;
    } else if (winner == -1) {
	return -10 + depth;
    } else if (winner == 2 || depth == max_depth) {
	return 0;
    }

    int best_score = 0;
    if (player == 1) {
	best_score = -1000;
    } else {
	best_score = 1000;
    }
  
    for (int i = 1; i <= 9; i++) {  
	struct point p = convert_pos_to_coord(i);
	if (board[p.row][p.col] == 0) {
	    board[p.row][p.col] = player;
	    int score = minimax(board, 0, depth+1, -player);
	    if (player == 1) {
		if (score > best_score) {
		    best_score = score;
		}
	    } else {
		if (score < best_score) {
		    best_score = score;
		}
	    }
	    board[p.row][p.col] = 0;
	}
    }
    return best_score;
}

void bot_move (int board[][BOARD_SIZE]) {
    int best_pos = -1;
    int best_score = 1000;

    for (int i = 1; i <= 9; i++) {
	struct point p = convert_pos_to_coord(i);
	if (board[p.row][p.col] == 0) {
	    board[p.row][p.col] = -1;
	    int score = minimax(board, i, 0, 1);
	    if (score < best_score) {
		best_score = score;
		best_pos = i;
	    } 
	    board[p.row][p.col] = 0;
	}
    }
    if (best_pos != -1) {
	make_move(best_pos, board, -1);
    }
}

int main() {
    char ans;

    printf("Welcome to Tic-Tac-Toe Bot \n");
    printf("Do you want to play? y/n \n");

    scanf("%c", &ans);

    int board[BOARD_SIZE][BOARD_SIZE];
    memset(board, 0, sizeof(board[0][0])*BOARD_SIZE*BOARD_SIZE);
  
    enum game_state state = PLAYING;
    if (ans == 'y') {
	printf("Enter a level: 1=Easy, 2=Medium, 3=Hard \n");
	int user_level;
	scanf("%d", &user_level);
	if (user_level >= 1 && user_level <= 3) {
	    level = user_level;
	} else {
	    level = 3;
	    printf("Defaulting to the hardest level. \n");
	}
	draw_board(board);
	while (state == PLAYING) {
	    printf("Enter a position: \n");
	    int pos;
	    scanf("%d", &pos);
	    if (pos >= 1 && pos <= 9) {
		int move_result = make_move(pos, board, 1);
		if (move_result == 1) {
		    draw_board(board);
		    int is_winner = get_winner(board);
		    if (is_winner == 1) {
			state = USER_WIN;
		    } else if (is_winner == -1) {
			state = BOT_WIN;
		    } else if (is_winner == 2) {
			state = CATSGAME;
		    } else {
			bot_move(board);
			printf("Bot Played \n");
			draw_board(board);
			int is_winner = get_winner(board);
			if (is_winner == 1) {
			    state = USER_WIN;
			} else if (is_winner == -1) {
			    state = BOT_WIN;
			} else if (is_winner == 2) {
			    state = CATSGAME;
			} else {
			    state = PLAYING;
			}
		    }
		} else {
		    printf("Position already used. \n");
		}
	    } else {
		printf("Invalid value. Please enter a number between 1 and 9 \n");
	    }
	}
    }

    switch (state) {
    case USER_WIN:
	printf("You Won the Game!!! \n");
	return 1;

    case BOT_WIN:
	printf("You Lost the Game!!! \n");
	return 2;
    
    case CATSGAME:
	printf("It's a Cat's Game!!! \n");
	return 3;

    default: return 0;
    }
    return 0;
}
