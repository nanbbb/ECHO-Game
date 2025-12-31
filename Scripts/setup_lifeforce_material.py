import unreal

def create_lifeforce_material():
    """Create a complete material that responds to LifeForce from MPC_Revival"""
    
    material_path = "/Game/ECHO/Materials/M_LifeForce_Ground"
    mpc_path = "/Game/ECHO/Materials/MPC_Revival"
    
    # Load the material
    material = unreal.EditorAssetLibrary.load_asset(material_path)
    if not material:
        print(f"ERROR: Material not found at {material_path}")
        return
    
    # Load the MPC
    mpc = unreal.EditorAssetLibrary.load_asset(mpc_path)
    if not mpc:
        print(f"ERROR: MPC not found at {mpc_path}")
        return
    
    # Get material editor subsystem
    mel = unreal.MaterialEditingLibrary
    
    # Create nodes
    # 1. Collection Parameter for LifeForce
    param_node = mel.create_material_expression(material, unreal.MaterialExpressionCollectionParameter, -400, 0)
    if param_node:
        param_node.set_editor_property("collection", mpc)
        param_node.set_editor_property("parameter_name", "LifeForce")
        print("Created Collection Parameter node")
    
    # 2. Dead color (dark gray)
    dead_color = mel.create_material_expression(material, unreal.MaterialExpressionConstant3Vector, -400, -150)
    if dead_color:
        dead_color.set_editor_property("constant", unreal.LinearColor(0.05, 0.05, 0.08, 1.0))
        print("Created dead color node")
    
    # 3. Alive color (vibrant green)
    alive_color = mel.create_material_expression(material, unreal.MaterialExpressionConstant3Vector, -400, 150)
    if alive_color:
        alive_color.set_editor_property("constant", unreal.LinearColor(0.1, 0.8, 0.2, 1.0))
        print("Created alive color node")
    
    # 4. Lerp node
    lerp_node = mel.create_material_expression(material, unreal.MaterialExpressionLinearInterpolate, -100, 0)
    if lerp_node:
        print("Created Lerp node")
    
    # Connect nodes
    try:
        # Dead color -> Lerp.A
        mel.connect_material_expressions(dead_color, "", lerp_node, "A")
        print("Connected dead color to Lerp.A")
        
        # Alive color -> Lerp.B
        mel.connect_material_expressions(alive_color, "", lerp_node, "B")
        print("Connected alive color to Lerp.B")
        
        # LifeForce -> Lerp.Alpha
        mel.connect_material_expressions(param_node, "", lerp_node, "Alpha")
        print("Connected LifeForce to Lerp.Alpha")
        
        # Lerp -> Base Color
        mel.connect_material_property(lerp_node, "", unreal.MaterialProperty.MP_BASE_COLOR)
        print("Connected Lerp to Base Color")
        
    except Exception as e:
        print(f"Connection error: {str(e)}")
    
    # Recompile and save
    try:
        mel.recompile_material(material)
        print("Material recompiled")
    except:
        pass
    
    unreal.EditorAssetLibrary.save_asset(material_path)
    print(f"Material saved: {material_path}")
    print("SUCCESS! Material is ready to use.")

if __name__ == "__main__":
    create_lifeforce_material()
