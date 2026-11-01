#include "SudarshanChakraActor.h"
#include "Sudarshan.h"
#include "UObject/ConstructorHelpers.h"

ASudarshanChakraActor::ASudarshanChakraActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Root Scene Component
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRootComponent;

	// 3D Mesh Component (High-Poly Golden Chakra)
	ChakraMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChakraMesh"));
	ChakraMeshComponent->SetupAttachment(RootComponent);
	ChakraMeshComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ChakraMeshComponent->SetGenerateOverlapEvents(true);
	ChakraMeshComponent->SetCastShadow(true);

	// Niagara Divine Aura
	EnergyAuraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EnergyAura"));
	EnergyAuraComponent->SetupAttachment(ChakraMeshComponent);
	EnergyAuraComponent->bAutoActivate = true;

	// Niagara Blade Trails
	BladeTrailsComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BladeTrails"));
	BladeTrailsComponent->SetupAttachment(ChakraMeshComponent);
	BladeTrailsComponent->bAutoActivate = true;

	// Dynamic Golden Point Light
	DivineLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("DivineLight"));
	DivineLightComponent->SetupAttachment(ChakraMeshComponent);
	DivineLightComponent->SetIntensity(3500.0f);
	DivineLightComponent->SetLightColor(FLinearColor(1.0f, 0.78f, 0.15f));
	DivineLightComponent->SetAttenuationRadius(750.0f);
	DivineLightComponent->bUseInverseSquaredFalloff = false;

	// Audio: Looping Hypersonic Spin
	SpinAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SpinAudio"));
	SpinAudioComponent->SetupAttachment(ChakraMeshComponent);
	SpinAudioComponent->bAutoActivate = false;

	// Audio: Action Cue One-Shots (Throw, Charge, Recall)
	ActionAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ActionAudio"));
	ActionAudioComponent->SetupAttachment(RootComponent);
	ActionAudioComponent->bAutoActivate = false;

	// Tuning Parameters
	TargetRPM = 180.0f;
	CurrentRPM = 180.0f;
	RotationAcceleration = 900.0f;
	BobbingAmplitude = 4.5f;
	BobbingFrequency = 2.2f;
	PrecessionTiltDegrees = 4.0f;
	FlightSpeed = 4800.0f;
	BladeDamage = 250.0f;
	MaxFlightDistance = 6500.0f;
	CurrentState = EChakraState::CeremonialSpin;

	TotalTraveledDistance = 0.0f;
	InternalTimer = 0.0f;
}

void ASudarshanChakraActor::BeginPlay()
{
	Super::BeginPlay();
	HomeAnchorLocation = GetActorLocation();

	if (SpinAudioComponent)
	{
		SpinAudioComponent->Play();
	}

	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: ASudarshanChakraActor initialized. Default State: %d"), (int32)CurrentState);
}

void ASudarshanChakraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InternalTimer += DeltaTime;

	UpdateSpinPhysics(DeltaTime);

	switch (CurrentState)
	{
	case EChakraState::IdleFloating:
	case EChakraState::CeremonialSpin:
		UpdateFloatingAnimation(DeltaTime);
		break;

	case EChakraState::CombatSpin:
	case EChakraState::MahaStorm:
		UpdateFloatingAnimation(DeltaTime);
		break;

	case EChakraState::Flying:
	case EChakraState::Returning:
		UpdateFlightTrajectory(DeltaTime);
		break;

	case EChakraState::ThrowPreparation:
		// Charging pulse effect
		if (DivineLightComponent)
		{
			float Pulse = FMath::Sin(InternalTimer * 12.0f) * 1500.0f;
			DivineLightComponent->SetIntensity(5000.0f + Pulse);
		}
		break;
	}
}

void ASudarshanChakraActor::UpdateSpinPhysics(float DeltaTime)
{
	// Interpolate RPM towards target based on state
	switch (CurrentState)
	{
	case EChakraState::IdleFloating:
		TargetRPM = 60.0f;
		break;
	case EChakraState::CeremonialSpin:
		TargetRPM = 180.0f;
		break;
	case EChakraState::CombatSpin:
		TargetRPM = 720.0f;
		break;
	case EChakraState::MahaStorm:
		TargetRPM = 1800.0f;
		break;
	case EChakraState::ThrowPreparation:
		TargetRPM = 960.0f;
		break;
	case EChakraState::Flying:
	case EChakraState::Returning:
		TargetRPM = 1440.0f;
		break;
	}

	CurrentRPM = FMath::FInterpTo(CurrentRPM, TargetRPM, DeltaTime, RotationAcceleration / 60.0f);

	// Degrees per second: RPM * 360 / 60 = RPM * 6
	float DeltaYaw = CurrentRPM * 6.0f * DeltaTime;

	if (ChakraMeshComponent)
	{
		FRotator MeshRot = ChakraMeshComponent->GetRelativeRotation();
		MeshRot.Yaw = FMath::Fmod(MeshRot.Yaw + DeltaYaw, 360.0f);
		ChakraMeshComponent->SetRelativeRotation(MeshRot);
	}

	// Modulate spin audio pitch by RPM
	if (SpinAudioComponent && SpinAudioComponent->IsPlaying())
	{
		float PitchMultiplier = FMath::Clamp(CurrentRPM / 360.0f, 0.4f, 3.0f);
		SpinAudioComponent->SetPitchMultiplier(PitchMultiplier);
	}
}

