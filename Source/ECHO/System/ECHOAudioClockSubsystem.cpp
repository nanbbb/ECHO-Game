#include "ECHOAudioClockSubsystem.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "Quartz/QuartzSubsystem.h"
#include "Sound/QuartzQuantizationUtilities.h"
#include "Sound/SoundBase.h"

void UECHOAudioClockSubsystem::Initialize(
    FSubsystemCollectionBase &Collection) {
  Super::Initialize(Collection);
  ClockName = FName("ECHO_MainClock");
  CurrentBPM = 120.0f;
  LatencyOffsetMs = 0.0f;
  CurrentRadius = 0.0f;
  TargetRadius = 0.0f;

  // Register Ticker
  TickHandle = FTSTicker::GetCoreTicker().AddTicker(
      FTickerDelegate::CreateUObject(this, &UECHOAudioClockSubsystem::Tick));
}

void UECHOAudioClockSubsystem::Deinitialize() {
  if (TickHandle.IsValid()) {
    FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
  }
  Super::Deinitialize();
}

void UECHOAudioClockSubsystem::PlayMusic(USoundBase *MusicSound, float BPM) {
  if (!MusicSound)
    return;

  UWorld *World = GetWorld();
  if (!World)
    return;

  StopMusic();

  CurrentBPM = BPM > 0.0f ? BPM : 120.0f;
  BeatDuration = 60.0f / CurrentBPM;

  AudioComponent = UGameplayStatics::SpawnSound2D(World, MusicSound, 1.0f, 1.0f,
                                                  0.0f, nullptr, false, false);

  if (AudioComponent) {
    FQuartzClockSettings ClockSettings;
    ClockSettings.TimeSignature.NumBeats = 4;
    ClockSettings.TimeSignature.BeatType =
        EQuartzTimeSignatureQuantization::QuarterNote;
    ClockSettings.bIgnoreLevelChange = true;

    UQuartzSubsystem *Quartz = UQuartzSubsystem::Get(World);
    if (Quartz) {
      // Create clock and get handle
      UQuartzClockHandle *ClockHandle =
          Quartz->CreateNewClock(World, ClockName, ClockSettings);

      if (ClockHandle) {
        FQuartzQuantizationBoundary QuantizationBoundary;
        QuantizationBoundary.Quantization = EQuartzCommandQuantization::Bar;

        // Set BPM using the handle
        ClockHandle->SetBeatsPerMinute(World, QuantizationBoundary,
                                       FOnQuartzCommandEventBP(), ClockHandle,
                                       CurrentBPM);

        FOnQuartzMetronomeEventBP MetronomeDelegate;
        MetronomeDelegate.BindUFunction(this, FName("HandleQuartzMetronome"));

        // Subscribe using the handle
        ClockHandle->SubscribeToQuantizationEvent(
            World, EQuartzCommandQuantization::Bar, MetronomeDelegate,
            ClockHandle);
        ClockHandle->SubscribeToQuantizationEvent(
            World, EQuartzCommandQuantization::Beat, MetronomeDelegate,
            ClockHandle);
        ClockHandle->SubscribeToQuantizationEvent(
            World, EQuartzCommandQuantization::QuarterNote, MetronomeDelegate,
            ClockHandle);

        LastBeatWorldTime = World->GetTimeSeconds();
        NextBeatWorldTime = LastBeatWorldTime + BeatDuration;

        // PlayQuantized expects FOnQuartzCommandEventBP (2 params)
        AudioComponent->PlayQuantized(World, ClockHandle, QuantizationBoundary,
                                      FOnQuartzCommandEventBP());
      }
    }
  }
}

void UECHOAudioClockSubsystem::StopMusic() {
  if (AudioComponent) {
    AudioComponent->Stop();
    AudioComponent = nullptr;
  }

  UWorld *World = GetWorld();
  if (World) {
    UQuartzSubsystem *Quartz = UQuartzSubsystem::Get(World);
    if (Quartz && Quartz->DoesClockExist(World, ClockName)) {
      Quartz->DeleteClockByName(World, ClockName);
    }
  }
}

