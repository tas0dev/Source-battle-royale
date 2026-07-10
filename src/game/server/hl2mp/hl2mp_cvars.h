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

extern ConVar br_winner_prop_batch_size;
extern ConVar br_winner_prop_batch_interval;

extern ConVar br_zone_enabled;
extern ConVar br_zone_initial_radius;
extern ConVar br_zone_min_radius;
extern ConVar br_zone_phase_count;
extern ConVar br_zone_phase_time;
extern ConVar br_zone_shrink_scale;
extern ConVar br_zone_damage;
extern ConVar br_zone_damage_interval;
extern ConVar br_zone_debug;
extern ConVar br_zone_shrink_time;

#endif