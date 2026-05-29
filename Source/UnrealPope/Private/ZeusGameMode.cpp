#include "ZeusGameMode.h"
#include "ZeusCharacter.h"
#include "ZeusPlayerController.h"

AZeusGameMode::AZeusGameMode()
{
    DefaultPawnClass = AZeusCharacter::StaticClass();
    PlayerControllerClass = AZeusPlayerController::StaticClass();
}
