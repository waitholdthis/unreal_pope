#include "ZeusProtectedZone.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AZeusProtectedZone::AZeusProtectedZone()
{
    PrimaryActorTick.bCanEverTick = false;

    ZoneBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("ZoneBounds"));
    SetRootComponent(ZoneBounds);
    ZoneBounds->SetBoxExtent(FVector(600.0f, 600.0f, 200.0f));
    ZoneBounds->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    VisualMesh->SetupAttachment(ZoneBounds);
    VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeFinder(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeFinder.Succeeded())
    {
        VisualMesh->SetStaticMesh(CubeFinder.Object);
        VisualMesh->SetRelativeScale3D(FVector(12.0f, 12.0f, 0.05f));
    }
}
