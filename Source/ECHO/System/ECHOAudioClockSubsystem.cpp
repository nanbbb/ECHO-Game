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

  // Auto-load Revival MPC
  static const FString MPCPath =
      TEXT("/Game/ECHO/Materials/MPC_Revival.MPC_Revival");
  RevivalMPC = Cast<UMaterialParameterCollection>(StaticLoadObject(
      UMaterialParameterCollection::StaticClass(), nullptr, *MPCPath));
  if (RevivalMPC) {
    UE_LOG(LogTemp, Log, TEXT("ECHOAudioClockSubsystem: Loaded MPC_Revival"));
  } else {
    UE_LOG(LogTemp, Warning,
           TEXT("ECHOAudioClockSubsystem: Failed to load MPC_Revival"));
  }

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

  // 创建音频组件并直接播放
  AudioComponent = UGameplayStatics::SpawnSound2D(World, MusicSound, 1.0f, 1.0f,
                                                  0.0f, nullptr, true, true);

  if (AudioComponent) {
    // 启用循环播放，防止音乐结束后节拍系统停止
    AudioComponent->bIsUISound = false;
    AudioComponent->bAllowSpatialization = false;
    AudioComponent->SetIntParameter(FName("Loop"), 1);

    // 如果是 SoundWave，直接设置循环
    if (USoundWave *Wave = Cast<USoundWave>(MusicSound)) {
      Wave->bLooping = true;
    }

    UE_LOG(LogTemp, Log,
           TEXT("ECHOAudioClockSubsystem: Music started playing (LOOPING)"));

    FQuartzClockSettings ClockSettings;
    ClockSettings.TimeSignature.NumBeats = 4;
    ClockSettings.TimeSignature.BeatType =
        EQuartzTimeSignatureQuantization::QuarterNote;
    ClockSettings.bIgnoreLevelChange = true;

    UQuartzSubsystem *Quartz = UQuartzSubsystem::Get(World);
    if (Quartz) {
      // Create clock and get handle - 存储为成员变量防止 GC
      QuartzClockHandle =
          Quartz->CreateNewClock(World, ClockName, ClockSettings);

      if (QuartzClockHandle) {
        // 设置 BPM - 使用 Tick 避免等待
        FQuartzQuantizationBoundary QuantizationBoundary;
        QuantizationBoundary.Quantization = EQuartzCommandQuantization::Tick;

        QuartzClockHandle->SetBeatsPerMinute(World, QuantizationBoundary,
                                             FOnQuartzCommandEventBP(),
                                             QuartzClockHandle, CurrentBPM);

        // 启动时钟
        QuartzClockHandle->StartClock(World, QuartzClockHandle);

        FOnQuartzMetronomeEventBP MetronomeDelegate;
        MetronomeDelegate.BindUFunction(this, FName("HandleQuartzMetronome"));

        // Subscribe to beat events
        QuartzClockHandle->SubscribeToQuantizationEvent(
            World, EQuartzCommandQuantization::Beat, MetronomeDelegate,
            QuartzClockHandle);

        LastBeatWorldTime = World->GetTimeSeconds();
        NextBeatWorldTime = LastBeatWorldTime + BeatDuration;

        UE_LOG(LogTemp, Log,
               TEXT("ECHOAudioClockSubsystem: Quartz clock started at %f BPM"),
               CurrentBPM);
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

  UE_LOG(LogTemp, Log, TEXT("HandleQuartzMetronome called! Clock=%s, Beat=%d"),
         *InClockName.ToString(), Beat);

  if (InClockName == ClockName) {
    UWorld *World = GetWorld();
    if (World && QuantizationType == EQuartzCommandQuantization::Beat) {
      double CurrentTime = World->GetTimeSeconds();
      LastBeatWorldTime = CurrentTime;
      NextBeatWorldTime = CurrentTime + BeatDuration;

      UE_LOG(LogTemp, Log,
             TEXT("ECHOAudioClock: BEAT! Broadcasting pulse event"));
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

float UECHOAudioClockSubsystem::GetBeatOffset() {
  UWorld *World = GetWorld();
  if (!World)
    return 1.0f;

  double CurrentTime = World->GetTimeSeconds();
  double CorrectedTime = CurrentTime - (LatencyOffsetMs / 1000.0f);

  double DistToLast = FMath::Abs(CorrectedTime - LastBeatWorldTime);
  double DistToNext = FMath::Abs(CorrectedTime - NextBeatWorldTime);

  float ClosestDist = (float)FMath::Min(DistToLast, DistToNext);

  // 打印详细的判定调试信息
  UE_LOG(LogTemp, Verbose,
         TEXT("ECHOAudioClock: Judgment Request - Offset: %f, LastBeat: %f, "
              "NextBeat: %f"),
         ClosestDist, LastBeatWorldTime, NextBeatWorldTime);

  return ClosestDist;
}

bool UECHOAudioClockSubsystem::GetBeatJudgment(float JudgmentWindowMs,
                                               float &OutTimeDifference) {
  float Distance = GetBeatOffset();
  OutTimeDifference = Distance * 1000.0f;
  return Distance <= (JudgmentWindowMs / 1000.0f);
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
  // 1. 生命力随时间流逝缓慢衰减 (每秒 1.5%)
  ModifyLifeForce(-0.015f * DeltaTime);

  // 2. 脉冲半径随时间衰减
  TargetRadius =
      FMath::FInterpTo(TargetRadius, 0.0f, DeltaTime, PulseDecaySpeed);

  // 3. 平滑更新当前半径
  CurrentRadius = FMath::FInterpTo(CurrentRadius, TargetRadius, DeltaTime,
                                   RadiusInterpSpeed);

  // 4. 计算当前生命力对复苏半径的影响
  float VitalityEffect = FMath::Clamp(LifeForce, 0.05f, 1.0f);
  float ActualRadius = CurrentRadius * VitalityEffect;

  // 5. 更新材质全局属性
  UWorld *World = GetWorld();
  if (World && RevivalMPC) {
    APlayerController *PC = World->GetFirstPlayerController();
    FVector PlayerLocation = FVector::ZeroVector;
    if (PC && PC->GetPawn()) {
      PlayerLocation = PC->GetPawn()->GetActorLocation();
    }

    // 同步复苏半径和中心点
    UpdateRevivalRadius(ActualRadius, PlayerLocation);

    // 同步生命力到 MPC (用于环境灰度插值)
    if (UMaterialParameterCollectionInstance *MPCInstance =
            World->GetParameterCollectionInstance(RevivalMPC)) {
      MPCInstance->SetScalarParameterValue(ParamName_LifeForce, LifeForce);
    }
  }

  // 6. 死亡检测
  if (LifeForce <= 0.05f) {
    // 触发死亡状态 - 将在下一步实现完整的死亡画面
    UE_LOG(LogTemp, Error, TEXT("[DEATH] LifeForce depleted! Game Over."));
  }

  return true;
}