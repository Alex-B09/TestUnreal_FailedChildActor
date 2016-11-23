// Fill out your copyright notice in the Description page of Project Settings.

#include "ChildActorTest1.h"
#include "MyActorParent1.h"
#include "MyActorChild1.h"
#include <Components/ChildActorComponent.h>


// Sets default values
AMyActorParent1::AMyActorParent1()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Board"));
    }

    for (int i = 0; i < 4; i++)
    {
        FString componentName = "ChildFromParent_" + FString::FromInt(i);

        auto childComponent = CreateDefaultSubobject<UChildActorComponent>(*componentName);
        childComponent->SetChildActorClass(AMyActorChild1::StaticClass());
        childComponent->SetupAttachment(RootComponent);
    }
}

// Called when the game starts or when spawned
void AMyActorParent1::BeginPlay()
{
    Super::BeginPlay();
}

void AMyActorParent1::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    const float TILE_SIZE_Y = 200.f * Transform.GetScale3D().Y + 20.f;

    int i = 0;
    for (auto component : RootComponent->GetAttachChildren())
    {
        if (auto child = Cast <UChildActorComponent>(component))
        {
            FVector location(0, i * TILE_SIZE_Y, 10.f);

            FTransform relativeTransform;
            relativeTransform.SetLocation(location);
            child->AddLocalTransform(relativeTransform);

            if (!Cast<AMyActorChild1>(child->GetChildActor()))
            {
                UE_LOG(LogTemp, Warning, TEXT("Invalid child actor"));
            }
        }
        ++i;
    }
}
