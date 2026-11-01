#include "SudarshanGameModeBase.h"
#include "Sudarshan.h"

ASudarshanGameModeBase::ASudarshanGameModeBase()
{
	MaxMatchDurationSeconds = 3600.0f; // 1-Hour Maha-Yuddha Rule
	TotalAsurasDefeated = 0;
}

void ASudarshanGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Maha-Yuddha GameMode started. 1-Hour Challenge active."));
}
