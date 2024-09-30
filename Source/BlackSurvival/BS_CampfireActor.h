// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BS_InteractableActor.h"
#include "BS_CampfireActor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCampfireActor, Log, All);

UCLASS()
class BLACKSURVIVAL_API ABS_CampfireActor : public ABS_InteractableActor
{
	GENERATED_BODY()
	
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
    UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
    USoundBase* FireSound;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle", meta = (AllowPrivateAccess = "true"))
    UParticleSystemComponent* ParticleSystemComponent; 

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle", meta = (AllowPrivateAccess = "true"))
    UParticleSystem* FireParticle;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
    UStaticMesh* MeshWithoutWood;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
    UStaticMesh* MeshWithWood;

public:
    ABS_CampfireActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void Interact() override;

private:
    bool bIsHasWood = false;
};
