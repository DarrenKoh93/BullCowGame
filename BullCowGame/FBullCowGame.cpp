#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map //to make syntax Unreal friendly
/*
Game difficulty depends on the word length
The harder the game difficulty, the more amount of tries (life) will be given
*/
FBullCowGame::FBullCowGame() {Reset();} //default constructor


int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const {return bGameIsWon;}
int32 FBullCowGame::WordLengthChoice() const { return WLChoice; }
void FBullCowGame::SetWordLengthChoice(int32 choice) { WLChoice = choice; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	//a system that increments the # of max tries in accordance to word length
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,21}};
	return WordLengthToMaxTries[MyHiddenWord.length()]; //returns the # of max tries in accordance of word length
}

FString FBullCowGame::Dictionary(int32 WordLength) const
{
	TMap<int32, FString> WordLengthToHiddenWord{ { 3,"top" },{ 4,"dota" },{ 5,"tries" },{ 6,"planet" },{ 7,"planets" },{ 8,"" },{ 9,"" } };

	return WordLengthToHiddenWord[WordLength];
}

void FBullCowGame::Reset()
{	
	MyHiddenWord = Dictionary(WordLengthChoice()); //Hiddenword MUST be an isogram
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

//important thing to note is that each check must not rely on each other and can be placed in any order e.g. IsLowerCase -> IsIsogram avoid implicit dependency
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if the guess is not an isogram 
	{
		return EGuessStatus::Not_Isogram; //return an error 
	}
	else if (!IsLowerCase(Guess)) //if the guess is not a lower case TODO Not_Lower  function
	{
		return EGuessStatus::Not_Lowercase; //return an error 
	}
	else if (Guess.length() != GetHiddenWordLength()) //if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length; //return an error
	}
	else //otherwise
	{
		return EGuessStatus::OK; //return OK
	}
}

//recevies a VALID guess, increments turn, and return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) 
{
	//increment the turn number
	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;  //BullCowCount is a type that consist of 2 integers bull and Cow

	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	int32 GuessWordLength = Guess.length();
		for(int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) //loop through all letters in the guess MHWChar = MyHiddenWordCharacter
		{
			for (int32 GChar = 0; GChar < WordLength; GChar++) //compare letters against the hidden word GChar = GuessCharacter
			{				
				if (Guess[GChar] == MyHiddenWord[MHWChar]) //if they match then
				{
					if (MHWChar ==GChar) //if they are in the same place
					{
						BullCowCount.Bulls++; //increment bulls
					}
					else //else , must be cow
					{
						BullCowCount.Cows++; //increment cows
					}
				}
			}
		}
		if (BullCowCount.Bulls == WordLength)
		{
			bGameIsWon = true;
		}
		else
		{
			bGameIsWon = false;
		}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true;}

	TMap<char, bool> LetterSeen; //setup our map
	//loop through all the letters of the word
	for (auto Letter : Word) //for all letters of the Word , auto allows the computer to decide the data type ; in this case its a character
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) //If letter is in the map
		{
			return false;//the word is NOT isogram
		}
		else //otherwise
		{
			LetterSeen[Letter] = true; //add the letter to the map as seen
		}
	}
	return true; //for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	//handle strings of zero length
	if (Word.length() == 0) { return true; }
	//handle strings that contains '\0'
	//handle strings that contains space

	for (auto Letter : Word) //for all letters of the Word , auto allows the computer to decide the data type ; in this case its a character
	{
		if (!islower(Letter))//if the letter is not lowercase,
		{
			return false;//the word contains a uppercase letter
		}
		else //otherwise
		{
			//continue loop
		}	
	}
	return true; //for example in cases where /0 is entered
}
