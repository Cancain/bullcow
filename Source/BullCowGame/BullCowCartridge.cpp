#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
// #include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() {  // When the game starts
  Super::BeginPlay();
  GetWords();
  SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) {
  if (bGameOver) {
    ClearScreen();
    SetupGame();
  } else {
    ProcessGuess(PlayerInput);
  }
}

void UBullCowCartridge::SetupGame() {
  PrintLine(TEXT("Welcome to BullCow!"));

  HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];

  Lives = HiddenWord.Len();
  bGameOver = false;

  PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
  PrintLine(TEXT("You have %i lives."), Lives);
  PrintLine(TEXT("Type in your guess and \nPress enter to continue..."));
  PrintLine(TEXT("The hidden word is %s."), *HiddenWord);  // Debug line
}

void UBullCowCartridge::EndGame() {
  bGameOver = true;
  PrintLine(TEXT("\nPress enter to play again"));
}

bool UBullCowCartridge::IsIsogram(const FString& Word) {
  for (int32 Index = 0; Index < Word.Len(); Index++) {
    for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++) {
      if (Word[Index] == Word[Comparison]) {
        return false;
      }
    }
  }

  return true;
}

void UBullCowCartridge::ProcessGuess(const FString& Guess) {
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

void UBullCowCartridge::GetWords() {
  const FString WordListPath{FPaths::ProjectContentDir() /
                             TEXT("WordLists/HiddenWordList.txt")};
  FFileHelper::LoadFileToStringArrayWithPredicate(
      Isograms, *WordListPath, [](const FString& Word) {
        return Word.Len() > 4 && Word.Len() < 8 && IsIsogram(Word);
      });
}

TArray<FString> UBullCowCartridge::GetValidWords(
    const TArray<FString>& WordList) const {
  TArray<FString> ValidWords;

  for (FString Word : WordList) {
    if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word)) {
      ValidWords.Emplace(Word);
    }
  }

  return ValidWords;
}