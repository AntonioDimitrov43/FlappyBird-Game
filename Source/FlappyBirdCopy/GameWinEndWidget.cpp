// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWinEndWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "FlappyBirdController.h"
#include "PW_SkippyBird.h"
#include "FlappyBirdCopyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UGameWinEndWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayAgain)
	{
		PlayAgain->OnClicked.AddDynamic(this, &UGameWinEndWidget::PlayAgainClick);
	}
	if (Quit)
	{
		Quit->OnClicked.AddDynamic(this, &UGameWinEndWidget::QuitClick);
	}

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
	GameMode = GetWorld()->GetAuthGameMode<AFlappyBirdCopyGameModeBase>();
}

void UGameWinEndWidget::PlayAgainClick()
{
	GameMode->RestartGame();
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
}

void UGameWinEndWidget::QuitClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}

void UGameWinEndWidget::InitializeHUDLost()
{
	GameWinLose->SetText(FText::FromString("YOU HAVE LOST!"));
	PlayAgainText->SetText(FText::FromString("Play Again"));
	QuitText->SetText(FText::FromString("Quit"));

	int Score = GameMode->GetGameScore();
	FinalScore->SetText(FText::FromString("Final Points: " + FString::FromInt(Score)));
	GameMode->SetGameScore(0);
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

}
void UGameWinEndWidget::InitializeHUDWon()
{
	GameWinLose->SetText(FText::FromString("YOU HAVE WON!"));
	PlayAgainText->SetText(FText::FromString("Play Again"));
	QuitText->SetText(FText::FromString("Quit"));

	int Score = GameMode->GetGameScore();
	FinalScore->SetText(FText::FromString("Final Points: " + FString::FromInt(Score)));
	GameMode->SetGameScore(0);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

}
