// Fill out your copyright notice in the Description page of Project Settings.


#include "Pacman.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h>
#include <string>
#include "PortalActor.h"
#include "PickupItem.h"
#include "GameCharacter.h"

APacman::APacman()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Pacman Camera"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Pacman SpringArm"));
	
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	PacmanState = PACMAN_STATE::Normal;

	Lives = 1;
	bIsDead = false;
}

void APacman::BeginPlay()
{
	Super::BeginPlay();

	Score = 0;
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &APacman::OnOverlapBegin);
	FV_StartLocation = GetActorLocation();
}

void APacman::OnOverlapBegin(	UPrimitiveComponent* OverlappedComp,
								AActor* OtherActor,
								UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex,
								bool bFromSweep,
								const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Find("Enemy_BP") != std::string::npos)
	{
		if (PacmanState != PACMAN_STATE::PoweredUp)
		{
			if (Lives > 0)
			{
				Lives--;
				SetActorLocation(FV_StartLocation);
			}
			else
			{
				bIsDead = true;
				Mesh->SetHiddenInGame(true);
			}
			UE_LOG(LogTemp, Warning, TEXT("Pacman Dead"));
		}
		else if (PacmanState == PACMAN_STATE::PoweredUp)
		{
			AGameCharacter* EnemyPawn = Cast<AGameCharacter>(OtherActor);
			EnemyPawn->SetActorLocation(EnemyPawn->FV_StartLocation);
			if (EnemyPawn == nullptr)
				UE_LOG(LogTemp, Warning, TEXT("null"));
			UE_LOG(LogTemp, Warning, TEXT("Enemy Dead"));
		}
	}
	
	if (OtherActor->GetName().Find("BP_Portal") != std::string::npos)
		SetActorLocation(Cast<APortalActor>(OtherActor)->FV_TargetLocation);
	UE_LOG(LogTemp, Warning, TEXT("OtherActor Name: %s"), *OtherActor->GetName());
	if (OtherActor->GetName().Find("BP_Fruit") != std::string::npos)
		PowerUp(OtherActor);

}

void APacman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDead)
		return;

	MoveForward(DeltaTime);

	if (PacmanState != PACMAN_STATE::Normal)
	{
		if (GetWorld()->GetTimeSeconds() - fTimeSincePowerup > fPowerUpDuration)
		{
			PacmanState = PACMAN_STATE::Normal;
			fSpeed /= 2;
		}
	}
}

void APacman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("TurnRight"), IE_Pressed, this, &APacman::TurnRight);
	PlayerInputComponent->BindAction(TEXT("TurnLeft"), IE_Pressed, this, &APacman::TurnLeft);
}

void APacman::PowerUp(AActor* Pickup)
{
	APickupItem* Fruit = Cast<APickupItem>(Pickup);
	switch (Fruit->FruitType)
	{
	case FRUIT_TYPE::Cherry:
		Score += 30;
		fPowerUpDuration = Fruit->fDuration;
		fTimeSincePowerup = GetWorld()->GetTimeSeconds();
		PacmanState = PACMAN_STATE::PoweredUp;
		fSpeed *= 2;
		break;
	case FRUIT_TYPE::Pear:
		Score += 25;
		fPowerUpDuration = Fruit->fDuration;
		fTimeSincePowerup = GetWorld()->GetTimeSeconds();
		PacmanState = PACMAN_STATE::SpeedUp;
		fSpeed *= 2;
		break;
	case FRUIT_TYPE::Orange: // Because orange is my least favourite fruit
		Score += 10;
		break;
	}
	UE_LOG(LogTemp, Warning, TEXT("Score: %d"), Score);
	Pickup->Destroy();
}
