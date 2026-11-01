#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AsuraBaseCharacter.generated.h"

UENUM(BlueprintType)
enum class EAsuraType : uint8
{
	KaliyaSerpent  UMETA(DisplayName = "Toxic Kaliya Serpent"),
	AghasuraPython UMETA(DisplayName = "Heavy Aghasura Python"),
	HornedWarrior  UMETA(DisplayName = "Demonic Horned Infantry"),
	ShadowFiend    UMETA(DisplayName = "Flying Shadow Fiend")
};

UENUM(BlueprintType)
enum class EAsuraAIState : uint8
{
	Patrolling  UMETA(DisplayName = "Patrolling Area"),
	Chasing     UMETA(DisplayName = "Pursuing Player"),
	Attacking   UMETA(DisplayName = "Executing Attack"),
	Staggered   UMETA(DisplayName = "Blade Sliced / Staggered"),
	Defeated    UMETA(DisplayName = "Sanhar / Dissolved")
};

UCLASS()
class SUDARSHAN_API AAsuraBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAsuraBaseCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Asura")
	EAsuraType AsuraType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Asura")
	EAsuraAIState AIState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Asura")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Asura")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Asura")
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Asura")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Asura")
	float AttackCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Asura")
	float SightRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Asura")
	bool bCanSpitVenom;

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Asura")
	void PerformAttack(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Asura")
	void SpitVenom(const FVector& TargetDirection);

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Asura")
	void OnDefeated();

	UFUNCTION(BlueprintPure, Category = "Sudarshan|Asura")
	float GetHealthPercent() const { return CurrentHealth / MaxHealth; }

protected:
	float LastAttackTime;
	void DissolveIntoSparks();
};
