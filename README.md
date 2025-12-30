# ECHO: The Last Resonance
## 《ECHO：最后一次呼吸》

> "世界并没有死，它只是屏住了呼吸。而你，是它的肺。"

---

## 项目概述

**ECHO** 是一款使用 Unreal Engine 5.7 开发的 3D 写实叙事节奏游戏。

**故事**: 世界因"大石化"陷入永恒静止，你是最后的"调律者"埃利安。背负着巨大的"共鸣肺"装备，用音乐唤醒石化的万物。从第一朵花的绽放，到巨鲸的苏醒，最终以生命为代价换取整个星球的重生。

### 核心特性
- **叙事化节奏**: 判定点是场景中的真实物体（悬浮雨滴、发光蘑菇、古树心跳）
- **动态世界**: Nanite/Lumen 驱动的石化/复苏实时效果
- **情感叙事**: 4 章节史诗旅程，牺牲与重生的主题
- **电影流**: Sequencer 编排的一镜到底体验

---

## 快速开始

### 系统要求
- **引擎**: Unreal Engine 5.7.1
- **操作系统**: Windows 10/11 (64-bit)
- **GPU**: NVIDIA RTX 2070 或更高（需支持光线追踪）
- **内存**: 32GB RAM 推荐

### 克隆与设置

```powershell
# 克隆项目
git clone <repository_url> ECHO
cd ECHO

# 生成项目文件
& "F:\UE_5.7\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="$PWD\ECHO.uproject" -game -engine
```

### 启动编辑器

> **⚠️ 重要**: UE 5.7 存在 mimalloc 兼容性问题，必须使用以下方式启动：

```powershell
& "F:\UE_5.7\Engine\Binaries\Win64\UnrealEditor.exe" "F:\ECHO\ECHO\ECHO.uproject" -ansimalloc
```

### 编译项目

```powershell
& "F:\UE_5.7\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe" ECHOEditor Win64 Development -Project="F:\ECHO\ECHO\ECHO.uproject"
```

---

## 项目结构

```
ECHO/
├── Source/ECHO/                    # C++ 源代码
│   ├── Actors/                     # 游戏 Actor
│   │   └── ECHORhythmActor.*       # 节奏响应 Actor
│   ├── System/                     # 核心系统
│   │   └── ECHOAudioClockSubsystem.* # Quartz 音频时钟
│   ├── ECHOCharacter.*             # 玩家角色
│   ├── ECHOPlayerController.*      # 玩家控制器（输入处理）
│   ├── ECHOGameMode.*              # 游戏模式
│   └── ECHOCameraManager.*         # 摄像机管理
│
├── Content/ECHO/                   # 游戏资产
│   └── Materials/                  # 材质资产
│       ├── MPC_Revival.uasset      # 复苏材质参数集
│       └── MF_RevivalLogic.uasset  # 复苏逻辑材质函数
│
├── Plugins/                        # 插件
│   └── McpAutomationBridge/        # MCP 自动化桥接
│
├── Config/                         # 配置文件
├── docs/                           # 设计文档
└── Saved/                          # 运行时数据
```

---

## 文档索引

| 文档 | 描述 | 目标读者 |
|------|------|---------|
| [PRD_v0.2.md](docs/PRD_v0.2.md) | 产品需求文档 | 全团队 |
| [Narrative_Design.md](docs/Narrative_Design.md) | 叙事设计与剧本 | 策划/美术 |
| [System_Architecture.md](docs/System_Architecture.md) | 系统架构设计 | 程序 |
| [Art_Pipeline.md](docs/Art_Pipeline.md) | 美术资产管线 | 美术/TA |
| [Audio_System_Design.md](docs/Audio_System_Design.md) | 音频系统设计 | 程序/音效 |
| [Game_State_Flow.md](docs/Game_State_Flow.md) | 存档系统设计 | 程序 |
| [Level_Design_Guidelines.md](docs/Level_Design_Guidelines.md) | 关卡设计指南 | 关卡设计 |
| [Input_System.md](docs/Input_System.md) | 输入系统规范 | 程序 |
| [Material_System.md](docs/Material_System.md) | 材质系统详解 | TA/程序 |
| [Code_Reference.md](docs/Code_Reference.md) | 代码参考手册 | 程序 |
| [Troubleshooting.md](docs/Troubleshooting.md) | 故障排除指南 | 全团队 |

---

## 开发阶段

| 阶段 | 状态 | 内容 |
|------|:----:|------|
| Phase 1: MVP | ✅ | Quartz 时钟、节奏 Actor、基础输入 |
| Phase 1.5: 架构 | ✅ | 系统设计文档 |
| Phase 2: 视觉原型 | 🔄 | 复苏材质系统、Nanite/Lumen 测试 |
| Phase 3: 垂直切片 | ⏳ | 30秒实机演示 |

---

## 技术栈

- **引擎**: Unreal Engine 5.7.1
- **渲染**: Lumen (GI/Reflections), Nanite (Geometry)
- **音频**: Quartz Subsystem (采样级精度同步)
- **平台**: PC (High-End), PS5 (目标)

---

## 许可证

本项目为私有项目，未经授权不得商用。

---

*最后更新: 2025-12-31 | 文档版本: v2.0*
