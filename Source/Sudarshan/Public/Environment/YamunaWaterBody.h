#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YamunaWaterBody.generated.h"

class UStaticMeshComponent;
class UNiagaraComponent;

UCLASS()
class SUDARSHAN_API AYamunaWaterBody : public AActor
{
	GENERATED_BODY()

public:
	AYamunaWaterBody();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Water")
	UStaticMeshComponent* WaterSurfaceMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Water")
	UNiagaraComponent* WaterSprayFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Water")
	float WaveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Water")
	float WaveAmplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Water")
	bool bIsContaminatedByKaliya;

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Water")
	void TriggerPurificationWave(const FVector& ImpactCenter);

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Water")
	void SetContaminationState(bool bContaminated);
};
