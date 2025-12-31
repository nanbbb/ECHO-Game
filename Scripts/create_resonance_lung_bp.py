import unreal

def create_resonance_lung_blueprint():
    """创建共鸣肺角色蓝图并配置视觉效果"""
    
    eal = unreal.EditorAssetLibrary
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    
    print("=== 创建共鸣肺角色蓝图 ===")
    
    # 1. 确保目录存在
    bp_path = "/Game/ECHO/Blueprints"
    if not eal.does_directory_exist(bp_path):
        eal.make_directory(bp_path)
    
    # 2. 创建蓝图
    bp_name = "BP_ResonanceLung"
    bp_full_path = f"{bp_path}/{bp_name}"
    
    if eal.does_asset_exist(bp_full_path):
        print(f"蓝图已存在: {bp_full_path}")
        bp = unreal.load_asset(bp_full_path)
    else:
        # 获取父类
        parent_class = unreal.load_class(None, "/Script/ECHO.ECHOResonanceLung")
        if not parent_class:
            print("错误: 找不到 ECHOResonanceLung 类，请确保项目已编译。")
            return
        
        # 创建蓝图
        factory = unreal.BlueprintFactory()
        factory.set_editor_property("parent_class", parent_class)
        bp = asset_tools.create_asset(bp_name, bp_path, unreal.Blueprint, factory)
        print(f"蓝图已创建: {bp_full_path}")
    
    # 3. 创建发光材质 (如果不存在)
    lung_mat_path = "/Game/ECHO/Materials/M_Lung_Core"
    if not eal.does_asset_exist(lung_mat_path):
        print("创建肺部发光材质...")
        mel = unreal.MaterialEditingLibrary
        lung_mat = asset_tools.create_asset("M_Lung_Core", "/Game/ECHO/Materials", unreal.Material, unreal.MaterialFactoryNew())
        
        # 简单的自发光材质
        color_param = mel.create_material_expression(lung_mat, unreal.MaterialExpressionVectorParameter, -300, 0)
        color_param.set_editor_property('parameter_name', 'LungColor')
        color_param.set_editor_property('default_value', unreal.LinearColor(0.0, 0.8, 0.4, 1.0))
        
        glow_param = mel.create_material_expression(lung_mat, unreal.MaterialExpressionScalarParameter, -300, 150)
        glow_param.set_editor_property('parameter_name', 'GlowIntensity')
        glow_param.set_editor_property('default_value', 8.0)
        
        multiply = mel.create_material_expression(lung_mat, unreal.MaterialExpressionMultiply, -100, 50)
        mel.connect_material_expressions(color_param, "", multiply, "A")
        mel.connect_material_expressions(glow_param, "", multiply, "B")
        
        mel.connect_material_property(multiply, "", unreal.MaterialProperty.MP_EMISSIVE_COLOR)
        
        # 半透明设置
        lung_mat.set_editor_property('blend_mode', unreal.BlendMode.BLEND_TRANSLUCENT)
        lung_mat.set_editor_property('shading_model', unreal.MaterialShadingModel.MSM_UNLIT)
        
        mel.recompile_material(lung_mat)
        eal.save_asset(lung_mat_path)
        print(f"材质已创建: {lung_mat_path}")
    
    # 4. 保存蓝图
    eal.save_asset(bp_full_path)
    
    print("")
    print("=== 配置完成 ===")
    print(f"角色蓝图: {bp_full_path}")
    print(f"发光材质: {lung_mat_path}")
    print("")
    print("下一步操作:")
    print("1. 双击打开 BP_ResonanceLung 蓝图")
    print("2. 在组件面板中选择 ResonanceLung 组件")
    print("3. 在详情面板中设置 Static Mesh 为 Sphere")
    print("4. 设置材质为 M_Lung_Core")
    print("5. 编译并保存蓝图")

create_resonance_lung_blueprint()
