// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <String>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WelcomeMessage {TEXT("Welcome to BullCow!\nPress Enter to continue...")};
    PrintLine(WelcomeMessage);
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    FString HiddenWord {TEXT("mouse")};
    ClearScreen();
}