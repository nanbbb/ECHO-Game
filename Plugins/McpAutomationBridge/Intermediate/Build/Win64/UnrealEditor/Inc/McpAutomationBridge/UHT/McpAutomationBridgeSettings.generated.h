// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "McpAutomationBridgeSettings.h"

#ifdef MCPAUTOMATIONBRIDGE_McpAutomationBridgeSettings_generated_h
#error "McpAutomationBridgeSettings.generated.h already included, missing '#pragma once' in McpAutomationBridgeSettings.h"
#endif
#define MCPAUTOMATIONBRIDGE_McpAutomationBridgeSettings_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UMcpAutomationBridgeSettings *********************************************
struct Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics;
MCPAUTOMATIONBRIDGE_API UClass* Z_Construct_UClass_UMcpAutomationBridgeSettings_NoRegister();

#define FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h_26_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMcpAutomationBridgeSettings(); \
	friend struct ::Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MCPAUTOMATIONBRIDGE_API UClass* ::Z_Construct_UClass_UMcpAutomationBridgeSettings_NoRegister(); \
public: \
	DECLARE_CLASS2(UMcpAutomationBridgeSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/McpAutomationBridge"), Z_Construct_UClass_UMcpAutomationBridgeSettings_NoRegister) \
	DECLARE_SERIALIZER(UMcpAutomationBridgeSettings) \
	static constexpr const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h_26_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UMcpAutomationBridgeSettings(UMcpAutomationBridgeSettings&&) = delete; \
	UMcpAutomationBridgeSettings(const UMcpAutomationBridgeSettings&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMcpAutomationBridgeSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMcpAutomationBridgeSettings); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UMcpAutomationBridgeSettings) \
	NO_API virtual ~UMcpAutomationBridgeSettings();


#define FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h_23_PROLOG
#define FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h_26_INCLASS_NO_PURE_DECLS \
	FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h_26_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UMcpAutomationBridgeSettings;

// ********** End Class UMcpAutomationBridgeSettings ***********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h

// ********** Begin Enum EMcpLogVerbosity **********************************************************
#define FOREACH_ENUM_EMCPLOGVERBOSITY(op) \
	op(EMcpLogVerbosity::NoLogging) \
	op(EMcpLogVerbosity::Fatal) \
	op(EMcpLogVerbosity::Error) \
	op(EMcpLogVerbosity::Warning) \
	op(EMcpLogVerbosity::Display) \
	op(EMcpLogVerbosity::Log) \
	op(EMcpLogVerbosity::Verbose) \
	op(EMcpLogVerbosity::VeryVerbose) 

enum class EMcpLogVerbosity : uint8;
template<> struct TIsUEnumClass<EMcpLogVerbosity> { enum { Value = true }; };
template<> MCPAUTOMATIONBRIDGE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMcpLogVerbosity>();
// ********** End Enum EMcpLogVerbosity ************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
