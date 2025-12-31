import unreal

mel = unreal.MaterialEditingLibrary
eal = unreal.EditorAssetLibrary

print('=== 创建全新独立材质（不使用 MF_RevivalLogic）===')

# 创建全新材质
new_mat_path = '/Game/ECHO/Materials/M_Revival_Final'

if eal.does_asset_exist(new_mat_path):
    eal.delete_asset(new_mat_path)
    print('Deleted existing material')

# 创建新材质
new_mat = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
    'M_Revival_Final',
    '/Game/ECHO/Materials',
    unreal.Material,
    unreal.MaterialFactoryNew()
)

# 1. CameraPositionWS
cam_pos = mel.create_material_expression(new_mat, unreal.MaterialExpressionCameraPositionWS, -800, 200)

# 2. WorldPosition  
world_pos = mel.create_material_expression(new_mat, unreal.MaterialExpressionWorldPosition, -800, 300)

# 3. Distance
distance = mel.create_material_expression(new_mat, unreal.MaterialExpressionDistance, -600, 250)
mel.connect_material_expressions(cam_pos, '', distance, 'A')
mel.connect_material_expressions(world_pos, '', distance, 'B')

# 4. 范围常量 (500)
range_const = mel.create_material_expression(new_mat, unreal.MaterialExpressionConstant, -600, 400)
range_const.set_editor_property('r', 500.0)

# 5. Divide (distance / range)
divide = mel.create_material_expression(new_mat, unreal.MaterialExpressionDivide, -400, 300)
mel.connect_material_expressions(distance, '', divide, 'A')
mel.connect_material_expressions(range_const, '', divide, 'B')

# 6. Saturate
saturate = mel.create_material_expression(new_mat, unreal.MaterialExpressionSaturate, -200, 300)
mel.connect_material_expressions(divide, '', saturate, '')

# 7. OneMinus (近=1, 远=0)
one_minus = mel.create_material_expression(new_mat, unreal.MaterialExpressionOneMinus, 0, 300)
mel.connect_material_expressions(saturate, '', one_minus, '')

# 8. 颜色 Lerp
lerp = mel.create_material_expression(new_mat, unreal.MaterialExpressionLinearInterpolate, 200, 100)

# 石化颜色（灰色）
stone = mel.create_material_expression(new_mat, unreal.MaterialExpressionConstant3Vector, 0, 0)
stone.set_editor_property('constant', unreal.LinearColor(0.3, 0.3, 0.3, 1))

# 复苏颜色（绿色）
alive = mel.create_material_expression(new_mat, unreal.MaterialExpressionConstant3Vector, 0, 100)
alive.set_editor_property('constant', unreal.LinearColor(0.2, 0.9, 0.2, 1))

mel.connect_material_expressions(stone, '', lerp, 'A')
mel.connect_material_expressions(alive, '', lerp, 'B')
mel.connect_material_expressions(one_minus, '', lerp, 'Alpha')

# 9. 连接到 BaseColor
mel.connect_material_property(lerp, '', unreal.MaterialProperty.MP_BASE_COLOR)

# 10. 粗糙度
roughness = mel.create_material_expression(new_mat, unreal.MaterialExpressionConstant, 200, 300)
roughness.set_editor_property('r', 0.5)
mel.connect_material_property(roughness, '', unreal.MaterialProperty.MP_ROUGHNESS)

# 保存
mel.recompile_material(new_mat)
eal.save_asset(new_mat_path)
print(f'新材质创建完成: {new_mat_path}')

print('')
print('请停止 PIE 模式，然后执行:')
print('py "F:/ECHO/ECHO/Scripts/apply_final_material.py"')
