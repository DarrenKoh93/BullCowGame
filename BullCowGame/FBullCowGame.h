/* The game logic (no view code or direct user interaction)
The game is a simple "guess the word game" based on Mastermind
*/

#pragma once //everything that is imported is imported once
#include <string>

//to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	void Reset(); 
	int32 GetMaxTries() const; //const prevents further value change
	FString Dictionary(int32 WordLength) const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	int32 WordLengthChoice() const;
	void SetWordLengthChoice(int32 choice);
	EGuessStatus CheckGuessValidity(FString) const;

	// provide a method for counting bulls & cows, and increasing try # (return 2 integers in 1 go aka STRUCT)
	FBullCowCount SubmitValidGuess(FString Guess);  //counts bulls & cows , and increases try # assuming valid guess

private:
	int32 MyCurrentTry;
	int32 WLChoice;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString ) const;
	bool IsLowerCase(FString ) const;
};
