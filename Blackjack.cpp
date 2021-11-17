#include <bits/stdc++.h>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <math.h>
#include <string>
#include "BJrun.h"
#define numOfCards 52

using namespace std;
class Card
{
    // Access specifier
    public:
 
    // Data Members
    string face, suit;
    int cardValue;
	
	void setCardValue() 
	{
			
			if(face=="ace"){
				cardValue=1;
			}
			else if(face=="jack") {
				cardValue=10;

			}
			else if(face=="king") {
				cardValue=10;

			}
			else if(face=="queen") {
				cardValue=10;
			}else
			{
				cardValue=stoi(face);
			}
	}
	
	Card()
	{}
	Card(string x, string y)
	{
		face=x;
		suit=y;
		setCardValue();
	}

};

class DeckOfCards
{
    // Access specifier
    public:
 
    // Data Members
	int currentCard;
	Card deck[numOfCards];
	
    DeckOfCards()//deck creation method
    {
        string faces[] = {"ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king"};
		string suits[] = {"hearts", "diamonds", "clubs", "spades"};
		currentCard = 0; // first Card dealt will be deck[0]

		// populate deck with Card objects
		for (int count = 0; count < numOfCards; count++) 
		{
			deck[count] = Card(faces[count % 13], suits[count / 13]);
			//[count] = Card("hekl", "Jyve");
		}

    }
	
    void shuffleDeck()//method for shuffling deck after creation
    {
		srand(time(NULL));
        	// next call to method dealCard should start at deck[0] again
		currentCard = 0; 

		// for each Card, pick another random Card (0-51) and swap them
		for (int first = 0; first < numOfCards; first++) 
		{
			// select a random number between 0 and 51 
			int second =  (rand()%numOfCards);
			// swap current Card with randomly selected Card
			Card temp = deck[first];        
			deck[first] = deck[second];   
			deck[second] = temp;            
		} 
    }
	
    Card dealCard()//method for returning a card value to add to player handValue
	{
		//if (currentCard < numOfCards)
			cout<<deck[currentCard].cardValue<<"\n";
			return deck[currentCard++]; // return current Card in array
		//else        
		//	return 0; // return null to indicate that all Cards were dealt
	} 

};

class Player
{
    // Access specifier
    public:
 
    // Data Members
    string playerName;
    int handValue;
 
	Player(string name)
	{
		playerName=name;
		handValue=0;
	}
    // Member Functions()
    void printPlayer()
    {
       cout << "Player is: " << playerName << "\nNumber is player: " << handValue;
    }
};

void game(Player p1, Player p2, DeckOfCards deck)
{
    int winner=1;
    int choice, doneHitP1, doneHitP2=0;
	deck.shuffleDeck();
    do
    {
		if(doneHitP1!=1)
			{
				//loop for choosing to hit or stay
				cout<<"Would "<<p1.playerName<<" like to hit? 1 for yes and 2 for no.";
				scanf("%d", &choice);
				if(choice==1)
				{
					p1.handValue+=deck.dealCard().cardValue;
					cout<<p1.playerName<<","<<p1.handValue<<"\n";
					doneHitP1=0;
				}else if(choice==2)
				{
					doneHitP1=1;
				}
			}
			if(p1.handValue>21) //checks to see if p1 has gone over 21
        {
            cout<<"Player: "<<p1.playerName<<" Busts, you Lose.";
			winner=0;
            break;
        }
		
			if(doneHitP2!=1)
			{
				cout<<"Would "<<p2.playerName<<" like to hit? 1 for yes and 2 for no.";
				scanf("%d", &choice);
				if(choice==1)
				{
					p2.handValue+=deck.dealCard().cardValue;
					cout<<p2.playerName<<","<<p2.handValue<<"\n";
					doneHitP2=0;
				}else if(choice==2)
				{
					doneHitP2=1;
				}
			}
        //cout<<"Debug "<<p1.playerName<<","<<p1.handValue<<"\n";
        if(p2.handValue>21)//checks to see if p2 has gone over 21
        {
            cout<<"Player: "<<p2.playerName<<" Busts, you Lose.";
            winner=0;
			break;
        }
		
		if(p1.handValue==21 || p1.handValue>p2.handValue && doneHitP1==1 && doneHitP2==1)//checks to see if p1 has blackjack or beat p2
        {
            cout<<"Player: "<<p1.playerName<<" Wins the game.";
            break;
        }else if(p2.handValue==21 || p2.handValue>p1.handValue && doneHitP1==1 && doneHitP2==1)//checks to see if p2 has gotten blackjack or beat p1
        {
            cout<<"Player: "<<p2.playerName<<" Wins the game.";
            break;
        }
		
    }while(winner!=0);
}
 
int runner() 
{
	string name1;
	cout<<"Player 1, please enter your name!\n";
	cin.ignore();
	getline(cin,name1);
	string name2;
	cout<<"Player 2, please enter your name!\n";
	getline(cin,name2);
	
    Player p1= Player(name1);
    Player p2= Player(name2);
	DeckOfCards deck = DeckOfCards();
   // DeckOfCards deck();
    game(p1,p2,deck);
    return 0;
}

/*int main()
{
	return 0;
}*/