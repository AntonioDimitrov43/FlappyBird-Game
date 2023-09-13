// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "PW_SkippyBird.generated.h"

UCLASS()
class FLAPPYBIRDCOPY_API APW_SkippyBird : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category="Meshes")
		UStaticMeshComponent* BirdMesh;

	UPROPERTY(EditAnywhere, Category = "Hit Box")
		UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere, Category="Jumping")
		float JumpForce;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	// Sets default values for this pawn's properties
	APW_SkippyBird();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
			, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void BirdJump();

	UFUNCTION()
		void BirdStop();

	UPROPERTY(EditAnywhere, Category = "Points")
		bool bHasStarted;
};
