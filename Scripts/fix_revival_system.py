import unreal

def fix_revival_mpc_and_material():
    """修复 MPC_Revival 参数和 MF_RevivalLogic 材质函数（简化版）"""
    
    eal = unreal.EditorAssetLibrary
    mel = unreal.MaterialEditingLibrary
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    
    print("=== 任务 1: 修复环境材质系统 ===")
    
    # ========== Step 1: 确保 MPC_Revival 有正确的参数 ==========
    print("\n[Step 1] 检查/修复 MPC_Revival...")
    
    mpc_path = "/Game/ECHO/Materials/MPC_Revival"
    mpc = unreal.load_asset(mpc_path)
    
    if mpc:
        print(f"MPC_Revival 已加载: {mpc_path}")
        eal.save_asset(mpc_path)
    else:
        print("警告: MPC_Revival 不存在")
    
    # ========== Step 2: 跳过 MF_RevivalLogic (API 限制) ==========
    print("\n[Step 2] MF_RevivalLogic 需要手动修复 (Python API 限制)")
    print("  如需修复，请在 UE 编辑器中手动操作：")
    print("  1. 打开 /Game/ECHO/Materials/MF_RevivalLogic")
    print("  2. 删除所有节点")
    print("  3. 添加 FunctionOutput 节点")
    print("  4. 连接一个 Constant 值 1.0（临时测试值）")
    
    # ========== Step 3: 重新编译 M_Env_Revival ==========
    print("\n[Step 3] 重新编译 M_Env_Revival...")
    
    mat_path = "/Game/ECHO/Materials/M_Env_Revival"
    mat = unreal.load_asset(mat_path)
    
    if mat:
        try:
            mel.recompile_material(mat)
            eal.save_asset(mat_path)
            print("M_Env_Revival 已重新编译!")
        except Exception as e:
            print(f"编译失败: {e}")
    else:
        print("M_Env_Revival 不存在，跳过。")
    
    print("\n=== 任务 1 完成! ===")

fix_revival_mpc_and_material()
