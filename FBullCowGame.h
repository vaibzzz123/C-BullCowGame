/* The game logic (no view code or direct user interaction */
/* The game is a simple guess the word game based on Mastermind*/

#pragma once
#include <string>

//these substitutions are made to make syntax Unreal Engine friendly later
using FString = std::string;
using int32 = int;

//touple that packages two numbers, the bulls and the cows in a guess
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

//error codes that are used in checking if a user guess is valid
enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	//maybe add a "not letters" type in case user inputs numbers or symbols
};

//main game class
class FBullCowGame 
{
public:
	FBullCowGame(); //constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	bool IsValidWordLength(FString Input) const;
	void SubmitValidWordInput(FString Input);

	EGuessStatus CheckGuessValidity(FString Guess) const;
	//counts bulls and cows, and increases try # (assuming valid guess)
	FBullCowCount SubmitValidGuess(FString);
	void Reset(); //TODO: make a more rich return value

private:
	//see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	int32 UserInputWordLength;
	bool bIsGameWon;

	bool IsIsogram(FString Guess) const;
	bool IsLowercase(FString Guess) const;
};