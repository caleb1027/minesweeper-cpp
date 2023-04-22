#include <bits/stdc++.h>
using namespace std;

class Tile {
    public:
        Tile(bool isMine, int numMinesAdjacent);
        Tile();
        void setFlagged();
        void setRevealed();
        void setIsMine(bool isMine);
        bool getIsFlagged();
        bool getIsRevealed();
        int getNumMinesAdjacent();
        void setNumMinesAdjacent(int numMinesAdjacent);
        void incrNumFlagsAdjacent();
        int getNumFlagsAdjacent();
        bool isFlagged;
        bool isRevealed;
        int numFlagsAdjacent;
    private:
        bool getIsMine();
        bool isMine;
        int numMinesAdjacent;
};

Tile::Tile() {
    this->isMine = false;
    this->numMinesAdjacent = 0;
    this->numFlagsAdjacent = 0;
    this->isFlagged = false;
    this->isRevealed = false;
}
Tile::Tile(bool isMine, int numMinesAdjacent) {
    this->isMine = isMine;
    this->numMinesAdjacent = numMinesAdjacent;
    this->numFlagsAdjacent = 0;
    this->isFlagged = false;
    this->isRevealed = false;
}

void Tile::setIsMine(bool IsMine) {
    this->isMine = isMine;
}

void Tile::setNumMinesAdjacent(int numMinesAdjacent) {
    this->numMinesAdjacent = numMinesAdjacent;
}

void Tile::setFlagged() {
    this->isFlagged = true;
}

void Tile::setRevealed() {
    this->isRevealed = true;
}

bool Tile::getIsMine() {
    return this->isMine;
}

bool Tile::getIsFlagged() {
    return this->isFlagged;
}

bool Tile::getIsRevealed() {
    return this->isRevealed;
}

int Tile::getNumMinesAdjacent() {
    return this->numMinesAdjacent;
}

void Tile::incrNumFlagsAdjacent() {
    this->numFlagsAdjacent++;
}

int Tile::getNumFlagsAdjacent() {
    return this->numFlagsAdjacent;
}
