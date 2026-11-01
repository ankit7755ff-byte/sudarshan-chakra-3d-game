#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MahaKaliyaBoss.generated.h"

UENUM(BlueprintType)
enum class EBossCombatPhase : uint8
{
	PhaseOne_Standard   UMETA(DisplayName = "Phase 1: Toxic Strikes"),
	PhaseTwo_Enraged    UMETA(DisplayName = "Phase 2: Enraged Poison Nova"),
	DefeatedCinematic   UMETA(DisplayName = "Defeated: Divine Liberation")
};

UCLASS()
class SUDARSHAN_API AMahaKaliyaBoss : public ACharacter
{
	GENERATED_BODY()

public:
	AMahaKaliyaBoss();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Boss")
	FString BossTitle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Boss")
	EBossCombatPhase BossPhase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Boss")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Boss")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Boss")
	float ToxicSpitDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Boss")
	float TailSweepDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Boss")
	float EnrageThresholdPercent;

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Boss")
	void UnleashPoisonNova();

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Boss")
	void ExecuteTailSweep();

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Boss")
	void TriggerEnragePhase();

	UFUNCTION(BlueprintPure, Category = "Sudarshan|Boss")
	float GetBossHealthPercent() const { return CurrentHealth / MaxHealth; }

private:
	bool bHasEnraged;
	float AttackTimer;
};
