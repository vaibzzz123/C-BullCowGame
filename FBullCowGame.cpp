#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

void FBullCowGame::Reset()
{
	TMap<int32, FString> Isograms{ {3, "ant"}, {4, "bail"}, {5, "haiku"}, {6, "planet"} }; //chooses hidden word isogram based on user input
	MyHiddenWord = Isograms[UserInputWordLength];

	MyCurrentTry = 1;
	bIsGameWon = false;

	return;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	//special case, will treat 0 or 1 letter inputs as isograms
	if (Guess.length() <= 1) {
		return true;
	}

	//make hash table with chars corresponding to letters, and bools corresponding to if they were seen or not
	TMap<char, bool> LetterSeen;
	//have a for loop from 0 to guess.length
	for (char Letter : Guess) /*for all letters in the guess*/ {
		Letter = tolower(Letter); //handle mixed case
		//if the current character has a value of true in the hash table
		if (LetterSeen[Letter]) {
			//return false
			return false;
		}
		//otherwise
		else {
			//add letter to the hash table
			LetterSeen[Letter] = true;
		}
	}
	//otherwise return true
	return true;
}

//receives a valid guess, increments turns and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	//setup a return variable/struct
	FBullCowCount BullCowCount;
	//loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); //assuming same length
	for (int32 MHWChar = 0; MHWChar < WordLength; ++MHWChar) {
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; ++GChar) {
			//if they match, then
			if (Guess[MHWChar] == MyHiddenWord[GChar]) {
				//if in the same position
				if (MHWChar == GChar) {
					//increment bulls
					BullCowCount.Bulls++;
				}
				//if not
				else {
					//increment cows
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
	}
	return BullCowCount;
}

FBullCowGame::FBullCowGame() //default constructor
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const //max tries vary on the length of the hidden word
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,6}, {5,7}, {6,8} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}

bool FBullCowGame::IsValidWordLength(FString Input) const
{
	return (Input[0] == '3' || Input[0] == '4' || Input[0] == '5' || Input[0] == '6');
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//if guess isn't isogram,
	if (!IsIsogram(Guess)) { 
		//return not isogram error
		return EGuessStatus::Not_Isogram;
	}
	//if guess isn't all lowercase
	else if (!IsLowercase(Guess)) {
		//return not all lowercase error
		return EGuessStatus::Not_Lowercase;
	}
	//if guess length is wrong,
	else if (Guess.length() != GetHiddenWordLength()) {
		//return wrong length error
		return EGuessStatus::Wrong_Length;
	}
	//otherwise
	else {
		//return ok status
		return EGuessStatus::OK;
	}
}

void FBullCowGame::SubmitValidWordInput(FString Input)
{
	UserInputWordLength = Input[0] - 48; //converting ascii to numbers
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess) {
		//if not a lowercase letter
		if (!islower(Letter)) {
			//return false
			return false;
		}
	}
	return true;
}
