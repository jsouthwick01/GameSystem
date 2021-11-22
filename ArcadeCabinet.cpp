#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include "BJrun.h"
using namespace std;

int main() 
{
	int bored=1;
	int input=0;
	while(bored!=0)
	{
		cout<<"\nWould you like to play a game? \nEnter 1 for Blackjack \nEnter 2 for Tic-Tac-Toe \nEnter 3 for Minesweeper";
		scanf("%d", &input);
		switch (input)
		{
			case 1:
			{
				runner(); break;
			}
			case 2:
			{
				return 0;
			}
			case 3:
			{
				return 0;
			}
		}
		cin.ignore();
		cout<<"\nWould you like to play another game? Enter 1 for yes and 0 for no.";
		scanf("%d", &bored);
	}
	return 0;
}