#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZeusCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UZeusInteractionComponent;

UCLASS()
class UNREALPOPE_API AZeusCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AZeusCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
    TObjectPtr<UZeusInteractionComponent> InteractionComponent;
};
