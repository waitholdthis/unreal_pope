#include "ZeusPlayerController.h"
#include "EnhancedInputSubsystems.h"

AZeusPlayerController::AZeusPlayerController()
{
    bShowMouseCursor = false;
}

void AZeusPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (DefaultMappingContext)
            {
                Subsystem->AddMappingContext(DefaultMappingContext, MappingPriority);
            }
        }
    }
}
