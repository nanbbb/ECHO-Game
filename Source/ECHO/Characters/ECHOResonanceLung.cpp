// Copyright ECHO Team. All Rights Reserved.

#include "ECHOResonanceLung.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/GameInstance.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "InputTriggers.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "System/ECHOAudioClockSubsystem.h"

AECHOResonanceLung::AECHOResonanceLung() {
  PrimaryActorTick.bCanEverTick = true;

  // 创建共鸣肺组件
  ResonanceLungMesh =
      CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResonanceLung"));
  ResonanceLungMesh->SetupAttachment(GetCapsuleComponent());
  // 设置到头部高度，并稍微靠前
  ResonanceLungMesh->SetRelativeLocation(FVector(20.0f, 0.0f, 60.0f));

  // 禁用物理和碰撞，因为它只是一个视觉表示
  ResonanceLungMesh->SetCollisionProfileName(TEXT("NoCollision"));
  ResonanceLungMesh->SetCastShadow(false);

  // --- 修复摄像机挂载 ---
  // 将摄像机挂载到小球上，但向后偏移，使小球在视野内
  if (UCameraComponent *Camera = GetFirstPersonCameraComponent()) {
    Camera->SetupAttachment(ResonanceLungMesh);
    // 向后移动 80 单位
    Camera->SetRelativeLocation(FVector(-80.0f, 0.0f, 0.0f));
    Camera->bUsePawnControlRotation = true;
  }

  // 创建音频组件
  MusicComponent =
      CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
  MusicComponent->SetupAttachment(RootComponent);
  MusicComponent->bAutoActivate = false;

  // 调整后的脉冲参数
  PulseDecaySpeed = 6.0f;
  MaxPulseScale = 0.4f;
  PulseIntensity = 0.0f;
  BackgroundMusic = nullptr;
}

