// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "McpAutomationBridgeSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMcpAutomationBridgeSubsystem() {}

// ********** Begin Cross Module References ********************************************************
EDITORSUBSYSTEM_API UClass* Z_Construct_UClass_UEditorSubsystem();
MCPAUTOMATIONBRIDGE_API UClass* Z_Construct_UClass_UMcpAutomationBridgeSubsystem();
MCPAUTOMATIONBRIDGE_API UClass* Z_Construct_UClass_UMcpAutomationBridgeSubsystem_NoRegister();
MCPAUTOMATIONBRIDGE_API UEnum* Z_Construct_UEnum_McpAutomationBridge_EMcpAutomationBridgeState();
MCPAUTOMATIONBRIDGE_API UFunction* Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature();
MCPAUTOMATIONBRIDGE_API UScriptStruct* Z_Construct_UScriptStruct_FMcpAutomationMessage();
UPackage* Z_Construct_UPackage__Script_McpAutomationBridge();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EMcpAutomationBridgeState *************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EMcpAutomationBridgeState;
static UEnum* EMcpAutomationBridgeState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EMcpAutomationBridgeState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EMcpAutomationBridgeState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_McpAutomationBridge_EMcpAutomationBridgeState, (UObject*)Z_Construct_UPackage__Script_McpAutomationBridge(), TEXT("EMcpAutomationBridgeState"));
	}
	return Z_Registration_Info_UEnum_EMcpAutomationBridgeState.OuterSingleton;
}
template<> MCPAUTOMATIONBRIDGE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMcpAutomationBridgeState>()
{
	return EMcpAutomationBridgeState_StaticEnum();
}
struct Z_Construct_UEnum_McpAutomationBridge_EMcpAutomationBridgeState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Connected.Name", "EMcpAutomationBridgeState::Connected" },
		{ "Connecting.Name", "EMcpAutomationBridgeState::Connecting" },
		{ "Disconnected.Name", "EMcpAutomationBridgeState::Disconnected" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSubsystem.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EMcpAutomationBridgeState::Disconnected", (int64)EMcpAutomationBridgeState::Disconnected },
		{ "EMcpAutomationBridgeState::Connecting", (int64)EMcpAutomationBridgeState::Connecting },
		{ "EMcpAutomationBridgeState::Connected", (int64)EMcpAutomationBridgeState::Connected },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_McpAutomationBridge_EMcpAutomationBridgeState_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_McpAutomationBridge_EMcpAutomationBridgeState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_McpAutomationBridge,
	nullptr,
	"EMcpAutomationBridgeState",
	"EMcpAutomationBridgeState",
	Z_Construct_UEnum_McpAutomationBridge_EMcpAutomationBridgeState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_McpAutomationBridge_EMcpAutomationBridgeState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_McpAutomationBridge_EMcpAutomationBridgeState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_McpAutomationBridge_EMcpAutomationBridgeState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_McpAutomationBridge_EMcpAutomationBridgeState()
{
	if (!Z_Registration_Info_UEnum_EMcpAutomationBridgeState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EMcpAutomationBridgeState.InnerSingleton, Z_Construct_UEnum_McpAutomationBridge_EMcpAutomationBridgeState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EMcpAutomationBridgeState.InnerSingleton;
}
// ********** End Enum EMcpAutomationBridgeState ***************************************************

// ********** Begin ScriptStruct FMcpAutomationMessage *********************************************
struct Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FMcpAutomationMessage); }
	static inline consteval int16 GetStructAlignment() { return alignof(FMcpAutomationMessage); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimal payload wrapper for incoming automation messages. */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimal payload wrapper for incoming automation messages." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[] = {
		{ "Category", "MCP Automation" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PayloadJson_MetaData[] = {
		{ "Category", "MCP Automation" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FMcpAutomationMessage constinit property declarations *************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Type;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PayloadJson;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FMcpAutomationMessage constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMcpAutomationMessage>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMcpAutomationMessage;
class UScriptStruct* FMcpAutomationMessage::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMcpAutomationMessage.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMcpAutomationMessage.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMcpAutomationMessage, (UObject*)Z_Construct_UPackage__Script_McpAutomationBridge(), TEXT("McpAutomationMessage"));
	}
	return Z_Registration_Info_UScriptStruct_FMcpAutomationMessage.OuterSingleton;
	}

// ********** Begin ScriptStruct FMcpAutomationMessage Property Definitions ************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMcpAutomationMessage, Type), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Type_MetaData), NewProp_Type_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::NewProp_PayloadJson = { "PayloadJson", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMcpAutomationMessage, PayloadJson), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PayloadJson_MetaData), NewProp_PayloadJson_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::NewProp_PayloadJson,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FMcpAutomationMessage Property Definitions **************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_McpAutomationBridge,
	nullptr,
	&NewStructOps,
	"McpAutomationMessage",
	Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::PropPointers),
	sizeof(FMcpAutomationMessage),
	alignof(FMcpAutomationMessage),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMcpAutomationMessage()
{
	if (!Z_Registration_Info_UScriptStruct_FMcpAutomationMessage.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMcpAutomationMessage.InnerSingleton, Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FMcpAutomationMessage.InnerSingleton);
}
// ********** End ScriptStruct FMcpAutomationMessage ***********************************************

