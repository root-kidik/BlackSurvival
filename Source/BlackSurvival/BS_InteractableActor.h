// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BS_InteractableActor.generated.h"

UCLASS()
class BLACKSURVIVAL_API ABS_InteractableActor : public AActor
{
	GENERATED_BODY()
	
public:
	ABS_InteractableActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
    
	virtual void Interact();
};
