#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

#define PLAYER_1 1
#define PLAYER_2 2

#define BLANK       0
#define W_PAWN      1
#define W_KNIGHT    2
#define W_ROOK      3
#define W_BISHOP    4
#define W_QUEEN     5
#define W_KING      6
#define B_PAWN      7
#define B_KNIGHT    8
#define B_ROOK      9
#define B_BISHOP    10
#define B_QUEEN     11
#define B_KING      12

#include <stdio.h>
int spaces[BOARD_WIDTH][BOARD_HEIGHT];
char* translations[] = {
    "___", "WPN", "WKT", "WRK", "WBP", "WQN", "WKG", "BPN", "BKT", "BRK", "BBP", "BQN", "BKG"
};
int playerTurn;

int print_board(){
    for(int i = 0; i <= BOARD_HEIGHT; i++){
        for (int j = 0; j < BOARD_WIDTH; j++){
            printf("%s  ", translations[spaces[i][j]]);
        }
        printf("\n\n");
    }
    return 0;
}

int init_board(){
    playerTurn = PLAYER_1;
    for (int i = 0; i < BOARD_WIDTH; i++){
        spaces[1][i] = B_PAWN;
        spaces[BOARD_HEIGHT - 1][i] = W_PAWN;
        
    }
        spaces[0][0] = B_ROOK;
        spaces[0][1] = B_KNIGHT;
        spaces[0][2] = B_BISHOP;
        spaces[0][3] = B_KING;
        spaces[0][4] = B_QUEEN;
        spaces[0][5] = B_BISHOP;
        spaces[0][6] = B_KNIGHT;
        spaces[0][7] = B_ROOK;

        spaces[BOARD_HEIGHT][0] = W_ROOK;
        spaces[BOARD_HEIGHT][1] = W_KNIGHT;
        spaces[BOARD_HEIGHT][2] = W_BISHOP;
        spaces[BOARD_HEIGHT][3] = W_KING;
        spaces[BOARD_HEIGHT][4] = W_QUEEN;
        spaces[BOARD_HEIGHT][5] = W_BISHOP;
        spaces[BOARD_HEIGHT][6] = W_KNIGHT;
        spaces[BOARD_HEIGHT][7] = W_ROOK;
}

int select_piece(int x, int y){
    char playerIn[5] = "init";
    printf("Select X coordinate: ");
    gets(playerIn);
    x = atoi(playerIn);
    if(x < 0 || x > BOARD_WIDTH){
        printf("Error! Try again!\n");
        return select_piece();
    }else{
        printf("You selected: %d\n", x);
    }

    printf("Select Y coordinate: ");
    gets(playerIn);
    y = atoi(playerIn);
    if(y < 0 || y > BOARD_WIDTH){
        printf("Error! Try again!\n");
        return select_piece();
    }else{
        printf("You selected: %d\n", y);
    }
    
    if(playerTurn == PLAYER_1){
        if(spaces[x][y] <= BLANK || spaces[x][y] > W_KING){
            printf("Error - Please select a white piece\n");
        }
    }else{
        if(spaces[x][y] <= W_KING || spaces[x][y] > B_KING){
            printf("Error - Please select a white piece\n");
        }
    }
}

int select_move(){
    return 0;
}

int perform_move(){
    return 0;
}

int switch_players(){
    return 0;
}

int gameplay_loop(){
    int startX, startY, endX, endY;
    printf("Player %d's turn!\n", playerTurn);
    select_piece();
    select_move();
    perform_move();
    switch_players();
}

int main() {

    printf("Hello, World!\n");
    print_board();
    printf("\n\n");
    init_board();
    print_board();
    while(1){
        gameplay_loop();
    }
    return 0;
}