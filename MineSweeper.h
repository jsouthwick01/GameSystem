#include <iostream>
#include <string>
#define SIZE 14
class MineSweeper
{
public:
    MineSweeper();
    void startGame(void);
private:
        //This is the board the user sees, the board with all our info, and the size of our key.
        std::string board[SIZE+1][SIZE+1];
        //Key for board: # represents an unrevealed positon
        //F represents a flag
        //9 represents a bomb
        //numbers 0-8 represent how many bombs are around that position.
        int key[SIZE][SIZE];
        bool revealed[SIZE][SIZE];
        int bombNum;
        int score;
    void initializeBoard(void);
    int checkSurroundings(int,int,int);
    bool pickPosition(int,int);
    void reset(void);
    void reveal(int,int);
    bool playAgain(void);
    void printBoard(void);
    void printKey(void);
    void flagPosition(int,int);
};

