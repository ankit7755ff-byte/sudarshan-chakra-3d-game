#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SudarshanGameInstance.generated.h"

class USudarshanSaveGame;

UENUM(BlueprintType)
enum class EPlatformProfile : uint8
{
	WindowsPC   UMETA(DisplayName = "Windows PC (High/Ultra)"),
	AndroidMobile UMETA(DisplayName = "Android Mobile (Optimized Touch/LOD)")
};

UCLASS()
class SUDARSHAN_API USudarshanGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USudarshanGameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Core")
	EPlatformProfile ActivePlatform;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Core")
	USudarshanSaveGame* ActiveSaveProfile;

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Core")
	void SaveGameData();

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Core")
	void LoadGameData();

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Optimization")
	void ApplyScalabilityPreset(int32 QualityLevel);
};
