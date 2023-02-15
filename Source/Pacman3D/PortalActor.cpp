// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalActor.h"
#include <Components/CapsuleComponent.h>

// Sets default values
APortalActor::APortalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Portal Capsule"));
	RootComponent = CapsuleComp;

	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &APortalActor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void APortalActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (FV_TargetLocation == FVector::ZeroVector)
		FV_TargetLocation = this->GetActorLocation();
}

// Called every frame
void APortalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortalActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Triggered"));
}

