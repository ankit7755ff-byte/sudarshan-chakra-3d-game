#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SudarshanCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class ASudarshanChakraActor;
class USudarshanCombatComponent;

UENUM(BlueprintType)
enum class ELocomotionState : uint8
{
	Walking     UMETA(DisplayName = "Walking"),
	Sprinting   UMETA(DisplayName = "Divine Sprint"),
	Dashing     UMETA(DisplayName = "Divine Dash"),
	Jumping     UMETA(DisplayName = "Airborne"),
	CombatStance UMETA(DisplayName = "Chakra Aim Stance")
};

UCLASS(config=Game)
class SUDARSHAN_API ASudarshanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASudarshanCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// --- CAMERA RIG ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Camera")
	UCameraComponent* FollowCamera;

	// --- COMBAT COMPONENT ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Combat")
	USudarshanCombatComponent* CombatComponent;

	// --- ATTACHED CHAKRA WEAPON ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Weapon")
	ASudarshanChakraActor* EquippedChakra;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sudarshan|Weapon")
	FName ChakraFingerSocketName;

	// --- LOCOMOTION ATTRIBUTES ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Locomotion")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Locomotion")
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Locomotion")
	float DashSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Locomotion")
	float DashDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Locomotion")
	float DashCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Locomotion")
	float MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Locomotion")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Locomotion")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Locomotion")
	float StaminaRecoveryRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Locomotion")
	ELocomotionState LocomotionState;

	// --- INPUT ACTIONS (Enhanced Input) ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sudarshan|Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sudarshan|Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sudarshan|Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sudarshan|Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sudarshan|Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sudarshan|Input")
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sudarshan|Input")
	UInputAction* ThrowChakraAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sudarshan|Input")
	UInputAction* RecallChakraAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sudarshan|Input")
	UInputAction* MahaStormAction;

	// --- LOCOMOTION FUNCTIONS ---
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprint();
	void StopSprint();
	void DivineDash();

	// --- HEALTH & DIVINE ENERGY ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sudarshan|Stats")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sudarshan|Stats")
	float CurrentHealth;

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Stats")
	void ApplyDivineDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Sudarshan|Stats")
	void RestoreHealth(float HealAmount);

	UFUNCTION(BlueprintPure, Category = "Sudarshan|Stats")
	float GetHealthPercent() const { return CurrentHealth / MaxHealth; }

	UFUNCTION(BlueprintPure, Category = "Sudarshan|Stats")
	float GetStaminaPercent() const { return CurrentStamina / MaxStamina; }

private:
	bool bIsSprinting;
	bool bIsDashing;
	float DashTimer;
	float LastDashTime;
	FVector DashDirection;

	void UpdateStamina(float DeltaTime);
	void UpdateDash(float DeltaTime);
};
