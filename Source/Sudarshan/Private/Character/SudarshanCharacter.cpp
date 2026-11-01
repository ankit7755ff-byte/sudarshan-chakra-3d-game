#include "Character/SudarshanCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Combat/SudarshanCombatComponent.h"
#include "SudarshanChakraActor.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Sudarshan.h"

ASudarshanCharacter::ASudarshanCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Capsule setup
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Character movement setup
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Camera Boom (Pull toward player on collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 450.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.f, 60.f, 40.f); // Over-the-shoulder Vedic combat view

	// Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Combat Component
	CombatComponent = CreateDefaultSubobject<USudarshanCombatComponent>(TEXT("CombatComponent"));

	// Socket Name
	ChakraFingerSocketName = TEXT("ChakraFingerSocket_R");

	// Locomotion tuning
	WalkSpeed = 600.f;
	SprintSpeed = 1100.f;
	DashSpeed = 2600.f;
	DashDuration = 0.22f;
	DashCooldown = 1.0f;

	// Stamina & Health
	MaxStamina = 100.f;
	CurrentStamina = 100.f;
	StaminaDrainRate = 22.f;
	StaminaRecoveryRate = 18.f;

	MaxHealth = 200.f;
	CurrentHealth = 200.f;

	bIsSprinting = false;
	bIsDashing = false;
	DashTimer = 0.f;
	LastDashTime = -10.f;
	LocomotionState = ELocomotionState::Walking;
}

void ASudarshanCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Enhanced Input Subsystem setup
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: ASudarshanCharacter spawned into divine realm."));
}

void ASudarshanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateStamina(DeltaTime);
	UpdateDash(DeltaTime);
}

void ASudarshanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASudarshanCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASudarshanCharacter::Look);

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ASudarshanCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASudarshanCharacter::StopSprint);

		// Divine Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &ASudarshanCharacter::DivineDash);
	}
}

void ASudarshanCharacter::Move(const FInputActionValue& Value)
{
	if (bIsDashing) return;

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASudarshanCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASudarshanCharacter::StartSprint()
{
	if (CurrentStamina > 10.f && !bIsDashing)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		LocomotionState = ELocomotionState::Sprinting;
	}
}

void ASudarshanCharacter::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	if (LocomotionState == ELocomotionState::Sprinting)
	{
		LocomotionState = ELocomotionState::Walking;
	}
}

void ASudarshanCharacter::DivineDash()
{
	float CurrentTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
	if (CurrentTime - LastDashTime < DashCooldown || CurrentStamina < 20.f || bIsDashing)
	{
		return;
	}

	FVector Forward = GetLastMovementInputVector();
	if (Forward.IsNearlyZero())
	{
		Forward = GetActorForwardVector();
	}

	DashDirection = Forward.GetSafeNormal();
	bIsDashing = true;
	DashTimer = DashDuration;
	LastDashTime = CurrentTime;

	CurrentStamina = FMath::Max(0.f, CurrentStamina - 20.f);
	LocomotionState = ELocomotionState::Dashing;

	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Divine Dash executed. Direction: %s"), *DashDirection.ToString());
}

void ASudarshanCharacter::UpdateStamina(float DeltaTime)
{
	if (bIsSprinting)
	{
		CurrentStamina = FMath::Max(0.f, CurrentStamina - StaminaDrainRate * DeltaTime);
		if (CurrentStamina <= 0.f)
		{
			StopSprint();
		}
	}
	else
	{
		CurrentStamina = FMath::Min(MaxStamina, CurrentStamina + StaminaRecoveryRate * DeltaTime);
	}
}

void ASudarshanCharacter::UpdateDash(float DeltaTime)
{
	if (bIsDashing)
	{
		DashTimer -= DeltaTime;
		GetCharacterMovement()->Velocity = DashDirection * DashSpeed;

		if (DashTimer <= 0.f)
		{
			bIsDashing = false;
			GetCharacterMovement()->MaxWalkSpeed = bIsSprinting ? SprintSpeed : WalkSpeed;
			LocomotionState = bIsSprinting ? ELocomotionState::Sprinting : ELocomotionState::Walking;
		}
	}
}

void ASudarshanCharacter::ApplyDivineDamage(float DamageAmount)
{
	CurrentHealth = FMath::Max(0.f, CurrentHealth - DamageAmount);
	UE_LOG(LogSudarshan, Warning, TEXT("SUDARSHAN: Player took %f damage. Current Health: %f"), DamageAmount, CurrentHealth);
}

void ASudarshanCharacter::RestoreHealth(float HealAmount)
{
	CurrentHealth = FMath::Min(MaxHealth, CurrentHealth + HealAmount);
}
