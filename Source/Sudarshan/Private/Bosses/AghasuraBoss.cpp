#include "Bosses/AghasuraBoss.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sudarshan.h"

AAghasuraBoss::AAghasuraBoss()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(180.0f, 320.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	GetCharacterMovement()->MaxWalkSpeed = 480.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	BossTitle = TEXT("॥ अघासुर दानव वध ॥");
	MaxHealth = 4000.0f;
	CurrentHealth = 4000.0f;
	EarthTremorDamage = 75.0f;
}

void AAghasuraBoss::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	UE_LOG(LogSudarshan, Warning, TEXT("SUDARSHAN BOSS SPAWNED: %s (HP: %f)"), *BossTitle, MaxHealth);
}

void AAghasuraBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AAghasuraBoss::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHealth = FMath::Max(0.0f, CurrentHealth - DamageAmount);
	UE_LOG(LogSudarshan, Warning, TEXT("SUDARSHAN: Aghasura took %f damage! Remaining HP: %f / %f"), DamageAmount, CurrentHealth, MaxHealth);

	if (CurrentHealth <= 0.0f)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCharacterMovement()->StopMovementImmediately();
		UE_LOG(LogSudarshan, Warning, TEXT("SUDARSHAN: AGHASURA VANQUISHED BY SUDARSHAN CHAKRA!"));
		SetLifeSpan(3.0f);
	}

	return DamageAmount;
}

void AAghasuraBoss::PerformCavernousCharge()
{
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Aghasura executes Cavernous Maw charge!"));
}
