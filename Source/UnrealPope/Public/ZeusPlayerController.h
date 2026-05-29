#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZeusPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class UNREALPOPE_API AZeusPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AZeusPlayerController();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category="Input")
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly, Category="Input")
    int32 MappingPriority = 0;
};
