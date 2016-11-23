Project to show error on c++ child actor components

the problem was poster on unreal engine forum
https://answers.unrealengine.com/questions/527899/invalidated-actor-in-uchildactorcomponent-in-c.html

-------------------
Hi,

I'm having two problems with using a ChildActorComponent in a c++ actor.

the code for the problems can be found on my Github (https://github.com/Alex-B09/TestUnreal_FailedChildActor)

To make a basic setup, let's say I have 2 actors MyParentActor1 and MyChildActor1. Both have a USceneComponent RootComponent. The ParentActor have 4 ChildActors added in the constructor.

 AMyActorParent1::AMyActorParent1()
 {
     //for simplicity, all null checks have been removed
     RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Parent1"));
 
     for (int i = 0; i < 4; i++)
     {
         FString componentName = "ChildFromParent_" + FString::FromInt(i);
 
         auto childComponent = CreateDefaultSubobject<UChildActorComponent>(*componentName);
         childComponent->SetChildActorClass(AMyActorChild1::StaticClass());
         childComponent->SetupAttachment(RootComponent);
     }
 }
 
While the child only contains a static mesh (this is a test project. In my real project, I have more meshes and I want to encapsulate some actor functionalities).

 AMyActorChild1::AMyActorChild1()
 {
     // skipped mesh loading and null checks
     RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Child1"));
     mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubChild1"));
     mMesh->SetupAttachment(RootComponent);
     mMesh->SetStaticMesh(meshAsset);
 }
 
I also have a bit of processing done in MyParentActor1::OnConstruction

 void AMyActorParent1::OnConstruction(const FTransform& Transform)
 {
     Super::OnConstruction(Transform);
 
     int i = 0;
     for (auto component : RootComponent->GetAttachChildren())
     {
         if (auto child = Cast <UChildActorComponent>(component))
         {
             // change position -- skipped
 
             if (!Cast<AMyActorChild1>(child->GetChildActor()))
             {
                 // check if the child is ok
                 UE_LOG(LogTemp, Warning, TEXT("Invalid child actor"));
             }
         }
         ++i;
     }
 }
 
 
Problem 1 :

When I Insert the MyParentActor1 in the editor, everything works fine. However, when I try to resize it, I always get the warning "Invalid child actor" hence loosing everything that happend in the MyChildActor1 constructor (like setting the mMesh attribut).

Why does this happens? (or what am I doing wrong?)

Problem 2 :

When I try to create a blueprint of MyParentActor1 in the editor, I get a lot of engine errors and warnings. The 3 most noticeable being :

LogOutputDevice:Error: Ensure condition failed: false [File:D:\Build\++UE4+Release-4.14+Compile\Sync\Engine\Source\Runtime\Engine\Private\Components\SceneComponent.cpp] [Line: 1671]

LogOutputDevice:Error: Template Mismatch during attachment. Attaching instanced component to template component. Parent 'Child1' Self 'SubChild1'

LogActor:Warning: MyActorChild1 /Engine/Transient.World_3:PersistentLevel.ChildFromParent_2_MyActorChild1_CAT_15 has natively added scene component(s), but none of them were set as the actor's RootComponent - picking one arbitrarily -- repeated 3 times

And the result being the 3 (out of 4) of my child actors are stack on top of each other.

Again, I suppose that I am doing something illegal and I want to know what it is to avoid it in the future.

Thank you for your time.
