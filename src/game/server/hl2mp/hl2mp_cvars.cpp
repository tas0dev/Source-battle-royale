//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "hl2mp_cvars.h"
#include "hl2mp_gamerules.h"
#include "hl2mp_player.h"

ConVar mp_readyrestart(
    "mp_readyrestart",
    "0",
    FCVAR_GAMEDLL,
    "If non-zero, game will restart once each player gives the ready signal");

ConVar mp_ready_signal(
    "mp_ready_signal",
    "ready",
    FCVAR_GAMEDLL,
    "Text that each player must speak for the match to begin");

ConVar br_min_players(
    "br_min_players",
    "1",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Minimum players required to start a battle royale round",
    true,
    1.0f,
    true,
    static_cast<float>(MAX_PLAYERS));

ConVar br_countdown_time(
    "br_countdown_time",
    "5",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Countdown duration before a round starts",
    true,
    1.0f,
    true,
    60.0f);

ConVar br_round_time(
    "br_round_time",
    "480",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Maximum battle royale round duration in seconds",
    true,
    30.0f,
    true,
    1800.0f);

ConVar br_restart_time(
    "br_restart_time",
    "10",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Delay before starting the next round",
    true,
    3.0f,
    true,
    60.0f);

CON_COMMAND_F(
    br_test_status,
    "Prints the current battle royale state",
    FCVAR_GAMEDLL)
{
    CHL2MPRules *rules = HL2MPRules();

    if (!rules)
    {
        Warning(
            "[BR TEST] Game rules are unavailable\n");

        return;
    }

    CBasePlayer *lastAlive = NULL;

    const int playerCount =
        rules->GetBattleRoyalePlayerCount();

    const int aliveCount =
        rules->GetBattleRoyaleAliveCount(
            &lastAlive);

    Msg(
        "[BR TEST] state=%s players=%d alive=%d",
        rules->GetBattleRoyaleStateName(),
        playerCount,
        aliveCount);

    if (lastAlive)
    {
        Msg(
            " last_alive=\"%s\"",
            lastAlive->GetPlayerName());
    }

    Msg("\n");
}

CON_COMMAND_F(
    br_test_start,
    "Immediately starts a battle royale round",
    FCVAR_GAMEDLL | FCVAR_CHEAT)
{
    CHL2MPRules *rules = HL2MPRules();

    if (!rules)
    {
        Warning(
            "[BR TEST] Game rules are unavailable\n");

        return;
    }

    Msg(
        "[BR TEST] Forcing round start\n");

    rules->StartBattleRoyaleRound();
}

CON_COMMAND_F(
    br_test_finish,
    "Immediately finishes the current round",
    FCVAR_GAMEDLL | FCVAR_CHEAT)
{
    CHL2MPRules *rules = HL2MPRules();

    if (!rules)
    {
        Warning(
            "[BR TEST] Game rules are unavailable\n");

        return;
    }

    Msg(
        "[BR TEST] Forcing round finish\n");

    rules->FinishBattleRoyaleRound(
        NULL);
}

CON_COMMAND_F(
    br_test_eliminate,
    "Eliminates the command client",
    FCVAR_GAMEDLL | FCVAR_CHEAT)
{
    CHL2MP_Player *player =
        ToHL2MPPlayer(
            UTIL_GetCommandClient());

    if (!player)
    {
        Warning(
            "[BR TEST] Run this command "
            "from a listen-server client\n");

        return;
    }

    CHL2MPRules *rules = HL2MPRules();

    if (
        !rules ||
        !rules->IsBattleRoyaleRoundActive())
    {
        Warning(
            "[BR TEST] No active round\n");

        return;
    }

    if (
        !player->IsBattleRoyaleParticipant())
    {
        Warning(
            "[BR TEST] Player is not "
            "a round participant\n");

        return;
    }

    Msg(
        "[BR TEST] Eliminating %s\n",
        player->GetPlayerName());

    CBaseEntity *playerEntity = player;

    CTakeDamageInfo damage(
        playerEntity,
        playerEntity,
        10000.0f,
        DMG_GENERIC);

    player->TakeDamage(
        damage);
}

CON_COMMAND_F(
    br_test_late_join,
    "Simulates joining during an active round",
    FCVAR_GAMEDLL | FCVAR_CHEAT)
{
    CHL2MP_Player *player =
        ToHL2MPPlayer(
            UTIL_GetCommandClient());

    if (!player)
    {
        Warning(
            "[BR TEST] Run this command "
            "from a listen-server client\n");

        return;
    }

    player->SetBattleRoyaleParticipant(
        false);

    player->EnterBattleRoyaleObserver();

    Msg(
        "[BR TEST] %s moved to "
        "late-join observer mode\n",
        player->GetPlayerName());
}

CON_COMMAND_F(
    br_test_reset,
    "Resets the battle royale round",
    FCVAR_GAMEDLL | FCVAR_CHEAT)
{
    CHL2MPRules *rules = HL2MPRules();

    if (!rules)
    {
        Warning(
            "[BR TEST] Game rules are unavailable\n");

        return;
    }

    rules->ResetBattleRoyaleRoundForTesting();
}

