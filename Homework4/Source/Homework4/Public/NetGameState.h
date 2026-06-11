#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameInstance.h" 
#include "NetGameState.generated.h"

UCLASS()
class ANetGameState : public AGameStateBase
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void ShowResultsScreen(EPlayerTeam WinningTeam);
};
