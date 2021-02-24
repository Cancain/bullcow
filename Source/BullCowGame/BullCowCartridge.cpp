// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <String>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString welcomeMessage {TEXT("Welcome to BullCow!\nGuess the 4 letter word\nPress enter to continue...")}; // Magic number remove
    PrintLine(welcomeMessage);
}

void UBullCowCartridge::OnInput(const FString& input) // When the player hits enter
{
    FString hiddenWord {TEXT("mouse")}; // Move outside this function
    ClearScreen();
    bool isCorrect = input == hiddenWord;
    PrintLine(isCorrect ? "You have won!" : "You have lost!");
}