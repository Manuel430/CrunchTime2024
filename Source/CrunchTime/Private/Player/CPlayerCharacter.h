// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacterBase.h"
#include "CPlayerCharacter.generated.h"

//forward declartion. I am telling the compiler that this class exists.
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class ACPlayerCharacter : public ACCharacterBase
{
	GENERATED_BODY()
public:
	//this is the construtor
	ACPlayerCharacter();

private:
	UPROPERTY(visibleAnywhere, Category="View")
	USpringArmComponent* cameraBoom;
	
	UPROPERTY(visibleAnywhere, Category="View")
	UCameraComponent* viewCamera;

	UPROPERTY(visibleAnywhere, Category = "View")
	FVector AnimCameraLocalOffset;

	UPROPERTY(visibleAnywhere, Category = "View")
	float AnimCameraLerpingSpeed = 5;

	virtual void PawnClientRestart() override;

	/*****************************************************/
	/*                       Input                       */
	/*****************************************************/
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* inputMapping;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* moveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* lookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* jumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* baiscAttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* abilityOneInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* abilityConfirmAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* abilityCancelAction;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void AimingTagChanged(bool bNewIsAiming) override;

	UFUNCTION()
	void Move(const FInputActionValue& InputValue);

	UFUNCTION()
	void Look(const FInputActionValue& InputValue);

	UFUNCTION()
	void DoBasicAttack();

	UFUNCTION()
	void TryActivateAbilityOne();

	UFUNCTION()
	void ConfirmActionTriggered();

	UFUNCTION()
	void CancelActionTriggered();

	FVector GetMoveFwdDir() const;
	FVector GetMoveRightDir() const;

	void LerpCameraToLocalOffset(const FVector& LocalOffset);
	void TickCameraLocalOffset(FVector Goal);
	FTimerHandle CameraLerpHandle;
};
