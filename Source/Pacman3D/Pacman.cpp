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

}

void APacman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
