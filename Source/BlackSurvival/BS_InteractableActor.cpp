// Fill out your copyright notice in the Description page of Project Settings.


#include "BS_InteractableActor.h"

#include "Components/CapsuleComponent.h"

ABS_InteractableActor::ABS_InteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABS_InteractableActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABS_InteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABS_InteractableActor::Interact()
{
}

