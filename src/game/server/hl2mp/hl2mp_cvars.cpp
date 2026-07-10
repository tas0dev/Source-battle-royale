//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:  
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "hl2mp_cvars.h"

// Ready restart
ConVar mp_readyrestart(
    "mp_readyrestart",
    "0",
    FCVAR_GAMEDLL,
    "If non-zero, game will restart once each player gives the ready signal"
);

// Ready signal
ConVar mp_ready_signal(
    "mp_ready_signal",
    "ready",
    FCVAR_GAMEDLL,
    "Text that each player must speak for the match to begin"
);

// Round duration
ConVar bp_round_time(
    "bp_round_time",
    "180",
    FCVAR_GAMEDLL | FCVAR_NOTIFY,
    "Round duration in seconds",
    true,
    30.0f,
    true,
    1200.0f
);