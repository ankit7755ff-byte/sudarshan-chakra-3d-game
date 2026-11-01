#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SudarshanGameModeBase.generated.h"

UCLASS()
class SUDARSHAN_API ASudarshanGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASudarshanGameModeBase();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sudarshan|Rules")
	float MaxMatchDurationSeconds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|State")
	int32 TotalAsurasDefeated;
};
