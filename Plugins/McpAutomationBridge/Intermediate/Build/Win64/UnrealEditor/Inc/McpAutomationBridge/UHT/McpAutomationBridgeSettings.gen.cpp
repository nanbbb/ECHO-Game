// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "McpAutomationBridgeSettings.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMcpAutomationBridgeSettings() {}

// ********** Begin Cross Module References ********************************************************
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
MCPAUTOMATIONBRIDGE_API UClass* Z_Construct_UClass_UMcpAutomationBridgeSettings();
MCPAUTOMATIONBRIDGE_API UClass* Z_Construct_UClass_UMcpAutomationBridgeSettings_NoRegister();
MCPAUTOMATIONBRIDGE_API UEnum* Z_Construct_UEnum_McpAutomationBridge_EMcpLogVerbosity();
UPackage* Z_Construct_UPackage__Script_McpAutomationBridge();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EMcpLogVerbosity **********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EMcpLogVerbosity;
static UEnum* EMcpLogVerbosity_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EMcpLogVerbosity.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EMcpLogVerbosity.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_McpAutomationBridge_EMcpLogVerbosity, (UObject*)Z_Construct_UPackage__Script_McpAutomationBridge(), TEXT("EMcpLogVerbosity"));
	}
	return Z_Registration_Info_UEnum_EMcpLogVerbosity.OuterSingleton;
}
template<> MCPAUTOMATIONBRIDGE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMcpLogVerbosity>()
{
	return EMcpLogVerbosity_StaticEnum();
}
struct Z_Construct_UEnum_McpAutomationBridge_EMcpLogVerbosity_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Store these settings in the project's config (DefaultGame.ini) and expose\n// them in Project Settings -> Plugins. Use defaultconfig so the values are\n// written to the project's default INI file when persisted.\n" },
#endif
		{ "Display.DisplayName", "Display" },
		{ "Display.Name", "EMcpLogVerbosity::Display" },
		{ "Error.DisplayName", "Error" },
		{ "Error.Name", "EMcpLogVerbosity::Error" },
		{ "Fatal.DisplayName", "Fatal" },
		{ "Fatal.Name", "EMcpLogVerbosity::Fatal" },
		{ "Log.DisplayName", "Log" },
		{ "Log.Name", "EMcpLogVerbosity::Log" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
		{ "NoLogging.DisplayName", "No Logging" },
		{ "NoLogging.Name", "EMcpLogVerbosity::NoLogging" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Store these settings in the project's config (DefaultGame.ini) and expose\nthem in Project Settings -> Plugins. Use defaultconfig so the values are\nwritten to the project's default INI file when persisted." },
#endif
		{ "Verbose.DisplayName", "Verbose" },
		{ "Verbose.Name", "EMcpLogVerbosity::Verbose" },
		{ "VeryVerbose.DisplayName", "VeryVerbose" },
		{ "VeryVerbose.Name", "EMcpLogVerbosity::VeryVerbose" },
		{ "Warning.DisplayName", "Warning" },
		{ "Warning.Name", "EMcpLogVerbosity::Warning" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EMcpLogVerbosity::NoLogging", (int64)EMcpLogVerbosity::NoLogging },
		{ "EMcpLogVerbosity::Fatal", (int64)EMcpLogVerbosity::Fatal },
		{ "EMcpLogVerbosity::Error", (int64)EMcpLogVerbosity::Error },
		{ "EMcpLogVerbosity::Warning", (int64)EMcpLogVerbosity::Warning },
		{ "EMcpLogVerbosity::Display", (int64)EMcpLogVerbosity::Display },
		{ "EMcpLogVerbosity::Log", (int64)EMcpLogVerbosity::Log },
		{ "EMcpLogVerbosity::Verbose", (int64)EMcpLogVerbosity::Verbose },
		{ "EMcpLogVerbosity::VeryVerbose", (int64)EMcpLogVerbosity::VeryVerbose },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_McpAutomationBridge_EMcpLogVerbosity_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_McpAutomationBridge_EMcpLogVerbosity_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_McpAutomationBridge,
	nullptr,
	"EMcpLogVerbosity",
	"EMcpLogVerbosity",
	Z_Construct_UEnum_McpAutomationBridge_EMcpLogVerbosity_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_McpAutomationBridge_EMcpLogVerbosity_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_McpAutomationBridge_EMcpLogVerbosity_Statics::Enum_MetaDataParams), Z_Construct_UEnum_McpAutomationBridge_EMcpLogVerbosity_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_McpAutomationBridge_EMcpLogVerbosity()
{
	if (!Z_Registration_Info_UEnum_EMcpLogVerbosity.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EMcpLogVerbosity.InnerSingleton, Z_Construct_UEnum_McpAutomationBridge_EMcpLogVerbosity_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EMcpLogVerbosity.InnerSingleton;
}
// ********** End Enum EMcpLogVerbosity ************************************************************

// ********** Begin Class UMcpAutomationBridgeSettings *********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UMcpAutomationBridgeSettings;
UClass* UMcpAutomationBridgeSettings::GetPrivateStaticClass()
{
	using TClass = UMcpAutomationBridgeSettings;
	if (!Z_Registration_Info_UClass_UMcpAutomationBridgeSettings.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("McpAutomationBridgeSettings"),
			Z_Registration_Info_UClass_UMcpAutomationBridgeSettings.InnerSingleton,
			StaticRegisterNativesUMcpAutomationBridgeSettings,
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
	return Z_Registration_Info_UClass_UMcpAutomationBridgeSettings.InnerSingleton;
}
UClass* Z_Construct_UClass_UMcpAutomationBridgeSettings_NoRegister()
{
	return UMcpAutomationBridgeSettings::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "DisplayName", "MCP Automation Bridge" },
		{ "IncludePath", "McpAutomationBridgeSettings.h" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAlwaysListen_MetaData[] = {
		{ "Category", "Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, the plugin will always start a listening WebSocket server on startup and accept inbound MCP connections. */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, the plugin will always start a listening WebSocket server on startup and accept inbound MCP connections." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ListenHost_MetaData[] = {
		{ "Category", "Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Host to bind the listening sockets. Use 0.0.0.0 to accept connections from any interface. */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Host to bind the listening sockets. Use 0.0.0.0 to accept connections from any interface." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ListenPorts_MetaData[] = {
		{ "Category", "Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Comma-separated list of ports to listen on. Example: \"8090,8091\" */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Comma-separated list of ports to listen on. Example: \"8090,8091\"" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EndpointUrl_MetaData[] = {
		{ "Category", "Connection" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CapabilityToken_MetaData[] = {
		{ "Category", "Security" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AutoReconnectDelay_MetaData[] = {
		{ "Category", "Connection" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClientPort_MetaData[] = {
		{ "Category", "Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Port the plugin expects the MCP server to use when the tool connects back as a client (optional). */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Port the plugin expects the MCP server to use when the tool connects back as a client (optional)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRequireCapabilityToken_MetaData[] = {
		{ "Category", "Security" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** When true, require a capability token for incoming connections (enforces matching token). */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When true, require a capability token for incoming connections (enforces matching token)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LogVerbosity_MetaData[] = {
		{ "Category", "Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Optional runtime log verbosity override exposed via Project Settings. */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional runtime log verbosity override exposed via Project Settings." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bApplyLogVerbosityToAll_MetaData[] = {
		{ "Category", "Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** When true, apply the selected LogVerbosity to this plugin's log category at runtime. */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When true, apply the selected LogVerbosity to this plugin's log category at runtime." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableSocketTelemetry_MetaData[] = {
		{ "Category", "Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** When true, emit extra per-socket telemetry for control/response delivery\n     * attempts. This is intended for short-term debugging of intermittent\n     * delivery failures and is off by default to avoid log spam. When enabled\n     * the subsystem will raise aggregated delivery summaries to Log level and\n     * include per-socket details for inspection.\n     */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When true, emit extra per-socket telemetry for control/response delivery\nattempts. This is intended for short-term debugging of intermittent\ndelivery failures and is off by default to avoid log spam. When enabled\nthe subsystem will raise aggregated delivery summaries to Log level and\ninclude per-socket details for inspection." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bMultiListen_MetaData[] = {
		{ "Category", "Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** When true, the plugin will open multiple listen sockets provided by ListenPorts. */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When true, the plugin will open multiple listen sockets provided by ListenPorts." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeartbeatIntervalMs_MetaData[] = {
		{ "Category", "Heartbeat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Heartbeat interval to advertise to connected clients (milliseconds). If <= 0, server default will be used. */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Heartbeat interval to advertise to connected clients (milliseconds). If <= 0, server default will be used." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeartbeatTimeoutSeconds_MetaData[] = {
		{ "Category", "Heartbeat" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** How many seconds without a heartbeat before a connection is considered timed out. If <= 0, heartbeat timeout checking is disabled. */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How many seconds without a heartbeat before a connection is considered timed out. If <= 0, heartbeat timeout checking is disabled." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ListenBacklog_MetaData[] = {
		{ "Category", "Connection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Backlog parameter passed to listen() when creating the listening socket. If <= 0, engine default will be used. */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Backlog parameter passed to listen() when creating the listening socket. If <= 0, engine default will be used." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AcceptSleepSeconds_MetaData[] = {
		{ "Category", "Connection" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** How long (seconds) the server socket thread should sleep when no incoming connection; small values reduce CPU but increase latency. If <= 0, engine default will be used. */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How long (seconds) the server socket thread should sleep when no incoming connection; small values reduce CPU but increase latency. If <= 0, engine default will be used." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TickerIntervalSeconds_MetaData[] = {
		{ "Category", "Debug" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Frequency, in seconds, for the subsystem ticker. If <= 0, engine default will be used. */" },
#endif
		{ "ModuleRelativePath", "Public/McpAutomationBridgeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Frequency, in seconds, for the subsystem ticker. If <= 0, engine default will be used." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UMcpAutomationBridgeSettings constinit property declarations *************
	static void NewProp_bAlwaysListen_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAlwaysListen;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ListenHost;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ListenPorts;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EndpointUrl;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CapabilityToken;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AutoReconnectDelay;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientPort;
	static void NewProp_bRequireCapabilityToken_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRequireCapabilityToken;
	static const UECodeGen_Private::FBytePropertyParams NewProp_LogVerbosity_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_LogVerbosity;
	static void NewProp_bApplyLogVerbosityToAll_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bApplyLogVerbosityToAll;
	static void NewProp_bEnableSocketTelemetry_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableSocketTelemetry;
	static void NewProp_bMultiListen_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bMultiListen;
	static const UECodeGen_Private::FIntPropertyParams NewProp_HeartbeatIntervalMs;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HeartbeatTimeoutSeconds;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ListenBacklog;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AcceptSleepSeconds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TickerIntervalSeconds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UMcpAutomationBridgeSettings constinit property declarations ***************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMcpAutomationBridgeSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics

// ********** Begin Class UMcpAutomationBridgeSettings Property Definitions ************************
void Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bAlwaysListen_SetBit(void* Obj)
{
	((UMcpAutomationBridgeSettings*)Obj)->bAlwaysListen = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bAlwaysListen = { "bAlwaysListen", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UMcpAutomationBridgeSettings), &Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bAlwaysListen_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAlwaysListen_MetaData), NewProp_bAlwaysListen_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_ListenHost = { "ListenHost", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSettings, ListenHost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ListenHost_MetaData), NewProp_ListenHost_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_ListenPorts = { "ListenPorts", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSettings, ListenPorts), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ListenPorts_MetaData), NewProp_ListenPorts_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_EndpointUrl = { "EndpointUrl", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSettings, EndpointUrl), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EndpointUrl_MetaData), NewProp_EndpointUrl_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_CapabilityToken = { "CapabilityToken", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSettings, CapabilityToken), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CapabilityToken_MetaData), NewProp_CapabilityToken_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_AutoReconnectDelay = { "AutoReconnectDelay", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSettings, AutoReconnectDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AutoReconnectDelay_MetaData), NewProp_AutoReconnectDelay_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_ClientPort = { "ClientPort", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSettings, ClientPort), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClientPort_MetaData), NewProp_ClientPort_MetaData) };
void Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bRequireCapabilityToken_SetBit(void* Obj)
{
	((UMcpAutomationBridgeSettings*)Obj)->bRequireCapabilityToken = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bRequireCapabilityToken = { "bRequireCapabilityToken", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UMcpAutomationBridgeSettings), &Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bRequireCapabilityToken_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRequireCapabilityToken_MetaData), NewProp_bRequireCapabilityToken_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_LogVerbosity_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_LogVerbosity = { "LogVerbosity", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSettings, LogVerbosity), Z_Construct_UEnum_McpAutomationBridge_EMcpLogVerbosity, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LogVerbosity_MetaData), NewProp_LogVerbosity_MetaData) }; // 1127334271
void Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bApplyLogVerbosityToAll_SetBit(void* Obj)
{
	((UMcpAutomationBridgeSettings*)Obj)->bApplyLogVerbosityToAll = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bApplyLogVerbosityToAll = { "bApplyLogVerbosityToAll", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UMcpAutomationBridgeSettings), &Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bApplyLogVerbosityToAll_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bApplyLogVerbosityToAll_MetaData), NewProp_bApplyLogVerbosityToAll_MetaData) };
void Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bEnableSocketTelemetry_SetBit(void* Obj)
{
	((UMcpAutomationBridgeSettings*)Obj)->bEnableSocketTelemetry = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bEnableSocketTelemetry = { "bEnableSocketTelemetry", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UMcpAutomationBridgeSettings), &Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bEnableSocketTelemetry_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableSocketTelemetry_MetaData), NewProp_bEnableSocketTelemetry_MetaData) };
void Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bMultiListen_SetBit(void* Obj)
{
	((UMcpAutomationBridgeSettings*)Obj)->bMultiListen = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bMultiListen = { "bMultiListen", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UMcpAutomationBridgeSettings), &Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bMultiListen_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bMultiListen_MetaData), NewProp_bMultiListen_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_HeartbeatIntervalMs = { "HeartbeatIntervalMs", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSettings, HeartbeatIntervalMs), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeartbeatIntervalMs_MetaData), NewProp_HeartbeatIntervalMs_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_HeartbeatTimeoutSeconds = { "HeartbeatTimeoutSeconds", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSettings, HeartbeatTimeoutSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeartbeatTimeoutSeconds_MetaData), NewProp_HeartbeatTimeoutSeconds_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_ListenBacklog = { "ListenBacklog", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSettings, ListenBacklog), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ListenBacklog_MetaData), NewProp_ListenBacklog_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_AcceptSleepSeconds = { "AcceptSleepSeconds", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSettings, AcceptSleepSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AcceptSleepSeconds_MetaData), NewProp_AcceptSleepSeconds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_TickerIntervalSeconds = { "TickerIntervalSeconds", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMcpAutomationBridgeSettings, TickerIntervalSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TickerIntervalSeconds_MetaData), NewProp_TickerIntervalSeconds_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bAlwaysListen,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_ListenHost,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_ListenPorts,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_EndpointUrl,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_CapabilityToken,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_AutoReconnectDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_ClientPort,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bRequireCapabilityToken,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_LogVerbosity_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_LogVerbosity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bApplyLogVerbosityToAll,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bEnableSocketTelemetry,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_bMultiListen,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_HeartbeatIntervalMs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_HeartbeatTimeoutSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_ListenBacklog,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_AcceptSleepSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::NewProp_TickerIntervalSeconds,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::PropPointers) < 2048);
// ********** End Class UMcpAutomationBridgeSettings Property Definitions **************************
UObject* (*const Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_McpAutomationBridge,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::ClassParams = {
	&UMcpAutomationBridgeSettings::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::PropPointers),
	0,
	0x001000A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::Class_MetaDataParams)
};
void UMcpAutomationBridgeSettings::StaticRegisterNativesUMcpAutomationBridgeSettings()
{
}
UClass* Z_Construct_UClass_UMcpAutomationBridgeSettings()
{
	if (!Z_Registration_Info_UClass_UMcpAutomationBridgeSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMcpAutomationBridgeSettings.OuterSingleton, Z_Construct_UClass_UMcpAutomationBridgeSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMcpAutomationBridgeSettings.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UMcpAutomationBridgeSettings);
UMcpAutomationBridgeSettings::~UMcpAutomationBridgeSettings() {}
// ********** End Class UMcpAutomationBridgeSettings ***********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h__Script_McpAutomationBridge_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EMcpLogVerbosity_StaticEnum, TEXT("EMcpLogVerbosity"), &Z_Registration_Info_UEnum_EMcpLogVerbosity, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1127334271U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMcpAutomationBridgeSettings, UMcpAutomationBridgeSettings::StaticClass, TEXT("UMcpAutomationBridgeSettings"), &Z_Registration_Info_UClass_UMcpAutomationBridgeSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMcpAutomationBridgeSettings), 1907716527U) },
	};
}; // Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h__Script_McpAutomationBridge_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h__Script_McpAutomationBridge_3056294097{
	TEXT("/Script/McpAutomationBridge"),
	Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h__Script_McpAutomationBridge_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h__Script_McpAutomationBridge_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h__Script_McpAutomationBridge_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ECHO_ECHO_Plugins_McpAutomationBridge_Source_McpAutomationBridge_Public_McpAutomationBridgeSettings_h__Script_McpAutomationBridge_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
