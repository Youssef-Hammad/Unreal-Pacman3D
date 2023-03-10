// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PickupItem.generated.h"

UENUM()
enum FRUIT_TYPE
{
	Cherry		UMETA(DisplayName = "Cherry"),
	Pear		UMETA(DisplayName = "Pear"),
	Orange		UMETA(DisplayName = "Orange"),
};

UCLASS()
class PACMAN3D_API APickupItem : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Pickup Variables")
	TEnumAsByte<FRUIT_TYPE> FruitType;

	UPROPERTY(EditAnywhere, Category = "Pickup Variables")
	float fDuration;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup Variables", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup Variables", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Variables", meta = (AllowPrivateAccess = "true"))
	float fPickupRotationSpeed = 10.f;

};
