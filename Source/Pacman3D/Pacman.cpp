// Fill out your copyright notice in the Description page of Project Settings.


#include "Pacman.h"

APacman::APacman()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
