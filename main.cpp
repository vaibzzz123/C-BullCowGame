/*
This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic, see the FBullCowGame class.

Made this game by following the Unreal Engine/C++ course here: https://www.udemy.com/unrealcourse/?start=0
I added some of my own stuff, like the user being able to make a choice for the length of the hidden word, and the number of guesses adjusting accordingly
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//these substitutions are made to make syntax Unreal Engine friendly later
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //makes instance of new game, which we re-use across plays

int main()
{
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

//plays a single game till completion
void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while the game
	//is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {

		FText Guess = GetValidGuess();
		//Submit valid guess to the game, simple bool if the guess is valid, receive count

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//Print number of bulls and cows
		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << " Cows: " << BullCowCount.Cows << std::endl << std::endl;
	}
	PrintGameSummary();
}

void PrintIntro()
{
	std::cout << "Please choose the length of the hidden word for the game! (3-6) ";
	//reading in user input indefinitely until they enter valid word length
	while (true) {
		FString Input = "";
		std::getline(std::cin, Input);
		if (BCGame.IsValidWordLength(Input)) {
			//submit the user input through a function
			BCGame.SubmitValidWordInput(Input);
			break;
		}
		else {
			std::cout << "Please enter a number between 3 and 6. ";
		}
	}
	BCGame.Reset();
	std::cout << "\nWelcome to Vaib's Bulls and Cows game!" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter word I'm thinking of within " << BCGame.GetMaxTries() << " tries?" << std::endl;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "You won!" << std::endl;
	}
	else {
		std::cout << "You lost!" << std::endl;
	}
}

// Loop continually until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurTry = BCGame.GetCurrentTry();
		std::cout << "Try #" << CurTry << ", you have " << BCGame.GetMaxTries() - BCGame.GetCurrentTry() << " tries left. What is your guess? ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase: //TODO: just convert input to all lowercase instead
			std::cout << "Please enter all letters in lowercase." << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a valid isogram: A word with no repeating letters." << std::endl;
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until no more errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Would you like to play again? (y/n)" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);
	return((Response[0] == 'y') || (Response[0] == 'Y'));
}
