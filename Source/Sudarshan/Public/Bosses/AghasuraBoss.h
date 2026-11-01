#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AghasuraBoss.generated.h"

UCLASS()
class SUDARSHAN_API AAghasuraBoss : public ACharacter
{
	GENERATED_BODY()

public:
	AAghasuraBoss();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Boss")
	FString BossTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Boss")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Boss")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Boss")
	float EarthTremorDamage;

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Boss")
	void PerformCavernousCharge();

	UFUNCTION(BlueprintPure, Category = "Sudarshan|Boss")
	float GetBossHealthPercent() const { return CurrentHealth / MaxHealth; }
};
