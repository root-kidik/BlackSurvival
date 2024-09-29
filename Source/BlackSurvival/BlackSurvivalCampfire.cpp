// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackSurvivalCampfire.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABlackSurvivalCampfire::ABlackSurvivalCampfire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlackSurvivalCampfire::BeginPlay()
{
	Super::BeginPlay();

	// Try and play the sound if specified
    if (FireSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
    }

	if (FireParticle)
	{
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireParticle, GetActorTransform());
	}
	
}

// Called every frame
void ABlackSurvivalCampfire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

