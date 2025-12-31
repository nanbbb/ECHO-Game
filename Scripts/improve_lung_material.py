import unreal

def improve_lung_material():
    """改进 M_Lung_Core 材质：添加 Fresnel、呼吸动画、脉冲强度参数"""
    
    eal = unreal.EditorAssetLibrary
    mel = unreal.MaterialEditingLibrary
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    
    print("=== 任务 3: 改进 M_Lung_Core 材质 ===")
    
    mat_path = "/Game/ECHO/Materials/M_Lung_Core"
    mat = unreal.load_asset(mat_path)
    
    if not mat:
        print(f"材质不存在，创建新的...")
        mat = asset_tools.create_asset("M_Lung_Core", "/Game/ECHO/Materials",
                                        unreal.Material, unreal.MaterialFactoryNew())
    
    # 清除现有表达式
    mel.delete_all_material_expressions(mat)
    
    # ========== 基础颜色参数 ==========
    lung_color = mel.create_material_expression(mat, unreal.MaterialExpressionVectorParameter, -600, 0)
    lung_color.set_editor_property('parameter_name', 'LungColor')
    lung_color.set_editor_property('default_value', unreal.LinearColor(0.0, 0.9, 0.5, 1.0))  # 青绿色
    
    # ========== Fresnel 边缘效果 ==========
    fresnel = mel.create_material_expression(mat, unreal.MaterialExpressionFresnel, -400, 150)
    fresnel.set_editor_property('exponent', 3.0)
    
    fresnel_color = mel.create_material_expression(mat, unreal.MaterialExpressionVectorParameter, -600, 150)
    fresnel_color.set_editor_property('parameter_name', 'FresnelColor')
    fresnel_color.set_editor_property('default_value', unreal.LinearColor(0.5, 1.0, 0.8, 1.0))  # 浅青色
    
    fresnel_mult = mel.create_material_expression(mat, unreal.MaterialExpressionMultiply, -200, 150)
    mel.connect_material_expressions(fresnel, "", fresnel_mult, "A")
    mel.connect_material_expressions(fresnel_color, "", fresnel_mult, "B")
    
    # ========== 呼吸动画 (Sine 波动) ==========
    time_node = mel.create_material_expression(mat, unreal.MaterialExpressionTime, -600, 300)
    
    breath_speed = mel.create_material_expression(mat, unreal.MaterialExpressionConstant, -500, 350)
    breath_speed.set_editor_property('r', 2.0)  # 呼吸速度
    
    time_mult = mel.create_material_expression(mat, unreal.MaterialExpressionMultiply, -400, 320)
    mel.connect_material_expressions(time_node, "", time_mult, "A")
    mel.connect_material_expressions(breath_speed, "", time_mult, "B")
    
    sine_node = mel.create_material_expression(mat, unreal.MaterialExpressionSine, -300, 320)
    mel.connect_material_expressions(time_mult, "", sine_node, "")
    
    # 将 Sin 结果映射到 0.8-1.2 范围
    breath_amplitude = mel.create_material_expression(mat, unreal.MaterialExpressionConstant, -300, 400)
    breath_amplitude.set_editor_property('r', 0.2)  # 振幅
    
    breath_mult = mel.create_material_expression(mat, unreal.MaterialExpressionMultiply, -200, 350)
    mel.connect_material_expressions(sine_node, "", breath_mult, "A")
    mel.connect_material_expressions(breath_amplitude, "", breath_mult, "B")
    
    breath_base = mel.create_material_expression(mat, unreal.MaterialExpressionConstant, -200, 450)
    breath_base.set_editor_property('r', 1.0)
    
    breath_add = mel.create_material_expression(mat, unreal.MaterialExpressionAdd, -100, 380)
    mel.connect_material_expressions(breath_mult, "", breath_add, "A")
    mel.connect_material_expressions(breath_base, "", breath_add, "B")
    
    # ========== 脉冲强度参数 (由 C++ 控制) ==========
    pulse_intensity = mel.create_material_expression(mat, unreal.MaterialExpressionScalarParameter, -400, 500)
    pulse_intensity.set_editor_property('parameter_name', 'PulseIntensity')
    pulse_intensity.set_editor_property('default_value', 0.0)
    
    # 脉冲对发光的影响
    pulse_mult_factor = mel.create_material_expression(mat, unreal.MaterialExpressionConstant, -300, 550)
    pulse_mult_factor.set_editor_property('r', 5.0)  # 脉冲时亮度倍数
    
    pulse_effect = mel.create_material_expression(mat, unreal.MaterialExpressionMultiply, -200, 520)
    mel.connect_material_expressions(pulse_intensity, "", pulse_effect, "A")
    mel.connect_material_expressions(pulse_mult_factor, "", pulse_effect, "B")
    
    pulse_add_one = mel.create_material_expression(mat, unreal.MaterialExpressionAdd, -100, 500)
    mel.connect_material_expressions(pulse_effect, "", pulse_add_one, "A")
    one_const = mel.create_material_expression(mat, unreal.MaterialExpressionConstant, -200, 600)
    one_const.set_editor_property('r', 1.0)
    mel.connect_material_expressions(one_const, "", pulse_add_one, "B")
    
    # ========== 基础发光强度 ==========
    base_glow = mel.create_material_expression(mat, unreal.MaterialExpressionScalarParameter, -400, -100)
    base_glow.set_editor_property('parameter_name', 'GlowIntensity')
    base_glow.set_editor_property('default_value', 8.0)
    
    # ========== 组合所有效果 ==========
    # 颜色 * 基础发光 * 呼吸 * 脉冲
    color_glow = mel.create_material_expression(mat, unreal.MaterialExpressionMultiply, 0, 0)
    mel.connect_material_expressions(lung_color, "", color_glow, "A")
    mel.connect_material_expressions(base_glow, "", color_glow, "B")
    
    with_breath = mel.create_material_expression(mat, unreal.MaterialExpressionMultiply, 100, 50)
    mel.connect_material_expressions(color_glow, "", with_breath, "A")
    mel.connect_material_expressions(breath_add, "", with_breath, "B")
    
    with_pulse = mel.create_material_expression(mat, unreal.MaterialExpressionMultiply, 200, 80)
    mel.connect_material_expressions(with_breath, "", with_pulse, "A")
    mel.connect_material_expressions(pulse_add_one, "", with_pulse, "B")
    
    # 添加 Fresnel 效果
    final_emissive = mel.create_material_expression(mat, unreal.MaterialExpressionAdd, 300, 100)
    mel.connect_material_expressions(with_pulse, "", final_emissive, "A")
    mel.connect_material_expressions(fresnel_mult, "", final_emissive, "B")
    
    # ========== 连接到材质输出 ==========
    mel.connect_material_property(final_emissive, "", unreal.MaterialProperty.MP_EMISSIVE_COLOR)
    
    # 设置材质属性
    mat.set_editor_property('blend_mode', unreal.BlendMode.BLEND_TRANSLUCENT)
    mat.set_editor_property('shading_model', unreal.MaterialShadingModel.MSM_UNLIT)
    
    # 添加少量不透明度（让它看起来像发光的能量体）
    opacity = mel.create_material_expression(mat, unreal.MaterialExpressionScalarParameter, 0, 250)
    opacity.set_editor_property('parameter_name', 'Opacity')
    opacity.set_editor_property('default_value', 0.8)
    mel.connect_material_property(opacity, "", unreal.MaterialProperty.MP_OPACITY)
    
    # 编译保存
    mel.recompile_material(mat)
    eal.save_asset(mat_path)
    
    print(f"M_Lung_Core 材质改进完成!")
    print("  - 添加了 Fresnel 边缘效果")
    print("  - 添加了呼吸动画 (Sine 波动)")
    print("  - 添加了 PulseIntensity 参数 (供 C++ 控制)")
    print("")
    print("=== 任务 3 完成! ===")

improve_lung_material()
