#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::GetWords() {
  const FString WordListPath{FPaths::ProjectContentDir() /
                             TEXT("WordLists/HiddenWordList.txt")};
  FFileHelper::LoadFileToStringArray(Words, *WordListPath);
}

void UBullCowCartridge::BeginPlay() {  // When the game starts
  Super::BeginPlay();
  GetWords();
  SetupGame();

  PrintLine(TEXT("The number of possible words is: %i"), Words.Num());
  PrintLine(TEXT("The number of valid words is: %i."),
            GetValidWords(Words).Num());
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
  HiddenWord = Words[2];
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

TArray<FString> UBullCowCartridge::GetValidWords(
    TArray<FString> WordList) const {
  TArray<FString> ValidWords;

  for (size_t i = 0; i < WordList.Num(); i++) {
    if (WordList[i].Len() >= 4 && WordList[i].Len() <= 8 &&
        IsIsogram(WordList[i])) {
      ValidWords.Emplace(WordList[i]);
    }
  }

  return ValidWords;
}