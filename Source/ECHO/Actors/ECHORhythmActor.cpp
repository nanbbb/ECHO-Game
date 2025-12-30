#include "ECHORhythmActor.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "System/ECHOAudioClockSubsystem.h"

AECHORhythmActor::AECHORhythmActor() {
  PrimaryActorTick.bCanEverTick = true;

  RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

  PointLightComp =
      CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
  PointLightComp->SetupAttachment(RootComponent);
  PointLightComp->SetIntensity(0.0f);

  // Properties have default values in header
  CurrentIntensity = 0.0f;
}

void AECHORhythmActor::BeginPlay() {
  Super::BeginPlay();

  UGameInstance *GI = GetGameInstance();
  if (GI) {
    UECHOAudioClockSubsystem *AudioClock =
        GI->GetSubsystem<UECHOAudioClockSubsystem>();
    if (AudioClock) {
      AudioClock->OnQuantizationEvent.AddDynamic(
          this, &AECHORhythmActor::HandleQuantizationEvent);
    }
  }
}

void AECHORhythmActor::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

  // Simple linear decay for the pulse effect
  CurrentIntensity =
      FMath::FInterpTo(CurrentIntensity, BaseIntensity, DeltaTime, DecaySpeed);
  PointLightComp->SetIntensity(CurrentIntensity);
}

void AECHORhythmActor::HandleQuantizationEvent(
    EQuartzCommandQuantization QuantizationType) {
  // Only respond to the configured quantization type
  if (QuantizationType == ResponseType) {
    OnRhythmEvent(QuantizationType);
  }
}

void AECHORhythmActor::TriggerPulse() { CurrentIntensity = PeakIntensity; }

void AECHORhythmActor::OnRhythmEvent_Implementation(
    EQuartzCommandQuantization QuantizationType) {
  // Default behavior: Trigger visual pulse
  TriggerPulse();
}
