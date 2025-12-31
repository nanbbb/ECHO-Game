import unreal

mel = unreal.MaterialEditingLibrary

# ========== Step 1: 确保 MPC 参数存在 ==========
mpc = unreal.load_asset('/Game/ECHO/Materials/MPC_Revival')

scalars = mpc.get_editor_property('scalar_parameters')
vectors = mpc.get_editor_property('vector_parameters')

if len(scalars) == 0 or len(vectors) == 0:
    print('Creating MPC parameters...')
    scalar_param = unreal.CollectionScalarParameter()
    scalar_param.set_editor_property('parameter_name', 'RevivalRadius')
    scalar_param.set_editor_property('default_value', 0.0)
    
    vector_param = unreal.CollectionVectorParameter()
    vector_param.set_editor_property('parameter_name', 'RevivalCenter')
    vector_param.set_editor_property('default_value', unreal.LinearColor(0, 0, 0, 0))
    
    mpc.set_editor_property('scalar_parameters', [scalar_param])
    mpc.set_editor_property('vector_parameters', [vector_param])
    unreal.EditorAssetLibrary.save_asset('/Game/ECHO/Materials/MPC_Revival')
    
    # 重新加载 MPC 确保更新
    mpc = unreal.load_asset('/Game/ECHO/Materials/MPC_Revival')
    print('MPC parameters created and saved!')
else:
    print(f'MPC already has {len(scalars)} scalar and {len(vectors)} vector params')

# ========== Step 2: 重建 MF_RevivalLogic ==========
print('Rebuilding MF_RevivalLogic...')
mf = unreal.load_asset('/Game/ECHO/Materials/MF_RevivalLogic')

# 清空现有表达式
mel.delete_all_material_expressions_in_function(mf)

# 创建节点 - 使用最新的 MPC 引用
world_pos = mel.create_material_expression_in_function(mf, unreal.MaterialExpressionWorldPosition, -600, 0)

center_param = mel.create_material_expression_in_function(mf, unreal.MaterialExpressionCollectionParameter, -600, 100)
center_param.set_editor_property('collection', mpc)
center_param.set_editor_property('parameter_name', unreal.Name('RevivalCenter'))

radius_param = mel.create_material_expression_in_function(mf, unreal.MaterialExpressionCollectionParameter, -400, 200)
radius_param.set_editor_property('collection', mpc)
radius_param.set_editor_property('parameter_name', unreal.Name('RevivalRadius'))

distance_node = mel.create_material_expression_in_function(mf, unreal.MaterialExpressionDistance, -300, 50)
divide_node = mel.create_material_expression_in_function(mf, unreal.MaterialExpressionDivide, -100, 100)
saturate_node = mel.create_material_expression_in_function(mf, unreal.MaterialExpressionSaturate, 100, 100)
one_minus_node = mel.create_material_expression_in_function(mf, unreal.MaterialExpressionOneMinus, 300, 100)

output_node = mel.create_material_expression_in_function(mf, unreal.MaterialExpressionFunctionOutput, 500, 100)
output_node.set_editor_property('output_name', 'RevivalMask')

# 连接
mel.connect_material_expressions(world_pos, '', distance_node, 'A')
mel.connect_material_expressions(center_param, '', distance_node, 'B')
mel.connect_material_expressions(distance_node, '', divide_node, 'A')
mel.connect_material_expressions(radius_param, '', divide_node, 'B')
mel.connect_material_expressions(divide_node, '', saturate_node, '')
mel.connect_material_expressions(saturate_node, '', one_minus_node, '')
mel.connect_material_expressions(one_minus_node, '', output_node, '')

unreal.EditorAssetLibrary.save_asset('/Game/ECHO/Materials/MF_RevivalLogic')
print('MF_RevivalLogic rebuilt!')

# ========== Step 3: 重编译材质 ==========
print('Recompiling M_Env_Revival...')
mat = unreal.load_asset('/Game/ECHO/Materials/M_Env_Revival')
mel.recompile_material(mat)
unreal.EditorAssetLibrary.save_asset('/Game/ECHO/Materials/M_Env_Revival')
print('Done! Check for compilation errors.')