CON_COMMAND_F(
    br_zone_status,
    "Prints the battle royale zone status",
    FCVAR_GAMEDLL)
{
    CHL2MPRules *rules =
        HL2MPRules();

    if (!rules)
    {
        Warning(
            "[BR ZONE] Game rules are unavailable\n");

        return;
    }

    rules->PrintBattleRoyaleZoneStatus();
}

CON_COMMAND_F(
    br_test_zone_start,
    "Starts or restarts the battle royale zone",
    FCVAR_GAMEDLL | FCVAR_CHEAT)
{
    CHL2MPRules *rules =
        HL2MPRules();

    if (!rules)
    {
        Warning(
            "[BR ZONE] Game rules are unavailable\n");

        return;
    }

    if (!rules->IsBattleRoyaleRoundActive())
    {
        rules->StartBattleRoyaleRound();
    }

    rules->StartBattleRoyaleZone();
}

CON_COMMAND_F(
    br_test_zone_next,
    "Advances the battle royale zone phase",
    FCVAR_GAMEDLL | FCVAR_CHEAT)
{
    CHL2MPRules *rules =
        HL2MPRules();

    if (!rules)
    {
        Warning(
            "[BR ZONE] Game rules are unavailable\n");

        return;
    }

    rules->AdvanceBattleRoyaleZone();
}

CON_COMMAND_F(
    br_test_zone_stop,
    "Stops the battle royale zone",
    FCVAR_GAMEDLL | FCVAR_CHEAT)
{
    CHL2MPRules *rules =
        HL2MPRules();

    if (!rules)
    {
        Warning(
            "[BR ZONE] Game rules are unavailable\n");

        return;
    }

    rules->StopBattleRoyaleZone();
}

ConVar br_winner_crate_count(
    "br_winner_crate_count",
    "40",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Number of crates dropped on the winner",
    true,
    0.0f,
    true,
    128.0f);

ConVar br_winner_crate_spread(
    "br_winner_crate_spread",
    "220",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Horizontal spread of winner crates",
    true,
    0.0f,
    true,
    1024.0f);

ConVar br_winner_crate_height(
    "br_winner_crate_height",
    "160",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Minimum height of winner crates",
    true,
    64.0f,
    true,
    1024.0f);

CON_COMMAND_F(
    br_test_win,
    "Makes the command client win immediately",
    FCVAR_GAMEDLL | FCVAR_CHEAT)
{
    CHL2MP_Player *player =
        ToHL2MPPlayer(
            UTIL_GetCommandClient());

    if (!player)
    {
        Warning(
            "[BR TEST] Run this command "
            "from a listen-server client\n");

        return;
    }

    CHL2MPRules *rules =
        HL2MPRules();

    if (!rules)
    {
        Warning(
            "[BR TEST] Game rules are unavailable\n");

        return;
    }

    if (
        player->GetTeamNumber() ==
        TEAM_SPECTATOR)
    {
        player->ChangeTeam(
            TEAM_UNASSIGNED);
    }

    if (
        !rules->IsBattleRoyaleRoundActive() ||
        !player->IsAlive() ||
        !player->IsBattleRoyaleParticipant())
    {
        rules->StartBattleRoyaleRound();
    }

    Msg(
        "[BR TEST] Forcing %s to win\n",
        player->GetPlayerName());

    rules->FinishBattleRoyaleRound(
        player);
}

ConVar br_winner_prop_batch_size(
    "br_winner_prop_batch_size",
    "100",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Number of winner props spawned per batch",
    true,
    1.0f,
    true,
    64.0f);

ConVar br_winner_prop_batch_interval(
    "br_winner_prop_batch_interval",
    "0.5",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Interval between winner prop batches",
    true,
    0.05f,
    true,
    5.0f);

ConVar br_zone_enabled(
    "br_zone_enabled",
    "1",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Enables the battle royale containment zone");

ConVar br_zone_initial_radius(
    "br_zone_initial_radius",
    "2400",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Initial battle royale zone radius",
    true,
    64.0f,
    true,
    16384.0f);

ConVar br_zone_min_radius(
    "br_zone_min_radius",
    "100",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Minimum battle royale zone radius",
    true,
    16.0f,
    true,
    4096.0f);

ConVar br_zone_phase_count(
    "br_zone_phase_count",
    "5",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Total number of battle royale zone phases",
    true,
    1.0f,
    true,
    16.0f);

ConVar br_zone_phase_time(
    "br_zone_phase_time",
    "30",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Seconds between battle royale zone phases",
    true,
    1.0f,
    true,
    600.0f);

ConVar br_zone_shrink_scale(
    "br_zone_shrink_scale",
    "0.55",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Radius multiplier applied during each zone phase",
    true,
    0.1f,
    true,
    0.95f);

ConVar br_zone_damage(
    "br_zone_damage",
    "2",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Damage applied to players outside the zone",
    true,
    0.0f,
    true,
    1000.0f);

ConVar br_zone_damage_interval(
    "br_zone_damage_interval",
    "1.0",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Seconds between zone damage ticks",
    true,
    0.1f,
    true,
    10.0f);

ConVar br_zone_debug(
    "br_zone_debug",
    "1",
    FCVAR_GAMEDLL | FCVAR_CHEAT,
    "Draws the battle royale zone boundary");

ConVar br_zone_shrink_time(
    "br_zone_shrink_time",
    "15",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Time in seconds taken to shrink to the next zone radius",
    true,
    1.0f,
    true,
    120.0f
);