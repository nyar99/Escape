// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has open door component but no pressure plate set"), *GetOwner()->GetName());
	}
	startingYaw = GetOwner()->GetActorRotation().Yaw;
	targetYaw += startingYaw;
	currentYaw = startingYaw;

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
	if (PressurePlate ->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor(DeltaTime);
		doorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else {
		if (GetWorld()->GetTimeSeconds() - doorLastOpened > doorCloseDelay) {
			CloseDoor(DeltaTime);
		}
	}

	
}

void UOpenDoor::OpenDoor(float DeltaTime) {
	currentYaw = FMath::Lerp(currentYaw, targetYaw, DeltaTime * 1.f);
	FRotator* doorRotation = new FRotator(0.f, currentYaw, 0.f);
	GetOwner()->SetActorRotation(*doorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime) {
	currentYaw = FMath::Lerp(currentYaw, startingYaw, DeltaTime * 2.f);
	FRotator* doorRotation = new FRotator(0.f, currentYaw, 0.f);
	GetOwner()->SetActorRotation(*doorRotation);
}