void AECHOResonanceLung::BeginPlay() {
  Super::BeginPlay();

  // --- 1. 核心状态检查 ---
  AController *CurrController = GetController();
  UE_LOG(LogTemp, Warning,
         TEXT("[DEBUG] ECHOResonanceLung: BeginPlay. Controller: %s, "
              "AutoPossess: %d"),
         CurrController ? *CurrController->GetName() : TEXT("NONE"),
         (int32)AutoPossessPlayer.GetValue());

  // --- 强力层级修复 ---
  // 通过 BeginPlay 强制重新挂载，绕过构造函数在 BP 序列化中的潜在问题
  if (ResonanceLungMesh) {
    ResonanceLungMesh->AttachToComponent(
        GetCapsuleComponent(),
        FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    // 高度略低于视线，中心稍稍靠前
    ResonanceLungMesh->SetRelativeLocation(FVector(30.0f, 0.0f, 40.0f));
    ResonanceLungMesh->SetRelativeScale3D(
        FVector(0.3f, 0.3f, 0.3f)); // 稍微缩小一点防止挡住视野
    UE_LOG(
        LogTemp, Warning,
        TEXT("[DEBUG] ECHOResonanceLung: Forced Mesh attachment to Capsule"));
  }

  if (UCameraComponent *Camera = GetFirstPersonCameraComponent()) {
    Camera->AttachToComponent(
        GetCapsuleComponent(),
        FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    // 相机位于胶囊体中心偏上
    Camera->SetRelativeLocation(FVector(-50.0f, 0.0f, 60.0f));
    Camera->bUsePawnControlRotation = true;
    UE_LOG(
        LogTemp, Warning,
        TEXT("[DEBUG] ECHOResonanceLung: Forced Camera attachment to Capsule"));
  }

  // --- 视觉清理 ---
  // 隐藏默认的 FP Arms 网格体，消除骨骼插槽警告
  if (USkeletalMeshComponent *FPMesh = GetFirstPersonMesh()) {
    FPMesh->SetVisibility(false, true);
    FPMesh->SetHiddenInGame(true);
  }
  if (USkeletalMeshComponent *BaseMesh = GetMesh()) {
    BaseMesh->SetVisibility(false, true);
    BaseMesh->SetHiddenInGame(true);
  }

  // --- 1.1 注册输入映射上下文 ---
  if (APlayerController *PC = Cast<APlayerController>(CurrController)) {
    if (UEnhancedInputLocalPlayerSubsystem *Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                PC->GetLocalPlayer())) {
      if (DefaultMappingContext) {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
        UE_LOG(LogTemp, Warning,
               TEXT("[INPUT] ECHOResonanceLung: Registered "
                    "DefaultMappingContext: %s"),
               *DefaultMappingContext->GetName());
      } else {
        UE_LOG(LogTemp, Error,
               TEXT("[INPUT] ECHOResonanceLung: DefaultMappingContext is NULL "
                    "in BeginPlay!"));
      }
    }
  }

  if (ResonanceLungMesh) {
    // 如果没有网格体，加载默认的球体
    if (!ResonanceLungMesh->GetStaticMesh()) {
      UStaticMesh *SphereMesh = LoadObject<UStaticMesh>(
          nullptr, TEXT("/Engine/BasicShapes/Sphere.Sphere"));
      if (SphereMesh) {
        ResonanceLungMesh->SetStaticMesh(SphereMesh);
        UE_LOG(LogTemp, Log,
               TEXT("ECHOResonanceLung: Loaded default sphere mesh"));
      }
    }

    // 设置材质
    UMaterialInterface *LungMat = LoadObject<UMaterialInterface>(
        nullptr, TEXT("/Game/ECHO/Materials/M_Lung_Core.M_Lung_Core"));
    if (LungMat) {
      LungDynamicMaterial = UMaterialInstanceDynamic::Create(LungMat, this);
      ResonanceLungMesh->SetMaterial(0, LungDynamicMaterial);
      UE_LOG(LogTemp, Log, TEXT("ECHOResonanceLung: Created dynamic material"));
    }

    // 设置位置和缩放
    ResonanceLungMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
    DefaultLungScale = ResonanceLungMesh->GetRelativeScale3D();
  }

  // --- 2. 订阅系统事件 ---
  UGameInstance *GI = GetGameInstance();
  if (GI) {
    AudioClockSubsystem = GI->GetSubsystem<UECHOAudioClockSubsystem>();
  }

  if (AudioClockSubsystem) {
    // 订阅 Quantization 事件
    AudioClockSubsystem->OnQuantizationEvent.AddDynamic(
        this, &AECHOResonanceLung::OnResonancePulseInternal);
    UE_LOG(LogTemp, Log,
           TEXT("ECHOResonanceLung: Subscribed to OnQuantizationEvent"));

    // 播放背景音乐
    USoundBase *MusicToPlay = BackgroundMusic;
    if (!MusicToPlay) {
      MusicToPlay = LoadObject<USoundWave>(
          nullptr, TEXT("/Game/ECHO/Audio/1_Drums.1_Drums"));
    }

    if (MusicToPlay) {
      AudioClockSubsystem->PlayMusic(MusicToPlay, 140.0f);
      UE_LOG(LogTemp, Warning,
             TEXT("ECHOResonanceLung: Music playback triggered (140 BPM)"));
    }
  }
}

void AECHOResonanceLung::SetupPlayerInputComponent(
    UInputComponent *PlayerInputComponent) {
  UE_LOG(LogTemp, Warning,
         TEXT("[DEBUG] ECHOResonanceLung: SetupPlayerInputComponent called!"));

  Super::SetupPlayerInputComponent(PlayerInputComponent);

  if (UEnhancedInputComponent *EnhancedInputComponent =
          Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
    if (BreatheAction) {
      EnhancedInputComponent->BindAction(BreatheAction, ETriggerEvent::Started,
                                         this,
                                         &AECHOResonanceLung::BreatheInput);
      UE_LOG(
          LogTemp, Warning,
          TEXT("[DEBUG] ECHOResonanceLung: BreatheAction successfully bound!"));
    } else {
      UE_LOG(LogTemp, Error,
             TEXT("[DEBUG] ECHOResonanceLung: BreatheAction is NULL in "
                  "SetupPlayerInputComponent!"));
    }
  } else {
    UE_LOG(LogTemp, Error,
           TEXT("[DEBUG] ECHOResonanceLung: PlayerInputComponent is NOT "
                "EnhancedInputComponent"));
  }
}

void AECHOResonanceLung::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
  UpdateLungVisuals(DeltaTime);
}

