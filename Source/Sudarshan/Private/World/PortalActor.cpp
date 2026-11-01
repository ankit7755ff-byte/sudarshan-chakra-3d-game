#include "World/PortalActor.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/Character.h"
#include "Sudarshan.h"

APortalActor::APortalActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	PortalTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalTrigger"));
	PortalTrigger->SetupAttachment(RootComponent);
	PortalTrigger->SetBoxExtent(FVector(80.0f, 220.0f, 320.0f));
	PortalTrigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	PortalVortexFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PortalVortex"));
	PortalVortexFX->SetupAttachment(RootComponent);

	PortalLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PortalLight"));
	PortalLight->SetupAttachment(RootComponent);
	PortalLight->SetLightColor(FLinearColor(0.2f, 0.8f, 1.0f));
	PortalLight->SetIntensity(6000.0f);
	PortalLight->SetAttenuationRadius(1200.0f);

	DestinationRealm = EWorldRealm::CelestialRealm;
	DestinationLocation = FVector(0.0f, 0.0f, 5000.0f);
}

void APortalActor::BeginPlay()
{
	Super::BeginPlay();
	PortalTrigger->OnComponentBeginOverlap.AddDynamic(this, &APortalActor::OnPortalOverlap);
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Sacred Portal active. Links to Realm %d"), (int32)DestinationRealm);
}

void APortalActor::OnPortalOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* PlayerChar = Cast<ACharacter>(OtherActor))
	{
		UE_LOG(LogSudarshan, Warning, TEXT("SUDARSHAN: Player stepped through sacred portal! Teleporting to %s"), *DestinationLocation.ToString());
		PlayerChar->TeleportTo(DestinationLocation, PlayerChar->GetActorRotation());
	}
}
