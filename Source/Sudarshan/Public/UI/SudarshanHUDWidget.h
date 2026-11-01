#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SudarshanHUDWidget.generated.h"

UCLASS()
class SUDARSHAN_API USudarshanHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Sudarshan|HUD")
	void UpdateHealthBar(float Percent);

	UFUNCTION(BlueprintImplementableEvent, Category = "Sudarshan|HUD")
	void UpdateStaminaBar(float Percent);

	UFUNCTION(BlueprintImplementableEvent, Category = "Sudarshan|HUD")
	void UpdateScoreAndKills(int32 Score, int32 Kills);

	UFUNCTION(BlueprintImplementableEvent, Category = "Sudarshan|HUD")
	void ShowBossBar(const FString& BossTitle, float HealthPercent);

	UFUNCTION(BlueprintImplementableEvent, Category = "Sudarshan|HUD")
	void HideBossBar();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sudarshan|HUD")
	void ShowKillNotification(const FString& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = "Sudarshan|HUD")
	void ShowRealmTransition(const FString& RealmName);
};
