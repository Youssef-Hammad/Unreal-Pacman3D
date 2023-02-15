// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "Pacman.generated.h"

/**
 * 
 */
UENUM()
enum PACMAN_STATE
{
	Normal		UMETA(DisplayName = "Normal"),
	SpeedUp		UMETA(DisplayName = "SpeedUp"),
	PoweredUp	UMETA(DisplayName = "PoweredUp"),
};

UCLASS()
class PACMAN3D_API APacman : public AGameCharacter
{
	GENERATED_BODY()

public:
	APacman();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
						AActor* OtherActor,
						UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex,
						bool bFromSweep,
						const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float fPowerUpDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float fTimeSincePowerup; //Time since the powerup was taken

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Lives;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsDead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pacman Variables", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pacman Variables", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pacman Variables", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<PACMAN_STATE> PacmanState;

	void PowerUp(AActor* Pickup);


};
