#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalActor.generated.h"

class UBoxComponent;
class UNiagaraComponent;
class UPointLightComponent;

UENUM(BlueprintType)
enum class EWorldRealm : uint8
{
	EarthRealm      UMETA(DisplayName = "Earth Universe (Kurukshetra)"),
	CelestialRealm  UMETA(DisplayName = "Divine Celestial Universe (Vaikuntha)")
};

UCLASS()
class SUDARSHAN_API APortalActor : public AActor
{
	GENERATED_BODY()

public:
	APortalActor();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Portal")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Portal")
	UBoxComponent* PortalTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Portal")
	UNiagaraComponent* PortalVortexFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Portal")
	UPointLightComponent* PortalLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Portal")
	EWorldRealm DestinationRealm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Portal")
	FVector DestinationLocation;

	UFUNCTION()
	void OnPortalOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
