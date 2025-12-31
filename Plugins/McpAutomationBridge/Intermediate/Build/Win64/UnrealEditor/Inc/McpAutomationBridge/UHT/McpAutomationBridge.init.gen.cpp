// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMcpAutomationBridge_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");	MCPAUTOMATIONBRIDGE_API UFunction* Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_McpAutomationBridge;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_McpAutomationBridge()
	{
		if (!Z_Registration_Info_UPackage__Script_McpAutomationBridge.OuterSingleton)
		{
		static UObject* (*const SingletonFuncArray[])() = {
			(UObject* (*)())Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature,
		};
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/McpAutomationBridge",
			SingletonFuncArray,
			UE_ARRAY_COUNT(SingletonFuncArray),
			PKG_CompiledIn | 0x00000040,
			0x65990271,
			0x8D95E3EE,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_McpAutomationBridge.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_McpAutomationBridge.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_McpAutomationBridge(Z_Construct_UPackage__Script_McpAutomationBridge, TEXT("/Script/McpAutomationBridge"), Z_Registration_Info_UPackage__Script_McpAutomationBridge, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x65990271, 0x8D95E3EE));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
