// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyActorParent1.generated.h"

UCLASS()
class CHILDACTORTEST1_API AMyActorParent1 : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyActorParent1();

    // Called when the game starts or when spawned
    void BeginPlay() override;
    void OnConstruction(const FTransform& Transform) override;
};
