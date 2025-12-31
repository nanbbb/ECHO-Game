import unreal

def add_lifeforce_param():
    mpc_path = "/Game/ECHO/Materials/MPC_Revival"
    mpc = unreal.EditorAssetLibrary.load_asset(mpc_path)
    
    if not mpc:
        print(f"ERROR: Failed to load MPC at {mpc_path}")
        return
    
    # Check if LifeForce param already exists
    scalar_params = mpc.get_editor_property("scalar_parameters")
    for param in scalar_params:
        if param.get_editor_property("parameter_name") == "LifeForce":
            print("LifeForce parameter already exists in MPC_Revival")
            return
    
    # Try to add new parameter
    try:
        new_param = unreal.CollectionScalarParameter()
        new_param.set_editor_property("parameter_name", "LifeForce")
        new_param.set_editor_property("default_value", 1.0)
        scalar_params.append(new_param)
        mpc.set_editor_property("scalar_parameters", scalar_params)
        unreal.EditorAssetLibrary.save_asset(mpc_path)
        print("Successfully added LifeForce parameter to MPC_Revival")
    except Exception as e:
        print(f"ERROR: {str(e)}")
        print("Please manually add 'LifeForce' scalar parameter to MPC_Revival")

if __name__ == "__main__":
    add_lifeforce_param()
