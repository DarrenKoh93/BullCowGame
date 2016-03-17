/*
This is the console executable, that makes use of the the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class.
*/
#pragma once

#include "main.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using FText = std::string; //FText usually used for user interaction therefore used in main
using int32 = int32;

//function prototypes
void PlayGame();
void GetWordLength();
void PrintIntro();
FText GetValidGuess();
void printGuess(FText Guess);
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;//create a instant of new game , which we re-use across plays

//the entry point of application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain()==1);
	system("pause");
	return 0;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 NUMBER_OF_TRIES = BCGame.GetMaxTries();
	//loop asking for guesses while the game 
	//is NOT won & there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() != NUMBER_OF_TRIES+1)
	{
		FText Guess = GetValidGuess();
		
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess); //submit valid guess to the game
		
		std::cout << "Your guess is: " << Guess << std::endl;
		std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}
	PrintGameSummary(); //summarise game
	return;	
}

//obtain player's choice of word length, and set it into game object, BCGame
void GetWordLength()
{
	FText WLChoice = "";
	do
	{
		std::cout << "Select Word Length: 3, 4, 5, 6, 7" << std::endl;
		std::getline(std::cin, WLChoice);
	} while (!std::stoi(WLChoice)<8 && !std::stoi(WLChoice) >2);

	BCGame.SetWordLengthChoice(std::stoi(WLChoice));
	std::cout << "Can you guess the " << WLChoice << " letter isogram I'm thinking of?" << std::endl << std::endl;
	return;
}

void PrintIntro() 
{
	//introduce game
	//constexpr int32 WORD_LENGTH = 5; constant expression, WORD_LENGTH cannot change and has a value of 5.
	
	std::cout << "Welcome to Bulls and Cows, a fun word game" << std::endl;
	GetWordLength();
	return;
}

FText GetValidGuess() //Loop until player gives a valid guess
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do
	{
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry <<" of " << BCGame.GetMaxTries()<< ". Enter your guess" << std::endl;
		getline(std::cin, Guess);

		//check if guess is valid , status
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word" << std::endl;
			break;

		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters" << std::endl;
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter the word in lowercase" << std::endl;
			break;

		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status!=EGuessStatus::OK); //keep looping until we get no errors
	return Guess;
}

void printGuess(FText Guess) 
{
	//repeat the guess back to them
	std::cout << "Your guess was: " << Guess << std::endl;
}

bool AskToPlayAgain()
{
	FText response ="";
	std::cout << "Do you want to play again" << std::endl << "(y/n)"<< std::endl << std::endl;
	getline(std::cin, response);

	return (response[0] == 'Y') || (response[0] == 'y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You won, Welldone" << std::endl;
	}
	else 
	{
		std::cout << "You lose, Better luck next time" << std::endl;
	}
}
