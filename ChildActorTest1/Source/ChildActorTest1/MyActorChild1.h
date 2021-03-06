// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include <Components/StaticMeshComponent.h>

#include "MyActorChild1.generated.h"

UCLASS()
class CHILDACTORTEST1_API AMyActorChild1 : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyActorChild1();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Mesh")
        UStaticMeshComponent * mMesh;
};
