// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdCopyGameModeBase.h"
#include "FlappyBirdController.h"
#include "PW_SkippyBird.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "MainMenuWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "InputCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"


void AFlappyBirdCopyGameModeBase::BeginPlay()
{
	AFlappyBirdController* OurBird = Cast<AFlappyBirdController>(UGameplayStatics::GetPlayerController(this, 0));
	
	WinOrLose = 0;

	TSubclassOf<APW_SkippyBird> PawnToFind = APW_SkippyBird::StaticClass();
	TArray<AActor*> FoundPawn;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PawnToFind, FoundPawn);
	if (!IsValid(FoundPawn[0]))
	{
		UE_LOG(LogTemp, Warning, TEXT("AFlappyBirdCopyGameModeBase::BeginPlay !IsValid(FoundCamera[0])"));
		return;
	}
	OurBird->Possess(Cast<APW_SkippyBird>(FoundPawn[0]));
	BirdStart = FoundPawn[0]->GetActorLocation();
	CurrentBird = Cast<APW_SkippyBird>(FoundPawn[0]);
	
	TSubclassOf<ABirdCamera> CameraToFind = ABirdCamera::StaticClass();
	TArray<AActor*> FoundCamera;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CameraToFind, FoundCamera);
	if (!IsValid(FoundCamera[0]))
	{
		UE_LOG(LogTemp, Warning, TEXT("AFlappyBirdCopyGameModeBase::BeginPlay !IsValid(FoundCamera[0])"));
		return;
	}
	
	OurBird->SetViewTarget(Cast<ABirdCamera>(FoundCamera[0]));
	CameraStart = FoundCamera[0]->GetActorLocation();
	CurrentCamera = Cast<ABirdCamera>(FoundCamera[0]);
	
	SpawnBoxLocation.X = BirdStart.X;
	SpawnBoxLocation.Y = BirdStart.Y + 1300.f;
	SpawnBoxLocation.Z = 450.f;
	
	GameScore = 0;
	SpawnObstacleBox();
	while (SpawnedObstacleBoxes < 25)
	{
		SpawnObstacleBox();
	}

	CurrentBird->BirdStop();
	PausedGame = true;
}

void AFlappyBirdCopyGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PausedGame)
	{
		GameMovement(DeltaTime);
	}
	
	if (GameScore == 10)
	{
		WinOrLose = 1;
		CurrentBird->BirdStop();
		PausedGame = true;
	}

}

AFlappyBirdCopyGameModeBase::AFlappyBirdCopyGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SpawnedObstacleBoxes = 0;

	MovementDirection.ZeroVector;
	MovementDirection.Y = 1.f;

}

void AFlappyBirdCopyGameModeBase::GameMovement(float Time)
{
	const FVector NewLocationCamera = CurrentCamera->GetActorLocation() + (MovementDirection * Time * MovementSpeed);
	CurrentCamera->SetActorLocation(NewLocationCamera);
	const FVector NewLocationBird = CurrentBird->GetActorLocation() + (MovementDirection * Time * MovementSpeed);
	CurrentBird->SetActorLocation(NewLocationBird);
}

void AFlappyBirdCopyGameModeBase::SpawnObstacleBox()
{
	if (SpawnedObstacleBoxes > 0)
	{
		SpawnBoxLocation.Y += 1200.f;
	}

	FRotator BoxRotation = FRotator(0.f, 0.f, 0.f);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnBox = GetWorld()->SpawnActor<AA_SpawningCube>(SpawnBoxLocation, BoxRotation, SpawnInfo);
	SpawnBox->CreateBoxWithObstacles(SpawnBoxLocation, BoxRotation);
	SpawnedObstacleBoxes++;
}

int AFlappyBirdCopyGameModeBase::GetGameScore()
{
	return GameScore;
}

void AFlappyBirdCopyGameModeBase::IncreaseScore()
{
	GameScore++;
}

void AFlappyBirdCopyGameModeBase::SetGameScore(int Score)
{
	this->GameScore = Score;
}

void AFlappyBirdCopyGameModeBase::PauseGame()
{
	PausedGame = true;
}

void AFlappyBirdCopyGameModeBase::UnPauseGame()
{
	PausedGame = false;
}

void AFlappyBirdCopyGameModeBase::RestartGame()
{
	CurrentBird->SetActorLocation(BirdStart);
	CurrentCamera->SetActorLocation(CameraStart);
	bHasRestarted = true;
	GameScore = 0;
	PauseGame();
	CurrentBird->BirdStop();
}
