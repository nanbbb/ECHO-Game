#pragma once

#include "Containers/Ticker.h"
#include "CoreMinimal.h"
#include "Sound/QuartzQuantizationUtilities.h"
#include "Subsystems/GameInstanceSubsystem.h"

// --- Unreal Generated Header MUST be last ---
#include "ECHOAudioClockSubsystem.generated.h"

class UMaterialParameterCollection;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantizationEvent,
                                            EQuartzCommandQuantization,
                                            QuantizationType);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLifeForceChanged, float,
                                            NewLifeForce);

/**
 * Subsystem to handle Audio Clock, Rhythm events, and Revival System.
 * Core system for ECHO's music-driven gameplay.
 */
UCLASS()
class ECHO_API UECHOAudioClockSubsystem : public UGameInstanceSubsystem {
  GENERATED_BODY()

public:
  // Begin USubsystem
  virtual void Initialize(FSubsystemCollectionBase &Collection) override;
  virtual void Deinitialize() override;
  // End USubsystem

  // ========== Audio Playback ==========

  UFUNCTION(BlueprintCallable, Category = "ECHO|Audio")
  void PlayMusic(USoundBase *MusicSound, float BPM = 120.0f);

  UFUNCTION(BlueprintCallable, Category = "ECHO|Audio")
  void StopMusic();

  // ========== Judgment ==========

  /** Returns true if the current time is within the judgment window of a beat
   */
  UFUNCTION(BlueprintCallable, Category = "ECHO|Input")
  bool GetBeatJudgment(float JudgmentWindowMs, float &OutTimeDifference);

  // ========== Calibration ==========

  UFUNCTION(BlueprintCallable, Category = "ECHO|Calibration")
  void SetLatencyOffset(float InLatencyMs);

  UFUNCTION(BlueprintCallable, Category = "ECHO|Calibration")
  float GetLatencyOffset() const { return LatencyOffsetMs; }

  // ========== Revival System ==========

  /** Set the Global MPC for controlling the Revival Shader */
  UFUNCTION(BlueprintCallable, Category = "ECHO|Visuals")
  void SetRevivalMPC(UMaterialParameterCollection *InMPC);

  /** Update the Revival Radius (e.g. called from Tick or Timeline) */
  UFUNCTION(BlueprintCallable, Category = "ECHO|Visuals")
  void UpdateRevivalRadius(float NewRadius, FVector CenterLocation);

  /** Trigger a pulse (called on beat) */
  UFUNCTION(BlueprintCallable, Category = "ECHO|Visuals")
  void TriggerRevivalPulse();

  // ========== Life Force System ==========

  /** Get current life force (0-1) */
  UFUNCTION(BlueprintCallable, Category = "ECHO|Gameplay")
  float GetLifeForce() const { return LifeForce; }

  /** Set life force directly */
  UFUNCTION(BlueprintCallable, Category = "ECHO|Gameplay")
  void SetLifeForce(float NewLifeForce);

  /** Modify life force (positive = heal, negative = damage) */
  UFUNCTION(BlueprintCallable, Category = "ECHO|Gameplay")
  void ModifyLifeForce(float Delta);

  // ========== Events ==========

  UPROPERTY(BlueprintAssignable, Category = "ECHO|Audio")
  FOnQuantizationEvent OnQuantizationEvent;

  UPROPERTY(BlueprintAssignable, Category = "ECHO|Gameplay")
  FOnLifeForceChanged OnLifeForceChanged;

  // ========== Configuration ==========

  /** Maximum pulse radius when beat is hit */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Visuals")
  float MaxPulseRadius = 1500.0f;

  /** Decay speed for pulse radius */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Visuals")
  float PulseDecaySpeed = 5.0f;

  /** Interpolation speed for smooth radius changes */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Visuals")
  float RadiusInterpSpeed = 10.0f;

protected:
  // Signature for Metronome Delegate
  UFUNCTION()
  void HandleQuartzMetronome(FName InClockName,
                             EQuartzCommandQuantization QuantizationType,
                             int32 NumBars, int32 Beat, float BeatFraction);

private:
  UPROPERTY()
  UAudioComponent *AudioComponent;

  FName ClockName;
  float CurrentBPM;

  // Time tracking for judgment
  double LastBeatWorldTime;
  double NextBeatWorldTime;
  double BeatDuration;

  // Calibration
  float LatencyOffsetMs;

  // Revival Params
  UPROPERTY()
  UMaterialParameterCollection *RevivalMPC;

  const FName ParamName_Radius = FName("RevivalRadius");
  const FName ParamName_Center = FName("RevivalCenter");

  // Pulse & Decay
  FTSTicker::FDelegateHandle TickHandle;
  float CurrentRadius = 0.0f;
  float TargetRadius = 0.0f;
  bool Tick(float DeltaTime);

  // Life Force (0-1, 0 = stone, 1 = full life)
  float LifeForce = 1.0f;
};