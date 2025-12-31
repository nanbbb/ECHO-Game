// Copyright ECHO Team. All Rights Reserved.

#pragma once

#include "Components/AudioComponent.h"
#include "CoreMinimal.h"
#include "ECHOCharacter.h"
#include "InputMappingContext.h"
#include "Sound/QuartzQuantizationUtilities.h"
#include "Sound/SoundWave.h"

// 必须保持在最后以通过 UHT 检查
#include "ECHOResonanceLung.generated.h"

/**
 * AECHOResonanceLung
 *
 * 核心主角类：共鸣肺。
 * 使用 Quartz 时钟实现随音乐节拍呼吸（脉冲）的视觉效果。
 */
UCLASS()
class ECHO_API AECHOResonanceLung : public AECHOCharacter {
  GENERATED_BODY()

public:
  AECHOResonanceLung();

protected:
  virtual void BeginPlay() override;
  virtual void Tick(float DeltaTime) override;
  virtual void SetupPlayerInputComponent(
      class UInputComponent *PlayerInputComponent) override;

  /** 处理呼吸脉冲 */
  UFUNCTION(BlueprintNativeEvent, Category = "ECHO|Resonance")
  void OnResonancePulse(int32 Bar, int32 Beat);

  /** 呼吸输入动作回调 */
  UFUNCTION(BlueprintCallable, Category = "ECHO|Resonance")
  void BreatheInput();

  /** 修改共鸣肺的视觉缩放/亮度 */
  void UpdateLungVisuals(float DeltaTime);

  /** Perfect 判定时触发视觉反馈 */
  void TriggerPerfectFeedback();

  /** Quartz 节拍回调 */
  UFUNCTION()
  void OnResonancePulseInternal(EQuartzCommandQuantization QuantizationType);

protected:
  /** 默认输入映射上下文 */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ECHO|Input")
  class UInputMappingContext *DefaultMappingContext;

  /** 呼吸输入动作 (Enhanced Input) */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ECHO|Input")
  class UInputAction *BreatheAction;
  /** 共鸣肺的网格体 */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  UStaticMeshComponent *ResonanceLungMesh;

  /** 脉冲强度 */
  UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "ECHO|Resonance")
  float PulseIntensity = 0.0f;

  /** 脉冲衰减速度 */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Resonance")
  float PulseDecaySpeed = 6.0f;

  /** 脉冲最大缩放增量 */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Resonance")
  float MaxPulseScale = 0.4f;

  /** Perfect 判定窗口 (秒) */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Judgment")
  float PerfectWindowSec = 0.08f; // 80ms

  /** Good 判定窗口 (秒) */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECHO|Judgment")
  float GoodWindowSec = 0.15f; // 150ms

  /** 背景音乐资产 */
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ECHO|Audio")
  USoundWave *BackgroundMusic;

  /** 音频组件 */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  UAudioComponent *MusicComponent;

private:
  /** 缓存初始缩放 */
  FVector DefaultLungScale;

  /** 动态材质实例 */
  UPROPERTY()
  UMaterialInstanceDynamic *LungDynamicMaterial;

  /** 缓存音频时钟子系统引用 */
  UPROPERTY()
  class UECHOAudioClockSubsystem *AudioClockSubsystem;

  /** 节拍跟踪 - 本拍是否已按键 */
  bool bPressedThisBeat = false;

  /** 上一次节拍索引 */
  int32 LastBeatIndex = 0;
};
