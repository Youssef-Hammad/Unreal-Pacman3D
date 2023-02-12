// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"
#include <Components/CapsuleComponent.h>


// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("GameCharacter Capsule"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GameCharacter Mesh"));

	RootComponent = CapsuleComp;
	Mesh->SetupAttachment(CapsuleComp);

}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveForward(DeltaTime);

	// The turning loops are made for the sake of Linear Interpolation so the characters turn smoothly instead of snapping to the new rotation
	if (bTurnRight)
		TurnRightLoop(DeltaTime);
	if (bTurnLeft)
		TurnLeftLoop(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGameCharacter::MoveForward(float DeltaTime)
{
	FVector DeltaLocation(0.f);

	DeltaLocation.X = DeltaTime * fSpeed;
	AddActorLocalOffset(DeltaLocation, true);
}

void AGameCharacter::TurnRight()
{
	if (bTurnRight || bTurnLeft)
		return;
	bTurnRight = true;
	TargetRotation.Yaw += 90.f;

	UE_LOG(LogTemp, Warning, TEXT("Turning Right"));
}

void AGameCharacter::TurnLeft()
{
	if (bTurnLeft || bTurnRight)
		return;

	bTurnLeft = true;
	TargetRotation.Yaw -= 90.f;

	UE_LOG(LogTemp, Warning, TEXT("Turning Left"));
}

void AGameCharacter::TurnRightLoop(float DeltaTime)
{
	if (ceil(GetActorRotation().Yaw) < TargetRotation.Yaw)
	{
		SetActorRotation(FMath::RInterpConstantTo(GetActorRotation(), TargetRotation, DeltaTime * fDeltaTimeRotationConstant, fRotationSpeed));
		if (GetActorRotation().Yaw < 0 && TargetRotation.Yaw >= 180.f) // Makes sure TargetRotation stays in range of -180 and 180
			TargetRotation.Yaw *= -1;
	}
	else
	{
		bTurnRight = false;
	}
}

void AGameCharacter::TurnLeftLoop(float DeltaTime)
{
	if (abs(TargetRotation.Yaw - GetActorRotation().Yaw) > 1.f)
	{
		SetActorRotation(FMath::RInterpConstantTo(GetActorRotation(), TargetRotation, DeltaTime * fDeltaTimeRotationConstant, fRotationSpeed));
		//UE_LOG(LogTemp, Warning, TEXT("Current Yaw: %f\tTarget Yaw: %f"), ceil(GetActorRotation().Yaw), TargetRotation.Yaw);
		if (GetActorRotation().Yaw >= 0 && TargetRotation.Yaw <= -180.f) // Makes sure TargetRotation stays in range of -180 and 180
			TargetRotation.Yaw += 360.f;
	}
	else
	{
		bTurnLeft = false;
	}
}

