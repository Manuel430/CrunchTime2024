// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/CTargetActor_GroundPick.h"

#include "AbilitySystemBlueprintLibrary.h"

#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"

ACTargetActor_GroundPick::ACTargetActor_GroundPick()
{
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	TargetSphere = CreateDefaultSubobject<USphereComponent>("TargetSphere");
	TargetSphere->SetupAttachment(GetRootComponent());

	TargetSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TargetSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	TargetSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	TargetDecal = CreateDefaultSubobject<UDecalComponent>("TargetDecal");
	TargetDecal->SetupAttachment(GetRootComponent());

	PrimaryActorTick.bCanEverTick = true;
}

void ACTargetActor_GroundPick::SetTargetingRadius(float TargettingRadius)
{
	TargetSphere->SetSphereRadius(TargettingRadius);
	TargetDecal->DecalSize = FVector(TargettingRadius);
}

void ACTargetActor_GroundPick::SetTargetingRange(float NewTargetingRange)
{
	TargetingRange = NewTargetingRange;
}

void ACTargetActor_GroundPick::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FHitResult PlayerView = GetPlayerView();
	if (PlayerView.bBlockingHit)
	{
		SetActorLocation(PlayerView.ImpactPoint);
	}
}

bool ACTargetActor_GroundPick::IsConfirmTargetingAllowed()
{
	return GetPlayerView().bBlockingHit;
}

void ACTargetActor_GroundPick::ConfirmTargetingAndContinue()
{
	TSet<AActor*> CurrentActorsInRange;
	TargetSphere->GetOverlappingActors(CurrentActorsInRange, APawn::StaticClass());

	TArray<AActor*> Targets;
	for (AActor* ActorInRange : CurrentActorsInRange)
	{
		if (ActorInRange != PrimaryPC->GetPawn())
			Targets.Add(ActorInRange);
	}
}

FHitResult ACTargetActor_GroundPick::GetPlayerView() const
{
	FHitResult HitResult;
	if (PrimaryPC)
	{
		FVector ViewLoc;
		FRotator ViewRot;

		PrimaryPC->GetPlayerViewPoint(ViewLoc, ViewRot);

		FVector TraceEnd = ViewLoc + ViewRot.Vector() * TargetingRange;

		GetWorld()->LineTraceSingleByChannel(HitResult, ViewLoc, TraceEnd, ECC_Visibility);

		if (!HitResult.bBlockingHit)
		{
			GetWorld()->LineTraceSingleByChannel(HitResult, TraceEnd, TraceEnd + FVector::DownVector * TargetingRange, ECC_Visibility);
		}
	}

	return HitResult;
}
