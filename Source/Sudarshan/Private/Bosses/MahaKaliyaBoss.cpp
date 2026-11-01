#include "Bosses/MahaKaliyaBoss.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sudarshan.h"

AMahaKaliyaBoss::AMahaKaliyaBoss()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(120.0f, 280.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	GetCharacterMovement()->MaxWalkSpeed = 520.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	BossTitle = TEXT("॥ महाकालिया नाग संहार ॥");
	BossPhase = EBossCombatPhase::PhaseOne_Standard;

	MaxHealth = 2500.0f;
	CurrentHealth = 2500.0f;
	ToxicSpitDamage = 35.0f;
	TailSweepDamage = 60.0f;
	EnrageThresholdPercent = 0.5f;

	bHasEnraged = false;
	AttackTimer = 0.0f;
}

void AMahaKaliyaBoss::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	UE_LOG(LogSudarshan, Warning, TEXT("SUDARSHAN BOSS SPAWNED: %s (HP: %f)"), *BossTitle, MaxHealth);
}

void AMahaKaliyaBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AttackTimer += DeltaTime;

	// Periodic special attacks
	if (AttackTimer >= (bHasEnraged ? 3.5f : 6.0f))
	{
		AttackTimer = 0.0f;
		if (bHasEnraged) UnleashPoisonNova();
		else ExecuteTailSweep();
	}
}

float AMahaKaliyaBoss::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (BossPhase == EBossCombatPhase::DefeatedCinematic) return 0.0f;

	CurrentHealth = FMath::Max(0.0f, CurrentHealth - DamageAmount);
	UE_LOG(LogSudarshan, Warning, TEXT("SUDARSHAN: Maha-Kaliya took %f damage! Remaining HP: %f / %f"), DamageAmount, CurrentHealth, MaxHealth);

	if (!bHasEnraged && (CurrentHealth / MaxHealth) <= EnrageThresholdPercent)
	{
		TriggerEnragePhase();
	}

	if (CurrentHealth <= 0.0f)
	{
		BossPhase = EBossCombatPhase::DefeatedCinematic;
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCharacterMovement()->StopMovementImmediately();
		UE_LOG(LogSudarshan, Warning, TEXT("SUDARSHAN: MAHA-KALIYA DEFEATED! Divine victory achieved."));
		SetLifeSpan(3.0f);
	}

	return DamageAmount;
}

void AMahaKaliyaBoss::TriggerEnragePhase()
{
	bHasEnraged = true;
	BossPhase = EBossCombatPhase::PhaseTwo_Enraged;
	GetCharacterMovement()->MaxWalkSpeed = 750.0f;
	UE_LOG(LogSudarshan, Error, TEXT("SUDARSHAN: MAHA-KALIYA HAS ENRAGED! Toxic Nova unleashed!"));
	UnleashPoisonNova();
}

void AMahaKaliyaBoss::UnleashPoisonNova()
{
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Maha-Kaliya Poison Nova 360 burst!"));
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (AActor* Target : OverlappingActors)
	{
		UGameplayStatics::ApplyDamage(Target, ToxicSpitDamage * 1.5f, GetController(), this, nullptr);
	}
}

void AMahaKaliyaBoss::ExecuteTailSweep()
{
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Maha-Kaliya Tail Sweep attack!"));
}
