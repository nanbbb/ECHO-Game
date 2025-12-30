// Copyright Epic Games, Inc. All Rights Reserved.

#include "ECHOPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ECHO.h"
#include "ECHOCameraManager.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "System/ECHOAudioClockSubsystem.h"
#include "Widgets/Input/SVirtualJoystick.h"


AECHOPlayerController::AECHOPlayerController() {
  PlayerCameraManagerClass = AECHOCameraManager::StaticClass();

  // Default judgment windows (can be overridden in Blueprint)
  PerfectWindowMs = 30.0f;
  GreatWindowMs = 60.0f;
  GoodWindowMs = 100.0f;
}

void AECHOPlayerController::BeginPlay() {
  Super::BeginPlay();

  // only spawn touch controls on local player controllers
  if (ShouldUseTouchControls() && IsLocalPlayerController()) {
    MobileControlsWidget =
        CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

    if (MobileControlsWidget) {
      MobileControlsWidget->AddToPlayerScreen(0);
    } else {
      UE_LOG(LogECHO, Error, TEXT("Could not spawn mobile controls widget."));
    }
  }
}

void AECHOPlayerController::SetupInputComponent() {
  Super::SetupInputComponent();

  if (IsLocalPlayerController()) {
    // Add Input Mapping Context
    if (UEnhancedInputLocalPlayerSubsystem *Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                GetLocalPlayer())) {
      for (UInputMappingContext *CurrentContext : DefaultMappingContexts) {
        Subsystem->AddMappingContext(CurrentContext, 0);
      }

      if (!ShouldUseTouchControls()) {
        for (UInputMappingContext *CurrentContext :
             MobileExcludedMappingContexts) {
          Subsystem->AddMappingContext(CurrentContext, 0);
        }
      }
    }

    // Bind Rhythm Action
    if (UEnhancedInputComponent *EnhancedInputComponent =
            Cast<UEnhancedInputComponent>(InputComponent)) {
      if (RhythmAction) {
        EnhancedInputComponent->BindAction(RhythmAction, ETriggerEvent::Started,
                                           this,
                                           &AECHOPlayerController::OnRhythmHit);
      }
    }
  }
}

bool AECHOPlayerController::ShouldUseTouchControls() const {
  return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

EJudgmentRating AECHOPlayerController::CalculateRating(float TimeDiffMs) const {
  const float AbsDiff = FMath::Abs(TimeDiffMs);

  if (AbsDiff <= PerfectWindowMs) {
    return EJudgmentRating::Perfect;
  } else if (AbsDiff <= GreatWindowMs) {
    return EJudgmentRating::Great;
  } else if (AbsDiff <= GoodWindowMs) {
    return EJudgmentRating::Good;
  }

  return EJudgmentRating::Miss;
}

void AECHOPlayerController::OnRhythmHit() {
  UGameInstance *GI = GetGameInstance();
  if (!GI)
    return;

  UECHOAudioClockSubsystem *AudioClock =
      GI->GetSubsystem<UECHOAudioClockSubsystem>();
  if (!AudioClock)
    return;

  float TimeDiff = 0.0f;
  // Use the widest window (GoodWindowMs) to check if input is even close
  bool bWithinWindow = AudioClock->GetBeatJudgment(GoodWindowMs, TimeDiff);

  if (bWithinWindow) {
    EJudgmentRating Rating = CalculateRating(TimeDiff);

    // Visual feedback colors based on rating
    FColor FeedbackColor;
    FString RatingText;

    switch (Rating) {
    case EJudgmentRating::Perfect:
      FeedbackColor = FColor::Yellow;
      RatingText = TEXT("PERFECT");
      break;
    case EJudgmentRating::Great:
      FeedbackColor = FColor::White;
      RatingText = TEXT("GREAT");
      break;
    case EJudgmentRating::Good:
      FeedbackColor = FColor::Cyan;
      RatingText = TEXT("GOOD");
      break;
    default:
      FeedbackColor = FColor::Red;
      RatingText = TEXT("MISS");
      break;
    }

    // Debug display
    GEngine->AddOnScreenDebugMessage(
        -1, 1.5f, FeedbackColor,
        FString::Printf(TEXT("%s! (%.1fms)"), *RatingText, TimeDiff));

    // Broadcast judgment event
    if (Rating != EJudgmentRating::Miss) {
      OnJudgmentReceived.Broadcast(Rating, TimeDiff);
    } else {
      OnMiss.Broadcast();
    }
  } else {
    // Complete miss - not even close to a beat
    GEngine->AddOnScreenDebugMessage(
        -1, 1.5f, FColor::Red,
        FString::Printf(TEXT("MISS! (%.1fms)"), TimeDiff));
    OnMiss.Broadcast();
  }
}
