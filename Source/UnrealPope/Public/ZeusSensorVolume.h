#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZeusSensorVolume.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class AZeusDroneThreatActor;

UCLASS()
class UNREALPOPE_API AZeusSensorVolume : public AActor
{
    GENERATED_BODY()

public:
    AZeusSensorVolume();
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category="Sensor")
    bool IsDroneDetected(const AZeusDroneThreatActor* Drone) const;

    UFUNCTION(BlueprintPure, Category="Sensor")
    float GetDetectionRadius() const { return DetectionRadius; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sensor")
    float DetectionRadius = 1800.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sensor")
    float ClassificationDelaySeconds = 2.5f;

private:
    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<USphereComponent> DetectionSphere;

    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<UStaticMeshComponent> VisualMesh;
};
