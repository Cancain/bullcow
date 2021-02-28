// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <String>

void UBullCowCartridge::BeginPlay()
{ // When the game starts
    Super::BeginPlay();
    SetupGame();

    // PrintLine(FString::Printf(TEXT("The hidden word is %s"), *HiddenWord)); // Overridden in Cartridge.h
    PrintLine(TEXT("The hidden word is %s."), *HiddenWord); // Debug line
}

void UBullCowCartridge::OnInput(const FString &Input)
{ // When the player hits enter
    // If the game is over ClearScreen() and SetupGame() the game
    // Else check player guess

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to BullCow!"));

    HiddenWord = TEXT("mouse");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \nPress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again"));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
        EndGame();
    }
    else
    {
        PrintLine(TEXT("Lost a life!"));
        PrintLine(TEXT("%i"), --Lives);
        if (Lives > 0)
        {
            if (Guess.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("Sorry, try guessing again!.\nYou have %i lives"), Lives);
            }
        }
        else
        {
            PrintLine(TEXT("You have no lives left"));
            EndGame();
        }
    }
}