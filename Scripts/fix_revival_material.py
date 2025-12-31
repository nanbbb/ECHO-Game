import unreal

mel = unreal.MaterialEditingLibrary
eal = unreal.EditorAssetLibrary
ell = unreal.EditorLevelLibrary

print('=== 修复颜色并测试复苏材质 ===')

# 加载 M_Env_Revival
mat = unreal.load_asset('/Game/ECHO/Materials/M_Env_Revival')
mf = unreal.load_asset('/Game/ECHO/Materials/MF_RevivalLogic')

# 创建石化颜色 (灰色)
stone_color = mel.create_material_expression(mat, unreal.MaterialExpressionVectorParameter, -600, -100)
stone_color.set_editor_property('parameter_name', 'StoneColor')
stone_color.set_editor_property('default_value', unreal.LinearColor(0.3, 0.3, 0.3, 1))

# 创建复苏颜色 (绿色)
alive_color = mel.create_material_expression(mat, unreal.MaterialExpressionVectorParameter, -600, 100)
alive_color.set_editor_property('parameter_name', 'AliveColor')
alive_color.set_editor_property('default_value', unreal.LinearColor(0.2, 0.8, 0.2, 1))

# 创建 MaterialFunctionCall 引用 MF_RevivalLogic
mf_call = mel.create_material_expression(mat, unreal.MaterialExpressionMaterialFunctionCall, -400, 200)
mf_call.set_editor_property('material_function', mf)

# 创建 Lerp 节点
lerp_node = mel.create_material_expression(mat, unreal.MaterialExpressionLinearInterpolate, -200, 0)

# 连接
mel.connect_material_expressions(stone_color, '', lerp_node, 'A')
mel.connect_material_expressions(alive_color, '', lerp_node, 'B')
mel.connect_material_expressions(mf_call, '', lerp_node, 'Alpha')

# 连接到材质输出
mel.connect_material_property(lerp_node, '', unreal.MaterialProperty.MP_BASE_COLOR)

# 设置粗糙度为 0.5
roughness = mel.create_material_expression(mat, unreal.MaterialExpressionConstant, -200, 300)
roughness.set_editor_property('r', 0.5)
mel.connect_material_property(roughness, '', unreal.MaterialProperty.MP_ROUGHNESS)

# 保存
mel.recompile_material(mat)
eal.save_asset('/Game/ECHO/Materials/M_Env_Revival')
print('M_Env_Revival updated!')

# 应用到物体
actors = ell.get_all_level_actors()
static_mesh_actors = [a for a in actors if a.get_class().get_name() == 'StaticMeshActor']

for actor in static_mesh_actors:
    smc = actor.static_mesh_component
    if smc:
        smc.set_material(0, mat)

print(f'Applied to {len(static_mesh_actors)} actors')
print('')
print('现在物体应该显示灰色（石化）或绿色（复苏），取决于 MF_RevivalLogic 的输出！')
