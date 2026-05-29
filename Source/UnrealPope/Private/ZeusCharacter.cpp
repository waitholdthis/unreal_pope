#include "ZeusCharacter.h"
#include "ZeusInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AZeusCharacter::AZeusCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 420.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    InteractionComponent = CreateDefaultSubobject<UZeusInteractionComponent>(TEXT("InteractionComponent"));
}

void AZeusCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AZeusCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind Enhanced Input actions in a Blueprint subclass or extend AZeusPlayerController
    // once IA_Move, IA_Look, and IA_Interact assets are created in Content/Input.
}
