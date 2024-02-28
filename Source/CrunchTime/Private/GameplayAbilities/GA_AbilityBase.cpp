// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/GA_AbilityBase.h"
#include "GameplayAbilities/CAbilityGenericTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Perception/AISenseConfig_Damage.h"

UGA_AbilityBase::UGA_AbilityBase()
{
	ActivationBlockedTags.AddTag(UCAbilityGenericTags::GetDeadTag());
}

void UGA_AbilityBase::SignalDamageStimuliEvent(FGameplayAbilityTargetDataHandle TargetHandle)
{
	TArray<AActor*> Targets = UAbilitySystemBlueprintLibrary::GetAllActorsFromTargetData(TargetHandle);

	//for (AActor* Target : Targets)
	//{
	//	UAISense_Damage::ReportDamageEvent()
	//}
}
