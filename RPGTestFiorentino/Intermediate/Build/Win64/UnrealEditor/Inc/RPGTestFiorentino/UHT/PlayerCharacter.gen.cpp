// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RPGTestFiorentino/Public/PlayerCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePlayerCharacter() {}
// Cross Module References
	PAPERZD_API UClass* Z_Construct_UClass_APaperZDCharacter();
	RPGTESTFIORENTINO_API UClass* Z_Construct_UClass_APlayerCharacter();
	RPGTESTFIORENTINO_API UClass* Z_Construct_UClass_APlayerCharacter_NoRegister();
	UPackage* Z_Construct_UPackage__Script_RPGTestFiorentino();
// End Cross Module References
	void APlayerCharacter::StaticRegisterNativesAPlayerCharacter()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APlayerCharacter);
	UClass* Z_Construct_UClass_APlayerCharacter_NoRegister()
	{
		return APlayerCharacter::StaticClass();
	}
	struct Z_Construct_UClass_APlayerCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bIsRunning_MetaData[];
#endif
		static void NewProp_bIsRunning_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsRunning;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_APlayerCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APaperZDCharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_RPGTestFiorentino,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APlayerCharacter_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "PlayerCharacter.h" },
		{ "ModuleRelativePath", "Public/PlayerCharacter.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APlayerCharacter_Statics::NewProp_bIsRunning_MetaData[] = {
		{ "Category", "Player" },
		{ "ModuleRelativePath", "Public/PlayerCharacter.h" },
	};
#endif
	void Z_Construct_UClass_APlayerCharacter_Statics::NewProp_bIsRunning_SetBit(void* Obj)
	{
		((APlayerCharacter*)Obj)->bIsRunning = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_bIsRunning = { "bIsRunning", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(APlayerCharacter), &Z_Construct_UClass_APlayerCharacter_Statics::NewProp_bIsRunning_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::NewProp_bIsRunning_MetaData), Z_Construct_UClass_APlayerCharacter_Statics::NewProp_bIsRunning_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APlayerCharacter_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_bIsRunning,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_APlayerCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APlayerCharacter>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_APlayerCharacter_Statics::ClassParams = {
		&APlayerCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_APlayerCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_APlayerCharacter_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_APlayerCharacter()
	{
		if (!Z_Registration_Info_UClass_APlayerCharacter.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APlayerCharacter.OuterSingleton, Z_Construct_UClass_APlayerCharacter_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_APlayerCharacter.OuterSingleton;
	}
	template<> RPGTESTFIORENTINO_API UClass* StaticClass<APlayerCharacter>()
	{
		return APlayerCharacter::StaticClass();
	}
	APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(APlayerCharacter);
	APlayerCharacter::~APlayerCharacter() {}
	struct Z_CompiledInDeferFile_FID_RPGTestFiorentino_Source_RPGTestFiorentino_Public_PlayerCharacter_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RPGTestFiorentino_Source_RPGTestFiorentino_Public_PlayerCharacter_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_APlayerCharacter, APlayerCharacter::StaticClass, TEXT("APlayerCharacter"), &Z_Registration_Info_UClass_APlayerCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APlayerCharacter), 2837177684U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RPGTestFiorentino_Source_RPGTestFiorentino_Public_PlayerCharacter_h_1605661371(TEXT("/Script/RPGTestFiorentino"),
		Z_CompiledInDeferFile_FID_RPGTestFiorentino_Source_RPGTestFiorentino_Public_PlayerCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RPGTestFiorentino_Source_RPGTestFiorentino_Public_PlayerCharacter_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
