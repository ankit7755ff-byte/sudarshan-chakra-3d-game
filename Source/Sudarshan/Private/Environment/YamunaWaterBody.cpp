#include "Environment/YamunaWaterBody.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Sudarshan.h"

AYamunaWaterBody::AYamunaWaterBody()
{
	PrimaryActorTick.bCanEverTick = true;

	WaterSurfaceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WaterSurfaceMesh"));
	RootComponent = WaterSurfaceMesh;
	WaterSurfaceMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	WaterSprayFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("WaterSprayFX"));
	WaterSprayFX->SetupAttachment(RootComponent);

	WaveSpeed = 1.4f;
	WaveAmplitude = 18.0f;
	bIsContaminatedByKaliya = false;
}

void AYamunaWaterBody::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Sacred Yamuna River biome initialized."));
}

void AYamunaWaterBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AYamunaWaterBody::TriggerPurificationWave(const FVector& ImpactCenter)
{
	bIsContaminatedByKaliya = false;
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Sudarshan Chakra purified Yamuna water at %s"), *ImpactCenter.ToString());
}

void AYamunaWaterBody::SetContaminationState(bool bContaminated)
{
	bIsContaminatedByKaliya = bContaminated;
	UE_LOG(LogSudarshan, Warning, TEXT("SUDARSHAN: Yamuna Water contamination state: %d"), bContaminated);
}
