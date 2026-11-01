#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SudarshanChakraActor.generated.h"

UENUM(BlueprintType)
enum class EChakraFlightState : uint8
{
	Holstered UMETA(DisplayName = "Held on Finger"),
	Launched  UMETA(DisplayName = "Flying to Target"),
	Returning UMETA(DisplayName = "Returning to Hand"),
	MahaStorm UMETA(DisplayName = "108 Blades Shield Storm")
};

UCLASS()
class SUDARSHAN_API ASudarshanChakraActor : public AActor
{
	GENERATED_BODY()

public:
	ASudarshanChakraActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void LaunchAtTarget(const FVector& TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Combat")
	void RecallToOwner();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|State")
	EChakraFlightState FlightState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sudarshan|Properties")
	float FlightSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sudarshan|Properties")
	float BladeDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sudarshan|Properties")
	float MaxFlightDistance;
};
