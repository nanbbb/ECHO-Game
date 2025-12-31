import unreal

mel = unreal.MaterialEditingLibrary
eal = unreal.EditorAssetLibrary

print('=== 修正后的石头质感材质构建 ===')

mat = unreal.load_asset('/Game/ECHO/Materials/M_Revival_Final')

# 使用正确的清空方法
mel.delete_all_material_expressions(mat)

# 1. 距离逻辑 (CameraPositionWS -> Distance -> Divide -> Saturate -> OneMinus)
cam_pos = mel.create_material_expression(mat, unreal.MaterialExpressionCameraPositionWS, -1200, 200)
world_pos = mel.create_material_expression(mat, unreal.MaterialExpressionWorldPosition, -1200, 400)
distance_node = mel.create_material_expression(mat, unreal.MaterialExpressionDistance, -1000, 300)
mel.connect_material_expressions(cam_pos, '', distance_node, 'A')
mel.connect_material_expressions(world_pos, '', distance_node, 'B')

range_param = mel.create_material_expression(mat, unreal.MaterialExpressionScalarParameter, -1000, 500)
range_param.set_editor_property('parameter_name', 'RevivalRange')
range_param.set_editor_property('default_value', 1200.0)

divide_node = mel.create_material_expression(mat, unreal.MaterialExpressionDivide, -800, 400)
mel.connect_material_expressions(distance_node, '', divide_node, 'A')
mel.connect_material_expressions(range_param, '', divide_node, 'B')

saturate_node = mel.create_material_expression(mat, unreal.MaterialExpressionSaturate, -600, 400)
mel.connect_material_expressions(divide_node, '', saturate_node, '')

one_minus_node = mel.create_material_expression(mat, unreal.MaterialExpressionOneMinus, -400, 400)
mel.connect_material_expressions(saturate_node, '', one_minus_node, '')

# 2. 程序化石头颜色模拟
# 根据世界坐标的 X 和 Y 混合深浅色，制造斑驳感
color_dark = mel.create_material_expression(mat, unreal.MaterialExpressionVectorParameter, -800, -200)
color_dark.set_editor_property('parameter_name', 'StoneColor_Dark')
color_dark.set_editor_property('default_value', unreal.LinearColor(0.12, 0.12, 0.12, 1))

color_light = mel.create_material_expression(mat, unreal.MaterialExpressionVectorParameter, -800, -50)
color_light.set_editor_property('parameter_name', 'StoneColor_Light')
color_light.set_editor_property('default_value', unreal.LinearColor(0.28, 0.28, 0.28, 1))

# 使用世界坐标模拟噪波 Alpha
coord_mask = mel.create_material_expression(mat, unreal.MaterialExpressionComponentMask, -650, -100)
coord_mask.set_editor_property('r', True)
coord_mask.set_editor_property('g', True)
mel.connect_material_expressions(world_pos, '', coord_mask, '')

# 简单的缩放
scale_node = mel.create_material_expression(mat, unreal.MaterialExpressionMultiply, -550, -100)
scale_node.set_editor_property('const_b', 0.01) # 控制石头花纹大小
mel.connect_material_expressions(coord_mask, '', scale_node, 'A')

stone_lerp = mel.create_material_expression(mat, unreal.MaterialExpressionLinearInterpolate, -400, -100)
mel.connect_material_expressions(color_dark, '', stone_lerp, 'A')
mel.connect_material_expressions(color_light, '', stone_lerp, 'B')
mel.connect_material_expressions(scale_node, '', stone_lerp, 'Alpha')

# 3. 复苏颜色
alive_color = mel.create_material_expression(mat, unreal.MaterialExpressionVectorParameter, -400, 100)
alive_color.set_editor_property('parameter_name', 'AliveColor')
alive_color.set_editor_property('default_value', unreal.LinearColor(0.02, 0.75, 0.12, 1))

# 4. 颜色最终混合
final_base_color = mel.create_material_expression(mat, unreal.MaterialExpressionLinearInterpolate, 0, 0)
mel.connect_material_expressions(stone_lerp, '', final_base_color, 'A')
mel.connect_material_expressions(alive_color, '', final_base_color, 'B')
mel.connect_material_expressions(one_minus_node, '', final_base_color, 'Alpha')

# 5. 粗糙度 (0.95 -> 0.45)
r_stone = mel.create_material_expression(mat, unreal.MaterialExpressionConstant, -200, 200)
r_stone.set_editor_property('r', 0.98) # 非常干涩
r_alive = mel.create_material_expression(mat, unreal.MaterialExpressionConstant, -200, 300)
r_alive.set_editor_property('r', 0.45)

final_rough = mel.create_material_expression(mat, unreal.MaterialExpressionLinearInterpolate, 100, 200)
mel.connect_material_expressions(r_stone, '', final_rough, 'A')
mel.connect_material_expressions(r_alive, '', final_rough, 'B')
mel.connect_material_expressions(one_minus_node, '', final_rough, 'Alpha')

# 6. 连接输出
mel.connect_material_property(final_base_color, '', unreal.MaterialProperty.MP_BASE_COLOR)
mel.connect_material_property(final_rough, '', unreal.MaterialProperty.MP_ROUGHNESS)

# 确保 Metallic=0
metallic = mel.create_material_expression(mat, unreal.MaterialExpressionConstant, 100, 300)
metallic.set_editor_property('r', 0.0)
mel.connect_material_property(metallic, '', unreal.MaterialProperty.MP_METALLIC)

# 重新编译保存
mel.recompile_material(mat)
eal.save_asset('/Game/ECHO/Materials/M_Revival_Final')

print('材质修复脚本执行完毕：修正了 API 调用并成功重建了带有材质层次的石头质感。')
