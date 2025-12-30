# 游戏状态与存档架构 (Game State Flow)

**版本**: v2.0
**日期**: 2025-12-31
**基于**: Narrative_Design.md v2.0

---

## 1. 设计哲学

鉴于《ECHO》的**线性叙事**和**情感体验**特性，我们采用**"检查点驱动 (Checkpoint Driven)"**策略：

- ✅ 只保存剧情节点和关键变量
- ✅ 不保存每个物体状态
- ✅ 不允许手动存档（S/L 大法破坏心流）
- ✅ 死亡后从最近检查点重生

---

## 2. 游戏状态定义

### 2.1 章节状态 (Chapter States)

```
游戏进度状态机:

[MainMenu] ──▶ [Prologue] ──▶ [Chapter1] ──▶ [Chapter2] ──▶ [Finale] ──▶ [Ending]
                   │              │              │             │
                   ▼              ▼              ▼             ▼
              [序章检查点]   [森林检查点]   [海洋检查点]   [终章检查点]
```

### 2.2 章节检查点

| 章节 | 检查点ID | 位置描述 | 自动存档触发 |
|------|---------|---------|:-------------:|
| 序章 | CP_Prologue_Start | 石洞入口 | ✓ |
| 序章 | CP_Prologue_Flower | 第一朵花绽放后 | ✓ |
| 第一章 | CP_Forest_Edge | 进入林缘 | ✓ |
| 第一章 | CP_Forest_Deep | 进入深林 | ✓ |
| 第一章 | CP_Forest_Tree | 古树苏醒后 | ✓ |
| 第二章 | CP_Ocean_Shore | 到达海岸 | ✓ |
| 第二章 | CP_Ocean_Tube | 进入浪管 | ✓ |
| 第二章 | CP_Ocean_Abyss | 深海坟场 | ✓ |
| 终章 | CP_Finale_Start | 到达极北 | ✓ |
| 终章 | CP_Finale_Whale | 开始演奏 | ✓ |

---

## 3. 存档数据结构

### 3.1 存档对象 (`UECHOSaveGame`)

```cpp
UCLASS()
class ECHO_API UECHOSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    // ========== 玩家位置 ==========
    UPROPERTY()
    FVector PlayerLocation;

    UPROPERTY()
    FRotator PlayerRotation;

    // ========== 剧情进度 ==========
    UPROPERTY()
    FName CurrentChapterID;  // e.g., "Chapter1_Forest"

    UPROPERTY()
    FName LastCheckpointID;  // e.g., "CP_Forest_Tree"

    // ========== 复苏状态 ==========
    // 使用 GameplayTags 标记已完成的关键复苏事件
    // 例如: "State.Forest.AncientTreeRevived"
    UPROPERTY()
    FGameplayTagContainer UnlockedStoryFlags;

    // 全局复苏参数（用于恢复 Shader 状态）
    UPROPERTY()
    float GlobalRevivalRadius;

    // ========== 统计数据 ==========
    UPROPERTY()
    int32 TotalNotesHit;

    UPROPERTY()
    int32 TotalPerfects;

    UPROPERTY()
    float PlayTime;  // 游戏时长（秒）

    // ========== 设置 ==========
    UPROPERTY()
    float AudioLatencyOffset;

    UPROPERTY()
    float VisualLatencyOffset;
};
```

### 3.2 运行时状态 (`UECHOGameInstance`)

```cpp
UCLASS()
class ECHO_API UECHOGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    // 当前存档槽位
    UPROPERTY()
    int32 CurrentSaveSlot;

    // 内存中的存档数据（避免频繁读盘）
    UPROPERTY()
    TObjectPtr<UECHOSaveGame> CachedSaveData;

    // 复苏材质参数集引用
    UPROPERTY()
    TObjectPtr<UMaterialParameterCollection> RevivalMPC;

    // ========== 方法 ==========
    UFUNCTION(BlueprintCallable)
    void SaveGame();

    UFUNCTION(BlueprintCallable)
    void LoadGame(int32 Slot);

    UFUNCTION(BlueprintCallable)
    void ResetToCheckpoint();
};
```

---

## 4. 状态流程

### 4.1 游戏启动流程

