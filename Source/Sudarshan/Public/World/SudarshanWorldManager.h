#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "World/PortalActor.h"
#include "SudarshanWorldManager.generated.h"

UCLASS()
class SUDARSHAN_API ASudarshanWorldManager : public AActor
{
	GENERATED_BODY()

public:
	ASudarshanWorldManager();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|World")
	EWorldRealm ActiveRealm;

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|World")
	void SwitchRealm(EWorldRealm NewRealm);

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|World")
	void SpawnWorldEnemies(EWorldRealm Realm);
};
