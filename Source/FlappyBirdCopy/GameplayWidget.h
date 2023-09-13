// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FlappyBirdCopyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCOPY_API UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* CurrentPointsBird;

public:

	UFUNCTION(BlueprintCallable)
		void UpdateHUD(int BirdPoints);

	UFUNCTION(BlueprintCallable)
		void InitializeHUD();
	
	AFlappyBirdCopyGameModeBase* GameMode;
	
};
