import unreal

def setup_core_gameplay():
    # --- 资源路径定义 ---
    # 根据 find_by_name 结果，IA_Breathe 在 /Game/ECHO/Input/
    # IMC_Default 在 /Game/Input/
    ia_path = "/Game/ECHO/Input/IA_Breathe"
    ia_folder = "/Game/ECHO/Input"
    ia_name = "IA_Breathe"
    
    imc_path = "/Game/Input/IMC_Default"
    bp_path = "/Game/ECHO/Blueprints/BP_ResonanceLung"
    gm_path = "/Game/FirstPerson/Blueprints/BP_FirstPersonGameMode"

    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()

    print("=== ECHO: 开始核心玩法自动配置 (UE 5.7+ 兼容版) ===")

    # 1. 确保 Input Action 存在
    if not unreal.EditorAssetLibrary.does_asset_exist(ia_path):
        print(f"> 创建 Input Action: {ia_name} at {ia_folder}")
        ia_obj = asset_tools.create_asset(ia_name, ia_folder, unreal.InputAction, None)
    else:
        ia_obj = unreal.EditorAssetLibrary.load_asset(ia_path)
        print(f"> Input Action 已存在: {ia_path}")

    if not ia_obj:
        print("> 错误: 无法获取 Input Action 对象")
        return

    # 2. 确保 IMC_Default 存在并绑定 IA_Breathe
    if unreal.EditorAssetLibrary.does_asset_exist(imc_path):
        imc = unreal.EditorAssetLibrary.load_asset(imc_path)
        mappings = imc.get_editor_property("mappings")
        
        # 查找是否已经绑定
        already_mapped = False
        for m in mappings:
            if m.get_editor_property("action") == ia_obj:
                already_mapped = True
                break
        
        if not already_mapped:
            print(f"> 添加按键映射 (SpaceBar) 到 {imc_path}")
            imc.add_mapping(ia_obj, unreal.InputKey("SpaceBar"))
            unreal.EditorAssetLibrary.save_asset(imc_path)
        else:
            print(f"> IMC 映射已存在")
    else:
        print(f"> 错误: 未找到 IMC_Default 于 {imc_path}，请确认项目自带的增强输入配置文件位置。")

    # 3. 设置 BP_ResonanceLung 的默认属性 (直接操作 CDO)
    if unreal.EditorAssetLibrary.does_asset_exist(bp_path):
        bp = unreal.EditorAssetLibrary.load_asset(bp_path)
        bp_gen = bp.generated_class()
        cdo = unreal.get_default_object(bp_gen)
        
        if cdo:
            # 设置 BreatheAction 引用
            try:
                cdo.set_editor_property("BreatheAction", ia_obj)
                # 设置自动开启控制 (AutoPossess)
                cdo.set_editor_property("auto_possess_player", unreal.AutoPossessAI.PLAYER0)
                print(f"> 已成功更新 BP_ResonanceLung CDO 属性")
                unreal.EditorAssetLibrary.save_asset(bp_path)
            except Exception as e:
                print(f"> 设置 CDO 属性失败: {e}")
        else:
            print(f"> 错误: 无法获取 BP CDO")
    else:
        print(f"> 错误: 未找到 BP_ResonanceLung 于 {bp_path}")

    # 4. 设置 GameMode 的默认 Pawn
    if unreal.EditorAssetLibrary.does_asset_exist(gm_path):
        gm_bp = unreal.EditorAssetLibrary.load_asset(gm_path)
        gm_cdo = unreal.get_default_object(gm_bp.generated_class())
        if gm_cdo:
            bp_asset = unreal.EditorAssetLibrary.load_asset(bp_path)
            gm_cdo.set_editor_property("default_pawn_class", bp_asset.generated_class())
            unreal.EditorAssetLibrary.save_asset(gm_path)
            print(f"> 已更新 GameMode 默认 Pawn 为 BP_ResonanceLung")
        else:
            print(f"> 无法获取 GameMode CDO")

    # 5. 处理当前关卡中的实例
    world_actors = unreal.EditorLevelLibrary.get_all_level_actors()
    for actor in world_actors:
        if "BP_ResonanceLung" in actor.get_name():
            try:
                actor.set_editor_property("auto_possess_player", unreal.AutoPossessAI.PLAYER0)
                print(f"> 已强制关卡实例 {actor.get_name()} 获取 Player0 控制权")
            except:
                pass

    print("=== 配置完成！请尝试运行游戏测试 === ")

if __name__ == "__main__":
    setup_core_gameplay()
