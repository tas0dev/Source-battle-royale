//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "hl2mp_cvars.h"

ConVar mp_readyrestart(
    "mp_readyrestart",
    "0",
    FCVAR_GAMEDLL,
    "If non-zero, game will restart once each player gives the ready signal"
);

ConVar mp_ready_signal(
    "mp_ready_signal",
    "ready",
    FCVAR_GAMEDLL,
    "Text that each player must speak for the match to begin"
);

ConVar br_min_players(
    "br_min_players",
    "1",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Minimum players required to start a battle royale round",
    true,
    1.0f,
    true,
    static_cast<float>( MAX_PLAYERS )
);

ConVar br_countdown_time(
    "br_countdown_time",
    "5",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Countdown duration before a round starts",
    true,
    1.0f,
    true,
    60.0f
);

ConVar br_round_time(
    "br_round_time",
    "480",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Maximum battle royale round duration in seconds",
    true,
    30.0f,
    true,
    1800.0f
);

ConVar br_restart_time(
    "br_restart_time",
    "10",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Delay before starting the next round",
    true,
    3.0f,
    true,
    60.0f
);