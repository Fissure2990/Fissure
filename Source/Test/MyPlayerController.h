// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "MyPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class TEST_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	AMyPlayerController();
	virtual void BeginPlay();
	virtual void SetupInputComponent() override;
	void OnMove(const FInputActionValue& InputActionValue);


	UEnhancedInputComponent* EnhancedInputComponent = nullptr;
	UInputMappingContext* DefaultContext = nullptr;
	UInputAction* Move = nullptr;
};
