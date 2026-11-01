#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AsuraAIController.generated.h"

UCLASS()
class SUDARSHAN_API AAsuraAIController : public AAIController
{
	GENERATED_BODY()

public:
	AAsuraAIController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|AI")
	float AcceptanceRadius;

private:
	APawn* PlayerPawn;
	void UpdateAIBehavior();
};
