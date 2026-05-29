#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZeusProtectedZone.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class UNREALPOPE_API AZeusProtectedZone : public AActor
{
    GENERATED_BODY()

public:
    AZeusProtectedZone();

    UFUNCTION(BlueprintPure, Category="Protected Zone")
    FName GetZoneName() const { return ZoneName; }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Protected Zone")
    FName ZoneName = TEXT("TrainingZone");

private:
    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<UBoxComponent> ZoneBounds;

    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<UStaticMeshComponent> VisualMesh;
};
