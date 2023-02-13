// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameCharacter.generated.h"

UCLASS()
class PACMAN3D_API AGameCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character Variables", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character Variables", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Character Variables", meta = (AllowPrivateAccess = "true"))
	float fSpeed = 200.f;

	void MoveForward(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Character Variables", meta = (AllowPrivateAccess = "true"))
		float fDeltaTimeRotationConstant = 80.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Character Variables", meta = (AllowPrivateAccess = "true"))
		float fRotationSpeed = 10.f;

	void TurnRight();
	void TurnLeft();

	void TurnRightLoop(float DeltaTime);
	void TurnLeftLoop(float DeltaTime);

	bool bTurnRight = false;
	bool bTurnLeft = false;

	FRotator TargetRotation;
};