void ASudarshanChakraActor::UpdateFloatingAnimation(float DeltaTime)
{
	// Harmonic Bobbing: Z = Z_0 + A * sin(omega * t)
	float BobOffset = FMath::Sin(InternalTimer * BobbingFrequency) * BobbingAmplitude;
	FVector NewLocation = HomeAnchorLocation + FVector(0.0f, 0.0f, BobOffset);
	SetActorLocation(NewLocation);

	// Precession Tilt: subtle cosmic wobble around X and Y
	float TiltRoll = FMath::Sin(InternalTimer * 1.5f) * PrecessionTiltDegrees;
	float TiltPitch = FMath::Cos(InternalTimer * 1.5f) * (PrecessionTiltDegrees * 0.7f);
	SetActorRotation(FRotator(TiltPitch, 0.0f, TiltRoll));

	// Light pulsation
	if (DivineLightComponent)
	{
		float BaseIntensity = (CurrentState == EChakraState::MahaStorm) ? 8000.0f : 3500.0f;
		float Flicker = FMath::Sin(InternalTimer * 6.0f) * 400.0f;
		DivineLightComponent->SetIntensity(BaseIntensity + Flicker);
	}
}

void ASudarshanChakraActor::UpdateFlightTrajectory(float DeltaTime)
{
	if (CurrentState == EChakraState::Flying)
	{
		FVector CurrentLoc = GetActorLocation();
		FVector Step = FlightVelocity * DeltaTime;
		SetActorLocation(CurrentLoc + Step);
		TotalTraveledDistance += Step.Size();

		if (TotalTraveledDistance >= MaxFlightDistance)
		{
			RecallToOwner();
		}
	}
	else if (CurrentState == EChakraState::Returning)
	{
		FVector CurrentLoc = GetActorLocation();
		FVector DirectionToHome = (HomeAnchorLocation - CurrentLoc);
		float DistanceToHome = DirectionToHome.Size();

		if (DistanceToHome <= 120.0f)
		{
			// Arrived back home
			SetActorLocation(HomeAnchorLocation);
			SetChakraState(EChakraState::CeremonialSpin);
			UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Chakra successfully returned to divine hand."));
		}
		else
		{
			DirectionToHome.Normalize();
			FVector Step = DirectionToHome * FlightSpeed * 1.25f * DeltaTime;
			SetActorLocation(CurrentLoc + Step);
		}
	}
}

void ASudarshanChakraActor::SetChakraState(EChakraState NewState)
{
	if (CurrentState == NewState) return;

	CurrentState = NewState;
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Chakra transition to state %d"), (int32)NewState);

	if (CurrentState == EChakraState::MahaStorm)
	{
		if (EnergyAuraComponent) EnergyAuraComponent->Activate(true);
		if (BladeTrailsComponent) BladeTrailsComponent->Activate(true);
	}
}

void ASudarshanChakraActor::LaunchAtTarget(const FVector& TargetLocation)
{
	HomeAnchorLocation = GetActorLocation();
	FlightTargetLocation = TargetLocation;
	TotalTraveledDistance = 0.0f;

	FVector LaunchDirection = (FlightTargetLocation - HomeAnchorLocation);
	LaunchDirection.Z = 0.0f; // Planar supersonic cut
	LaunchDirection.Normalize();

	FlightVelocity = LaunchDirection * FlightSpeed;
	SetChakraState(EChakraState::Flying);

	if (ActionAudioComponent)
	{
		ActionAudioComponent->Play();
	}

	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Chakra supersonic launch executed. Velocity: %s"), *FlightVelocity.ToString());
}

void ASudarshanChakraActor::RecallToOwner()
{
	SetChakraState(EChakraState::Returning);
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Chakra magnetic recall initiated."));
}

void ASudarshanChakraActor::TriggerCharge()
{
	SetChakraState(EChakraState::ThrowPreparation);
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Chakra charging divine cosmic energy."));
}
