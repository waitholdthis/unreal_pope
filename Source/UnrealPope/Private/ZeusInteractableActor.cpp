#include "ZeusInteractableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

AZeusInteractableActor::AZeusInteractableActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);

    InteractionMessage = FText::FromString(TEXT("The relic answers."));
}

void AZeusInteractableActor::Interact_Implementation(AActor* InstigatorActor)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor(255, 215, 0), InteractionMessage.ToString());
    }
}
