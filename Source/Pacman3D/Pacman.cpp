// Fill out your copyright notice in the Description page of Project Settings.


#include "Pacman.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>

APacman::APacman()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Pacman Camera"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Pacman SpringArm"));
	
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void APacman::BeginPlay()
{
	Super::BeginPlay();
}

void APacman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTurnRight)
		TurnRightLoop(DeltaTime);
	if (bTurnLeft)
		TurnLeftLoop(DeltaTime);

}

void APacman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("TurnRight"), IE_Pressed, this, &APacman::TurnRight);
	PlayerInputComponent->BindAction(TEXT("TurnLeft"), IE_Pressed, this, &APacman::TurnLeft);
}

void APacman::TurnRight()
{
	if (bTurnRight||bTurnLeft)
		return;
	bTurnRight = true;
	TargetRotation.Yaw += 90.f;

	UE_LOG(LogTemp, Warning, TEXT("Turning Right"));
}

void APacman::TurnLeft()
{
	if (bTurnLeft || bTurnRight)
		return;

	bTurnLeft = true;
	TargetRotation.Yaw -= 90.f;

	UE_LOG(LogTemp, Warning, TEXT("Turning Left"));
}

void APacman::TurnRightLoop(float DeltaTime)
{
	if (ceil(GetActorRotation().Yaw) < TargetRotation.Yaw)
	{
		SetActorRotation(FMath::RInterpConstantTo(GetActorRotation(), TargetRotation, DeltaTime*fDeltaTimeRotationConstant, fRotationSpeed));
		if (GetActorRotation().Yaw < 0 && TargetRotation.Yaw >= 180.f)
			TargetRotation.Yaw *= -1;
	}
	else
	{
		bTurnRight = false;
	}
}

void APacman::TurnLeftLoop(float DeltaTime)
{
	if (abs(TargetRotation.Yaw-GetActorRotation().Yaw)>1.f)
	{
		SetActorRotation(FMath::RInterpConstantTo(GetActorRotation(), TargetRotation, DeltaTime * fDeltaTimeRotationConstant, fRotationSpeed));
		//UE_LOG(LogTemp, Warning, TEXT("Current Yaw: %f\tTarget Yaw: %f"), ceil(GetActorRotation().Yaw), TargetRotation.Yaw);
		if (GetActorRotation().Yaw > 0 && TargetRotation.Yaw <= -180.f)
			TargetRotation.Yaw += 360.f;
	}
	else
	{
		bTurnLeft=false;
	}
}
