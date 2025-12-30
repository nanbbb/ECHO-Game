# 代码参考手册 (Code Reference)

**版本**: v1.0
**日期**: 2025-12-31
**适用**: 程序开发

---

## 1. 类层次结构

```
UObject
├── UGameInstanceSubsystem
│   └── UECHOAudioClockSubsystem        # 音频时钟子系统
│
├── USaveGame
│   └── UECHOSaveGame                   # 存档数据 (计划中)
│
AActor
├── AGameModeBase
│   └── AECHOGameMode                   # 游戏模式
│
├── ACharacter
│   └── AECHOCharacter                  # 玩家角色
│
├── APlayerController
│   └── AECHOPlayerController           # 玩家控制器
│
├── APlayerCameraManager
│   └── AECHOCameraManager              # 摄像机管理
│
└── AActor
    └── AECHORhythmActor                # 节奏响应 Actor
```

---

## 2. 核心类详解

### 2.1 UECHOAudioClockSubsystem

**路径**: `Source/ECHO/System/ECHOAudioClockSubsystem.h`

Quartz 音频时钟子系统，负责音频同步和复苏材质参数更新。

#### 公开方法

| 方法 | 参数 | 返回 | 描述 |
|------|------|------|------|
| `PlayMusic` | `USoundBase*, float BPM` | void | 播放音乐并启动 Quartz 时钟 |
| `StopMusic` | - | void | 停止音乐和时钟 |
| `GetBeatJudgment` | `float WindowMs, float& OutDiff` | bool | 检查当前时间是否在节拍窗口内 |
| `SetLatencyOffset` | `float LatencyMs` | void | 设置延迟补偿 |
| `SetRevivalMPC` | `UMaterialParameterCollection*` | void | 设置复苏 MPC 引用 |
| `UpdateRevivalRadius` | `float Radius, FVector Center` | void | 更新 MPC 参数 |

#### 事件委托

```cpp
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantizationEvent, EQuartzCommandQuantization, Type);

UPROPERTY(BlueprintAssignable)
FOnQuantizationEvent OnQuantizationEvent;
```

#### 使用示例

```cpp
// 在 GameMode 中初始化
void AECHOGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    UECHOAudioClockSubsystem* AudioClock = 
        GetGameInstance()->GetSubsystem<UECHOAudioClockSubsystem>();
    
    if (AudioClock && MPC_Revival)
    {
        AudioClock->SetRevivalMPC(MPC_Revival);
        AudioClock->PlayMusic(BackgroundMusic, 120.0f);
    }
}
```

---

### 2.2 AECHORhythmActor

**路径**: `Source/ECHO/Actors/ECHORhythmActor.h`

可响应节奏事件的 Actor，用于场景中的节拍灯光/物体。

#### 属性

| 属性 | 类型 | 默认值 | 描述 |
|------|------|:------:|------|
| `PointLightComp` | UPointLightComponent* | - | 点光源组件 |
| `BaseIntensity` | float | 5000.0 | 基础光照强度 |
| `PulseIntensity` | float | 20000.0 | 脉冲时光照强度 |
| `PulseDuration` | float | 0.1 | 脉冲持续时间(秒) |
| `ResponseType` | EQuartzCommandQuantization | Beat | 响应的节拍类型 |

#### 蓝图可调用

```cpp
UFUNCTION(BlueprintCallable, Category = "Rhythm")
void TriggerPulse();

UFUNCTION(BlueprintImplementableEvent, Category = "Rhythm")
void OnRhythmEvent(EQuartzCommandQuantization Type);
```

---

### 2.3 AECHOPlayerController

**路径**: `Source/ECHO/ECHOPlayerController.h`

处理玩家输入和节拍判定。

#### 属性

| 属性 | 类型 | 默认值 | 描述 |
|------|------|:------:|------|
| `JudgmentWindowMs` | float | 100.0 | 判定窗口(毫秒) |
| `LatencyOffsetMs` | float | 0.0 | 延迟补偿(毫秒) |

#### 事件委托

```cpp
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnJudgmentReceived, 
    EJudgmentRating, Rating, float, TimeDiffMs);

UPROPERTY(BlueprintAssignable)
FOnJudgmentReceived OnJudgmentReceived;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMiss);

UPROPERTY(BlueprintAssignable)
FOnMiss OnMiss;
```

---

### 2.4 AECHOCharacter

**路径**: `Source/ECHO/ECHOCharacter.h`

第一人称玩家角色。

#### 组件

| 组件 | 类型 | 描述 |
|------|------|------|
| `CameraComponent` | UCameraComponent | 第一人称摄像机 |
| `MovementComponent` | UCharacterMovementComponent | 移动组件 |

---

## 3. 枚举类型

### 3.1 EJudgmentRating

```cpp
UENUM(BlueprintType)
enum class EJudgmentRating : uint8
{
    Perfect UMETA(DisplayName = "Perfect"),
    Great   UMETA(DisplayName = "Great"),
    Good    UMETA(DisplayName = "Good"),
    Miss    UMETA(DisplayName = "Miss")
};
```

---

## 4. 模块依赖

**ECHO.Build.cs** 中的模块依赖：

```csharp
PublicDependencyModuleNames.AddRange(new string[] { 
    "Core", 
    "CoreUObject", 
    "Engine", 
    "InputCore",
    "EnhancedInput",
    "AudioMixer",
    "AudioExtensions"  // Quartz 支持
});
```

---

## 5. 命名规范

### 5.1 类名前缀

| 前缀 | 类型 | 示例 |
|------|------|------|
| `A` | Actor | `AECHORhythmActor` |
| `U` | UObject | `UECHOAudioClockSubsystem` |
| `F` | 结构体 | `FECHONoteData` |
| `E` | 枚举 | `EJudgmentRating` |
| `I` | 接口 | `IResettableInterface` |

### 5.2 文件组织

```
Source/ECHO/
├── ECHO.h                    # 模块头文件
├── ECHO.cpp                  # 模块实现
├── ECHO.Build.cs             # 构建配置
├── Actors/                   # Actor 类
├── System/                   # 子系统
├── Data/                     # 数据资产 (计划中)
└── Interfaces/               # 接口 (计划中)
```

---

## 6. 蓝图暴露规范

### 6.1 属性暴露

```cpp
// 可在编辑器和蓝图中访问
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rhythm")
float MyProperty;

// 仅蓝图可读
UPROPERTY(BlueprintReadOnly, Category = "Rhythm")
float ReadOnlyProperty;

// 仅在编辑器中可见
UPROPERTY(EditDefaultsOnly, Category = "Rhythm")
float EditorOnlyProperty;
```

### 6.2 函数暴露

```cpp
// 蓝图可调用
UFUNCTION(BlueprintCallable, Category = "Rhythm")
void DoSomething();

// 蓝图可实现
UFUNCTION(BlueprintImplementableEvent, Category = "Rhythm")
void OnEventTriggered();

// 蓝图可覆写
UFUNCTION(BlueprintNativeEvent, Category = "Rhythm")
void OnNativeEvent();
```

---

## 7. 调试宏

```cpp
// 日志输出
UE_LOG(LogECHO, Log, TEXT("Message: %s"), *Message);
UE_LOG(LogECHO, Warning, TEXT("Warning: %f"), Value);
UE_LOG(LogECHO, Error, TEXT("Error occurred!"));

// 屏幕调试
GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Debug"));

// 断言
check(Ptr != nullptr);
ensure(Value > 0);
```

---

*最后更新: 2025-12-31*
