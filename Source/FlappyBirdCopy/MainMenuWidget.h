// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FlappyBirdCopyGameModeBase.h"
#include "InfoWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCOPY_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* MainText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* PlayText;

	UPROPERTY(meta = (BindWidget))
		class UButton* PlayButton;

	UPROPERTY()
		bool Clicked;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void ButtonClicked();
public:

	UFUNCTION(BlueprintCallable)
		void InitializeHUD();

	UFUNCTION()
		bool IsClicked();
	
};
