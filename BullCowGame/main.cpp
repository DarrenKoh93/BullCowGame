#include "main.h"
#include <iostream>
#include <string>

using namespace std;
void PrintIntro();
string getGuess();
void printGuess(string Guess);
main::main()
{
	
}


main::~main()
{
}

//the entry point of application
int main()
{
	PrintIntro();
	printGuess(getGuess());
	system("pause");
	return 0;
}

void PrintIntro() 
{
	//introduce game
	constexpr int WORD_LENGTH = 5;//constant expression, WORD_LENGTH cannot change and has a value of 5.
	cout << "Welcome to Bulls and Cows, a fun word game" << endl;
	cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?" << endl << endl;
	return;
}

string getGuess()
{
	//get a guess from the player
	cout << "Enter your guess" << endl;
	string Guess = "";
	getline(cin, Guess);
	return Guess;
}

void printGuess(string Guess) 
{
	//repeat the guess back to them
	cout << "Your guess was: " << Guess << endl;
}
