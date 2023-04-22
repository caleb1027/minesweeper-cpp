using namespace std;

class Tile {
    public:
        Tile(bool isMine, int numMinesAdjacent);
        Tile();
        void setFlagged();
        void setRevealed();
        void setIsMine(bool isMine);
        bool getIsMine();
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
        bool isMine;
        int numMinesAdjacent;
};