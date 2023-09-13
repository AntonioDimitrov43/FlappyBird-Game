// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Clicked = false;

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ButtonClicked);
	}
}

void UMainMenuWidget::ButtonClicked()
{
	Clicked = true;
}

void UMainMenuWidget::InitializeHUD()
{
	MainText->SetText(FText::FromString("Flappy Bird Copy"));
	PlayText->SetText(FText::FromString("Start Game"));

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
}

bool UMainMenuWidget::IsClicked()
{
	return Clicked;
}
