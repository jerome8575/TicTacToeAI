#include <iostream>
#include <algorithm>

using namespace std;

struct Move{
    int row;
    int col;
};
int checkWin(char b[3][3]){
    for (int row = 0; row<3; row++){
        if (b[row][0]==b[row][1] && b[row][1]==b[row][2]){
            if (b[row][0]=='X') 
                return 10; 
            else if (b[row][0]=='O') 
                return -10; 
        } 
    } 
    for (int col = 0; col<3; col++){ 
        if (b[0][col]==b[1][col] && b[1][col]==b[2][col]){ 
            if (b[0][col]=='X') 
                return 10; 
            else if (b[0][col]=='O') 
                return -10; 
        } 
    } 
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]){ 
        if (b[0][0]=='X') 
            return 10; 
        else if (b[0][0]=='O') 
            return -10; 
    } 
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]){ 
        if (b[0][2]=='X') 
            return 10; 
        else if (b[0][2]=='O') 
            return -10; 
    } 
    return 0; 
}
bool isFull(char board[3][3]){
    for (int i = 0; i<3; i++) 
        for (int j = 0; j<3; j++) 
            if (board[i][j]=='-') 
                return false; 
    return true; 
}
void printBoard(char board[3][3]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}
int minimax(char board[3][3], int depth, bool isMax){

    int score = checkWin(board);

    if (score == 10)
        return score;
    if (score == -10)
        return score;
    if(isFull(board))
        return 0;

    if (isMax){
        int best = -1000;

        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (board[i][j] == '-'){
                    board[i][j] = 'X';
                    best = max(best, minimax(board, depth+1, false));
                    board[i][j] = '-';
                }
            }
        }
        return best;
    }
    else{
        int best = 1000;

        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (board[i][j] == '-'){
                    board[i][j] = 'O';
                    best = min(best, minimax(board, depth+1, true));
                    board[i][j] = '-';
                }
            }
        }
        return best;
    }
}
Move findBestMove(char board[3][3]){
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (board[i][j] == '-'){
                board[i][j] = 'X';

                int moveValue = minimax(board, 0, false);
                board[i][j] = '-';
                if (moveValue > bestVal){
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveValue;
                }

            }
        }
    }
    return bestMove;

}
void makeHumanPlay(char board[3][3]){
    int r,c;
    cout << "Input coordinates for move" << endl;
    cin >> r >> c;
    board[r][c] = 'O';
}
void makeAIPlay(char board[3][3]){
    Move Aimove = findBestMove(board);
    board[Aimove.row][Aimove.col] = 'X';
}
int main(){
    char board[3][3] = {{'-', '-', '-'},
                        {'-', '-', '-'},
                        {'-', '-', '-'}};
    printBoard(board);
    int player = 0;
    while (checkWin(board) == 0 && !isFull(board)){
        if (player%2 == 0){
            makeAIPlay(board);
            player++;
            printBoard(board);
        }
        else{
            makeHumanPlay(board);
            player++;
            printBoard(board);
        }
    }
    return 0;
}