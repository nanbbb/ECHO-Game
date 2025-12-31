import unreal

def optimize_lung_visuals():
    """任务 4: 优化共鸣肺蓝图的视觉参数"""
    
    eal = unreal.EditorAssetLibrary
    
    print("=== 任务 4: 视觉优化 ===")
    
    # 加载蓝图
    bp_path = "/Game/ECHO/Blueprints/BP_ResonanceLung"
    bp = unreal.load_asset(bp_path)
    
    if not bp:
        print(f"错误: 找不到蓝图 {bp_path}")
        return
    
    # 获取蓝图 CDO (Class Default Object)
    bp_cdo = unreal.get_default_object(bp.generated_class())
    
    if bp_cdo:
        # 设置脉冲参数
        bp_cdo.set_editor_property('PulseDecaySpeed', 3.0)
        bp_cdo.set_editor_property('MaxPulseScale', 0.3)
        print("已更新脉冲参数:")
        print("  - PulseDecaySpeed = 3.0")
        print("  - MaxPulseScale = 0.3")
    
    # 尝试更新 SCS 组件的变换
    scs = bp.simple_construction_script
    if scs:
        for node in scs.get_all_nodes():
            template = node.component_template
            if template and "LungVisual" in template.get_name():
                # 调整位置和缩放
                template.set_editor_property('relative_location', unreal.Vector(30, 0, -20))
                template.set_editor_property('relative_scale3d', unreal.Vector(0.2, 0.2, 0.2))
                print("已更新 LungVisual 变换:")
                print("  - 位置 = (30, 0, -20)")
                print("  - 缩放 = (0.2, 0.2, 0.2)")
    
    # 编译并保存
    unreal.BlueprintEditorLibrary.compile_blueprint(bp)
    eal.save_asset(bp_path)
    
    print("")
    print("=== 任务 4 完成! ===")

optimize_lung_visuals()
