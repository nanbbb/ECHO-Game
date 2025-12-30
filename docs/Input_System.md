# 输入系统设计 (Input System Design)

**版本**: v1.0
**日期**: 2025-12-31
**适用**: UE5 Enhanced Input System

---

## 1. 设计原则

ECHO 的输入系统强调**时机精准**和**沉浸体验**。为了保持沉浸感，我们简化键位，强调音乐节奏的时机判定。

### 1.1 延迟最小化
- 输入延迟目标：< 15ms
- 使用独立的输入线程避免与渲染线程竞争
- 所有输入时间戳使用 `AudioRenderTime` 而非 `DeltaTime`

---

## 2. 输入映射 (Input Mapping)

### 2.1 PC 键位布局

| 动作名称 | 键位 | 用途 |
|---------|------|------|
| `IA_RhythmHit_Left` | S, Left Arrow | 左侧节拍点击 |
| `IA_RhythmHit_Down` | D, Down Arrow | 下侧节拍点击 |
| `IA_RhythmHit_Up` | K, Up Arrow | 上侧节拍点击 |
| `IA_RhythmHit_Right` | L, Right Arrow | 右侧节拍点击 |
| `IA_RhythmHit_Any` | Space, Mouse L/R | 单键模式/简化模式 |
| `IA_Pause` | Escape | 暂停菜单 |

### 2.2 手柄映射 (DualSense/Xbox)

| 动作名称 | PS5 | Xbox | 用途 |
|---------|-----|------|------|
| `IA_RhythmHit_Left` | □ | X | 左侧节拍 |
| `IA_RhythmHit_Down` | × | A | 下侧节拍 |
| `IA_RhythmHit_Up` | △ | Y | 上侧节拍 |
| `IA_RhythmHit_Right` | ○ | B | 右侧节拍 |
| `IA_RhythmHit_Any` | L2/R2 | LT/RT | 简化模式 |
| `IA_Pause` | Options | Menu | 暂停 |

---

## 3. 判定系统 (Judgment System)

### 3.1 判定窗口

以节拍点为中心，判定窗口如下：

| 等级 | 窗口 (ms) | 分数倍率 | 视觉反馈 |
|------|:---------:|:--------:|---------|
| **Perfect** | ±30ms | 1.0x | 金色光环 + 爆炸粒子 |
| **Great** | ±60ms | 0.8x | 白色光环 |
| **Good** | ±100ms | 0.5x | 灰色光环 |
| **Miss** | >100ms | 0x | 腐朽效果 + 音频失真 |

### 3.2 延迟校准 (Latency Calibration)

```cpp
// ECHOPlayerController.h
UPROPERTY(EditDefaultsOnly, Category = "Calibration")
float AudioLatencyMs = 0.0f;  // 音频延迟补偿

UPROPERTY(EditDefaultsOnly, Category = "Calibration")
float VisualLatencyMs = 0.0f; // 视觉延迟补偿
```

**校准流程**:
1. 播放节拍声音，屏幕闪烁
2. 玩家按键匹配声音
3. 计算平均偏移作为 `AudioLatencyMs`
4. 视觉同步时，增加 `VisualLatencyMs` 到判定计算

---

## 4. C++ 实现

### 4.1 核心类

#### `AECHOPlayerController`

```cpp
// 节拍输入处理
void AECHOPlayerController::OnRhythmHit()
{
    // 1. 获取当前输入时间（校准后）
    double InputTime = GetWorld()->GetTimeSeconds() - (LatencyOffsetMs / 1000.0);
    
    // 2. 查询判定结果
    float TimeDiff;
    bool bOnBeat = AudioClock->GetBeatJudgment(JudgmentWindowMs, TimeDiff);
    
    // 3. 广播结果
    if (bOnBeat)
    {
        EJudgmentRating Rating = CalculateRating(TimeDiff);
        OnJudgmentReceived.Broadcast(Rating, TimeDiff);
    }
    else
    {
        OnMiss.Broadcast();
    }
}
```

### 4.2 Enhanced Input 配置

**输入动作 (`IA_RhythmHit`)**:
- Value Type: `Digital (Bool)`
- Trigger: `Pressed` (仅响应按下，不响应释放)

**输入上下文 (`IMC_Default`)**:
```cpp
// 绑定示例
void AECHOPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EIC->BindAction(IA_RhythmHit, ETriggerEvent::Started, this, &AECHOPlayerController::OnRhythmHit);
    }
}
```

---

## 5. 触觉反馈 (Haptic Feedback)

### 5.1 DualSense 特性

| 事件 | 触觉效果 | 自适应扳机 |
|------|---------|-----------|
| 节拍预警 | 轻微脉冲 | - |
| Perfect | 强烈冲击波 | - |
| Hold 开始 | 持续振动 | R2 阻力增加 |
| Hold 保持 | 渐强振动 | 阻力维持 |
| Miss | 不规则抖动 | 阻力突然消失 |

### 5.2 实现方式

```cpp
// 使用 UHapticFeedbackEffect_Curve
void AECHOPlayerController::PlayHapticFeedback(EJudgmentRating Rating)
{
    UHapticFeedbackEffect_Curve* Haptic = nullptr;
    
    switch (Rating)
    {
    case EJudgmentRating::Perfect:
        Haptic = PerfectHaptic;
        break;
    case EJudgmentRating::Miss:
        Haptic = MissHaptic;
        break;
    }
    
    if (Haptic)
    {
        GetLocalPlayer()->GetSubsystem<UPlayerMappedInputSubsystem>()
            ->PlayHapticEffect(Haptic, EControllerHand::Right);
    }
}
```

---

## 6. 无障碍选项 (Accessibility)

| 选项 | 描述 | 默认值 |
|------|------|:------:|
| **一键模式** | 所有节奏输入简化为任意键 | 关 |
| **加宽判定窗口** | 将 Perfect 窗口扩大到 ±60ms | 关 |
| **视觉辅助** | 节拍点高亮为明黄色 | 关 |
| **振动强度** | 0% - 100% | 100% |

---

*最后更新: 2025-12-31*
