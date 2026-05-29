#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZeusInteractionComponent.h"
#include "ZeusInteractableActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class UNREALPOPE_API AZeusInteractableActor : public AActor, public IZeusInteractable
{
    GENERATED_BODY()

public:
    AZeusInteractableActor();

    virtual void Interact_Implementation(AActor* InstigatorActor) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    TObjectPtr<UStaticMeshComponent> Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
    FText InteractionMessage;
};
