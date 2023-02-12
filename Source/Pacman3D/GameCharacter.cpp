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

	FVector DeltaLocation(0.f);

	DeltaLocation.X = DeltaTime * fSpeed;
	AddActorLocalOffset(DeltaLocation, true);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

