import unreal

print('=== 创建运行时 MPC 更新测试 Actor ===')

# 由于 Python 无法在 PIE 中直接运行，我们需要创建一个 Blueprint Actor
# 这里我们先创建一个简单的测试脚本，在编辑器视口中动态更新 MPC

mpc = unreal.load_asset('/Game/ECHO/Materials/MPC_Revival')
ell = unreal.EditorLevelLibrary

# 获取编辑器相机位置
viewport_client = unreal.EditorLevelLibrary.get_level_viewport_camera_info()
# 这会返回 (location, rotation)

if viewport_client:
    cam_loc = viewport_client[0]
    print(f'Camera location: {cam_loc.x}, {cam_loc.y}, {cam_loc.z}')
    
    # 更新 MPC 参数 - 使用相机位置作为中心
    scalars = mpc.get_editor_property('scalar_parameters')
    vectors = mpc.get_editor_property('vector_parameters')
    
    # 设置 RevivalRadius = 800
    new_scalars = []
    for s in scalars:
        if str(s.get_editor_property('parameter_name')) == 'RevivalRadius':
            new_s = unreal.CollectionScalarParameter()
            new_s.set_editor_property('parameter_name', 'RevivalRadius')
            new_s.set_editor_property('default_value', 800.0)
            new_scalars.append(new_s)
        else:
            new_scalars.append(s)
    
    # 设置 RevivalCenter = 相机位置
    new_vectors = []
    for v in vectors:
        if str(v.get_editor_property('parameter_name')) == 'RevivalCenter':
            new_v = unreal.CollectionVectorParameter()
            new_v.set_editor_property('parameter_name', 'RevivalCenter')
            new_v.set_editor_property('default_value', unreal.LinearColor(cam_loc.x, cam_loc.y, cam_loc.z, 1))
            new_vectors.append(new_v)
        else:
            new_vectors.append(v)
    
    mpc.set_editor_property('scalar_parameters', new_scalars)
    mpc.set_editor_property('vector_parameters', new_vectors)
    
    # 保存
    unreal.EditorAssetLibrary.save_asset('/Game/ECHO/Materials/MPC_Revival')
    
    # 重新编译材质
    mat = unreal.load_asset('/Game/ECHO/Materials/M_Env_Revival')
    unreal.MaterialEditingLibrary.recompile_material(mat)
    
    print(f'Updated RevivalCenter to camera location: ({cam_loc.x}, {cam_loc.y}, {cam_loc.z})')
    print('RevivalRadius = 800')
    print('场景效果应该以相机位置为中心变化!')
else:
    print('无法获取相机位置')
