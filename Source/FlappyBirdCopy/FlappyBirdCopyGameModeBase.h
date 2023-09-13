// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PW_SkippyBird.h"
#include "GameFramework/DefaultPawn.h"
#include "FlappyBirdController.h"
#include "BirdCamera.h"
#include "A_SpawningCube.h"
#include "FlappyBirdCopyGameModeBase.generated.h"

UCLASS()
class FLAPPYBIRDCOPY_API AFlappyBirdCopyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	UPROPERTY()
		bool PausedGame;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		AA_SpawningCube* SpawnBox;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementSpeed = 450.f;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
		FVector SpawnBoxLocation;

	UPROPERTY(EditAnywhere, Category = "Movement")
		int SpawnedObstacleBoxes;

	UPROPERTY(EditAnywhere, Category = "Score")
		int GameScore;
	
	UPROPERTY(EditAnywhere, Category = "Location")
		FVector BirdStart;

	UPROPERTY(EditAnywhere, Category = "Location")
		FVector CameraStart;

	UPROPERTY()
		APW_SkippyBird* CurrentBird;

	UPROPERTY()
		ABirdCamera* CurrentCamera;

protected:

	FVector MovementDirection;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	AFlappyBirdCopyGameModeBase();

	bool bHasBegun;

	bool bHasRestarted;

	int WinOrLose;

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
		void GameMovement(float Time);

	UFUNCTION()
		void SpawnObstacleBox();

	UFUNCTION()
		int GetGameScore();

	UFUNCTION()
		void SetGameScore(int Score);

	UFUNCTION()
		void IncreaseScore();

	UFUNCTION()
		void PauseGame();

	UFUNCTION()
		void UnPauseGame();

	UFUNCTION()
		void RestartGame();
};
