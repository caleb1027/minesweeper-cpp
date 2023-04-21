using namespace std;

class Tile {
    public:
        Tile(bool isMine, int numMinesAdjacent);
        void setFlagged();
        void setRevealed();
        bool getIsMine();
        bool getIsFlagged();
        bool getIsRevealed();
        int getNumMinesAdjacent();
        void incrNumFlagsAdjacent();
        int getNumFlagsAdjacent();
        bool isFlagged;
        bool isRevealed;
        int numFlagsAdjacent;
    private:
        bool isMine;
        int numMinesAdjacent;
}