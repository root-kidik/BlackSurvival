// Fill out your copyright notice in the Description page of Project Settings.


#include "BS_CampfireActor.h"

#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

DEFINE_LOG_CATEGORY(LogCampfireActor);
ABS_CampfireActor::ABS_CampfireActor()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    SetRootComponent(MeshComponent);

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootComponent);

    ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
    ParticleSystemComponent->SetupAttachment(RootComponent);
}

void ABS_CampfireActor::BeginPlay()
{
    Super::BeginPlay();

    check(FireSound);
    check(FireParticle);
    check(MeshWithoutWood);
    check(MeshWithWood);

    MeshComponent->SetStaticMesh(MeshWithoutWood);
    AudioComponent->SetSound(FireSound);

    ParticleSystemComponent->SetTemplate(FireParticle);
    ParticleSystemComponent->DeactivateSystem();
}

void ABS_CampfireActor::Interact()
{
    bIsHasWood = !bIsHasWood;

    if (bIsHasWood)
    {
        MeshComponent->SetStaticMesh(MeshWithWood);
        AudioComponent->Play();
        ParticleSystemComponent->ActivateSystem();
    }
    else
    {
        MeshComponent->SetStaticMesh(MeshWithoutWood);
        AudioComponent->Stop();
        ParticleSystemComponent->DeactivateSystem();
    }
}

void ABS_CampfireActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
