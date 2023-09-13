// Fill out your copyright notice in the Description page of Project Settings.

#include "A_BirdObstacle.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "FlappyBirdController.h"
#include "FlappyBirdCopyGameModeBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "PW_SkippyBird.h"


// Sets default values
AA_BirdObstacle::AA_BirdObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Game/Meshes/Cylinder.Cylinder"));

	//Bottom Obstacle
	BottomCylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottom Cylinder"));
	RootComponent = BottomCylinder;
	//BottomCylinder->SetupAttachment(RootComponent);
	BottomCylinder->SetGenerateOverlapEvents(false);

	// Box Component for Bottom Obstacle Hit
	BottomHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomHitBox"));
	BottomHitBox->InitBoxExtent(FVector(52.f, 52.f, 52.f));
	BottomHitBox->SetCollisionProfileName(TEXT("SimpleCollision"));
	BottomHitBox->SetupAttachment(BottomCylinder);

	BottomHitBox->OnComponentBeginOverlap.AddDynamic(this, &AA_BirdObstacle::OverlapCylinders);

	//Top Obstacle
	TopCylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top Cylinder"));
	RootComponent = TopCylinder;
	TopCylinder->SetGenerateOverlapEvents(false);

	// Box Component for Top Obstacle Hit
	TopHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TopHitBox"));
	TopHitBox->InitBoxExtent(FVector(52.f, 52.f, 52.f));
	TopHitBox->SetCollisionProfileName(TEXT("SimpleCollision"));
	TopHitBox->SetupAttachment(TopCylinder);

	TopHitBox->OnComponentBeginOverlap.AddDynamic(this, &AA_BirdObstacle::OverlapCylinders);

	if (CylinderAsset.Succeeded())
	{
		BottomCylinder->SetStaticMesh(CylinderAsset.Object);
		TopCylinder->SetStaticMesh(CylinderAsset.Object);
	}

	// Box that gives you points when you pass safely
	MiddlePassBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Passing Box"));
	RootComponent = MiddlePassBox;

	MiddlePassBox->SetGenerateOverlapEvents(true);
	MiddlePassBox->SetBoxExtent(FVector(25.f, 50.f, 45.f));
	MiddlePassBox->SetCollisionProfileName(TEXT("PointBox"));


	MiddlePassBox->OnComponentEndOverlap.AddDynamic(this, &AA_BirdObstacle::OverlapEndMiddle);

}

// Called when the game starts or when spawned
void AA_BirdObstacle::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AA_BirdObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AA_BirdObstacle::OverlapEndMiddle(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	
	AFlappyBirdCopyGameModeBase* GameMode = Cast<AFlappyBirdCopyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(GameMode))
	{
		UE_LOG(LogTemp, Warning, TEXT("AA_BirdObstacle::OverlapEndMiddle !IsValid(GameMode)"));
		return;
	}
	if (Cast<UStaticMeshComponent>(OtherComp))
	{
		GameMode->IncreaseScore();
	}
}

void AA_BirdObstacle::OverlapCylinders(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("Collision!"));

	AFlappyBirdController* Controller = Cast<AFlappyBirdController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if (!IsValid(Controller))
	{
		UE_LOG(LogTemp, Warning, TEXT("AA_BirdObstacle::OverlapCylinders !IsValid(Controller)"));
		return;
	}
	Controller->PauseBird();

	AFlappyBirdCopyGameModeBase* GameMode = Cast<AFlappyBirdCopyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(GameMode))
	{
		UE_LOG(LogTemp, Warning, TEXT("AA_BirdObstacle::OverlapCylinders !IsValid(GameMode)"));
		return;
	}
	GameMode->PauseGame();
	GameMode->WinOrLose = 2;

}

void AA_BirdObstacle::SetObstaclesInPlace(int SpawnVariation, FVector CurrentObstacleLocation)
{
	switch (SpawnVariation)
	{
	case 1: SetCylindersOnVariation(50.f, 650.f, 250.f, CurrentObstacleLocation); 
		TopCylinder->SetRelativeScale3D(FVector(1.f, 1.f, 5.f)); 
		break;

	case 2: SetCylindersOnVariation(100.f, 700.f, 350.f, CurrentObstacleLocation);
		BottomCylinder->SetRelativeScale3D(FVector(1.f, 1.f, 2.f));
		TopCylinder->SetRelativeScale3D(FVector(1.f, 1.f, 4.f));
		break;

	case 3: SetCylindersOnVariation(150.f, 750.f, 450.f, CurrentObstacleLocation);
		BottomCylinder->SetRelativeScale3D(FVector(1.f, 1.f, 3.f)); 
		TopCylinder->SetRelativeScale3D(FVector(1.f, 1.f, 3.f)); 
		break;

	case 4: SetCylindersOnVariation(200.f, 800.f, 550.f, CurrentObstacleLocation);
		BottomCylinder->SetRelativeScale3D(FVector(1.f, 1.f, 4.f)); 
		TopCylinder->SetRelativeScale3D(FVector(1.f, 1.f, 2.f)); 
		break;

	case 5: SetCylindersOnVariation(250.f, 850.f, 650.f, CurrentObstacleLocation);
		BottomCylinder->SetRelativeScale3D(FVector(1.f, 1.f, 5.f)); 
		break;

	default:
		break;
	}

}

void AA_BirdObstacle::SetCylindersOnVariation(float BottomLocation, float TopLocation, float BoxLocation, FVector CurrentObstacleLocation)
{
	BottomCylinder->SetRelativeLocation(FVector(CurrentObstacleLocation.X, CurrentObstacleLocation.Y, BottomLocation));
	TopCylinder->SetRelativeLocation(FVector(CurrentObstacleLocation.X, CurrentObstacleLocation.Y, TopLocation));
	MiddlePassBox->SetRelativeLocation(FVector(CurrentObstacleLocation.X, CurrentObstacleLocation.Y, BoxLocation));
}

