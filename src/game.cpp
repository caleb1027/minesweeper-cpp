#include <bits/stdc++.h>
#include <iostream>
#include "tile.h"
using namespace std;

class Game {
    int difficulty;
    int numMinesLeft;
    int **board;

    public:
        Game(int difficulty) {
            this->difficulty = difficulty;
            numMinesLeft = difficulty / 2;
            this->board = setBoard(1, 1, difficulty);
        }
        void printBoard();
        void freeBoard();

    private:
        int ** setBoard(int x, int y, int numRCs);
        void setAdjacent(int **board);
        int checkAdjacentForMines(int posX, int posY, int **board, int numRCs);
        bool checkAdjacentIsZero(int posX, int posY, int **board, int numRCs)

};

bool Game::checkAdjacentIsZero(int posX, int posY, int **board, int numRCs) {
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            if(posX+i >= 0 && posX+i < numRCs && posY+j >= 0 && posY+j < numRCs) {
                if(board[posX+i][posY+j] == 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

int Game::checkAdjacentForMines(int posX, int posY, int **board, int numRCs) {
    int counter = 0;
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            if(posX+i >= 0 && posX+i < numRCs && posY+j >= 0 && posY+j < numRCs) {
                if(board[posX+i][posY+j] == -1) {
                    counter++;
                }
            }
        }
    }
    return counter;
}


void Game::freeBoard() {
    for(int i = 0; i < difficulty; i++) {
        delete[] board[i];
    }
    delete[] board;
}
void Game::printBoard() {
    for(int i = 0; i < difficulty; i++) {
        for(int j = 0; j < difficulty; j++) {
            printf("%4d", board[i][j]);
        }
        cout << endl;
    }
}

void Game::setAdjacent(int **board) {
    for(int i = 0; i<difficulty; i++) {
        for(int j = 0; j<difficulty; j++) {
            if(board[i][j] != -1) {
                board[i][j] = checkAdjacentForMines(i, j, board, difficulty);
            }
        }
    }
}

int ** Game::setBoard(int x, int y, int numRCs) {
    int **board = new int*[numRCs];

    // Initiates board with -12 (arbitrary value)
    for(int i = 0; i < numRCs; i++) {
        board[i] = new int[numRCs];
        for(int j = 0;  j < numRCs; j++) {
            board[i][j] = -12;
        }
    }
    // Sets all tiles adjacent to game start position to 0
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            if(x+i >= 0 && x+i < numRCs && y+j >= 0 && y+j < numRCs) {
                board[x+i][y+j] = 0;
            }
        }
    }

    int counter = 0;
    // Sets random tiles as mines
    while(counter < numRCs) {
        int randX = rand() % numRCs;
        int randY = rand() % numRCs;
        if(board[randX][randY] < -1 && !checkAdjacentIsZero(randX, randY, board, difficulty)) {
            board[randX][randY] = -1;
            counter++;
        }
    }
    setAdjacent(board);

    Tile
    return board;
}

int main() {
    Game game = Game(10);
    game.printBoard();
    game.freeBoard();
}