import unreal

def setup_character_test_scene():
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    eal = unreal.EditorAssetLibrary
    mel = unreal.MaterialEditingLibrary
    ell = unreal.EditorLevelLibrary

    print("=== 开始配置共鸣肺视觉测试场景 ===")

    # 1. 创建专用材质 M_Lung_Core (自发光脉冲材质)
    lung_mat_path = "/Game/ECHO/Materials/M_Lung_Core"
    if not eal.does_asset_exist(lung_mat_path):
        lung_mat = asset_tools.create_asset("M_Lung_Core", "/Game/ECHO/Materials", unreal.Material, unreal.MaterialFactoryNew())
    else:
        lung_mat = unreal.load_asset(lung_mat_path)

    # 清亮材质
    mel.delete_all_material_expressions(lung_mat)

    # 核心逻辑：自发光颜色 * 强度
    color_param = mel.create_material_expression(lung_mat, unreal.MaterialExpressionVectorParameter, -400, 0)
    color_param.set_editor_property('parameter_name', 'LungColor')
    color_param.set_editor_property('default_value', unreal.LinearColor(0.0, 1.0, 0.5, 1.0)) # 蓝绿色

    glow_param = mel.create_material_expression(lung_mat, unreal.MaterialExpressionScalarParameter, -400, 200)
    glow_param.set_editor_property('parameter_name', 'GlowIntensity')
    glow_param.set_editor_property('default_value', 5.0)

    multiply = mel.create_material_expression(lung_mat, unreal.MaterialExpressionMultiply, -200, 100)
    mel.connect_material_expressions(color_param, "", multiply, "A")
    mel.connect_material_expressions(glow_param, "", multiply, "B")

    # 菲涅尔效果 (Fresnel) 让肺部边缘发光，看起来更像能量体
    fresnel = mel.create_material_expression(lung_mat, unreal.MaterialExpressionFresnel, -200, -100)
    
    final_emissive = mel.create_material_expression(lung_mat, unreal.MaterialExpressionMultiply, 0, 0)
    mel.connect_material_expressions(multiply, "", final_emissive, "A")
    mel.connect_material_expressions(fresnel, "", final_emissive, "B")

    mel.connect_material_property(final_emissive, "", unreal.MaterialProperty.MP_EMISSIVE_COLOR)
    
    # 设置为半透明
    lung_mat.set_editor_property('blend_mode', unreal.BlendMode.BLEND_TRANSLUCENT)
    lung_mat.set_editor_property('shading_model', unreal.MaterialShadingModel.MSM_UNLIT)
    
    mel.recompile_material(lung_mat)
    eal.save_asset(lung_mat_path)
    print(f"材质已创建: {lung_mat_path}")

    # 2. 创建新关卡 L_Character_Prototype
    level_path = "/Game/ECHO/Maps/L_Character_Prototype"
    if not eal.does_asset_exist(level_path):
        unreal.AssetToolsHelpers.get_asset_tools().create_asset("L_Character_Prototype", "/Game/ECHO/Maps", unreal.World, unreal.WorldFactory())
    
    # 加载关卡
    unreal.EditorLevelLibrary.load_level(level_path)

    # 3. 添加场景基础：暗色地面
    floor = ell.spawn_actor_from_class(unreal.StaticMeshActor, unreal.Vector(0, 0, 0))
    floor.static_mesh_component.set_static_mesh(unreal.load_asset("/Engine/BasicShapes/Plane"))
    floor.set_actor_scale3d(unreal.Vector(50, 50, 1))
    
    # 调暗灯光突出角色
    ell.spawn_actor_from_class(unreal.DirectionalLight, unreal.Vector(0, 0, 1000), unreal.Rotator(-45, 0, 0))
    
    # 添加一个 PlayerStart
    ell.spawn_actor_from_class(unreal.PlayerStart, unreal.Vector(0, 0, 200))

    unreal.EditorLevelLibrary.save_current_level()
    print("测试关卡准备就绪: L_Character_Prototype")
    print("注意: 编译成功后，请将 Character 类设为 ECHOResonanceLung 以测试呼吸效果。")

setup_character_test_scene()
