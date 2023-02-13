// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN3D_API AEnemy : public AGameCharacter
{
	GENERATED_BODY()
	
private:
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
