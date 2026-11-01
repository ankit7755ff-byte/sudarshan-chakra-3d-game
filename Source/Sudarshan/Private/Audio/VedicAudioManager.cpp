#include "Audio/VedicAudioManager.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sudarshan.h"

AVedicAudioManager::AVedicAudioManager()
{
	PrimaryActorTick.bCanEverTick = false;

	AmbientAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbientAudio"));
	RootComponent = AmbientAudioComponent;
	AmbientAudioComponent->bAutoActivate = true;

	CombatAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("CombatAudio"));
	CombatAudioComponent->SetupAttachment(RootComponent);
	CombatAudioComponent->bAutoActivate = false;

	CurrentThemeState = EAudioThemeState::PeacefulFlute;
	MasterVolume = 1.0f;
}

void AVedicAudioManager::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Vedic Audio Manager active. Theme: %d"), (int32)CurrentThemeState);
}

void AVedicAudioManager::TransitionToTheme(EAudioThemeState NewTheme, float FadeDuration)
{
	if (CurrentThemeState == NewTheme) return;

	CurrentThemeState = NewTheme;
	UE_LOG(LogSudarshan, Log, TEXT("SUDARSHAN: Audio transition to Theme %d with fade %f"), (int32)NewTheme, FadeDuration);

	if (NewTheme == EAudioThemeState::BossTandav || NewTheme == EAudioThemeState::CombatDamru)
	{
		if (AmbientAudioComponent) AmbientAudioComponent->FadeOut(FadeDuration, 0.2f);
		if (CombatAudioComponent) CombatAudioComponent->FadeIn(FadeDuration, MasterVolume);
	}
	else
	{
		if (CombatAudioComponent) CombatAudioComponent->FadeOut(FadeDuration, 0.0f);
		if (AmbientAudioComponent) AmbientAudioComponent->FadeIn(FadeDuration, MasterVolume);
	}
}

void AVedicAudioManager::PlaySpatialOneShot(USoundBase* Sound, const FVector& Location, float Volume)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, Location, Volume * MasterVolume);
	}
}
