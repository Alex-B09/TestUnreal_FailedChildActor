// Fill out your copyright notice in the Description page of Project Settings.

#include "ChildActorTest1.h"
#include "MyActorChild1.h"


// Sets default values
AMyActorChild1::AMyActorChild1()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> staticMesh(TEXT("StaticMesh'/Game/someMesh.someMesh'"));
    UStaticMesh * meshAsset = staticMesh.Object;

    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Child1"));
    }

    mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubChild1"));
    if (mMesh)
    {
        mMesh->SetupAttachment(RootComponent);
        mMesh->SetStaticMesh(meshAsset);
    }
}

// Called when the game starts or when spawned
void AMyActorChild1::BeginPlay()
{
    Super::BeginPlay();
}
