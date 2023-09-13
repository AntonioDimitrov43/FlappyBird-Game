// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayWidget.h"
#include "Components/TextBlock.h"

void UGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
}

void UGameplayWidget::UpdateHUD(int BirdPoints)
{
	CurrentPointsBird->SetText(FText::FromString("Points: " + FString::FromInt(BirdPoints)));
}

void UGameplayWidget::InitializeHUD()
{
	CurrentPointsBird->SetText(FText::FromString("Points: 0 "));
}