// ********** Begin Delegate FMcpAutomationMessageReceived *****************************************
struct Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics
{
	struct _Script_McpAutomationBridge_eventMcpAutomationMessageReceived_Parms
	{
		FMcpAutomationMessage Message;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FMcpAutomationMessageReceived constinit property declarations *********
	static const UECodeGen_Private::FStructPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FMcpAutomationMessageReceived constinit property declarations ***********
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FMcpAutomationMessageReceived Property Definitions ********************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_McpAutomationBridge_eventMcpAutomationMessageReceived_Parms, Message), Z_Construct_UScriptStruct_FMcpAutomationMessage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) }; // 2779437112
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FMcpAutomationMessageReceived Property Definitions **********************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_McpAutomationBridge, nullptr, "McpAutomationMessageReceived__DelegateSignature", 	Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics::_Script_McpAutomationBridge_eventMcpAutomationMessageReceived_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics::_Script_McpAutomationBridge_eventMcpAutomationMessageReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FMcpAutomationMessageReceived_DelegateWrapper(const FMulticastScriptDelegate& McpAutomationMessageReceived, FMcpAutomationMessage const& Message)
{
	struct _Script_McpAutomationBridge_eventMcpAutomationMessageReceived_Parms
	{
		FMcpAutomationMessage Message;
	};
	_Script_McpAutomationBridge_eventMcpAutomationMessageReceived_Parms Parms;
	Parms.Message=Message;
	McpAutomationMessageReceived.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FMcpAutomationMessageReceived *******************************************

// ********** Begin Class UMcpAutomationBridgeSubsystem Function GetBridgeState ********************
struct Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics
{
	struct McpAutomationBridgeSubsystem_eventGetBridgeState_Parms
	{
		EMcpAutomationBridgeState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "MCP Automation" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetBridgeState constinit property declarations ************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetBridgeState constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetBridgeState Property Definitions ***********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(McpAutomationBridgeSubsystem_eventGetBridgeState_Parms, ReturnValue), Z_Construct_UEnum_McpAutomationBridge_EMcpAutomationBridgeState, METADATA_PARAMS(0, nullptr) }; // 2791399219
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::PropPointers) < 2048);
// ********** End Function GetBridgeState Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMcpAutomationBridgeSubsystem, nullptr, "GetBridgeState", 	Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::McpAutomationBridgeSubsystem_eventGetBridgeState_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::McpAutomationBridgeSubsystem_eventGetBridgeState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMcpAutomationBridgeSubsystem::execGetBridgeState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EMcpAutomationBridgeState*)Z_Param__Result=P_THIS->GetBridgeState();
	P_NATIVE_END;
}
// ********** End Class UMcpAutomationBridgeSubsystem Function GetBridgeState **********************

// ********** Begin Class UMcpAutomationBridgeSubsystem Function IsBridgeActive ********************
struct Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics
{
	struct McpAutomationBridgeSubsystem_eventIsBridgeActive_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "MCP Automation" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsBridgeActive constinit property declarations ************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsBridgeActive constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsBridgeActive Property Definitions ***********************************
void Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((McpAutomationBridgeSubsystem_eventIsBridgeActive_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(McpAutomationBridgeSubsystem_eventIsBridgeActive_Parms), &Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::PropPointers) < 2048);
// ********** End Function IsBridgeActive Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMcpAutomationBridgeSubsystem, nullptr, "IsBridgeActive", 	Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::McpAutomationBridgeSubsystem_eventIsBridgeActive_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::McpAutomationBridgeSubsystem_eventIsBridgeActive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMcpAutomationBridgeSubsystem::execIsBridgeActive)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsBridgeActive();
	P_NATIVE_END;
}
// ********** End Class UMcpAutomationBridgeSubsystem Function IsBridgeActive **********************

