#include "AI/AsuraAIController.h"
#include "AI/AsuraBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sudarshan.h"

AAsuraAIController::AAsuraAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	AcceptanceRadius = 150.0f;
	PlayerPawn = nullptr;
}

void AAsuraAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AAsuraAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateAIBehavior();
}

void AAsuraAIController::UpdateAIBehavior()
{
	AAsuraBaseCharacter* AsuraChar = Cast<AAsuraBaseCharacter>(GetPawn());
	if (!AsuraChar || AsuraChar->AIState == EAsuraAIState::Defeated) return;

	if (!PlayerPawn)
	{
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (!PlayerPawn) return;
	}

	float DistToPlayer = FVector::Dist(AsuraChar->GetActorLocation(), PlayerPawn->GetActorLocation());

	if (DistToPlayer <= AsuraChar->SightRadius)
	{
		if (DistToPlayer <= AsuraChar->AttackRange)
		{
			StopMovement();
			AsuraChar->PerformAttack(PlayerPawn);
		}
		else
		{
			AsuraChar->AIState = EAsuraAIState::Chasing;
			MoveToActor(PlayerPawn, AcceptanceRadius);
		}
	}
	else
	{
		AsuraChar->AIState = EAsuraAIState::Patrolling;
	}
}
