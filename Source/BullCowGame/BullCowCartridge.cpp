#include "BullCowCartridge.h"

#include <String>

void UBullCowCartridge::BeginPlay() {  // When the game starts
  Super::BeginPlay();
  SetupGame();

  // PrintLine(FString::Printf(TEXT("The hidden word is %s"), *HiddenWord)); //
  // Overridden in Cartridge.h
  PrintLine(TEXT("The hidden word is %s."), *HiddenWord);  // Debug line
}

void UBullCowCartridge::OnInput(const FString& Input) {
  if (bGameOver) {
    ClearScreen();
    SetupGame();
  } else {
    ProcessGuess(Input);
  }
}

void UBullCowCartridge::SetupGame() {
  PrintLine(TEXT("Welcome to BullCow!"));

  HiddenWord = TEXT("mouse");
  Lives = HiddenWord.Len();
  bGameOver = false;

  PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
  PrintLine(TEXT("You have %i lives."), Lives);
  PrintLine(TEXT("Type in your guess and \nPress enter to continue..."));
}

void UBullCowCartridge::EndGame() {
  bGameOver = true;
  PrintLine(TEXT("\nPress enter to play again"));
}

bool UBullCowCartridge::IsIsogram(FString Word) const {
  for (int32 Index = 0; Index < Word.Len(); Index++) {
    for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++) {
      PrintLine(TEXT("index: %c, Comp: %c"), Word[Index], Word[Comparison]);
      if (Word[Index] == Word[Comparison]) {
        return false;
      }
    }
  }

  return true;
}

void UBullCowCartridge::ProcessGuess(FString Guess) {
  if (Guess == HiddenWord) {
    PrintLine(TEXT("You have won!"));
    EndGame();
    return;
  }

  if (Guess.Len() != HiddenWord.Len()) {
    PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
    PrintLine(TEXT("Sorry, try guessing again!.\nYou have %i lives"), Lives);
    return;
  }

  if (!IsIsogram(Guess)) {
    PrintLine(TEXT("No repeating letters, guess again"));
    return;
  }

  PrintLine(TEXT("Lost a life!"));
  --Lives;

  if (Lives <= 0) {
    ClearScreen();
    PrintLine(TEXT("You have no lives left"));
    PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
    EndGame();
    return;
  }

  PrintLine(TEXT("Guess again, you hav %i lives left"), Lives);
}