// Fill out your copyright notice in the Description page of Project Settings.


#include "FlappyBirdController.h"

AFlappyBirdController::AFlappyBirdController()
{
	
}

void AFlappyBirdController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Flappy Jump", IE_Pressed, this,&AFlappyBirdController::Jumping);
	InputComponent->BindAction("Flappy Jump 2", IE_Pressed, this, &AFlappyBirdController::Jumping);
}

void AFlappyBirdController::Jumping()
{
	//Put the jumping function here from the Pawn!

	APW_SkippyBird* PossessedPawn = Cast<APW_SkippyBird>(this->GetPawn());
	if (!IsValid(PossessedPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("AFlappyBirdController::Jumping !IsValid(PossessedPawn)"));
		return;
	}
	PossessedPawn->BirdJump();
}

void AFlappyBirdController::PauseBird()
{
	//Put the Stopping function here from the Pawn!
	APawn* PossessedPawn = this->GetPawn();
	if (!IsValid(PossessedPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("AFlappyBirdController::PauseBird !IsValid(PossessedPawn)"));
		return;
	}
	APW_SkippyBird* MainPlayer = Cast<APW_SkippyBird>(PossessedPawn);
	if (!IsValid(MainPlayer))
	{
		UE_LOG(LogTemp, Warning, TEXT("AFlappyBirdController::PauseBird !IsValid(MainPlayer)"));
		return;
	}
	MainPlayer->BirdStop();
}
