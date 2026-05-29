#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZeusInteractionComponent.generated.h"

UINTERFACE(BlueprintType)
class UNREALPOPE_API UZeusInteractable : public UInterface
{
    GENERATED_BODY()
};

class UNREALPOPE_API IZeusInteractable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
    void Interact(AActor* InstigatorActor);
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALPOPE_API UZeusInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UZeusInteractionComponent();

    UFUNCTION(BlueprintCallable, Category="Interaction")
    bool TryInteract();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
    float TraceDistance = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
    TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;
};
