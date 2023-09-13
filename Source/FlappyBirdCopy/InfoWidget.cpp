// Fill out your copyright notice in the Description page of Project Settings.


#include "InfoWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "FlappyBirdController.h"
#include "Kismet/GameplayStatics.h"

void UInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
}

void UInfoWidget::InputRegistered()
{
	Started = true;
}

bool UInfoWidget::HasStarted()
{
	return Started;
}

void UInfoWidget::InitializeHUD()
{
	InformationText->SetText(FText::FromString("Tip: Use Spacebar or Left Mouse button \n to Jump and Begin the Game"));
	FlappyBird = Cast<AFlappyBirdController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UInfoWidget::PlayerInputCheck()
{
	//UE_LOG(LogTemp, Warning, TEXT("Player Check"));

	if (FlappyBird->WasInputKeyJustPressed(EKeys::LeftMouseButton) || FlappyBird->WasInputKeyJustPressed(EKeys::SpaceBar))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Check!!!!"));
		InputRegistered();
	}
}
