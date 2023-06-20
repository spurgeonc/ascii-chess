const BOARD_WIDTH = 8;
const BOARD_HEIGHT = 8;
const PLAYER_1 = 1;
const PLAYER_2 = 2;
const BLANK = 0;
const W_PAWN = 1;
const W_KNIGHT = 2;
const W_ROOK = 3;
const W_BISHOP = 4;
const W_QUEEN = 5;
const W_KING = 6;
const B_PAWN = 7;
const B_KNIGHT = 8;
const B_ROOK = 9;
const B_BISHOP = 10;
const B_QUEEN = 11;
const B_KING = 12;
const TEST_ENEMY = 13;
const translations = [
    "___", "WPN", "WKT", "WRK", "WBP", "WQN", "WKG", "BPN", "BKT", "BRK", "BBP", "BQN", "BKG", "TST"
];
let spaces = new Array(BOARD_WIDTH).fill().map(() => new Array(BOARD_HEIGHT).fill(0));
function print_board(){
    for(let i = 0; i < BOARD_HEIGHT; i++){
        if (i == 0)
            console.log("    0    1    2    3    4    5    6    7  ");
        console.log(`${i}  `, end='');
        for (let j = 0; j < BOARD_WIDTH; j++){
            console.log(`${translations[spaces[i][j]]}  `, end='');
        }
        console.log("\n\n");
    }
    return 0;
}

function init_board(){
    playerTurn = PLAYER_1;
    for (let i = 0; i < BOARD_WIDTH; i++){
        spaces[1][i] = B_PAWN;
        spaces[BOARD_HEIGHT - 2][i] = W_PAWN;
    }
        spaces[0][0] = B_ROOK;
        spaces[0][1] = B_KNIGHT;
        spaces[0][2] = B_BISHOP;
        spaces[0][3] = B_KING;
        spaces[0][4] = B_QUEEN;
        spaces[0][5] = B_BISHOP;
        spaces[0][6] = B_KNIGHT;
        spaces[0][7] = B_ROOK;
}
