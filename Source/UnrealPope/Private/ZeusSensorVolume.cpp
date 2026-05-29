#include "ZeusSensorVolume.h"
#include "ZeusDroneThreatActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AZeusSensorVolume::AZeusSensorVolume()
{
    PrimaryActorTick.bCanEverTick = true;

    DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
    SetRootComponent(DetectionSphere);
    DetectionSphere->SetSphereRadius(DetectionRadius);
    DetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    DetectionSphere->SetCollisionResponseToAllChannels(ECR_Overlap);

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    VisualMesh->SetupAttachment(DetectionSphere);
    VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereFinder(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereFinder.Succeeded())
    {
        VisualMesh->SetStaticMesh(SphereFinder.Object);
        VisualMesh->SetRelativeScale3D(FVector(DetectionRadius / 50.0f));
    }
}

void AZeusSensorVolume::BeginPlay()
{
    Super::BeginPlay();
    DetectionSphere->SetSphereRadius(DetectionRadius);
}

void AZeusSensorVolume::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

bool AZeusSensorVolume::IsDroneDetected(const AZeusDroneThreatActor* Drone) const
{
    if (!Drone)
    {
        return false;
    }

    return FVector::DistSquared(GetActorLocation(), Drone->GetActorLocation()) <= FMath::Square(DetectionRadius);
}
