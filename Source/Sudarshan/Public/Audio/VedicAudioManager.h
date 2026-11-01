#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VedicAudioManager.generated.h"

class UAudioComponent;
class USoundBase;

UENUM(BlueprintType)
enum class EAudioThemeState : uint8
{
	PeacefulFlute  UMETA(DisplayName = "Peaceful Bansuri Exploration"),
	CombatDamru    UMETA(DisplayName = "Combat Damru Rhythm"),
	BossTandav     UMETA(DisplayName = "Boss Maha-Tandav War Theme"),
	VictoryShankh  UMETA(DisplayName = "Victory Shankh Naad")
};

UCLASS()
class SUDARSHAN_API AVedicAudioManager : public AActor
{
	GENERATED_BODY()

public:
	AVedicAudioManager();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Audio")
	UAudioComponent* AmbientAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Audio")
	UAudioComponent* CombatAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Audio")
	EAudioThemeState CurrentThemeState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Audio")
	float MasterVolume;

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Audio")
	void TransitionToTheme(EAudioThemeState NewTheme, float FadeDuration = 1.5f);

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Audio")
	void PlaySpatialOneShot(USoundBase* Sound, const FVector& Location, float Volume = 1.0f);
};
