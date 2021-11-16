#include <iostream>
#include <string>
#define SIZE 14
class MineSweeper {
    public:
       
        MineSweeper()
        {
            bombNum=30;
            score = 0;
            //We put this up here as well since we walk through this before initializing it in the initialize method.
            for(int i = 0; i < SIZE; i++)
            {
                for(int j = 0; j < SIZE; j++)
                {
                    revealed[i][j] = false;
                }
            }
        }
        void startGame()
        {
            reset(); //We start with a reset.
            bool flag = true;
            std::cout << "Type pick to choose a position. Type flag to insert a flag. Type reset to reset the game. Type exit to leave the game.\n";
            while(flag)
            {
                if(score >= (SIZE*SIZE) - bombNum) //The score keeps track of how close to finishing the game you are
                {
                    std::cout << "Congrats! Would you like to play again? y/n\n";
                    flag =playAgain();
                }
                else{
                //Print board
                printBoard();
                //Ask for x, then y position
                std::cout << "What would you like to do?\n";
                std::string hold = "";
                std::cin >> hold;
                if(hold.compare("pick") == 0) //We pick
                {
                    //Both the pick and the flag will begin similarly, they ask for the coordinates next.
                    std::cout <<"Give an X position (row): ";
                    int x =0;
                    std::cin >> x; //Does this break?
                    if(x > 0 && x <= SIZE) //Validate x before going forward.
                    {
                        std::cout <<"Give a Y position (col): ";
                        int y = 0;
                        std::cin >> y;
                        if(y > 0 && y <= SIZE)
                        {
                            std::cout << "\n";
                            flag = pickPosition(x-1,y-1); //This allows us to end the game using the gameover method
                        }
                        else{
                            std::cout <<"Invalid y.\n";
                        }
                    }
                    else
                    {
                        std::cout <<"Invalid x.\n";
                    }
                }
                else if(hold.compare("flag") == 0) //We flag
                {
                     std::cout <<"Give an X position: ";
                    int x =0;
                    std::cin >> x;
                    if(x > 0 && x <= SIZE)
                    {
                        std::cout <<"Give a Y position: ";
                        int y = 0;
                        std::cin >> y;
                        if(y > 0 && y <= SIZE)
                        {
                            std::cout << "\n";
                            flagPosition(x,y);
                        }
                        else{
                            std::cout <<"Invalid y.\n";
                        }
                    }
                    else
                    {
                        std::cout <<"Invalid x.\n";
                    }
                }
                else if(hold.compare("reset") == 0)//We reset the board
                {
                    reset();
                }
                else if(hold.compare("exit") == 0)//We exit the game
                {
                    flag = false;
                }
                else{
                    std::cout << "Invalid input. Try again.\n";
                }
                }
               
            }
        }
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
        //We call this when we want to initialize the Boards. We will also set our key up through this
        void initializeBoard()
        {
           
            //Next step we will place bombs.
            for(int i = 0; i < bombNum; i++)
            {
                //Get a random position
                int x = rand()%SIZE;
                int y = rand()%SIZE;
                if(key[x][y] != -1) //If that position is already filled up...
                {
                    i--;
                    continue; //reset
                }
                key[x][y] = 9; //Otherwise place bomb.
            }

            //Then we set up the numbers in the key.
            checkSurroundings(-1,0,0);
            //We set up the revealed array. We don't care about the values since the first check doesn't really reveal anything.
            for(int i = 0; i < SIZE; i++)
            {
                for(int j = 0; j < SIZE; j++)
                {
                    revealed[i][j] = false;
                }
            }
             //We end by showing coordinates on board
            for(int i = 1; i <=SIZE; i++)
            {
                board[i][0] = std::to_string(i);
                board[0][i] = std::to_string(i);;
            }
            //Then we fill the reset of the board with empty indicators.          
            for(int i = 1; i <= SIZE; i++)
            {
                for(int j =1; j <= SIZE; j++)
                {
                    board[i][j] = '#';
                }
            }
            //Final step is to reset our score.
            score = 0;

        }
        //A recursive function!
        int checkSurroundings(int recurseCase, int x, int y)
        {
            //We have found this position, reveal it.
            reveal(x,y);
            //We start by adding one to our current position, which ensures we don't infinitely recurse
            key[x][y]++;
            //Now we need to look at all surrounding positions, but keep in mind that we don't go out of bounds on the array.
            for(int i = x-1; i <= x+1; i++)
            {
                if(i > -1 && i < SIZE) //Not out of bounds
                {
                    for(int j = y-1; j <= y+1; j++)
                    {
                        if(j > -1 && j < SIZE)
                        {
                         
                            if(!revealed[i][j])
                            {
                                reveal(i,j);
                            }
                            //We have found one of the surrounding positions. If recurse is good, we do so
                            if(key[i][j] == recurseCase)
                            {                             
                                
                                checkSurroundings(recurseCase, i, j);
                            }
                            else if(key[i][j] == 9)//Bomb found
                            {
                                key[x][y]++;
                            }

                        }
                    }
                }

            }

        }
        bool pickPosition(int x, int y)
        {
            //Bomb picked
            if(key[x][y] == 9)
            {
                //We announce the game is over, then allow for you to continue or end.
                std::cout << "GAME OVER. Would you like to continue? y/n\n";
                printKey();
                return playAgain();
            }//0 picked
            else if(key[x][y] == 0)
            {
                checkSurroundings(0,x,y);
            }
            else{ //Everything else
                reveal(x,y);
            }

        }
        void reset()
        {
            for(int i = 0; i < SIZE; i++)
            {
                for(int j =0; j < SIZE; j++)
                {
                    key[i][j] = -1; //We set to -1 for empty boards.
                }
            }
            //We then set up the board
            initializeBoard();
        }
        //Reveals this position only.
        void reveal(int x, int y)
        {
            board[x+1][y+1] = std::to_string(key[x][y]);
            score++; //We update the score for each found tile.
            //Show that we have revealed this spot
            revealed[x][y] = true;
        }
        
        bool playAgain()
        {
            
            while(true)
            {
                std::string hold = "";
                std::cin >> hold;
                if(hold.compare("y") == 0)
                {
                    reset();
                    return true;
                }
                else if (hold.compare("n") == 0)
                {
                    return false;
                }
                std::cout << "Invalid input. Try Again.";
            }
        }

        void printBoard()
        {
            for(int i =0; i < SIZE+1; i++)
            {
                for(int j=0; j < SIZE+1; j++)
                {
                    //Print out position.
                    std::cout << board[i][j] << "   ";
                }
                std::cout <<"\n";
            }
        }
        //I might merge this with printboard later 
         void printKey()
        {
            for(int i =0; i < SIZE; i++)
            {
                for(int j=0; j < SIZE; j++)
                {
                    //Print out position.
                    std::cout << key[i][j] << "   ";
                }
                std::cout <<"\n";
            }
        }
        void flagPosition(int x, int y) //This just inserts a flag on the board position.
        {
            board[x][y] = 'F';
        }
        
};

int main()
{
    std::cout <<"Start";
    MineSweeper game;
    game.startGame();
    return 0;
}