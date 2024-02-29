// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StateMachine/Public/StateBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStateBase() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	STATEMACHINE_API UClass* Z_Construct_UClass_UStateBase();
	STATEMACHINE_API UClass* Z_Construct_UClass_UStateBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_StateMachine();
// End Cross Module References
	void UStateBase::StaticRegisterNativesUStateBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UStateBase);
	UClass* Z_Construct_UClass_UStateBase_NoRegister()
	{
		return UStateBase::StaticClass();
	}
	struct Z_Construct_UClass_UStateBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bCanTickState_MetaData[];
#endif
		static void NewProp_bCanTickState_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bCanTickState;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bCanRepeat_MetaData[];
#endif
		static void NewProp_bCanRepeat_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bCanRepeat;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StateDisplayName_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_StateDisplayName;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStateBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_StateMachine,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStateBase_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "StateBase.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/StateBase.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStateBase_Statics::NewProp_bCanTickState_MetaData[] = {
		{ "Category", "StateBase" },
		{ "ModuleRelativePath", "Public/StateBase.h" },
	};
#endif
	void Z_Construct_UClass_UStateBase_Statics::NewProp_bCanTickState_SetBit(void* Obj)
	{
		((UStateBase*)Obj)->bCanTickState = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStateBase_Statics::NewProp_bCanTickState = { "bCanTickState", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(UStateBase), &Z_Construct_UClass_UStateBase_Statics::NewProp_bCanTickState_SetBit, METADATA_PARAMS(Z_Construct_UClass_UStateBase_Statics::NewProp_bCanTickState_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStateBase_Statics::NewProp_bCanTickState_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStateBase_Statics::NewProp_bCanRepeat_MetaData[] = {
		{ "Category", "StateBase" },
		{ "ModuleRelativePath", "Public/StateBase.h" },
	};
#endif
	void Z_Construct_UClass_UStateBase_Statics::NewProp_bCanRepeat_SetBit(void* Obj)
	{
		((UStateBase*)Obj)->bCanRepeat = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStateBase_Statics::NewProp_bCanRepeat = { "bCanRepeat", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(UStateBase), &Z_Construct_UClass_UStateBase_Statics::NewProp_bCanRepeat_SetBit, METADATA_PARAMS(Z_Construct_UClass_UStateBase_Statics::NewProp_bCanRepeat_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStateBase_Statics::NewProp_bCanRepeat_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStateBase_Statics::NewProp_StateDisplayName_MetaData[] = {
		{ "Category", "StateBase" },
		{ "ModuleRelativePath", "Public/StateBase.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UStateBase_Statics::NewProp_StateDisplayName = { "StateDisplayName", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UStateBase, StateDisplayName), METADATA_PARAMS(Z_Construct_UClass_UStateBase_Statics::NewProp_StateDisplayName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UStateBase_Statics::NewProp_StateDisplayName_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStateBase_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStateBase_Statics::NewProp_bCanTickState,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStateBase_Statics::NewProp_bCanRepeat,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStateBase_Statics::NewProp_StateDisplayName,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStateBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStateBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UStateBase_Statics::ClassParams = {
		&UStateBase::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UStateBase_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UStateBase_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UStateBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStateBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStateBase()
	{
		if (!Z_Registration_Info_UClass_UStateBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UStateBase.OuterSingleton, Z_Construct_UClass_UStateBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UStateBase.OuterSingleton;
	}
	template<> STATEMACHINE_API UClass* StaticClass<UStateBase>()
	{
		return UStateBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStateBase);
	UStateBase::~UStateBase() {}
	struct Z_CompiledInDeferFile_FID_projects_TheLandOfFey_Plugins_StateMachine_Source_StateMachine_Public_StateBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_TheLandOfFey_Plugins_StateMachine_Source_StateMachine_Public_StateBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UStateBase, UStateBase::StaticClass, TEXT("UStateBase"), &Z_Registration_Info_UClass_UStateBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UStateBase), 2934090177U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_TheLandOfFey_Plugins_StateMachine_Source_StateMachine_Public_StateBase_h_441894891(TEXT("/Script/StateMachine"),
		Z_CompiledInDeferFile_FID_projects_TheLandOfFey_Plugins_StateMachine_Source_StateMachine_Public_StateBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_projects_TheLandOfFey_Plugins_StateMachine_Source_StateMachine_Public_StateBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
