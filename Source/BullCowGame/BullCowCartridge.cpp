// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <String>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    hiddenWord = TEXT("mouse");
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& input) // When the player hits enter
{
    
    ClearScreen();
    if(input == hiddenWord){
        PrintLine("You have won!");
    } else {
        PrintLine("You have lost!");
        if(hiddenWord.Len() != input.Len()){
            PrintLine("The hidden word is 4 characters long, try again!");
        }
    }
}

void UBullCowCartridge::SetupGame(){
    hiddenWord.Len();
    PrintLine(TEXT("Welcome to BullCow! Guess the 4 letter word"));   
    PrintLine(TEXT("Press enter to continue..."));
    lives = 4;
}