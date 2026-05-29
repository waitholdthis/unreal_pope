#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZeusTrainingWorldActor.generated.h"

class UInstancedStaticMeshComponent;
class UStaticMesh;
class UMaterialInterface;

UCLASS()
class UNREALPOPE_API AZeusTrainingWorldActor : public AActor
{
    GENERATED_BODY()

public:
    AZeusTrainingWorldActor();
    virtual void OnConstruction(const FTransform& Transform) override;

protected:
    UPROPERTY(EditAnywhere, Category="Training World|Scale")
    float WorldLength = 18000.0f;

    UPROPERTY(EditAnywhere, Category="Training World|Scale")
    float WorldWidth = 12000.0f;

    UPROPERTY(EditAnywhere, Category="Training World|Airfield")
    float RunwayLength = 10500.0f;

    UPROPERTY(EditAnywhere, Category="Training World|Airfield")
    float RunwayWidth = 550.0f;

    UPROPERTY(EditAnywhere, Category="Training World|Airfield")
    int32 HangarCount = 8;

    UPROPERTY(EditAnywhere, Category="Training World|Environment")
    int32 TreeLineCount = 160;

private:
    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<USceneComponent> SceneRoot;

    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<UInstancedStaticMeshComponent> GroundTiles;

    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<UInstancedStaticMeshComponent> RunwayTiles;

    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<UInstancedStaticMeshComponent> RoadTiles;

    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<UInstancedStaticMeshComponent> Buildings;

    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<UInstancedStaticMeshComponent> TreeLines;

    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<UInstancedStaticMeshComponent> SectorMarkers;

    UPROPERTY()
    TObjectPtr<UStaticMesh> CubeMesh;

    UPROPERTY()
    TObjectPtr<UStaticMesh> CylinderMesh;

    void RebuildWorld();
    void LoadMeshes();
    void ClearInstances();
    void AddBox(UInstancedStaticMeshComponent* Component, const FVector& Location, const FVector& Scale, const FRotator& Rotation = FRotator::ZeroRotator);
    void AddCylinder(UInstancedStaticMeshComponent* Component, const FVector& Location, const FVector& Scale, const FRotator& Rotation = FRotator::ZeroRotator);
};
