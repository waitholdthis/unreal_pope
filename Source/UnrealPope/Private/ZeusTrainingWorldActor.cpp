#include "ZeusTrainingWorldActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"

AZeusTrainingWorldActor::AZeusTrainingWorldActor()
{
    PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    GroundTiles = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GroundTiles"));
    GroundTiles->SetupAttachment(SceneRoot);

    RunwayTiles = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("RunwayTiles"));
    RunwayTiles->SetupAttachment(SceneRoot);

    RoadTiles = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("RoadTiles"));
    RoadTiles->SetupAttachment(SceneRoot);

    Buildings = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Buildings"));
    Buildings->SetupAttachment(SceneRoot);

    TreeLines = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeLines"));
    TreeLines->SetupAttachment(SceneRoot);

    SectorMarkers = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("SectorMarkers"));
    SectorMarkers->SetupAttachment(SceneRoot);

    LoadMeshes();
}

void AZeusTrainingWorldActor::LoadMeshes()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeFinder(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderFinder(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));

    if (CubeFinder.Succeeded())
    {
        CubeMesh = CubeFinder.Object;
        GroundTiles->SetStaticMesh(CubeMesh);
        RunwayTiles->SetStaticMesh(CubeMesh);
        RoadTiles->SetStaticMesh(CubeMesh);
        Buildings->SetStaticMesh(CubeMesh);
        TreeLines->SetStaticMesh(CubeMesh);
    }

    if (CylinderFinder.Succeeded())
    {
        CylinderMesh = CylinderFinder.Object;
        SectorMarkers->SetStaticMesh(CylinderMesh);
    }
}

void AZeusTrainingWorldActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    RebuildWorld();
}

void AZeusTrainingWorldActor::ClearInstances()
{
    GroundTiles->ClearInstances();
    RunwayTiles->ClearInstances();
    RoadTiles->ClearInstances();
    Buildings->ClearInstances();
    TreeLines->ClearInstances();
    SectorMarkers->ClearInstances();
}

void AZeusTrainingWorldActor::AddBox(UInstancedStaticMeshComponent* Component, const FVector& Location, const FVector& Scale, const FRotator& Rotation)
{
    if (!Component)
    {
        return;
    }

    Component->AddInstance(FTransform(Rotation, Location, Scale));
}

void AZeusTrainingWorldActor::AddCylinder(UInstancedStaticMeshComponent* Component, const FVector& Location, const FVector& Scale, const FRotator& Rotation)
{
    if (!Component)
    {
        return;
    }

    Component->AddInstance(FTransform(Rotation, Location, Scale));
}

void AZeusTrainingWorldActor::RebuildWorld()
{
    ClearInstances();

    // Abstracted, non-operational large-base environment: realistic scale and atmosphere without reproducing sensitive layouts.
    AddBox(GroundTiles, FVector(0.0f, 0.0f, -25.0f), FVector(WorldLength / 100.0f, WorldWidth / 100.0f, 0.25f));

    // Main runway and shoulders.
    AddBox(RunwayTiles, FVector(0.0f, 0.0f, 4.0f), FVector(RunwayLength / 100.0f, RunwayWidth / 100.0f, 0.08f));
    AddBox(RunwayTiles, FVector(0.0f, RunwayWidth * 0.72f, 2.0f), FVector(RunwayLength / 100.0f, 1.2f, 0.04f));
    AddBox(RunwayTiles, FVector(0.0f, -RunwayWidth * 0.72f, 2.0f), FVector(RunwayLength / 100.0f, 1.2f, 0.04f));

    // Taxiway and apron blocks.
    AddBox(RoadTiles, FVector(0.0f, 1200.0f, 6.0f), FVector(RunwayLength / 115.0f, 2.0f, 0.05f));
    AddBox(RoadTiles, FVector(-2700.0f, 1800.0f, 6.0f), FVector(22.0f, 12.0f, 0.05f));
    AddBox(RoadTiles, FVector(2600.0f, 1800.0f, 6.0f), FVector(18.0f, 10.0f, 0.05f));

    // Generic hangars and support buildings, deliberately non-real placement.
    for (int32 Index = 0; Index < HangarCount; ++Index)
    {
        const float X = -4200.0f + Index * 1200.0f;
        const float Y = 2550.0f + (Index % 2) * 450.0f;
        AddBox(Buildings, FVector(X, Y, 150.0f), FVector(5.0f, 3.5f, 1.5f));
    }

    // Generic administrative/training structures.
    for (int32 Row = 0; Row < 3; ++Row)
    {
        for (int32 Col = 0; Col < 5; ++Col)
        {
            AddBox(Buildings, FVector(-2400.0f + Col * 650.0f, -2400.0f - Row * 520.0f, 90.0f), FVector(3.0f, 2.0f, 0.9f));
        }
    }

    // Woodline/perimeter atmosphere represented as low-poly vertical markers.
    for (int32 Index = 0; Index < TreeLineCount; ++Index)
    {
        const float T = static_cast<float>(Index) / FMath::Max(1, TreeLineCount - 1);
        const float X = -WorldLength * 0.48f + T * WorldLength * 0.96f;
        const float Wave = FMath::Sin(T * PI * 8.0f) * 240.0f;
        AddBox(TreeLines, FVector(X, WorldWidth * 0.46f + Wave, 160.0f), FVector(0.9f, 0.9f, 3.2f));
        AddBox(TreeLines, FVector(X, -WorldWidth * 0.46f - Wave, 160.0f), FVector(0.9f, 0.9f, 3.2f));
    }

    // Sector markers for defensive training overlays.
    const FVector MarkerScale(2.0f, 2.0f, 0.08f);
    AddCylinder(SectorMarkers, FVector(-5200.0f, 4200.0f, 12.0f), MarkerScale);
    AddCylinder(SectorMarkers, FVector(0.0f, 4600.0f, 12.0f), MarkerScale);
    AddCylinder(SectorMarkers, FVector(5200.0f, 4200.0f, 12.0f), MarkerScale);
    AddCylinder(SectorMarkers, FVector(-5200.0f, -4200.0f, 12.0f), MarkerScale);
    AddCylinder(SectorMarkers, FVector(0.0f, -4600.0f, 12.0f), MarkerScale);
    AddCylinder(SectorMarkers, FVector(5200.0f, -4200.0f, 12.0f), MarkerScale);
}
