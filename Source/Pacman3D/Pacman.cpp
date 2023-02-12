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

	// Moving Pacman Forward all the time

	/*FVector DeltaLocation(0.f);

	DeltaLocation.X =  DeltaTime * fSpeed;
	AddActorLocalOffset(DeltaLocation, true);*/
}

void APacman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("TurnRight"), IE_Pressed, this, &APacman::Turn);

}

void APacman::Turn(float Value)
{
	int iValue = Value;

	FRotator DeltaRotation = FRotator::ZeroRotator;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	UE_LOG(LogTemp, Warning, TEXT("Turning"));

	switch (iValue)
	{
	case 1:
		DeltaRotation.Yaw = 180.f * DeltaTime;
		UE_LOG(LogTemp, Warning, TEXT("Turning Right"));
		break;
	case -1:
		DeltaRotation.Yaw = -180.f * DeltaTime;
		UE_LOG(LogTemp, Warning, TEXT("Turning Left"));
		break;
	}

	AddActorLocalRotation(DeltaRotation, true);

}
