# ECHO: The Last Resonance - 任务清单

## 已完成 ✅

### 核心系统
- [x] Quartz 音频时钟子系统 (`ECHOAudioClockSubsystem`)
- [x] 共鸣肺角色 (`ECHOResonanceLung`)
- [x] 140 BPM 音乐同步

### 节奏判定
- [x] 空格键输入绑定 (`IA_Breathe` + `IMC_Default`)
- [x] 三级判定系统 (Perfect <80ms / Good <150ms / Miss)
- [x] 节拍遗漏检测 (不按键自动 MISS)
- [x] 生命力增减机制 (+8% / +3% / -2% / -3%)

### 生命力视觉联动
- [x] `MPC_Revival` 参数扩展 (LifeForce)
- [x] C++ 实时同步 LifeForce 到 MPC
- [x] 测试材质 `M_LifeForce_Ground`
- [x] 死亡检测日志

### 视觉反馈
- [x] 小球脉冲动画
- [x] Perfect 屏幕闪光
- [x] 相机跟随修复

### 技术修复
- [x] 输入映射持久化
- [x] Quartz ClockHandle GC 问题
- [x] 音乐循环播放
- [x] 组件层级问题

## 待完成 ⏳

### 视觉增强
- [ ] 完整死亡画面 (屏幕渐黑 + 重启)
- [ ] Perfect 粒子爆发效果
- [ ] 场景材质全面应用生命力响应

### 音效
- [ ] Perfect/Good/Miss 判定音效
- [ ] 死亡音效

### 游戏循环
- [ ] 关卡选择
- [ ] 分数系统
- [ ] 排行榜
