// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ECHOPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
class UUserWidget;

/**
 * Judgment Rating Enum - 判定等级
 */
UENUM(BlueprintType)
enum class EJudgmentRating : uint8 {
  Perfect UMETA(DisplayName = "Perfect"),
  Great UMETA(DisplayName = "Great"),
  Good UMETA(DisplayName = "Good"),
  Miss UMETA(DisplayName = "Miss")
};

// Delegate for judgment results
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnJudgmentReceived,
                                             EJudgmentRating, Rating, float,
                                             TimeDiffMs);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMiss);

/**
 *  ECHO Player Controller
 *  Handles rhythm input and judgment logic.
 */
UCLASS(abstract, config = "Game")
class ECHO_API AECHOPlayerController : public APlayerController {
  GENERATED_BODY()

public:
  /** Constructor */
  AECHOPlayerController();

protected:
  /** Input Mapping Contexts */
  UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
  TArray<UInputMappingContext *> DefaultMappingContexts;

  /** Input Mapping Contexts */
  UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
  TArray<UInputMappingContext *> MobileExcludedMappingContexts;

  /** Rhythm Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|ECHO")
  UInputAction *RhythmAction;

  // ========== Judgment Windows (ms) ==========

  /** Perfect Window (±30ms) */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Judgment")
  float PerfectWindowMs = 30.0f;

  /** Great Window (±60ms) */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Judgment")
  float GreatWindowMs = 60.0f;

  /** Good Window (±100ms) */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Judgment")
  float GoodWindowMs = 100.0f;

  /** Mobile controls widget to spawn */
  UPROPERTY(EditAnywhere, Category = "Input|Touch Controls")
  TSubclassOf<UUserWidget> MobileControlsWidgetClass;

  /** Pointer to the mobile controls widget */
  UPROPERTY()
  TObjectPtr<UUserWidget> MobileControlsWidget;

  /** If true, the player will use UMG touch controls even if not playing on
   * mobile platforms */
  UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
  bool bForceTouchControls = false;

  /** Gameplay initialization */
  virtual void BeginPlay() override;

  /** Input mapping context setup */
  virtual void SetupInputComponent() override;

  /** Returns true if the player should use UMG touch controls */
  bool ShouldUseTouchControls() const;

  /** Handler for Rhythm Input */
  void OnRhythmHit();

  /** Calculate judgment rating based on time difference */
  EJudgmentRating CalculateRating(float TimeDiffMs) const;

public:
  // ========== Events ==========

  /** Broadcast when a judgment is received (not Miss) */
  UPROPERTY(BlueprintAssignable, Category = "ECHO|Events")
  FOnJudgmentReceived OnJudgmentReceived;

  /** Broadcast when the player misses */
  UPROPERTY(BlueprintAssignable, Category = "ECHO|Events")
  FOnMiss OnMiss;
};
