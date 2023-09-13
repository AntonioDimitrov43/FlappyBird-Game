// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuWidget.h"
#include "InfoWidget.h"
#include "GameplayWidget.h"
#include "PW_SkippyBird.h"
#include "Kismet/GameplayStatics.h"
#include "GameWinEndWidget.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "FlappyBirdHUD.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCOPY_API AFlappyBirdHUD : public AHUD
{
	GENERATED_BODY()

public:

	AFlappyBirdHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		void CreateMainMenu();

	UFUNCTION()
		void CreateInfoMenu();

	UFUNCTION()
		void CreateGameplayMenu();

	UFUNCTION()
		void CreateGameWinEndMenu();

	UFUNCTION()
		void RemoveMainMenu();

	UFUNCTION()
		void AddInfoWidget();

	UFUNCTION()
		void RemoveInfo();

	UFUNCTION()
		void AddGameplayWidget();

	UFUNCTION()
		void RemoveGameplay();

	UFUNCTION()
		void AddGameWinEndWidget();

	UFUNCTION()
		void RemoveGameWinEnd();

	UFUNCTION()
		void RestartHUD();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> InfoClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> GameplayClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> GameWinEndClass;

	AFlappyBirdController* FlappyBird;

	AFlappyBirdCopyGameModeBase* GameMode;
	
private:

	bool bMainMenuActive;
	bool bInfoMenuActive;
	bool bGamePlayActive;
	bool bGameWinEndActive;

	int PreviousPoints;


	UMainMenuWidget* CurrentMainMenu;
	UInfoWidget* CurrentInfo;
	UGameplayWidget* Gameplay;
	UGameWinEndWidget* GameWinEnd;
};
