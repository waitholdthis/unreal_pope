#include "ZeusDroneThreatActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AZeusDroneThreatActor::AZeusDroneThreatActor()
{
    PrimaryActorTick.bCanEverTick = true;

    BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
    SetRootComponent(BodyMesh);
    BodyMesh->SetCollisionProfileName(TEXT("Pawn"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeFinder(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeFinder.Succeeded())
    {
        BodyMesh->SetStaticMesh(CubeFinder.Object);
        BodyMesh->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.18f));
    }
}

void AZeusDroneThreatActor::BeginPlay()
{
    Super::BeginPlay();
    if (Waypoints.Num() == 0)
    {
        BuildDefaultRoute();
    }
}

void AZeusDroneThreatActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    SimulationAge += DeltaSeconds;
    AdvanceAlongRoute(DeltaSeconds);
}

void AZeusDroneThreatActor::SetRoute(const TArray<FVector>& NewWaypoints)
{
    Waypoints = NewWaypoints;
    CurrentWaypointIndex = 0;
}

void AZeusDroneThreatActor::BuildDefaultRoute()
{
    const float Altitude = 850.0f;
    switch (Pattern)
    {
    case EZeusDronePattern::PerimeterPatrol:
        Waypoints = {
            FVector(-6500.0f, -4600.0f, Altitude),
            FVector(6500.0f, -4600.0f, Altitude),
            FVector(6500.0f, 4600.0f, Altitude),
            FVector(-6500.0f, 4600.0f, Altitude)
        };
        break;
    case EZeusDronePattern::LoiterTrainingArea:
        Waypoints = {
            FVector(-1500.0f, 1800.0f, Altitude),
            FVector(1500.0f, 1800.0f, Altitude),
            FVector(1500.0f, 3200.0f, Altitude),
            FVector(-1500.0f, 3200.0f, Altitude)
        };
        break;
    case EZeusDronePattern::DirectTrainingRoute:
    default:
        Waypoints = {
            FVector(-7800.0f, -3600.0f, Altitude),
            FVector(-3200.0f, -1200.0f, Altitude),
            FVector(0.0f, 0.0f, Altitude),
            FVector(3600.0f, 1400.0f, Altitude),
            FVector(7600.0f, 3600.0f, Altitude)
        };
        break;
    }
}

void AZeusDroneThreatActor::AdvanceAlongRoute(float DeltaSeconds)
{
    if (Waypoints.Num() == 0)
    {
        return;
    }

    const FVector CurrentLocation = GetActorLocation();
    const FVector Target = Waypoints[CurrentWaypointIndex];
    const FVector ToTarget = Target - CurrentLocation;

    if (ToTarget.SizeSquared() <= FMath::Square(AcceptanceRadius))
    {
        CurrentWaypointIndex = (CurrentWaypointIndex + 1) % Waypoints.Num();
        return;
    }

    const FVector Direction = ToTarget.GetSafeNormal();
    const FVector NextLocation = CurrentLocation + Direction * CruiseSpeed * DeltaSeconds;
    SetActorLocation(NextLocation);
    SetActorRotation(Direction.Rotation());
}
