// Fill out your copyright notice in the Description page of Project Settings.


#include "Pacman.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h>

APacman::APacman()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Pacman Camera"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Pacman SpringArm"));
	
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	PacmanState = PACMAN_STATE::Normal;
}

void APacman::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &APacman::OnOverlapBegin);
}

void APacman::OnOverlapBegin(	UPrimitiveComponent* OverlappedComp,
								AActor* OtherActor,
								UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex,
								bool bFromSweep,
								const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Occurred"));
}

void APacman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveForward(DeltaTime);

}

void APacman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("TurnRight"), IE_Pressed, this, &APacman::TurnRight);
	PlayerInputComponent->BindAction(TEXT("TurnLeft"), IE_Pressed, this, &APacman::TurnLeft);
}