void AECHOResonanceLung::OnResonancePulse_Implementation(int32 Bar,
                                                         int32 Beat) {
  PulseIntensity = 1.0f;
}

void AECHOResonanceLung::OnResonancePulseInternal(
    EQuartzCommandQuantization QuantizationType) {
  if (QuantizationType == EQuartzCommandQuantization::Beat) {
    // 检测上一拍是否按过键
    if (LastBeatIndex > 0 && !bPressedThisBeat) {
      // 未按键 = MISS
      UE_LOG(LogTemp, Error, TEXT("MISS! (No input on beat %d)"),
             LastBeatIndex);
      if (AudioClockSubsystem) {
        AudioClockSubsystem->ModifyLifeForce(-0.03f); // -3% 生命力
      }
    }

    // 重置本拍状态
    bPressedThisBeat = false;
    LastBeatIndex++;

    // 视觉脉冲
    PulseIntensity = 1.0f;
  }
}

void AECHOResonanceLung::BreatheInput() {
  UE_LOG(LogTemp, Warning,
         TEXT("[INPUT] ECHOResonanceLung: Breathe Input Detected!"));

  // 标记本拍已按键
  bPressedThisBeat = true;

  if (!AudioClockSubsystem) {
    UGameInstance *GI = GetGameInstance();
    if (GI) {
      AudioClockSubsystem = GI->GetSubsystem<UECHOAudioClockSubsystem>();
    }
  }

  if (AudioClockSubsystem) {
    float Distance = AudioClockSubsystem->GetBeatOffset();

    // 多级判定系统
    if (Distance < PerfectWindowSec) {
      // PERFECT!
      UE_LOG(LogTemp, Warning, TEXT(">>> PERFECT BREATH! (Offset: %f) <<<"),
             Distance);
      PulseIntensity = 2.0f;
      AudioClockSubsystem->ModifyLifeForce(0.08f); // +8% 生命力
      TriggerPerfectFeedback();
    } else if (Distance < GoodWindowSec) {
      // GOOD
      UE_LOG(LogTemp, Log, TEXT(">> Good Breath (Offset: %f) <<"), Distance);
      PulseIntensity = 1.5f;
      AudioClockSubsystem->ModifyLifeForce(0.03f); // +3% 生命力
    } else {
      // MISS
      UE_LOG(LogTemp, Error, TEXT("MISS! (Offset: %f - too far from beat)"),
             Distance);
      AudioClockSubsystem->ModifyLifeForce(-0.02f); // -2% 生命力
    }
  }
}

void AECHOResonanceLung::UpdateLungVisuals(float DeltaTime) {
  if (!ResonanceLungMesh)
    return;

  // 脉冲衰减
  PulseIntensity =
      FMath::FInterpTo(PulseIntensity, 0.0f, DeltaTime, PulseDecaySpeed);

  // 计算新缩放
  float ScaleFactor = 1.0f + (PulseIntensity * MaxPulseScale);
  ResonanceLungMesh->SetRelativeScale3D(DefaultLungScale * ScaleFactor);

  // 更新材质参数
  if (LungDynamicMaterial) {
    LungDynamicMaterial->SetScalarParameterValue(FName("PulseIntensity"),
                                                 PulseIntensity);
  }
}

void AECHOResonanceLung::TriggerPerfectFeedback() {
  // 1. 触发复苏脉冲
  if (AudioClockSubsystem) {
    AudioClockSubsystem->TriggerRevivalPulse();
  }

  // 2. 屏幕闪光效果 - 通过摄像机后处理实现
  if (UCameraComponent *Camera = GetFirstPersonCameraComponent()) {
    // 临时增加曝光补偿来模拟闪光
    Camera->PostProcessSettings.bOverride_AutoExposureBias = true;
    Camera->PostProcessSettings.AutoExposureBias = 2.0f;

    // 0.1秒后恢复
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        [Camera]() {
          if (Camera) {
            Camera->PostProcessSettings.AutoExposureBias = 0.0f;
          }
        },
        0.1f, false);
  }

  UE_LOG(LogTemp, Log, TEXT("[VFX] Perfect feedback triggered!"));
}
