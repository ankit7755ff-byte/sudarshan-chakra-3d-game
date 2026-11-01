#include "Combat/SudarshanCombatComponent.h"
#include "Character/SudarshanCharacter.h"
#include "SudarshanChakraActor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Sudarshan.h"

USudarshanCombatComponent::USudarshanCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CombatMode = ECombatMode::FingerHover;
	MaxAimDistance = 7500.0f;
	BaseBladeDamage = 250.0f;
	MaxChainTargets = 4;
	bHasAimTarget = false;
	CurrentAimHitLocation = FVector::ZeroVector;
}

void USudarshanCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ASudarshanCharacter>(GetOwner());
}

void USudarshanCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CombatMode == ECombatMode::Aiming || CombatMode == ECombatMode::FingerHover)
	{
		UpdateAimTrace();
	}
}

void USudarshanCombatComponent::UpdateAimTrace()
{
	if (!OwnerCharacter || !OwnerCharacter->FollowCamera) return;

	FVector CameraLocation = OwnerCharacter->FollowCamera->GetComponentLocation();
	FVector CameraForward = OwnerCharacter->FollowCamera->GetForwardVector();
	FVector TraceEnd = CameraLocation + (CameraForward * MaxAimDistance);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerCharacter);
	if (ActiveChakra) QueryParams.AddIgnoredActor(ActiveChakra);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd, ECC_Visibility, QueryParams);

	if (bHit)
	{
		CurrentAimHitLocation = HitResult.ImpactPoint;
		bHasAimTarget = true;
	}
	else
	{
		CurrentAimHitLocation = TraceEnd;
		bHasAimTarget = false;
	}
}

void USudarshanCombatComponent::StartAiming()
{
	CombatMode = ECombatMode::Aiming;
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Precision Aiming stance active."));
}

void USudarshanCombatComponent::StopAiming()
{
	if (CombatMode == ECombatMode::Aiming)
	{
		CombatMode = ECombatMode::FingerHover;
	}
}

void USudarshanCombatComponent::ThrowChakra()
{
	if (!OwnerCharacter) return;

	if (!ActiveChakra)
	{
		ActiveChakra = OwnerCharacter->EquippedChakra;
	}

	if (ActiveChakra)
	{
		CombatMode = ECombatMode::Thrown;
		ActiveChakra->LaunchAtTarget(CurrentAimHitLocation);
		UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Chakra launched towards target: %s"), *CurrentAimHitLocation.ToString());
	}
}

void USudarshanCombatComponent::RecallChakra()
{
	if (ActiveChakra)
	{
		ActiveChakra->RecallToOwner();
		CombatMode = ECombatMode::FingerHover;
		UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Chakra recalled to player hand."));
	}
}

void USudarshanCombatComponent::TriggerMahaStormDefense()
{
	CombatMode = ECombatMode::MahaStorm;
	if (ActiveChakra)
	{
		ActiveChakra->SetChakraState(EChakraState::MahaStorm);
	}
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: 108 Blades Maha-Storm Defense barrier active."));
}

void USudarshanCombatComponent::PerformMeleeSpin()
{
	// 360-degree close-quarters sweep
	FVector SweepOrigin = OwnerCharacter ? OwnerCharacter->GetActorLocation() : FVector::ZeroVector;
	TArray<FHitResult> SweepHits;
	FCollisionShape SphereShape = FCollisionShape::MakeSphere(320.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerCharacter);

	bool bHit = GetWorld()->SweepMultiByChannel(SweepHits, SweepOrigin, SweepOrigin, FQuat::Identity, ECC_WorldDynamic, SphereShape, QueryParams);

	if (bHit)
	{
		for (const FHitResult& Hit : SweepHits)
		{
			OnChakraImpact(Hit.GetActor(), Hit.ImpactPoint, Hit.ImpactNormal);
		}
	}
}

void USudarshanCombatComponent::ExecuteChainRicochet(const TArray<AActor*>& TargetEnemies)
{
	CombatMode = ECombatMode::ChainSlice;
	int32 TargetsHit = 0;

	for (AActor* Target : TargetEnemies)
	{
		if (TargetsHit >= MaxChainTargets) break;
		if (Target && Target->IsValidLowLevel())
		{
			OnChakraImpact(Target, Target->GetActorLocation(), FVector::UpVector);
			TargetsHit++;
		}
	}
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Chain Ricochet sliced %d targets."), TargetsHit);
}

void USudarshanCombatComponent::OnChakraImpact(AActor* HitActor, const FVector& ImpactPoint, const FVector& ImpactNormal)
{
	if (!HitActor) return;

	UGameplayStatics::ApplyPointDamage(HitActor, BaseBladeDamage, ImpactNormal, FHitResult(HitActor, nullptr, ImpactPoint, ImpactNormal), OwnerCharacter ? OwnerCharacter->GetController() : nullptr, OwnerCharacter, nullptr);

	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Katili Blade Sliced %s at %s"), *HitActor->GetName(), *ImpactPoint.ToString());
}
