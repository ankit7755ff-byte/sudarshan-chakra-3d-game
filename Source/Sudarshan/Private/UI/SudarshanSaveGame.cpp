#include "UI/SudarshanSaveGame.h"

USudarshanSaveGame::USudarshanSaveGame()
{
	PlayerName = TEXT("Yoddha Arjun");
	WarriorRank = TEXT("Maha-Rathi");
	TotalAsurasSlain = 0;
	HighScore = 0;
	BestSurvivalTimeSeconds = 0.0f;
	bUnlockedCelestialVaikuntha = true;
	MasterAudioVolume = 1.0f;
	GraphicsQualityLevel = 2; // High
}
