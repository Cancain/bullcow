// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge {
  GENERATED_BODY()

 public:
  virtual void BeginPlay() override;
  virtual void OnInput(const FString& PlayerInput) override;
  void SetupGame();
  void EndGame();
  void ProcessGuess(const FString& Guess);
  static bool IsIsogram(const FString& Word);
  void GetWords();
  TArray<FString> GetValidWords(const TArray<FString>& WordList) const;

 private:
  TArray<FString> Isograms;
  int32 Lives;
  FString HiddenWord;
  bool bGameOver;
  TArray<FString> Words;
};
