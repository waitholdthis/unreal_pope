#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ZeusDroneThreatActor.generated.h"

class UStaticMeshComponent;
class UFloatingPawnMovement;

UENUM(BlueprintType)
enum class EZeusDronePattern : uint8
{
    DirectTrainingRoute,
    PerimeterPatrol,
    LoiterTrainingArea
};

UCLASS()
class UNREALPOPE_API AZeusDroneThreatActor : public APawn
{
    GENERATED_BODY()

public:
    AZeusDroneThreatActor();
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category="Drone")
    void SetRoute(const TArray<FVector>& NewWaypoints);

    UFUNCTION(BlueprintPure, Category="Drone")
    float GetSimulationAge() const { return SimulationAge; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drone")
    float CruiseSpeed = 650.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drone")
    float AcceptanceRadius = 120.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drone")
    EZeusDronePattern Pattern = EZeusDronePattern::DirectTrainingRoute;

private:
    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<UStaticMeshComponent> BodyMesh;

    UPROPERTY()
    TArray<FVector> Waypoints;

    int32 CurrentWaypointIndex = 0;
    float SimulationAge = 0.0f;

    void BuildDefaultRoute();
    void AdvanceAlongRoute(float DeltaSeconds);
};
