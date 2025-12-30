#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/QuartzQuantizationUtilities.h"
#include "ECHORhythmActor.generated.h"

/**
 * Actor that responds to rhythm events.
 * Used for environmental objects that pulse, glow, or animate on beat.
 */
UCLASS()
class ECHO_API AECHORhythmActor : public AActor {
  GENERATED_BODY()

public:
  AECHORhythmActor();

  virtual void Tick(float DeltaTime) override;

protected:
  virtual void BeginPlay() override;

  /** Called when a quantization event occurs (beat, bar, etc.) */
  UFUNCTION(BlueprintNativeEvent, Category = "ECHO|Audio")
  void OnRhythmEvent(EQuartzCommandQuantization QuantizationType);

  UFUNCTION()
  void HandleQuantizationEvent(EQuartzCommandQuantization QuantizationType);

  /** Manually trigger a pulse effect */
  UFUNCTION(BlueprintCallable, Category = "ECHO|Visuals")
  void TriggerPulse();

public:
  /** Visual component for MVP (light) */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  class UPointLightComponent *PointLightComp;

  // ========== Configuration ==========

  /** Which quantization type this actor responds to */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Rhythm")
  EQuartzCommandQuantization ResponseType = EQuartzCommandQuantization::Beat;

  /** Base intensity when not pulsing */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Visuals")
  float BaseIntensity = 0.0f;

  /** Peak intensity on beat */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Visuals")
  float PeakIntensity = 5000.0f;

  /** Duration of pulse effect (seconds) */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Visuals")
  float PulseDuration = 0.2f;

  /** Decay speed for the light pulse */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Visuals")
  float DecaySpeed = 10.0f;

private:
  float CurrentIntensity;
};