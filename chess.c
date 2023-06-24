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
#define TEST_ENEMY  13

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct move {
    int x;
    int y;
    int on_board;
};

int spaces[BOARD_WIDTH][BOARD_HEIGHT];
char* translations[] = {
    "___", "WPN", "WKT", "WRK", "WBP", "WQN", "WKG", "BPN", "BKT", "BRK", "BBP", "BQN", "BKG", "TST"
};
int playerTurn;

int print_board(){
    for(int i = 0; i < BOARD_HEIGHT; i++){
        if (i == 0)
            printf("    0    1    2    3    4    5    6    7  \n");
        printf("%d  ", i);

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
        //spaces[BOARD_HEIGHT - 2][i] = W_PAWN;
        
    }
        spaces[0][0] = B_ROOK;
        spaces[0][1] = B_KNIGHT;
        spaces[0][2] = B_BISHOP;
        spaces[0][3] = B_KING;
        spaces[0][4] = B_QUEEN;
        spaces[0][5] = B_BISHOP;
        spaces[0][6] = B_KNIGHT;
        spaces[0][7] = B_ROOK;

        spaces[BOARD_HEIGHT - 1][0] = W_ROOK;
        spaces[BOARD_HEIGHT - 1][1] = W_KNIGHT;
        spaces[BOARD_HEIGHT - 1][2] = W_BISHOP;
        spaces[BOARD_HEIGHT - 1][3] = W_KING;
        spaces[BOARD_HEIGHT - 1][4] = W_QUEEN;
        spaces[BOARD_HEIGHT - 1][5] = W_BISHOP;
        spaces[BOARD_HEIGHT - 1][6] = W_KNIGHT;
        spaces[BOARD_HEIGHT - 1][7] = W_ROOK;

        spaces[4][4] = W_QUEEN;
}

int select_piece(int *x, int *y){
    char playerIn[5];
    printf("Select X coordinate: ");
    fgets(playerIn, 5, stdin);
    *x = atoi(playerIn);
    if(*x < 0 || *x > BOARD_WIDTH - 1){
        printf("Error! Try again!\n");
        return select_piece(x, y);
    }

    printf("Select Y coordinate: ");
    fgets(playerIn, 5, stdin);
    *y = atoi(playerIn);
    if(*y < 0 || *y > BOARD_HEIGHT - 1){
        printf("Error! Try again!\n");
        return select_piece(x, y);
    }

    printf("You selected %s (id %d) at %d, %d \n", translations[spaces[*y][*x]], spaces[*y][*x], *x, *y);
    if(playerTurn == PLAYER_1){
        if(spaces[*y][*x] <= BLANK || spaces[*y][*x] > W_KING){
            printf("Error - Please select a white piece\n");
            return select_piece(x, y);
        }
    }else{
        if(spaces[*y][*x] <= W_KING || spaces[*y][*x] > B_KING){
            printf("Error - Please select a black piece\n");
            return select_piece(x, y);
        }
    }
    return spaces[*y][*x];
}

bool blankOrEnemy(int y, int x){
    if (x < 0 || x >= BOARD_WIDTH){ // x out of range
        return false;
    }
    if (y < 0 || y >= BOARD_HEIGHT){ // y out of range
        return false;
    }


    if(spaces[y][x] == BLANK){ // blank space
        return true;
    }else{
        if (playerTurn == PLAYER_1){    // white / player 1's enemies
            if (spaces[y][x] > W_KING){
                return true;
            }
        }else{                          // black / player 2's enemies
            if (spaces[y][x] < B_PAWN){
                return true;
            }
        }
    }

    return false; // not blank or enemy
}

struct move *get_legal_moves(int *x, int *y){
    struct move *returnStruct;
    int piece = spaces[*y][*x];
    int i;
    bool pawnCanMove;
    bool pathBlocked = false;