void UECHOAudioClockSubsystem::HandleQuartzMetronome(
    FName InClockName, EQuartzCommandQuantization QuantizationType,
    int32 NumBars, int32 Beat, float BeatFraction) {
  if (InClockName == ClockName) {
    UWorld *World = GetWorld();
    if (World && QuantizationType == EQuartzCommandQuantization::Beat) {
      double CurrentTime = World->GetTimeSeconds();
      LastBeatWorldTime = CurrentTime;
      NextBeatWorldTime = CurrentTime + BeatDuration;
    }

    OnQuantizationEvent.Broadcast(QuantizationType);

    // If beat, pulse!
    if (QuantizationType == EQuartzCommandQuantization::Beat) {
      TriggerRevivalPulse();
    }
  }
}

void UECHOAudioClockSubsystem::SetLatencyOffset(float InLatencyMs) {
  LatencyOffsetMs = InLatencyMs;
}

bool UECHOAudioClockSubsystem::GetBeatJudgment(float JudgmentWindowMs,
                                               float &OutTimeDifference) {
  UWorld *World = GetWorld();
  if (!World)
    return false;

  double CurrentTime = World->GetTimeSeconds();

  // Apply calibration
  double LatencySeconds = LatencyOffsetMs / 1000.0f;
  double CorrectedTime = CurrentTime - LatencySeconds;

  double DistToLast = FMath::Abs(CorrectedTime - LastBeatWorldTime);
  double DistToNext = FMath::Abs(CorrectedTime - NextBeatWorldTime);

  double ClosestDist = (DistToLast < DistToNext) ? DistToLast : DistToNext;
  double ClosestBeatTime =
      (DistToLast < DistToNext) ? LastBeatWorldTime : NextBeatWorldTime;

  OutTimeDifference = (CorrectedTime - ClosestBeatTime) * 1000.0f;

  double WindowSeconds = JudgmentWindowMs / 1000.0f;
  return ClosestDist <= WindowSeconds;
}

void UECHOAudioClockSubsystem::SetRevivalMPC(
    UMaterialParameterCollection *InMPC) {
  RevivalMPC = InMPC;
}

void UECHOAudioClockSubsystem::UpdateRevivalRadius(float NewRadius,
                                                   FVector CenterLocation) {
  if (!RevivalMPC)
    return;

  UWorld *World = GetWorld();
  if (!World)
    return;

  UMaterialParameterCollectionInstance *MPCInstance =
      World->GetParameterCollectionInstance(RevivalMPC);
  if (MPCInstance) {
    MPCInstance->SetScalarParameterValue(ParamName_Radius, NewRadius);
    MPCInstance->SetVectorParameterValue(ParamName_Center,
                                         FLinearColor(CenterLocation));
  }
}

void UECHOAudioClockSubsystem::TriggerRevivalPulse() {
  TargetRadius = MaxPulseRadius;
}

void UECHOAudioClockSubsystem::SetLifeForce(float NewLifeForce) {
  float OldLifeForce = LifeForce;
  LifeForce = FMath::Clamp(NewLifeForce, 0.0f, 1.0f);

  if (!FMath::IsNearlyEqual(OldLifeForce, LifeForce)) {
    OnLifeForceChanged.Broadcast(LifeForce);
  }
}

void UECHOAudioClockSubsystem::ModifyLifeForce(float Delta) {
  SetLifeForce(LifeForce + Delta);
}

bool UECHOAudioClockSubsystem::Tick(float DeltaTime) {
  // 1. Decay the pulse using configurable speed
  TargetRadius =
      FMath::FInterpTo(TargetRadius, 0.0f, DeltaTime, PulseDecaySpeed);

  // 2. Smoothly update CurrentRadius using configurable speed
  CurrentRadius = FMath::FInterpTo(CurrentRadius, TargetRadius, DeltaTime,
                                   RadiusInterpSpeed);

  // 3. Update MPC (Center is player location)
  UWorld *World = GetWorld();
  if (World && RevivalMPC) {
    APlayerController *PC = World->GetFirstPlayerController();
    if (PC && PC->GetPawn()) {
      UpdateRevivalRadius(CurrentRadius, PC->GetPawn()->GetActorLocation());
    } else {
      UpdateRevivalRadius(CurrentRadius, FVector::ZeroVector);
    }
  }

  return true;
}