#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SudarshanSaveGame.generated.h"

UCLASS()
class SUDARSHAN_API USudarshanSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	USudarshanSaveGame();

	UPROPERTY(VisibleAnywhere, Category = "Sudarshan|Save")
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = "Sudarshan|Save")
	FString WarriorRank;

	UPROPERTY(VisibleAnywhere, Category = "Sudarshan|Save")
	int32 TotalAsurasSlain;

	UPROPERTY(VisibleAnywhere, Category = "Sudarshan|Save")
	int32 HighScore;

	UPROPERTY(VisibleAnywhere, Category = "Sudarshan|Save")
	float BestSurvivalTimeSeconds;

	UPROPERTY(VisibleAnywhere, Category = "Sudarshan|Save")
	bool bUnlockedCelestialVaikuntha;

	UPROPERTY(VisibleAnywhere, Category = "Sudarshan|Save")
	float MasterAudioVolume;

	UPROPERTY(VisibleAnywhere, Category = "Sudarshan|Save")
	int32 GraphicsQualityLevel;
};