    i = 0;
    pawnCanMove = 0;
    returnStruct = malloc((BOARD_WIDTH - 1) * (BOARD_HEIGHT - 1) * sizeof(struct move));
    if(!returnStruct){
        printf("Error! Malloc failed!");
        return 0;
    }
    for (int j = 0; j < (BOARD_WIDTH * BOARD_HEIGHT); j++){
        returnStruct[i].x = 0;
        returnStruct[i].y = 0;
        returnStruct[i].on_board = 0;
    }
    switch(piece){
        case B_PAWN:
            printf("Piece is a pawn\n");
            if(spaces[*y + 1][*x] == BLANK){
                printf("Pawn can move forward this turn\n");
                pawnCanMove = true;
                returnStruct[i].x = *x;
                returnStruct[i].y = *y + 1;
                returnStruct[i].on_board = 1;
                i++;
            }else{
                printf("Pawn cannot move forward this turn\n");
                pawnCanMove = false;
            }

            if(*y == 1 && (pawnCanMove) && (spaces[*y + 2][*x] == BLANK)){
                printf("Pawn can dash this turn\n");
                returnStruct[i].x = *x;
                returnStruct[i].y = *y - 2;
                returnStruct[i].on_board = 1;
                i++;
            }

            if(spaces[*y + 1][*x - 1] < B_PAWN && spaces[*y + 1][*x - 1] != BLANK && *x != 0){
                printf("Pawn can do left-attack this turn\n");
                returnStruct[i].x = *x - 1;
                returnStruct[i].y = *y - 1;
                returnStruct[i].on_board = 1;
                i++;
            }

            if(spaces[*y + 1][*x + 1] < B_PAWN && spaces[*y + 1][*x + 1] != BLANK && *x <= BOARD_WIDTH - 1){
                printf("Pawn can do right-attack this turn\n");
                returnStruct[i].x = *x + 1;
                returnStruct[i].y = *y - 1;
                returnStruct[i].on_board = 1;
                i++;
            }
            break;
        case W_PAWN: 
            printf("Piece is a pawn\n");
            if(spaces[*y - 1][*x] == BLANK){
                printf("Pawn can move forward this turn\n");
                pawnCanMove = true;
                returnStruct[i].x = *x;
                returnStruct[i].y = *y - 1;
                returnStruct[i].on_board = 1;
                i++;
            }else{
                printf("Pawn cannot move forward this turn\n");
                pawnCanMove = false;
            }

            if(*y == 6 && (pawnCanMove) && (spaces[*y - 2][*x] == BLANK)){
                printf("Pawn can dash this turn\n");
                returnStruct[i].x = *x;
                returnStruct[i].y = *y - 2;
                returnStruct[i].on_board = 1;
                i++;
            }

            if(spaces[*y - 1][*x - 1] > W_KING && *x != 0){
                printf("Pawn can do left-attack this turn\n");
                returnStruct[i].x = *x - 1;
                returnStruct[i].y = *y - 1;
                returnStruct[i].on_board = 1;
                i++;
            }

            if(spaces[*y - 1][*x + 1] > W_KING && *x <= BOARD_WIDTH - 1){
                printf("Pawn can do right-attack this turn\n");
                returnStruct[i].x = *x + 1;
                returnStruct[i].y = *y - 1;
                returnStruct[i].on_board = 1;
                i++;
            }
            break;
        case B_ROOK:
        case W_ROOK: 
            printf("Piece is a rook\n");
            for(int j = 1; j < BOARD_HEIGHT; j++){ // upward movement
                if (blankOrEnemy(*y - j, *x) && pathBlocked == false){
                    returnStruct[i].x = *x;
                    returnStruct[i].y = *y - j;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y - j][*x] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // downward movement
                if (blankOrEnemy(*y + j, *x) && pathBlocked == false){
                    returnStruct[i].x = *x;
                    returnStruct[i].y = *y + j;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y + j][*x] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // leftward movement
                if (blankOrEnemy(*y, *x - j) && pathBlocked == false){
                    returnStruct[i].x = *x - j;
                    returnStruct[i].y = *y;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y][*x - j] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // rightward movement
                if (blankOrEnemy(*y, *x + j) && pathBlocked == false){
                    returnStruct[i].x = *x + j;
                    returnStruct[i].y = *y;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y][*x + j] != BLANK){
                    pathBlocked = true;
                }
            }
            break;
        case B_BISHOP:
        case W_BISHOP: 
            printf("Piece is a bishop\n");
            for(int j = 1; j < BOARD_HEIGHT; j++){ // up-left movement
                if (blankOrEnemy(*y - j, *x - j) && pathBlocked == false){
                    returnStruct[i].x = *x - j;
                    returnStruct[i].y = *y - j;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y - j][*x - j] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // up-right movement
                if (blankOrEnemy(*y - j, *x + j) && pathBlocked == false){
                    returnStruct[i].x = *x + j;
                    returnStruct[i].y = *y - j;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y - j][*x + j] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // down-right movement
                if (blankOrEnemy(*y + j, *x + j) && pathBlocked == false){
                    returnStruct[i].x = *x + j;
                    returnStruct[i].y = *y + j;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y + j][*x + j] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // down-left movement
                if (blankOrEnemy(*y + j, *x - j)&& pathBlocked == false){
                    returnStruct[i].x = *x - j;
                    returnStruct[i].y = *y + j;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y + j][*x - j] != BLANK){
                    pathBlocked = true;
                }
            }
            break;
        case B_KNIGHT:
        case W_KNIGHT: 
            printf("Piece is a knight\n");
            if(blankOrEnemy(*y - 2, *x - 1)){ // 11:00
                returnStruct[i].x = *x -1;
                returnStruct[i].y = *y - 2;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y - 2, *x + 1)){ // 1:00
                returnStruct[i].x = *x + 1;
                returnStruct[i].y = *y - 2;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y - 1, *x + 2)){ // 2:00
                returnStruct[i].x = *x + 2;
                returnStruct[i].y = *y - 1;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y + 1, *x + 2) ){ // 3:00
                returnStruct[i].x = *x + 2;
                returnStruct[i].y = *y + 1;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y + 2, *x + 1)){ // 5:00
                returnStruct[i].x = *x + 1;
                returnStruct[i].y = *y + 2;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y + 2, *x - 1)){ // 7:00
                returnStruct[i].x = *x - 1;
                returnStruct[i].y = *y + 2;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y + 1, *x - 2)){ // 8:00
                returnStruct[i].x = *x - 2;
                returnStruct[i].y = *y + 1;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y - 1, *x - 2)){ // 10:00
                returnStruct[i].x = *x - 2;
                returnStruct[i].y = *y - 1;
                returnStruct[i].on_board = 1;
                i++;
            }
            break;
        case B_KING:
        case W_KING: 
            printf("Piece is a king\n");
            if(blankOrEnemy(*y - 1, *x - 1)){ // up-left
                returnStruct[i].x = *x - 1;
                returnStruct[i].y = *y - 1;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y - 1, *x)){ // up-middle
                returnStruct[i].x = *x;
                returnStruct[i].y = *y - 1;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y - 1, *x + 1)){ // up-right
                returnStruct[i].x = *x + 1;
                returnStruct[i].y = *y - 1;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y, *x + 1)){ // right
                returnStruct[i].x = *x + 1;
                returnStruct[i].y = *y;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y + 1, *x + 1)){ // down-right
                returnStruct[i].x = *x + 1;
                returnStruct[i].y = *y + 1;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y + 1, *x)){ // down-middle
                returnStruct[i].x = *x;
                returnStruct[i].y = *y + 1;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y + 1, *x - 1)){ // down-left
                returnStruct[i].x = *x - 1;
                returnStruct[i].y = *y + 1;
                returnStruct[i].on_board = 1;
                i++;
            }
            if(blankOrEnemy(*y, *x - 1)){ // left
                returnStruct[i].x = *x - 1;
                returnStruct[i].y = *y;
                returnStruct[i].on_board = 1;
                i++;
            }
            break;
        case B_QUEEN:
        case W_QUEEN: 
            printf("Piece is a queen\n");
            for(int j = 1; j < BOARD_HEIGHT; j++){ // upward movement
                if (blankOrEnemy(*y - j, *x) && pathBlocked == false){
                    returnStruct[i].x = *x;
                    returnStruct[i].y = *y - j;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y - j][*x] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // downward movement
                if (blankOrEnemy(*y + j, *x) && pathBlocked == false){
                    returnStruct[i].x = *x;
                    returnStruct[i].y = *y + j;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y + j][*x] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // leftward movement
                if (blankOrEnemy(*y, *x - j) && pathBlocked == false){
                    returnStruct[i].x = *x - j;
                    returnStruct[i].y = *y;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y][*x - j] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // rightward movement
                if (blankOrEnemy(*y, *x + j) && pathBlocked == false){
                    returnStruct[i].x = *x + j;
                    returnStruct[i].y = *y;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y][*x + j] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // up-left movement
                if (blankOrEnemy(*y - j, *x - j) && pathBlocked == false){
                    returnStruct[i].x = *x - j;
                    returnStruct[i].y = *y - j;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y - j][*x - j] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // up-right movement
                if (blankOrEnemy(*y - j, *x + j) && pathBlocked == false){
                    returnStruct[i].x = *x + j;
                    returnStruct[i].y = *y - j;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y - j][*x + j] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // down-right movement
                if (blankOrEnemy(*y + j, *x + j) && pathBlocked == false){
                    returnStruct[i].x = *x + j;
                    returnStruct[i].y = *y + j;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y + j][*x + j] != BLANK){
                    pathBlocked = true;
                }
            }
            pathBlocked = false;
            for(int j = 1; j < BOARD_HEIGHT; j++){ // down-left movement
                if (blankOrEnemy(*y + j, *x - j)&& pathBlocked == false){
                    returnStruct[i].x = *x - j;
                    returnStruct[i].y = *y + j;
                    returnStruct[i].on_board = 1;
                    i++;
                }
                if(spaces[*y + j][*x - j] != BLANK){
                    pathBlocked = true;
                }
            }
            break;

    }
    printf("Possible moves: \n");
    for(int j = 0; j < i; j++){
        if(returnStruct[j].on_board > 0)
            printf("%d, %d\n", returnStruct[j].x, returnStruct[j].y);
    }
    for (int j = 0; j < i; j++){
        returnStruct[i].x = 0;
        returnStruct[i].y = 0;
        returnStruct[i].on_board = 0;
    }
    
    return returnStruct;
}

