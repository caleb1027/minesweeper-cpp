#include <bits/stdc++.h>
#include <iostream>
#include "tile.h"
using namespace std;

// Main goals: 
//  - reduce the amount of guessing necessary to solve the board.
//  - implement a solver that can solve the board.

class Game {
    int difficulty;
    int numMinesLeft;
    bool isSolved;

    public:
        Game(int difficulty, int x, int y) {
            this->difficulty = difficulty;
            numMinesLeft = difficulty / 2;
            this->board = setBoard(x, y, difficulty);
            this->initialClick = {x, y};
            this->isSolved = false;
        }
        void printBoard();
        void freeBoard();
        void revealTile(int x, int y);
        void solveBoard();
    private:
        vector<int> initialClick;
        Tile **board;
        Tile ** setBoard(int x, int y, int numRCs);
        void setAdjacent(int **board);
        int checkAdjacentForMines(int posX, int posY, int **board, int numRCs);
        bool checkAdjacentIsZero(int posX, int posY, int **board, int numRCs);
};

void Game::revealTile(int x, int y) {
    // If already revealed, do nothing
    if(board[x][y].isRevealed) {
        return;
    }
    // If mine, game over
    if(board[x][y].getIsMine()) {
        cout << "You hit a mine! Game over!" << endl;
        return;
    } else {
        // Reveals mine otherwise
        board[x][y].isRevealed = true;
        // If zero, recurse and reveal other mines around that square.
        if(board[x][y].getNumMinesAdjacent() == 0) {
            for(int i = -1; i < 2; i++) {
                for(int j = -1; j < 2; j++) {
                    if(x+i >= 0 && x+i < difficulty && y+j >= 0 && y+j < difficulty) {
                        revealTile(x+i, y+j);
                    }
                }
            }
        }
    }
}

bool Game::checkAdjacentIsZero(int posX, int posY, int **board, int numRCs) {
    // Checks to see if the tile is surrounded by 0s
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
    // Checks around a tile for the number of mines
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
    // Freeing the memory
    for(int i = 0; i < difficulty; i++) {
        delete[] board[i];
    }
    delete[] board;
}
void Game::printBoard() {
    // Prints the board.
    for(int i = 0; i < difficulty; i++) {
        for(int j = 0; j < difficulty; j++) {
            if(board[i][j].isRevealed) {
                if(board[i][j].isFlagged) {
                    printf("%4c", 'F');
                    continue;
                } 
                else {
                    printf("%4d", board[i][j].getNumMinesAdjacent());
                }
            } else {
                printf("%4c", 'X');
            }

        }
        cout << endl;
    }
}

void Game::setAdjacent(int **board) {
    // Checks area around each tile for mines and sets the tile to the number of mines adjacent.
    for(int i = 0; i<difficulty; i++) {
        for(int j = 0; j<difficulty; j++) {
            if(board[i][j] != -1) {
                board[i][j] = checkAdjacentForMines(i, j, board, difficulty);
            }
        }
    }
}

Tile ** Game::setBoard(int x, int y, int numRCs) {
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

    Tile **tileBoard = new Tile*[numRCs];
    // Converts board from ints to Tiles.
    for(int i = 0; i<numRCs; i++) {
        tileBoard[i] = new Tile[numRCs];
        for(int j = 0; j<numRCs; j++) {
            if(board[i][j] == -1) {
                tileBoard[i][j].setIsMine(true);
                tileBoard[i][j].setNumMinesAdjacent(-1);
            } else {
                tileBoard[i][j].setNumMinesAdjacent(board[i][j]);
            }
        }
    }
    return tileBoard;
}

void Game::solveBoard() {
    // Solves the board using set logic.
    // TODO: implement backtracking (? maybe not necessary)
}

int main() {
    Game game = Game(10, 3, 6);
    game.revealTile(3, 6);
    game.printBoard();
    game.freeBoard();
}