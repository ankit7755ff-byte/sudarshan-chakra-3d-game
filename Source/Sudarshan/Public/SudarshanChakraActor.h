#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"
#include "SudarshanChakraActor.generated.h"

/**
 * Operating States of Bhagwan Shri Krishna's Sudarshan Chakra
 */
UENUM(BlueprintType)
enum class EChakraState : uint8
{
	IdleFloating       UMETA(DisplayName = "Idle Floating (Bobbing & Tilt)"),
	CeremonialSpin     UMETA(DisplayName = "Ceremonial Hover (Finger Spin)"),
	CombatSpin         UMETA(DisplayName = "Combat Ready Spin"),
	MahaStorm          UMETA(DisplayName = "108 Blades Storm Velocity"),
	ThrowPreparation   UMETA(DisplayName = "Charging / Aim Lock"),
	Flying             UMETA(DisplayName = "Supersonic Flight to Target"),
	Returning          UMETA(DisplayName = "Magnetic Parabolic Recall")
};

/**
 * Reusable, High-Performance 3D Sudarshan Chakra Weapon Actor
 * Built for Unreal Engine 5 with modular components, PBR materials, Niagara FX, and procedural audio.
 */
UCLASS(Blueprintable, ClassGroup=(Sudarshan), meta=(BlueprintSpawnableComponent))
class SUDARSHAN_API ASudarshanChakraActor : public AActor
{
	GENERATED_BODY()

public:
	ASudarshanChakraActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// --- COMPONENTS ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Components")
	USceneComponent* SceneRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Components")
	UStaticMeshComponent* ChakraMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Components")
	UNiagaraComponent* EnergyAuraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Components")
	UNiagaraComponent* BladeTrailsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Components")
	UPointLightComponent* DivineLightComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Components")
	UAudioComponent* SpinAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Components")
	UAudioComponent* ActionAudioComponent;

	// --- PROPERTIES & TUNING ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Rotation")
	float TargetRPM;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Rotation")
	float CurrentRPM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Rotation")
	float RotationAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Animation")
	float BobbingAmplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Animation")
	float BobbingFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Animation")
	float PrecessionTiltDegrees;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Combat")
	float FlightSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Combat")
	float BladeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Combat")
	float MaxFlightDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|State")
	EChakraState CurrentState;

	// --- API FUNCTIONS ---
	UFUNCTION(BlueprintCallable, Category = "Sudarshan|State")
	void SetChakraState(EChakraState NewState);

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void LaunchAtTarget(const FVector& TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void RecallToOwner();

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void TriggerCharge();

	UFUNCTION(BlueprintPure, Category = "Sudarshan|State")
	float GetCurrentRPM() const { return CurrentRPM; }

private:
	FVector HomeAnchorLocation;
	FVector FlightTargetLocation;
	FVector FlightVelocity;
	float TotalTraveledDistance;
	float InternalTimer;

	void UpdateFloatingAnimation(float DeltaTime);
	void UpdateSpinPhysics(float DeltaTime);
	void UpdateFlightTrajectory(float DeltaTime);
};
