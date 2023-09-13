// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FlappyBirdCopyGameModeBase.h"
#include "InfoWidget.generated.h"


//DECLARE_MULTICAST_DELEGATE(FOnInputAction)

UCLASS()
class FLAPPYBIRDCOPY_API UInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* InformationText;

	virtual void NativeConstruct() override;

	bool Started;

public:

	UFUNCTION()
		bool HasStarted();

	UFUNCTION()
		void InputRegistered();

	UFUNCTION(BlueprintCallable)
		void InitializeHUD();

	UFUNCTION()
		void PlayerInputCheck();

	AFlappyBirdController* FlappyBird;
};
