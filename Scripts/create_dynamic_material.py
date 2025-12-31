import unreal

mel = unreal.MaterialEditingLibrary
eal = unreal.EditorAssetLibrary

print('=== 创建使用 CameraPosition 的动态材质 ===')

# 加载材质
mat = unreal.load_asset('/Game/ECHO/Materials/M_Env_Revival')

# 不使用 MPC，直接使用 CameraPositionWS 节点
# 这样效果会实时随相机/玩家位置变化

# 创建 CameraPositionWS 节点（摄像机世界位置）
cam_pos = mel.create_material_expression(mat, unreal.MaterialExpressionCameraPositionWS, -800, 200)

# 创建 WorldPosition 节点
world_pos = mel.create_material_expression(mat, unreal.MaterialExpressionWorldPosition, -800, 300)


# 创建 Distance 节点
distance = mel.create_material_expression(mat, unreal.MaterialExpressionDistance, -600, 250)

# 连接：CameraPos -> Distance.A, WorldPos -> Distance.B
mel.connect_material_expressions(cam_pos, '', distance, 'A')
mel.connect_material_expressions(world_pos, '', distance, 'B')

# 创建除法节点 - 除以范围（500）
divide = mel.create_material_expression(mat, unreal.MaterialExpressionDivide, -400, 250)
const_range = mel.create_material_expression(mat, unreal.MaterialExpressionConstant, -500, 350)
const_range.set_editor_property('r', 500.0)

mel.connect_material_expressions(distance, '', divide, 'A')
mel.connect_material_expressions(const_range, '', divide, 'B')

# Saturate - 限制到 0-1
saturate = mel.create_material_expression(mat, unreal.MaterialExpressionSaturate, -200, 250)
mel.connect_material_expressions(divide, '', saturate, '')

# OneMinus - 反转（近=1，远=0）
one_minus = mel.create_material_expression(mat, unreal.MaterialExpressionOneMinus, 0, 250)
mel.connect_material_expressions(saturate, '', one_minus, '')

# Lerp 颜色
lerp = mel.create_material_expression(mat, unreal.MaterialExpressionLinearInterpolate, 200, 100)

# 石化颜色（灰色）
stone = mel.create_material_expression(mat, unreal.MaterialExpressionConstant3Vector, 0, 0)
stone.set_editor_property('constant', unreal.LinearColor(0.3, 0.3, 0.3, 1))

# 复苏颜色（绿色）
alive = mel.create_material_expression(mat, unreal.MaterialExpressionConstant3Vector, 0, 100)
alive.set_editor_property('constant', unreal.LinearColor(0.2, 0.9, 0.2, 1))

mel.connect_material_expressions(stone, '', lerp, 'A')
mel.connect_material_expressions(alive, '', lerp, 'B')
mel.connect_material_expressions(one_minus, '', lerp, 'Alpha')

# 连接到 BaseColor
mel.connect_material_property(lerp, '', unreal.MaterialProperty.MP_BASE_COLOR)

# 保存
mel.recompile_material(mat)
eal.save_asset('/Game/ECHO/Materials/M_Env_Revival')
print('材质已更新为使用 CameraWorldPosition!')

# 重新应用到场景物体
ell = unreal.EditorLevelLibrary
actors = ell.get_all_level_actors()
static_mesh_actors = [a for a in actors if a.get_class().get_name() == 'StaticMeshActor']
for actor in static_mesh_actors:
    smc = actor.static_mesh_component
    if smc:
        smc.set_material(0, mat)

print(f'Applied to {len(static_mesh_actors)} actors')
print('')
print('现在在编辑器视口中移动相机，效果应该会实时变化！')
print('近处 = 绿色（复苏），远处 = 灰色（石化）')
