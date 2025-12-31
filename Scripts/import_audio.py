import unreal

def import_and_play_music():
    """导入音频文件并创建测试设置"""
    
    eal = unreal.EditorAssetLibrary
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    
    print("=== 导入音频并设置节拍测试 ===")
    
    # 源文件路径（使用鼓轨道，节拍最明显）
    source_path = "D:/33dmg/3Dmusicgame/Assets/Game/Audio/testmusic/140bpmProtocol 7 Stems/1 Drums.wav"
    dest_path = "/Game/ECHO/Audio"
    
    # 检查是否已经导入
    if eal.does_asset_exist("/Game/ECHO/Audio/1 Drums"):
        print("音频已存在，跳过导入")
    else:
        print(f"导入: {source_path}")
        # 导入音频
        import_task = unreal.AssetImportTask()
        import_task.filename = source_path
        import_task.destination_path = dest_path
        import_task.automated = True
        import_task.save = True
        asset_tools.import_asset_tasks([import_task])
        print("导入完成!")
    
    # 加载音频资产
    sound_wave = unreal.load_asset("/Game/ECHO/Audio/1_Drums")
    if not sound_wave:
        sound_wave = unreal.load_asset("/Game/ECHO/Audio/1 Drums")
    
    if sound_wave:
        print(f"音频资产已加载: {sound_wave.get_name()}")
        print(f"时长: {sound_wave.get_editor_property('duration'):.2f} 秒")
    else:
        print("警告: 无法加载音频资产")
        print("请手动导入:")
        print("  1. 在内容浏览器中右键 -> 导入")
        print("  2. 选择 D:/33dmg/.../1 Drums.wav")
        print("  3. 保存到 /Game/ECHO/Audio")
    
    print("\n=== 下一步 ===")
    print("要在游戏中播放音乐并触发节拍，请在 BP_ResonanceLung 的蓝图中：")
    print("1. 在 BeginPlay 事件后添加 'Play Sound 2D' 节点")
    print("2. 选择导入的音频资产")
    print("3. 或者我可以通过 C++ 代码来实现自动播放")

import_and_play_music()