// ********** Begin Class UMcpAutomationBridgeSubsystem Function SendRawMessage ********************
struct Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics
{
	struct McpAutomationBridgeSubsystem_eventSendRawMessage_Parms
	{
		FString Message;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "MCP Automation" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SendRawMessage constinit property declarations ************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SendRawMessage constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SendRawMessage Property Definitions ***********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(McpAutomationBridgeSubsystem_eventSendRawMessage_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
void Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((McpAutomationBridgeSubsystem_eventSendRawMessage_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(McpAutomationBridgeSubsystem_eventSendRawMessage_Parms), &Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::NewProp_Message,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::PropPointers) < 2048);
// ********** End Function SendRawMessage Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMcpAutomationBridgeSubsystem, nullptr, "SendRawMessage", 	Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::McpAutomationBridgeSubsystem_eventSendRawMessage_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::McpAutomationBridgeSubsystem_eventSendRawMessage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMcpAutomationBridgeSubsystem::execSendRawMessage)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Message);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->SendRawMessage(Z_Param_Message);
	P_NATIVE_END;
}
// ********** End Class UMcpAutomationBridgeSubsystem Function SendRawMessage **********************

// ********** Begin Class UMcpAutomationBridgeSubsystem ********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UMcpAutomationBridgeSubsystem;
UClass* UMcpAutomationBridgeSubsystem::GetPrivateStaticClass()
{
	using TClass = UMcpAutomationBridgeSubsystem;
	if (!Z_Registration_Info_UClass_UMcpAutomationBridgeSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("McpAutomationBridgeSubsystem"),
			Z_Registration_Info_UClass_UMcpAutomationBridgeSubsystem.InnerSingleton,
			StaticRegisterNativesUMcpAutomationBridgeSubsystem,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UMcpAutomationBridgeSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UMcpAutomationBridgeSubsystem_NoRegister()
{
	return UMcpAutomationBridgeSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "McpAutomationBridgeSubsystem.h" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnMessageReceived_MetaData[] = {
		{ "Category", "MCP Automation" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UMcpAutomationBridgeSubsystem constinit property declarations ************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnMessageReceived;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UMcpAutomationBridgeSubsystem constinit property declarations **************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetBridgeState"), .Pointer = &UMcpAutomationBridgeSubsystem::execGetBridgeState },
		{ .NameUTF8 = UTF8TEXT("IsBridgeActive"), .Pointer = &UMcpAutomationBridgeSubsystem::execIsBridgeActive },
		{ .NameUTF8 = UTF8TEXT("SendRawMessage"), .Pointer = &UMcpAutomationBridgeSubsystem::execSendRawMessage },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_GetBridgeState, "GetBridgeState" }, // 2250417370
		{ &Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_IsBridgeActive, "IsBridgeActive" }, // 811280084
		{ &Z_Construct_UFunction_UMcpAutomationBridgeSubsystem_SendRawMessage, "SendRawMessage" }, // 2022813434
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMcpAutomationBridgeSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics

// ********** Begin Class UMcpAutomationBridgeSubsystem Property Definitions ***********************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::NewProp_OnMessageReceived = { "OnMessageReceived", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSubsystem, OnMessageReceived), Z_Construct_UDelegateFunction_McpAutomationBridge_McpAutomationMessageReceived__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnMessageReceived_MetaData), NewProp_OnMessageReceived_MetaData) }; // 2049954202
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::NewProp_OnMessageReceived,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::PropPointers) < 2048);
// ********** End Class UMcpAutomationBridgeSubsystem Property Definitions *************************
UObject* (*const Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UEditorSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_McpAutomationBridge,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::ClassParams = {
	&UMcpAutomationBridgeSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::PropPointers),
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::Class_MetaDataParams)
};
void UMcpAutomationBridgeSubsystem::StaticRegisterNativesUMcpAutomationBridgeSubsystem()
{
	UClass* Class = UMcpAutomationBridgeSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::Funcs));
}
UClass* Z_Construct_UClass_UMcpAutomationBridgeSubsystem()
{
	if (!Z_Registration_Info_UClass_UMcpAutomationBridgeSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMcpAutomationBridgeSubsystem.OuterSingleton, Z_Construct_UClass_UMcpAutomationBridgeSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMcpAutomationBridgeSubsystem.OuterSingleton;
}
UMcpAutomationBridgeSubsystem::UMcpAutomationBridgeSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UMcpAutomationBridgeSubsystem);
UMcpAutomationBridgeSubsystem::~UMcpAutomationBridgeSubsystem() {}
// ********** End Class UMcpAutomationBridgeSubsystem **********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h__Script_McpAutomationBridge_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EMcpAutomationBridgeState_StaticEnum, TEXT("EMcpAutomationBridgeState"), &Z_Registration_Info_UEnum_EMcpAutomationBridgeState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2791399219U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FMcpAutomationMessage::StaticStruct, Z_Construct_UScriptStruct_FMcpAutomationMessage_Statics::NewStructOps, TEXT("McpAutomationMessage"),&Z_Registration_Info_UScriptStruct_FMcpAutomationMessage, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMcpAutomationMessage), 2779437112U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMcpAutomationBridgeSubsystem, UMcpAutomationBridgeSubsystem::StaticClass, TEXT("UMcpAutomationBridgeSubsystem"), &Z_Registration_Info_UClass_UMcpAutomationBridgeSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMcpAutomationBridgeSubsystem), 4112867120U) },
	};
}; // Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h__Script_McpAutomationBridge_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h__Script_McpAutomationBridge_954916310{
	TEXT("/Script/McpAutomationBridge"),
	Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h__Script_McpAutomationBridge_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h__Script_McpAutomationBridge_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h__Script_McpAutomationBridge_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h__Script_McpAutomationBridge_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h__Script_McpAutomationBridge_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSubsystem_h__Script_McpAutomationBridge_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