```
[主菜单]
    │
    ├─▶ [新游戏]
    │     │
    │     ▼
    │   创建新存档
    │     │
    │     ▼
    │   初始化 MPC (RevivalRadius = 0)
    │     │
    │     ▼
    │   加载序章关卡
    │
    └─▶ [继续游戏]
          │
          ▼
        读取存档
          │
          ▼
        恢复 MPC (RevivalRadius = 存档值)
          │
          ▼
        遍历场景，应用 StoryFlags
          │
          ▼
        传送玩家至 LastCheckpointID
```

### 4.2 检查点触发流程

```
玩家进入检查点触发器
          │
          ▼
    更新 CachedSaveData
          │
          ├─▶ PlayerLocation = 当前位置
          ├─▶ LastCheckpointID = 触发器ID
          ├─▶ GlobalRevivalRadius = 当前 MPC 值
          │
          ▼
    异步写入磁盘 (.sav 文件)
          │
          ▼
    UI 提示 "进度已保存"
```

### 4.3 死亡与重生流程

```
玩家生命值 <= 0
          │
          ▼
    [死亡动画]
    - 画面变黑变慢
    - 石化从边缘蔓延
    - "共鸣肺"停止蒸汽
          │
          ▼
    [黑屏 2 秒]
          │
          ▼
    从 CachedSaveData 恢复
          │
          ├─▶ MPC.RevivalRadius = 存档值
          ├─▶ 重置场景中的临时状态
          ├─▶ 重置 Quartz 时钟
          │
          ▼
    淡入，玩家在 LastCheckpointID 位置
```

---

## 5. 复苏状态管理

### 5.1 StoryFlags 示例

| Tag | 描述 | 影响 |
|-----|------|------|
| `State.Prologue.FirstFlowerBloom` | 第一朵花绽放 | 花保持开放状态 |
| `State.Forest.AncientTreeRevived` | 古树苏醒 | 古树完全复苏，阳光穿透 |
| `State.Ocean.WhaleSeen` | 看到凝固的鲸鱼 | 标记叙事事件 |
| `State.Finale.WhaleAwakened` | 鲸鱼苏醒 | 全局复苏开始 |

### 5.2 复苏半径管理

```cpp
// 存档时
SaveData->GlobalRevivalRadius = CurrentMPCRadius;

// 读档时
// 方法 1: 即时全局覆盖
MPC->SetScalarParameter("RevivalRadius", SaveData->GlobalRevivalRadius);

// 方法 2: 渐进覆盖（更电影化）
// 从 0 快速扩展到存档值，给玩家"世界苏醒"的瞬间体验
AnimateRevivalRadius(0, SaveData->GlobalRevivalRadius, 1.0f);
```

---

## 6. 关键设计决策

### 6.1 单向进度

```
✅ 只能向前推进
✅ 一旦进入 Chapter2，Chapter1 资源可卸载
✅ 极大简化内存管理
❌ 玩家无法重玩早期章节（通关后解锁章节选择）
```

### 6.2 无手动存档

```
✅ 增强沉浸感，避免 S/L 破坏心流
✅ 确保情感连续性（死亡有代价）
✅ 检查点设计需精心考量间距
❌ 玩家可能因意外中断丢失进度
```

### 6.3 终章特殊处理

```
终章的死亡不会重生:
- 血量归零后，继续进入结局动画
- 这是叙事设计的一部分
- 玩家的"失败"成就了拯救

// 代码实现
if (CurrentChapter == EChapter::Finale && LifeForce <= 0)
{
    // 不触发正常死亡流程
    // 直接进入结局 Sequencer
    PlayFinaleSequence();
}
```

---

## 7. 存档文件规范

### 7.1 文件位置

```
Windows: %LOCALAPPDATA%/ECHO/Saved/SaveGames/
PS5:     /savedata/ECHO/

文件名格式: ECHO_Slot{N}.sav  (N = 0, 1, 2)
```

### 7.2 存档槽位

| 槽位 | 用途 |
|:----:|------|
| 0 | 主存档 |
| 1 | 自动备份 (每章节开始时) |
| 2 | 手动备份 (主菜单触发) |

---

*"记忆不会消失，它只是等待被唤醒。"*

*最后更新: 2025-12-31*
