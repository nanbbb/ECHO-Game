# 材质系统设计 (Material System Design)

**版本**: v1.0
**日期**: 2025-12-31
**适用**: 技术美术、程序

---

## 1. 系统概述

ECHO 的材质系统核心是**"复苏效果 (Revival Effect)"**——场景中的物体随着玩家的节奏输入从石化状态逐渐恢复生机。这一效果通过全局 Material Parameter Collection (MPC) 驱动，确保所有材质同步响应。

---

## 2. 材质参数集 (MPC_Revival)

**路径**: `/Game/ECHO/Materials/MPC_Revival`

### 2.1 参数列表

| 参数名 | 类型 | 默认值 | 描述 |
|--------|------|:------:|------|
| `RevivalRadius` | Scalar | 0.0 | 复苏波半径（世界单位） |
| `RevivalCenter` | Vector | (0,0,0) | 复苏波中心位置 |

### 2.2 C++ 更新逻辑

```cpp
// ECHOAudioClockSubsystem.cpp
void UECHOAudioClockSubsystem::UpdateRevivalRadius(float NewRadius, FVector CenterLocation)
{
    if (!RevivalMPC) return;
    
    UWorld* World = GetWorld();
    if (!World) return;
    
    UMaterialParameterCollectionInstance* MPCInstance = 
        World->GetParameterCollectionInstance(RevivalMPC);
    
    if (MPCInstance)
    {
        MPCInstance->SetScalarParameterValue(FName("RevivalRadius"), NewRadius);
        MPCInstance->SetVectorParameterValue(FName("RevivalCenter"), 
            FLinearColor(CenterLocation));
    }
}
```

### 2.3 Tick 更新

```cpp
bool UECHOAudioClockSubsystem::Tick(float DeltaTime)
{
    // 1. 衰减脉冲目标
    TargetRadius = FMath::FInterpTo(TargetRadius, 0.0f, DeltaTime, 5.0f);
    
    // 2. 平滑插值当前半径
    CurrentRadius = FMath::FInterpTo(CurrentRadius, TargetRadius, DeltaTime, 10.0f);
    
    // 3. 更新 MPC
    if (RevivalMPC)
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        FVector Center = PC && PC->GetPawn() ? 
            PC->GetPawn()->GetActorLocation() : FVector::ZeroVector;
        UpdateRevivalRadius(CurrentRadius, Center);
    }
    
    return true;
}
```

---

## 3. 材质函数 (MF_RevivalLogic)

**路径**: `/Game/ECHO/Materials/MF_RevivalLogic`

### 3.1 逻辑图解

```
┌─────────────────┐     ┌─────────────────┐
│ WorldPosition   │────▶│   Distance      │
└─────────────────┘     │  (A - B)        │
                        └───────┬─────────┘
┌─────────────────┐             │
│ RevivalCenter   │─────────────┘
│ (MPC Vector)    │             ▼
└─────────────────┘     ┌─────────────────┐
                        │    Divide       │
┌─────────────────┐     │ (Dist / Radius) │
│ RevivalRadius   │────▶└───────┬─────────┘
│ (MPC Scalar)    │             ▼
└─────────────────┘     ┌─────────────────┐
                        │   Saturate      │──▶ Clamp [0,1]
                        └───────┬─────────┘
                                ▼
                        ┌─────────────────┐
                        │   OneMinus      │──▶ 反转 (1 = 内部, 0 = 外部)
                        └───────┬─────────┘
                                ▼
                        ┌─────────────────┐
                        │    Output       │──▶ RevivalMask (0-1)
                        └─────────────────┘
```

### 3.2 输出说明

| 输出 | 范围 | 含义 |
|------|:----:|------|
| `RevivalMask` | 0.0 - 1.0 | 0 = 石化状态, 1 = 完全复苏 |

---

## 4. 主材质 (M_Env_Revival)

**路径**: `/Game/ECHO/Materials/M_Env_Revival` (待创建)

### 4.1 参数槽位

| 参数组 | 参数名 | 类型 | 说明 |
|--------|--------|------|------|
| **Alive State** | `AlbedoAlive` | Texture2D | 复苏后的固有色 |
| | `NormalAlive` | Texture2D | 复苏后的法线 |
| | `RMAAlive` | Texture2D | Roughness/Metallic/AO |
| **Stone State** | `StoneTexture` | Texture2D | 世界对齐的石化纹理 |
| | `StoneColor` | LinearColor | 石化着色 (默认灰色) |
| | `StoneRoughness` | Scalar | 石化粗糙度 (默认 0.9) |
| **Blend** | `HardnessScale` | Scalar | 边缘过渡硬度 |
| **WPO** | `WindIntensity` | Scalar | 风动强度 (复苏后生效) |

### 4.2 混合逻辑

```hlsl
// 伪代码
float Mask = MF_RevivalLogic(); // 0-1

// Base Color 混合
float3 FinalBaseColor = lerp(StoneColor, AlbedoAlive, Mask);

// Roughness 混合
float FinalRoughness = lerp(StoneRoughness, RMAAlive.r, Mask);

// WPO 混合 (石化时无风动)
float3 FinalWPO = lerp(0, WindWPO, Mask);

// 自发光 (复苏边缘发光)
float EdgeGlow = fwidth(Mask) * EmissiveIntensity;
float3 FinalEmissive = lerp(0, EdgeGlow * EmissiveColor, Mask > 0.01 && Mask < 0.99);
```

### 4.3 材质实例创建规范

所有场景材质必须继承 `M_Env_Revival`，并设置：

1. **必填参数**:
   - `AlbedoAlive`
   - `NormalAlive`

2. **可选参数**:
   - `RMAAlive` (默认使用白色)
   - `WindIntensity` (默认 0)

---

## 5. 顶点色规范

为避免额外的纹理采样，我们使用顶点色控制复苏细节：

| 通道 | 名称 | 用途 |
|:----:|------|------|
| **R** | WPO Weight | 1 = 随风摆动, 0 = 刚体 |
| **G** | Revival Mask | 1 = 可复苏, 0 = 永远石化 |
| **B** | AO/Dirt | 石缝脏迹混合 |
| **A** | Reserved | 预留 |

---

## 6. 性能优化

### 6.1 MPC 更新频率
- 每帧更新 1 次（在 `Tick` 中）
- 使用 `FInterpTo` 平滑避免跳变

### 6.2 材质 LOD
| 距离 | 复杂度 | 说明 |
|------|--------|------|
| < 2000uu | 完整 | 全特效 |
| 2000-5000uu | 简化 | 禁用 WPO |
| > 5000uu | 最简 | 使用静态灰色 |

### 6.3 Draw Call 优化
- 使用 Material Instance Dynamic 而非每帧设置参数
- 大量使用 Instanced Static Mesh

---

## 7. 调试方法

### 7.1 编辑器内测试
1. 打开 `MPC_Revival` 资产
2. 手动修改 `RevivalRadius` (0 - 5000)
3. 观察场景物体响应

### 7.2 控制台命令
```
// 显示材质复杂度
r.MeshDrawCommands.LogMaterialOverflow 1

// 查看 MPC 状态
ShowMaterialParameterCollection MPC_Revival
```

---

*最后更新: 2025-12-31*
