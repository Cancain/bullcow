// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <String>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame();

    // PrintLine(FString::Printf(TEXT("The hidden word is %s"), *HiddenWord)); // Overridden in Cartridge.h 
    PrintLine(TEXT("The hidden word is %s."), *HiddenWord); // Debug line

    PrintLine(TEXT("Welcome to BullCow!"));  
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len()); 
    PrintLine(TEXT("Type in your guess and press enter to continue..."));

}

void UBullCowCartridge::OnInput(const FString& input) // When the player hits enter
{
    
    ClearScreen();
    if(input == HiddenWord){
        PrintLine("You have won!");
    } else {
        PrintLine("You have lost!");
        if(HiddenWord.Len() != input.Len()){
            PrintLine(
                TEXT("The hidden word is %i characters long, try again!"), 
                    HiddenWord.Len()
                    );
        }
    }
}

void UBullCowCartridge::SetupGame(){
    HiddenWord = TEXT("mouse");
    Lives = HiddenWord.Len();
}