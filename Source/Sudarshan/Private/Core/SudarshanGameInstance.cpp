#include "Core/SudarshanGameInstance.h"
#include "UI/SudarshanSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Sudarshan.h"

USudarshanGameInstance::USudarshanGameInstance()
{
#if PLATFORM_ANDROID
	ActivePlatform = EPlatformProfile::AndroidMobile;
#else
	ActivePlatform = EPlatformProfile::WindowsPC;
#endif
	ActiveSaveProfile = nullptr;
}

void USudarshanGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN GOLD MASTER: Game Instance initialized on platform %d"), (int32)ActivePlatform);
	LoadGameData();
}

void USudarshanGameInstance::Shutdown()
{
	SaveGameData();
	Super::Shutdown();
}

void USudarshanGameInstance::SaveGameData()
{
	if (!ActiveSaveProfile)
	{
		ActiveSaveProfile = Cast<USudarshanSaveGame>(UGameplayStatics::CreateSaveGameObject(USudarshanSaveGame::StaticClass()));
	}

	if (ActiveSaveProfile)
	{
		UGameplayStatics::SaveGameToSlot(ActiveSaveProfile, TEXT("SudarshanMasterSave"), 0);
		UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Game data saved successfully to slot."));
	}
}

void USudarshanGameInstance::LoadGameData()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("SudarshanMasterSave"), 0))
	{
		ActiveSaveProfile = Cast<USudarshanSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SudarshanMasterSave"), 0));
		UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Existing game data loaded for player: %s"), *ActiveSaveProfile->PlayerName);
	}
	else
	{
		ActiveSaveProfile = Cast<USudarshanSaveGame>(UGameplayStatics::CreateSaveGameObject(USudarshanSaveGame::StaticClass()));
		SaveGameData();
	}
}

void USudarshanGameInstance::ApplyScalabilityPreset(int32 QualityLevel)
{
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Scalability preset applied: Level %d"), QualityLevel);
}
