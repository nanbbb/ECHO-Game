// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "McpAutomationBridgeSubsystem.h"

#ifdef MCPAUTOMATIONBRIDGE_McpAutomationBridgeSubsystem_generated_h
#error "McpAutomationBridgeSubsystem.generated.h already included, missing '#pragma once' in McpAutomationBridgeSubsystem.h"
#endif
#define MCPAUTOMATIONBRIDGE_McpAutomationBridgeSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EMcpAutomationBridgeState : uint8;
struct FMcpAutomationMessage;

// ********** Begin ScriptStruct FMcpAutomationMessage *********************************************
struct Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics;
#define FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h_22_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics; \
	static class UScriptStruct* StaticStruct();


struct FMcpAutomationMessage;
// ********** End ScriptStruct FMcpAutomationMessage ***********************************************

// ********** Begin Delegate FMcpAutomationMessageReceived *****************************************
#define FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h_33_DELEGATE \
MCPAUTOMATIONBRIDGE_API void FMcpAutomationMessageReceived_DelegateWrapper(const FMulticastScriptDelegate& McpAutomationMessageReceived, FMcpAutomationMessage const& Message);


// ********** End Delegate FMcpAutomationMessageReceived *******************************************

// ********** Begin Class UMcpAutomationBridgeSubsystem ********************************************
#define FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h_41_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSendRawMessage); \
	DECLARE_FUNCTION(execGetBridgeState); \
	DECLARE_FUNCTION(execIsBridgeActive);


struct Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics;
MCPAUTOMATIONBRIDGE_API UClass* Z_Construct_UClass_UMcpAutomationBridgeSubsystem_NoRegister();

#define FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h_41_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMcpAutomationBridgeSubsystem(); \
	friend struct ::Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MCPAUTOMATIONBRIDGE_API UClass* ::Z_Construct_UClass_UMcpAutomationBridgeSubsystem_NoRegister(); \
public: \
	DECLARE_CLASS2(UMcpAutomationBridgeSubsystem, UEditorSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/McpAutomationBridge"), Z_Construct_UClass_UMcpAutomationBridgeSubsystem_NoRegister) \
	DECLARE_SERIALIZER(UMcpAutomationBridgeSubsystem)


#define FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h_41_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMcpAutomationBridgeSubsystem(); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UMcpAutomationBridgeSubsystem(UMcpAutomationBridgeSubsystem&&) = delete; \
	UMcpAutomationBridgeSubsystem(const UMcpAutomationBridgeSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMcpAutomationBridgeSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMcpAutomationBridgeSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UMcpAutomationBridgeSubsystem) \
	NO_API virtual ~UMcpAutomationBridgeSubsystem();


#define FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h_38_PROLOG
#define FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h_41_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h_41_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h_41_INCLASS_NO_PURE_DECLS \
	FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h_41_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UMcpAutomationBridgeSubsystem;

// ********** End Class UMcpAutomationBridgeSubsystem **********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h

// ********** Begin Enum EMcpAutomationBridgeState *************************************************
#define FOREACH_ENUM_EMCPAUTOMATIONBRIDGESTATE(op) \
	op(EMcpAutomationBridgeState::Disconnected) \
	op(EMcpAutomationBridgeState::Connecting) \
	op(EMcpAutomationBridgeState::Connected) 

enum class EMcpAutomationBridgeState : uint8;
template<> struct TIsUEnumClass<EMcpAutomationBridgeState> { enum { Value = true }; };
template<> MCPAUTOMATIONBRIDGE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMcpAutomationBridgeState>();
// ********** End Enum EMcpAutomationBridgeState ***************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
