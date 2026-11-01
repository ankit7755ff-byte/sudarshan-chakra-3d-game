#include "AI/AsuraBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sudarshan.h"

AAsuraBaseCharacter::AAsuraBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(45.0f, 95.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 420.0f;

	AsuraType = EAsuraType::KaliyaSerpent;
	AIState = EAsuraAIState::Patrolling;

	MaxHealth = 150.0f;
	CurrentHealth = 150.0f;
	AttackDamage = 18.0f;
	AttackRange = 160.0f;
	AttackCooldown = 1.6f;
	SightRadius = 1800.0f;
	bCanSpitVenom = true;
	LastAttackTime = -10.0f;
}

void AAsuraBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Asura spawned (Type %d, HP %f)"), (int32)AsuraType, MaxHealth);
}

void AAsuraBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AAsuraBaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (AIState == EAsuraAIState::Defeated) return 0.0f;

	CurrentHealth = FMath::Max(0.0f, CurrentHealth - DamageAmount);
	AIState = EAsuraAIState::Staggered;

	UE_LOG(LogSudarshan, Warning, TEXT("SUDARSHAN: Asura took %f blade damage! HP remaining: %f"), DamageAmount, CurrentHealth);

	if (CurrentHealth <= 0.0f)
	{
		OnDefeated();
	}
	else
	{
		// Reset stagger after brief delay
		FTimerHandle StaggerTimer;
		GetWorld()->GetTimerManager().SetTimer(StaggerTimer, [this]() {
			if (AIState != EAsuraAIState::Defeated) AIState = EAsuraAIState::Chasing;
		}, 0.35f, false);
	}

	return DamageAmount;
}

void AAsuraBaseCharacter::PerformAttack(AActor* TargetActor)
{
	float CurrentTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	if (CurrentTime - LastAttackTime < AttackCooldown || !TargetActor) return;

	LastAttackTime = CurrentTime;
	AIState = EAsuraAIState::Attacking;

	UGameplayStatics::ApplyDamage(TargetActor, AttackDamage, GetController(), this, nullptr);
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Asura struck player for %f damage!"), AttackDamage);
}

void AAsuraBaseCharacter::SpitVenom(const FVector& TargetDirection)
{
	if (!bCanSpitVenom) return;
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Asura spat toxic venom towards %s"), *TargetDirection.ToString());
}

void AAsuraBaseCharacter::OnDefeated()
{
	AIState = EAsuraAIState::Defeated;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->StopMovementImmediately();

	DissolveIntoSparks();
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Asura slain by Sudarshan Chakra! Dissolving."));

	SetLifeSpan(1.2f);
}

void AAsuraBaseCharacter::DissolveIntoSparks()
{
	// Trigger particle dissolve and drop divine energy orbs
}
