// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:
	float startingYaw;
	float currentYaw;
	float doorLastOpened = 0.f;
	float doorCloseDelay = 0.5.f;
	UPROPERTY(EditAnywhere)
		float targetYaw = 90.f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens;
};
