import unreal

def configure_lung_blueprint():
    """配置共鸣肺蓝图的组件属性 - 简化版"""
    
    eal = unreal.EditorAssetLibrary
    
    print("=== 配置 BP_ResonanceLung 组件 ===")
    
    # 加载资源
    bp_path = "/Game/ECHO/Blueprints/BP_ResonanceLung"
    bp = unreal.load_asset(bp_path)
    sphere_mesh = unreal.load_asset("/Engine/BasicShapes/Sphere")
    lung_material = unreal.load_asset("/Game/ECHO/Materials/M_Lung_Core")
    
    if not bp:
        print(f"错误: 找不到蓝图 {bp_path}")
        return
    
    # 通过 SCS (SimpleConstructionScript) 访问组件
    scs = bp.simple_construction_script
    if not scs:
        print("错误: 蓝图没有 SimpleConstructionScript")
        return
    
    # 获取所有 SCS 节点
    all_nodes = scs.get_all_nodes()
    print(f"发现 {len(all_nodes)} 个 SCS 节点")
    
    for node in all_nodes:
        template = node.component_template
        if template:
            name = template.get_name()
            print(f"  - 组件: {name} (类型: {type(template).__name__})")
            
            if "LungVisual" in name and isinstance(template, unreal.StaticMeshComponent):
                # 设置模型
                if sphere_mesh:
                    template.set_static_mesh(sphere_mesh)
                    print(f"    已设置模型: Sphere")
                
                # 设置材质
                if lung_material:
                    template.set_material(0, lung_material)
                    print(f"    已设置材质: M_Lung_Core")
                
                # 设置缩放和位置
                template.set_editor_property('relative_scale3d', unreal.Vector(0.3, 0.3, 0.3))
                template.set_editor_property('relative_location', unreal.Vector(50, 0, -30))
                print(f"    已设置缩放和位置")
    
    # 编译并保存
    unreal.BlueprintEditorLibrary.compile_blueprint(bp)
    eal.save_asset(bp_path)
    
    print("")
    print("=== 配置完成 ===")
    print("可以将 BP_ResonanceLung 放入场景测试了！")

configure_lung_blueprint()
