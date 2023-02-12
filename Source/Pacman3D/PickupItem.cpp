// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"
#include <Components/CapsuleComponent.h>

// Sets default values
APickupItem::APickupItem()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Pickup Capsule"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Static Mesh"));

	RootComponent = CapsuleComp;
	Mesh->SetupAttachment(CapsuleComp);

}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.f, fPickupRotationSpeed, 0.f));

}

// Called to bind functionality to input
void APickupItem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

