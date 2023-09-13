// Fill out your copyright notice in the Description page of Project Settings.

#include "PW_SkippyBird.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/WidgetLayoutLibrary.h"

// Sets default values
APW_SkippyBird::APW_SkippyBird()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;

	bHasStarted = false;

	BirdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(RootComponent);
	BirdMesh->SetGenerateOverlapEvents(false);
	FRotator Rotation;
	Rotation.ZeroRotator;
	Rotation.Roll = 90.f;
	BirdMesh->SetWorldRotation(Rotation);
	BirdMesh->SetWorldScale3D(FVector(1.f));

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->InitBoxExtent(FVector(52.f, 52.f, 52.f));
	HitBox->SetCollisionProfileName(TEXT("Bird Collision"));
	HitBox->SetupAttachment(BirdMesh);

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &APW_SkippyBird::OverlapBegin);
	
}

// Called when the game starts or when spawned
void APW_SkippyBird::BeginPlay()
{
	Super::BeginPlay();

	BirdMesh->SetSimulatePhysics(true);
	BirdMesh->BodyInstance.bLockXTranslation = true;
	BirdMesh->BodyInstance.bLockYTranslation = true;
	BirdMesh->BodyInstance.bLockRotation = true;
}

// Called every frame
void APW_SkippyBird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APW_SkippyBird::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(Cast<UStaticMeshComponent>(OtherComp)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Checking Floor"));
		BirdStop();
	}
}

void APW_SkippyBird::BirdJump()
{
	UE_LOG(LogTemp, Warning, TEXT("Jumping"));
	if (!IsValid(BirdMesh))
	{
		UE_LOG(LogTemp, Warning, TEXT("APW_SkippyBird::BirdJump !IsValid(BirdMesh)"));
		return;
	}

	if (!BirdMesh->IsSimulatingPhysics())
	{
		BirdMesh->SetSimulatePhysics(true);
	}
	BirdMesh->BodyInstance.SetLinearVelocity(FVector::UpVector * JumpForce, true);
}

void APW_SkippyBird::BirdStop()
{
	UE_LOG(LogTemp, Warning, TEXT("Stopping"));
	if (!IsValid(BirdMesh))
	{
		UE_LOG(LogTemp, Warning, TEXT("APW_SkippyBird::BirdStop !IsValid(BirdMesh)"));
		return;
	}
	BirdMesh->BodyInstance.SetLinearVelocity(FVector::ZeroVector, true);
	BirdMesh->SetSimulatePhysics(false);
}
