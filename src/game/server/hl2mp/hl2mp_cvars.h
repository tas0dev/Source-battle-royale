//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#ifndef HL2MP_CVARS_H
#define HL2MP_CVARS_H
#ifdef _WIN32
#pragma once
#endif

#define MAX_INTERMISSION_TIME 120

extern ConVar mp_restartround;
extern ConVar mp_readyrestart;
extern ConVar mp_ready_signal;

extern ConVar br_min_players;
extern ConVar br_countdown_time;
extern ConVar br_round_time;
extern ConVar br_restart_time;

extern ConVar br_winner_crate_count;
extern ConVar br_winner_crate_spread;
extern ConVar br_winner_crate_height;

#endif