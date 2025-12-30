# 故障排除指南 (Troubleshooting Guide)

**版本**: v1.0
**日期**: 2025-12-31

---

## 1. 编辑器启动问题

### 1.1 ❌ 编辑器启动时崩溃 (EXCEPTION_ACCESS_VIOLATION)

**症状**:
- 编辑器在加载地图后立即崩溃
- 日志显示 `EXCEPTION_ACCESS_VIOLATION writing address`
- 调用栈包含 `mimalloc` 和 `ZenCacheStore`

**原因**:
UE 5.7 的 `mimalloc` 内存分配器与系统 HTTP 代理（如 `127.0.0.1:7890`）或 Zen DDC 服务存在兼容性问题。

**解决方案**:
使用 `-ansimalloc` 参数启动编辑器，强制使用标准 Windows 堆分配器：

```powershell
& "F:\UE_5.7\Engine\Binaries\Win64\UnrealEditor.exe" "F:\ECHO\ECHO\ECHO.uproject" -ansimalloc
```

**永久修复** (可选):
在 `ECHO.uproject` 的运行配置中添加该参数，或创建快捷方式。

---

### 1.2 ❌ 编译失败：Live Coding is active

**症状**:
```
Unable to build while Live Coding is active. Exit the editor...
Result: Failed (OtherCompilationError)
```

**原因**:
Unreal Editor 正在运行，Live Coding 锁定了编译。

**解决方案**:
1. 关闭 Unreal Editor：
   ```powershell
   taskkill /IM UnrealEditor.exe /F
   ```
2. 或在编辑器内使用 `Ctrl+Alt+F11` 进行热重载

---

### 1.3 ❌ 编译失败：#include found after .generated.h file

**症状**:
```
error: #include found after .generated.h file - theass .generated.h file should always be the last #include in a header
```

**原因**:
Unreal Header Tool (UHT) 要求 `.generated.h` 必须是头文件的最后一个 `#include`。

**解决方案**:
检查报错的 `.h` 文件，确保 `#include "XXX.generated.h"` 是最后一个 include：

```cpp
// ✅ 正确
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// ... 其他 includes ...
#include "MyActor.generated.h"  // 必须在最后

// ❌ 错误
#include "CoreMinimal.h"
#include "MyActor.generated.h"
#include "GameFramework/Actor.h"  // 在 .generated.h 之后
```

---

## 2. Quartz 音频问题

### 2.1 ❌ 音乐播放但节拍事件不触发

**症状**:
- `PlayMusic()` 执行成功
- `OnQuantizationEvent` 委托无响应

**排查步骤**:
1. 检查时钟是否正确创建：
   ```cpp
   UQuartzSubsystem* Quartz = UQuartzSubsystem::Get(World);
   if (Quartz && Quartz->DoesClockExist(World, ClockName))
   {
       UE_LOG(LogTemp, Log, TEXT("Clock exists!"));
   }
   ```

2. 确认 `HandleQuartzMetronome` 已正确绑定：
   ```cpp
   FOnQuartzMetronomeEventBP MetronomeDelegate;
   MetronomeDelegate.BindUFunction(this, FName("HandleQuartzMetronome"));
   ```

3. 检查 `HandleQuartzMetronome` 函数签名是否正确：
   ```cpp
   UFUNCTION()
   void HandleQuartzMetronome(
       FName ClockName,
       EQuartzCommandQuantization QuantizationType,
       int32 NumBars,
       int32 Beat,
       float BeatFraction);
   ```

---

### 2.2 ❌ 节拍判定总是 Miss

**症状**:
- 按键时机正确但总是返回 `bOnBeat = false`

**原因**:
可能是延迟补偿未正确设置。

**解决方案**:
1. 检查 `LatencyOffsetMs` 是否被正确应用
2. 运行延迟校准流程
3. 增大 `JudgmentWindowMs`（测试用）

---

## 3. 材质问题

### 3.1 ❌ 复苏效果不响应

**症状**:
- 修改 `MPC_Revival` 的 `RevivalRadius` 无视觉变化

**排查步骤**:
1. 确认材质使用了 `MF_RevivalLogic`
2. 检查材质实例是否引用了正确的 MPC
3. 在材质编辑器中预览 `MF_RevivalLogic` 输出

---

### 3.2 ❌ 材质显示全黑或全白

**可能原因**:
- `RevivalRadius` = 0（全石化）
- `RevivalCenter` 距离物体太远
- Division by zero（Radius = 0 时的除法错误）

**解决方案**:
在 `MF_RevivalLogic` 中添加 `Max(Radius, 0.001)` 避免除零。

---

## 4. MCP 自动化问题

### 4.1 ❌ MCP 连接失败 (ERR_CONNECTION_REFUSED)

**症状**:
- 访问 `http://127.0.0.1:8091` 显示连接被拒绝

**原因**:
- Unreal Editor 未运行
- McpAutomationBridge 插件未启用

**解决方案**:
1. 确认编辑器正在运行
2. 检查日志：
   ```
   LogMcpAutomationBridgeSubsystem: Automation bridge listening on port=8091
   ```
3. 确认 `McpAutomationBridge` 插件在 `.uproject` 中启用

---

### 4.2 ❌ MCP 返回 ERR_EMPTY_RESPONSE

**症状**:
- 端口有响应但返回空

**原因**:
MCP Bridge 使用 WebSocket 协议，普通 HTTP GET 请求会返回空响应。

**解决方案**:
使用 WebSocket 客户端连接，而非 HTTP。

---

## 5. 性能问题

### 5.1 ❌ 帧率低于目标

**排查步骤**:
1. 使用 GPU Profiler (`ProfileGPU` 或 `Ctrl+Shift+,`)
2. 检查以下常见瓶颈：
   - Lumen GI 更新
   - Shadow Map 渲染
   - WPO 物体过多
   - Overdraw

**常用优化命令**:
```
stat gpu
stat unit
r.ScreenPercentage 80
r.Lumen.Reflections.Quality 0
```

---

## 6. 常用日志位置

| 日志 | 路径 |
|------|------|
| 编辑器日志 | `Saved/Logs/ECHO.log` |
| 崩溃日志 | `Saved/Crashes/` |
| DDC 日志 | `Saved/Logs/` (搜索 "DerivedDataCache") |
| 编译日志 | `Intermediate/Build/` |

---

## 7. 有用的控制台命令

| 命令 | 描述 |
|------|------|
| `stat fps` | 显示帧率 |
| `stat unit` | 显示 Game/Draw/GPU 时间 |
| `stat scenerendering` | 场景渲染统计 |
| `r.RayTracing 0/1` | 禁用/启用光线追踪 |
| `Quartz.Debug 1` | Quartz 调试输出 |

---

## 8. 联系支持

如果以上方法无法解决问题：
1. 收集完整的 `ECHO.log`
2. 记录复现步骤
3. 附上相关截图/录屏
4. 提交到项目 Issue 追踪器

---

*最后更新: 2025-12-31*
