#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NetGameInstance.h"
#include "NetPlayerState.generated.h"

UCLASS()
class ANetPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PlayerInfo)
    FSPlayerInfo Data;

    UPROPERTY(BlueprintReadOnly, Replicated)
    int PlayerIndex;

    UPROPERTY(BlueprintReadOnly, Replicated)
    EPlayerTeam TeamID;

    UPROPERTY(BlueprintReadOnly, Replicated)
    EGameResults Result;

private:
    UFUNCTION()
    void OnRep_PlayerInfo();
};
