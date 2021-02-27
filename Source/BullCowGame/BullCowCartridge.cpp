// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <String>

void UBullCowCartridge::BeginPlay(){ // When the game starts
    Super::BeginPlay();
    SetupGame();

    // PrintLine(FString::Printf(TEXT("The hidden word is %s"), *HiddenWord)); // Overridden in Cartridge.h 
    PrintLine(TEXT("The hidden word is %s."), *HiddenWord); // Debug line
}

void UBullCowCartridge::OnInput(const FString& input){ // When the player hits enter
    // If the game is over ClearScreen() and SetupGame() the game
    // Else check player guess

    if(bGameOver){
        ClearScreen();
        SetupGame();
    } else {
           if(input == HiddenWord){
            PrintLine(TEXT("You have won!"));
            EndGame();
        } else {
            if(HiddenWord.Len() != input.Len()){
                PrintLine(
                    TEXT("The hidden word is %i characters long. \nYou have lost"), 
                        HiddenWord.Len()
                );

                EndGame();
            }
        }
    }
}

void UBullCowCartridge::SetupGame(){
    PrintLine(TEXT("Welcome to BullCow!"));  

    HiddenWord = TEXT("mouse");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len()); 
    PrintLine(TEXT("Type in your guess. \nPress enter to continue..."));
}

void UBullCowCartridge::EndGame(){
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again"));
}