#include "NetGameMode.h"
#include "NetPlayerState.h"
#include "NetAvatar.h"
#include "NetGameState.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"

ANetGameMode::ANetGameMode()
{
    PlayerStateClass = ANetPlayerState::StaticClass();
    DefaultPawnClass = ANetAvatar::StaticClass();
    GameStateClass = ANetGameState::StaticClass();
}

void ANetGameMode::BeginPlay()
{
    Super::BeginPlay();


    GetWorld()->GetTimerManager().SetTimer(BlueTeamWinTimer, this, &ANetGameMode::OnBlueTeamTimeout, 30.0f, false);
}

void ANetGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    ANetPlayerState* PS = NewPlayer->GetPlayerState<ANetPlayerState>();
    if (PS) {

        if (GetNumPlayers() == 1) {
            PS->TeamID = EPlayerTeam::TEAM_Blue;
        }
        else {
            PS->TeamID = EPlayerTeam::TEAM_Red;
        }
    }
}

void ANetGameMode::OnBlueTeamTimeout()
{

    ANetPlayerState* WinningBluePlayer = nullptr;
    TArray<ANetPlayerState*> RedTeamPlayers;


    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (PC && PC->PlayerState)
        {
            ANetPlayerState* PS = Cast<ANetPlayerState>(PC->PlayerState);
            if (PS) {
                if (PS->TeamID == EPlayerTeam::TEAM_Blue) WinningBluePlayer = PS;
                else if (PS->TeamID == EPlayerTeam::TEAM_Red) RedTeamPlayers.Add(PS);
            }
        }
    }


    if (WinningBluePlayer && RedTeamPlayers.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, RedTeamPlayers.Num() - 1);
        ANetPlayerState* SwappedRedPlayer = RedTeamPlayers[RandomIndex];


        WinningBluePlayer->TeamID = EPlayerTeam::TEAM_Red;
        SwappedRedPlayer->TeamID = EPlayerTeam::TEAM_Blue;
    }


    ANetGameState* GS = GetGameState<ANetGameState>();
    if (GS) {
        GS->ShowResultsScreen(EPlayerTeam::TEAM_Blue);
    }
}