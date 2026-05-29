#include "ZeusInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"

UZeusInteractionComponent::UZeusInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool UZeusInteractionComponent::TryInteract()
{
    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return false;
    }

    FVector ViewLocation;
    FRotator ViewRotation;

    if (const APawn* PawnOwner = Cast<APawn>(Owner))
    {
        if (AController* Controller = PawnOwner->GetController())
        {
            Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
        }
        else
        {
            ViewLocation = Owner->GetActorLocation();
            ViewRotation = Owner->GetActorRotation();
        }
    }
    else
    {
        ViewLocation = Owner->GetActorLocation();
        ViewRotation = Owner->GetActorRotation();
    }

    const FVector TraceEnd = ViewLocation + (ViewRotation.Vector() * TraceDistance);

    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(ZeusInteractionTrace), false, Owner);

    if (!GetWorld() || !GetWorld()->LineTraceSingleByChannel(Hit, ViewLocation, TraceEnd, TraceChannel, Params))
    {
        return false;
    }

    AActor* HitActor = Hit.GetActor();
    if (HitActor && HitActor->GetClass()->ImplementsInterface(UZeusInteractable::StaticClass()))
    {
        IZeusInteractable::Execute_Interact(HitActor, Owner);
        return true;
    }

    return false;
}
