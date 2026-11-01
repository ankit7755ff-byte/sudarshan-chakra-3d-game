#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SudarshanCombatComponent.generated.h"

class ASudarshanCharacter;
class ASudarshanChakraActor;

UENUM(BlueprintType)
enum class ECombatMode : uint8
{
	FingerHover UMETA(DisplayName = "Hovering on Finger"),
	Aiming      UMETA(DisplayName = "Precision Aiming"),
	Thrown      UMETA(DisplayName = "Chakra In Flight"),
	MahaStorm   UMETA(DisplayName = "108 Blades Storm Defense"),
	ChainSlice  UMETA(DisplayName = "Multi-Target Ricochet")
};

UCLASS(ClassGroup=(Sudarshan), meta=(BlueprintSpawnableComponent))
class SUDARSHAN_API USudarshanCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USudarshanCombatComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Combat")
	ECombatMode CombatMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Combat")
	float MaxAimDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Combat")
	float BaseBladeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Combat")
	int32 MaxChainTargets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Combat")
	FVector CurrentAimHitLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Combat")
	bool bHasAimTarget;

	// --- COMBAT ACTIONS ---
	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void StartAiming();

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void StopAiming();

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void ThrowChakra();

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void RecallChakra();

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void TriggerMahaStormDefense();

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void PerformMeleeSpin();

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void ExecuteChainRicochet(const TArray<AActor*>& TargetEnemies);

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void OnChakraImpact(AActor* HitActor, const FVector& ImpactPoint, const FVector& ImpactNormal);

private:
	ASudarshanCharacter* OwnerCharacter;
	ASudarshanChakraActor* ActiveChakra;

	void UpdateAimTrace();
};
