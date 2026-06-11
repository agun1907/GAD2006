#include "NetPlayerState.h"
#include "NetBaseCharacter.h"
#include "Net/UnrealNetwork.h"

void ANetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ANetPlayerState, Data);
    DOREPLIFETIME(ANetPlayerState, PlayerIndex);
    DOREPLIFETIME(ANetPlayerState, TeamID);
    DOREPLIFETIME(ANetPlayerState, Result);
}

void ANetPlayerState::OnRep_PlayerInfo()
{
    ANetBaseCharacter* Char = Cast<ANetBaseCharacter>(GetPawn());
    if (Char) {
        Char->PlayerInfoReceived = true;
    }
    else {
        FTimerHandle PlayerInfoUpdateTimer;
        GetWorld()->GetTimerManager().SetTimer(PlayerInfoUpdateTimer, this, &ANetPlayerState::OnRep_PlayerInfo, 0.25f, false);
    }
}