int is_valid_move(struct move *legal, int x, int y){
    return 0;
}

int select_move(int *startX, int *startY, int *endX, int *endY){
    struct move *legalMoves;
    legalMoves = get_legal_moves(startX, startY);
    char playerIn[5];
    printf("Enter X coordinate: ");
    fgets(playerIn, 5, stdin);
    *endX = atoi(playerIn);
    if(*endX < 0 || *endX > BOARD_WIDTH - 1){
        printf("Error! Try again!\n");
        free(legalMoves);
        return select_move(startX, startY, endX, endY);
    }
    printf("Enter Y coordinate: ");
    fgets(playerIn, 5, stdin);
    *endY = atoi(playerIn);
    if(*endY < 0 || *endY > BOARD_HEIGHT - 1){
        printf("Error! Try again!\n");
        free(legalMoves);
        return select_move(startX, startY, endX, endY);
    }

    free(legalMoves);

    return 0;
}

int perform_move(){
    return 0;
}

int switch_players(){
    return 0;
}

int gameplay_loop(){
    int *startX, *startY, *endX, *endY;
    startX = malloc(sizeof(int));
    startY = malloc(sizeof(int));
    endX = malloc(sizeof(int));
    endY = malloc(sizeof(int));

    printf("Player %d's turn!\n", playerTurn);
    select_piece(startX, startY);
    select_move(startX, startY, endX, endY);
    printf("end move: %d, %d\n", *endX, *endY);
    perform_move();
    switch_players();

    free(startX);
    free(startY);
    free(endX);
    free(endY);
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