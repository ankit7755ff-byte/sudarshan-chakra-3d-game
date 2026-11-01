#include "SudarshanChakraActor.h"
#include "Sudarshan.h"

ASudarshanChakraActor::ASudarshanChakraActor()
{
	PrimaryActorTick.bCanEverTick = true;
	FlightState = EChakraFlightState::Holstered;
	FlightSpeed = 4500.0f;
	BladeDamage = 150.0f;
	MaxFlightDistance = 6000.0f;
}

void ASudarshanChakraActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Sudarshan Chakra spawned with 24 Katili Blades."));
}

void ASudarshanChakraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Continuous blade spin
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += (FlightState == EChakraFlightState::MahaStorm ? 1800.0f : 720.0f) * DeltaTime;
	SetActorRotation(CurrentRotation);
}

void ASudarshanChakraActor::LaunchAtTarget(const FVector& TargetLocation)
{
	FlightState = EChakraFlightState::Launched;
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Chakra launched towards target: %s"), *TargetLocation.ToString());
}

void ASudarshanChakraActor::RecallToOwner()
{
	FlightState = EChakraFlightState::Returning;
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Chakra recalling to owner."));
}
