#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZeusScenarioManager.generated.h"

class AZeusDroneThreatActor;
class AZeusSensorVolume;
class AZeusProtectedZone;

USTRUCT(BlueprintType)
struct FZeusSimulationEvent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    float TimeSeconds = 0.0f;

    UPROPERTY(BlueprintReadOnly)
    FString EventType;

    UPROPERTY(BlueprintReadOnly)
    FString Description;
};

UCLASS()
class UNREALPOPE_API AZeusScenarioManager : public AActor
{
    GENERATED_BODY()

public:
    AZeusScenarioManager();
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category="Scenario")
    void StartScenario();

    UFUNCTION(BlueprintCallable, Category="Scenario")
    void StopScenario();

    UFUNCTION(BlueprintCallable, Category="Scenario")
    void RegisterDrone(AZeusDroneThreatActor* Drone);

    UFUNCTION(BlueprintCallable, Category="Scenario")
    void RegisterSensor(AZeusSensorVolume* Sensor);

    UFUNCTION(BlueprintPure, Category="Scenario")
    const TArray<FZeusSimulationEvent>& GetEventLog() const { return EventLog; }

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TArray<TObjectPtr<AZeusDroneThreatActor>> Drones;

    UPROPERTY()
    TArray<TObjectPtr<AZeusSensorVolume>> Sensors;

    UPROPERTY()
    TArray<FZeusSimulationEvent> EventLog;

    UPROPERTY(EditAnywhere, Category="Scenario")
    bool bAutoDiscoverActors = true;

    bool bScenarioRunning = false;
    float ScenarioTime = 0.0f;

    TSet<TWeakObjectPtr<AZeusDroneThreatActor>> DetectedDrones;

    void AutoDiscoverActors();
    void RecordEvent(const FString& EventType, const FString& Description);
};
