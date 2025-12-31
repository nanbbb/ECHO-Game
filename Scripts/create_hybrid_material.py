import unreal

mel = unreal.MaterialEditingLibrary
eal = unreal.EditorAssetLibrary

print('=== 创建混合方案材质 ===')
print('使用 CameraPositionWS 计算距离，MPC 控制范围')

# 加载资源
mat = unreal.load_asset('/Game/ECHO/Materials/M_Env_Revival')
mpc = unreal.load_asset('/Game/ECHO/Materials/MPC_Revival')

# 清理现有连接 - 创建新的节点

# 1. CameraPositionWS
cam_pos = mel.create_material_expression(mat, unreal.MaterialExpressionCameraPositionWS, -900, 200)

# 2. WorldPosition  
world_pos = mel.create_material_expression(mat, unreal.MaterialExpressionWorldPosition, -900, 300)

# 3. Distance
distance = mel.create_material_expression(mat, unreal.MaterialExpressionDistance, -700, 250)
mel.connect_material_expressions(cam_pos, '', distance, 'A')
mel.connect_material_expressions(world_pos, '', distance, 'B')

# 4. 从 MPC 获取 RevivalRadius
radius_param = mel.create_material_expression(mat, unreal.MaterialExpressionCollectionParameter, -700, 400)
radius_param.set_editor_property('collection', mpc)
radius_param.set_editor_property('parameter_name', unreal.Name('RevivalRadius'))

# 5. Divide (distance / radius)
divide = mel.create_material_expression(mat, unreal.MaterialExpressionDivide, -500, 300)
mel.connect_material_expressions(distance, '', divide, 'A')
mel.connect_material_expressions(radius_param, '', divide, 'B')

# 6. Saturate
saturate = mel.create_material_expression(mat, unreal.MaterialExpressionSaturate, -300, 300)
mel.connect_material_expressions(divide, '', saturate, '')

# 7. OneMinus (近=1, 远=0)
one_minus = mel.create_material_expression(mat, unreal.MaterialExpressionOneMinus, -100, 300)
mel.connect_material_expressions(saturate, '', one_minus, '')

# 8. 颜色 Lerp
lerp = mel.create_material_expression(mat, unreal.MaterialExpressionLinearInterpolate, 100, 100)

# 石化颜色（灰色）
stone = mel.create_material_expression(mat, unreal.MaterialExpressionConstant3Vector, -100, 0)
stone.set_editor_property('constant', unreal.LinearColor(0.3, 0.3, 0.3, 1))

# 复苏颜色（绿色）
alive = mel.create_material_expression(mat, unreal.MaterialExpressionConstant3Vector, -100, 100)
alive.set_editor_property('constant', unreal.LinearColor(0.2, 0.9, 0.2, 1))

mel.connect_material_expressions(stone, '', lerp, 'A')
mel.connect_material_expressions(alive, '', lerp, 'B')
mel.connect_material_expressions(one_minus, '', lerp, 'Alpha')

# 9. 连接到 BaseColor
mel.connect_material_property(lerp, '', unreal.MaterialProperty.MP_BASE_COLOR)

# 10. 粗糙度
roughness = mel.create_material_expression(mat, unreal.MaterialExpressionConstant, 100, 300)
roughness.set_editor_property('r', 0.5)
mel.connect_material_property(roughness, '', unreal.MaterialProperty.MP_ROUGHNESS)

# 保存
mel.recompile_material(mat)
eal.save_asset('/Game/ECHO/Materials/M_Env_Revival')
print('材质已更新!')

# 重新应用
ell = unreal.EditorLevelLibrary
actors = ell.get_all_level_actors()
static_mesh_actors = [a for a in actors if a.get_class().get_name() == 'StaticMeshActor']
for actor in static_mesh_actors:
    smc = actor.static_mesh_component
    if smc:
        smc.set_material(0, mat)

print(f'Applied to {len(static_mesh_actors)} actors')
print('')
print('现在效果应该工作!')
print('- 使用 CameraPositionWS 作为中心（玩家/相机位置）')
print('- 使用 MPC RevivalRadius 控制范围（默认 500）')
