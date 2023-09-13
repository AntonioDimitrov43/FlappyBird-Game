// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PW_SkippyBird.h"
#include "FlappyBirdController.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCOPY_API AFlappyBirdController : public APlayerController
{
	GENERATED_BODY()

private:

	
public:

	AFlappyBirdController();

	virtual void SetupInputComponent() override;
	
	UFUNCTION()
		void Jumping();

	UFUNCTION()
		void PauseBird();
};
