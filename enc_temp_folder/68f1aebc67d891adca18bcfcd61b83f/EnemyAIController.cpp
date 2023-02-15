// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include <Kismet/GameplayStatics.h>

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	PacmanPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	UE_LOG(LogTemp, Warning, TEXT("Following Pawn: %s"), *PacmanPawn->GetName());

	SetFocus(PacmanPawn);
	MoveToActor(PacmanPawn);
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToActor(PacmanPawn);
}