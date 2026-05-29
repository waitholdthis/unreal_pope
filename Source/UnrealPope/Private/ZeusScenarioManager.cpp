#include "ZeusScenarioManager.h"
#include "ZeusDroneThreatActor.h"
#include "ZeusSensorVolume.h"
#include "EngineUtils.h"

AZeusScenarioManager::AZeusScenarioManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AZeusScenarioManager::BeginPlay()
{
    Super::BeginPlay();
    if (bAutoDiscoverActors)
    {
        AutoDiscoverActors();
    }
}

void AZeusScenarioManager::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!bScenarioRunning)
    {
        return;
    }

    ScenarioTime += DeltaSeconds;

    for (AZeusDroneThreatActor* Drone : Drones)
    {
        if (!Drone || DetectedDrones.Contains(Drone))
        {
            continue;
        }

        for (AZeusSensorVolume* Sensor : Sensors)
        {
            if (Sensor && Sensor->IsDroneDetected(Drone))
            {
                DetectedDrones.Add(Drone);
                RecordEvent(TEXT("Detection"), FString::Printf(TEXT("Generic drone detected by training sensor at %.1f seconds."), ScenarioTime));
                break;
            }
        }
    }
}

void AZeusScenarioManager::StartScenario()
{
    if (bAutoDiscoverActors)
    {
        AutoDiscoverActors();
    }

    EventLog.Reset();
    DetectedDrones.Reset();
    ScenarioTime = 0.0f;
    bScenarioRunning = true;
    RecordEvent(TEXT("Scenario"), TEXT("Defensive training scenario started."));
}

void AZeusScenarioManager::StopScenario()
{
    bScenarioRunning = false;
    RecordEvent(TEXT("Scenario"), TEXT("Defensive training scenario stopped."));
}

void AZeusScenarioManager::RegisterDrone(AZeusDroneThreatActor* Drone)
{
    if (Drone)
    {
        Drones.AddUnique(Drone);
    }
}

void AZeusScenarioManager::RegisterSensor(AZeusSensorVolume* Sensor)
{
    if (Sensor)
    {
        Sensors.AddUnique(Sensor);
    }
}

void AZeusScenarioManager::AutoDiscoverActors()
{
    Drones.Reset();
    Sensors.Reset();

    for (TActorIterator<AZeusDroneThreatActor> It(GetWorld()); It; ++It)
    {
        Drones.Add(*It);
    }

    for (TActorIterator<AZeusSensorVolume> It(GetWorld()); It; ++It)
    {
        Sensors.Add(*It);
    }
}

void AZeusScenarioManager::RecordEvent(const FString& EventType, const FString& Description)
{
    FZeusSimulationEvent Event;
    Event.TimeSeconds = ScenarioTime;
    Event.EventType = EventType;
    Event.Description = Description;
    EventLog.Add(Event);
}
