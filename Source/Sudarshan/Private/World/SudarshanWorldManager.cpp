#include "World/SudarshanWorldManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sudarshan.h"

ASudarshanWorldManager::ASudarshanWorldManager()
{
	PrimaryActorTick.bCanEverTick = false;
	ActiveRealm = EWorldRealm::EarthRealm;
}

void ASudarshanWorldManager::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: World Manager initialized in Earth Realm."));
	SpawnWorldEnemies(ActiveRealm);
}

void ASudarshanWorldManager::SwitchRealm(EWorldRealm NewRealm)
{
	ActiveRealm = NewRealm;
	FString RealmName = (NewRealm == EWorldRealm::EarthRealm) ? TEXT("Earth Universe (Kurukshetra)") : TEXT("Divine Celestial Universe (Vaikuntha)");
	UE_LOG(LogSudarshan, Warning, TEXT("SUDARSHAN: Active Realm switched to %s"), *RealmName);
	SpawnWorldEnemies(NewRealm);
}

void ASudarshanWorldManager::SpawnWorldEnemies(EWorldRealm Realm)
{
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Spawning environmental adversaries for realm %d"), (int32)Realm);
}
