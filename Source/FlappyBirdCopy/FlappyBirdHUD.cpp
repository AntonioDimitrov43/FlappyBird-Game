// Fill out your copyright notice in the Description page of Project Settings.


#include "FlappyBirdHUD.h"

AFlappyBirdHUD::AFlappyBirdHUD()
{

}

void AFlappyBirdHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AFlappyBirdHUD::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Start HUD"));

	FlappyBird = Cast<AFlappyBirdController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	GameMode = Cast<AFlappyBirdCopyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	APW_SkippyBird* PossessedPawn = Cast<APW_SkippyBird>(FlappyBird->GetPawn());
	PossessedPawn->BirdStop();

	CreateMainMenu();
}

void AFlappyBirdHUD::CreateMainMenu()
{
	if (MainMenuClass)
	{
		CurrentMainMenu = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuClass);
		if (CurrentMainMenu)
		{
			CurrentMainMenu->AddToViewport();
			CurrentMainMenu->InitializeHUD();
			bMainMenuActive = true;
		}
	}
}

void AFlappyBirdHUD::CreateInfoMenu()
{
	if (IsValid(CurrentInfo))
	{
		if (bInfoMenuActive)
		{
			CurrentInfo->PlayerInputCheck();

			if (CurrentInfo->HasStarted())
			{
				UE_LOG(LogTemp, Warning, TEXT("Info"));
				bInfoMenuActive = false;
				RemoveInfo();
			}
		}

	}
}

void AFlappyBirdHUD::CreateGameplayMenu()
{
	if (IsValid(Gameplay))
	{
		if (bGamePlayActive)
		{
			int CurrentPoints = GameMode->GetGameScore();
			if (CurrentPoints > PreviousPoints)
			{
				PreviousPoints = CurrentPoints;
				Gameplay->UpdateHUD(CurrentPoints);
			}
		}
	}
}

void AFlappyBirdHUD::CreateGameWinEndMenu()
{
	if (GameMode->WinOrLose == 1 || GameMode->WinOrLose == 2)
	{
		AddGameWinEndWidget();

		if (GameMode->WinOrLose == 1)
		{
			//Win
			RemoveGameplay();
			GameWinEnd->InitializeHUDWon();
			bGameWinEndActive = false;
		}
		else if (GameMode->WinOrLose == 2)
		{
			//Lose
			RemoveGameplay();
			GameWinEnd->InitializeHUDLost();
			bGameWinEndActive = false;
		}

		GameMode->WinOrLose = 0;
	}
}

void AFlappyBirdHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsValid(CurrentMainMenu))
	{
		if (CurrentMainMenu->IsClicked() && bMainMenuActive)
		{
			UE_LOG(LogTemp, Warning, TEXT("Main Menu"));
			bMainMenuActive = false;
			RemoveMainMenu();
		}
	}

	CreateInfoMenu();

	CreateGameplayMenu();

	CreateGameWinEndMenu();

	if (GameMode->bHasRestarted)
	{
		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
		CreateMainMenu();
		GameMode->bHasRestarted = false;
	}
}

void AFlappyBirdHUD::RemoveMainMenu()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	bInfoMenuActive = true;
	AddInfoWidget();
}

void AFlappyBirdHUD::RemoveInfo()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	GameMode->UnPauseGame();
	bGamePlayActive = true;
	AddGameplayWidget();
}

void AFlappyBirdHUD::RemoveGameplay()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	bGamePlayActive = false;
	AddGameWinEndWidget();
}

void AFlappyBirdHUD::RemoveGameWinEnd()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	bGameWinEndActive = false;
}

void AFlappyBirdHUD::RestartHUD()
{
	CreateMainMenu();
}

void AFlappyBirdHUD::AddInfoWidget()
{
	if (InfoClass)
	{
		CurrentInfo = CreateWidget<UInfoWidget>(GetWorld(), InfoClass);
		if (CurrentInfo)
		{
			CurrentInfo->AddToViewport();
			CurrentInfo->InitializeHUD();
		}
	}
}

void AFlappyBirdHUD::AddGameplayWidget()
{
	if (GameplayClass)
	{
		Gameplay = CreateWidget<UGameplayWidget>(GetWorld(), GameplayClass);
		if (Gameplay)
		{
			Gameplay->AddToViewport();
			Gameplay->InitializeHUD();
			PreviousPoints = GameMode->GetGameScore();
		}
	}
}

void AFlappyBirdHUD::AddGameWinEndWidget()
{
	if (GameWinEndClass)
	{
		GameWinEnd = CreateWidget<UGameWinEndWidget>(GetWorld(), GameWinEndClass);
		if (GameWinEnd)
		{
			GameWinEnd->AddToViewport();
			bGameWinEndActive = true;
		}
	}
}
