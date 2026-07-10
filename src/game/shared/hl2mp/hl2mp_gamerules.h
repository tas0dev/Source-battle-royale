//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#ifndef HL2MP_GAMERULES_H
#define HL2MP_GAMERULES_H
#pragma once

#include "gamerules.h"
#include "teamplay_gamerules.h"
#include "gamevars_shared.h"

class CHL2MP_Player;

#define VEC_CROUCH_TRACE_MIN \
    HL2MPRules()->GetHL2MPViewVectors()->m_vCrouchTraceMin

#define VEC_CROUCH_TRACE_MAX \
    HL2MPRules()->GetHL2MPViewVectors()->m_vCrouchTraceMax

enum
{
    TEAM_COMBINE = 2,
    TEAM_REBELS,
};

enum BattleRoyaleRoundState
{
    BR_ROUND_WAITING = 0,
    BR_ROUND_COUNTDOWN,
    BR_ROUND_ACTIVE,
    BR_ROUND_FINISHED,
};

#ifdef CLIENT_DLL
#define CHL2MPRules C_HL2MPRules
#define CHL2MPGameRulesProxy C_HL2MPGameRulesProxy
#endif

class CHL2MPGameRulesProxy : public CGameRulesProxy
{
public:
    DECLARE_CLASS(
        CHL2MPGameRulesProxy,
        CGameRulesProxy
    );

    DECLARE_NETWORKCLASS();
};

class HL2MPViewVectors : public CViewVectors
{
public:
    HL2MPViewVectors(
        Vector view,
        Vector hullMinimum,
        Vector hullMaximum,
        Vector duckHullMinimum,
        Vector duckHullMaximum,
        Vector duckView,
        Vector observerHullMinimum,
        Vector observerHullMaximum,
        Vector deadViewHeight,
        Vector crouchTraceMinimum,
        Vector crouchTraceMaximum
    ) :
        CViewVectors(
            view,
            hullMinimum,
            hullMaximum,
            duckHullMinimum,
            duckHullMaximum,
            duckView,
            observerHullMinimum,
            observerHullMaximum,
            deadViewHeight
        )
    {
        m_vCrouchTraceMin =
            crouchTraceMinimum;

        m_vCrouchTraceMax =
            crouchTraceMaximum;
    }

    Vector m_vCrouchTraceMin;
    Vector m_vCrouchTraceMax;
};

class CHL2MPRules : public CTeamplayRules
{
public:
    DECLARE_CLASS(
        CHL2MPRules,
        CTeamplayRules
    );

#ifdef CLIENT_DLL
    DECLARE_CLIENTCLASS_NOBASE();
#else
    DECLARE_SERVERCLASS_NOBASE();
#endif

    CHL2MPRules();
    virtual ~CHL2MPRules();

    virtual void Precache( void );

    virtual bool ShouldCollide(
        int collisionGroup0,
        int collisionGroup1
    );

    virtual bool ClientCommand(
        CBaseEntity *entity,
        const CCommand &arguments
    );

    virtual float FlWeaponRespawnTime(
        CBaseCombatWeapon *weapon
    );

    virtual float FlWeaponTryRespawn(
        CBaseCombatWeapon *weapon
    );

    virtual Vector VecWeaponRespawnSpot(
        CBaseCombatWeapon *weapon
    );

    virtual int WeaponShouldRespawn(
        CBaseCombatWeapon *weapon
    );

    virtual void Think( void );
    virtual void CreateStandardEntities( void );

    virtual void ClientSettingsChanged(
        CBasePlayer *player
    );

    virtual int PlayerRelationship(
        CBaseEntity *player,
        CBaseEntity *target
    );

    virtual void GoToIntermission( void );

    virtual void DeathNotice(
        CBasePlayer *victim,
        const CTakeDamageInfo &information
    );

    virtual const char *GetGameDescription(
        void
    );

    virtual const unsigned char *GetEncryptionKey(
        void
    )
    {
        return reinterpret_cast<
            const unsigned char *
        >( "x9Ke0BY7" );
    }

    virtual const CViewVectors *GetViewVectors(
        void
    ) const;

    const HL2MPViewVectors *GetHL2MPViewVectors(
        void
    ) const;

    float GetMapRemainingTime();

    void CleanUpMap();
    void CheckRestartGame();
    void RestartGame();

    void OnNavMeshLoad( void );

#ifndef CLIENT_DLL
    void StartBattleRoyaleZone();
    void StopBattleRoyaleZone();
    void AdvanceBattleRoyaleZone();
    void PrintBattleRoyaleZoneStatus();
#endif

#ifndef CLIENT_DLL
    virtual Vector VecItemRespawnSpot(
        CItem *item
    );

    virtual QAngle VecItemRespawnAngles(
        CItem *item
    );

    virtual float FlItemRespawnTime(
        CItem *item
    );

    virtual bool CanHavePlayerItem(
        CBasePlayer *player,
        CBaseCombatWeapon *item
    );

    virtual bool FShouldSwitchWeapon(
        CBasePlayer *player,
        CBaseCombatWeapon *weapon
    );

    virtual bool FPlayerCanRespawn(
        CBasePlayer *player
    );

    void AddLevelDesignerPlacedObject(
        CBaseEntity *entity
    );

    void RemoveLevelDesignerPlacedObject(
        CBaseEntity *entity
    );

    void ManageObjectRelocation( void );

    void CheckChatForReadySignal(
        CHL2MP_Player *player,
        const char *message
    );

    const char *GetChatFormat(
        bool teamOnly,
        CBasePlayer *player
    );

    bool IsBattleRoyaleRoundActive() const;
    bool IsBattleRoyaleRoundLocked() const;

    bool ShouldPlayerObserveBattleRoyale(
        const CHL2MP_Player *player
    ) const;

    const char *GetBattleRoyaleStateName() const;

    void UpdateBattleRoyaleRound();
    void EnterBattleRoyaleWaiting();
    void StartBattleRoyaleCountdown();
    void StartBattleRoyaleRound();

    void FinishBattleRoyaleRound(
        CBasePlayer *winner
    );

    void PrepareBattleRoyalePlayersForRound();
    void PrepareBattleRoyalePlayersForWaiting();

    void EnforceBattleRoyaleObservers();

    int GetBattleRoyalePlayerCount() const;

    int GetBattleRoyaleAliveCount(
        CBasePlayer **lastAlive
    ) const;

    void FreezeBattleRoyalePlayers(
        bool frozen
    );

    void ResetBattleRoyaleRoundForTesting();
#endif

    bool IsOfficialMap( void );

    virtual void ClientDisconnected(
        edict_t *client
    );

    bool CheckGameOver( void );
    bool IsIntermission( void );

    void PlayerKilled(
        CBasePlayer *victim,
        const CTakeDamageInfo &information
    );

    bool IsTeamplay( void )
    {
        return m_bTeamPlayEnabled;
    }

    void CheckAllPlayersReady( void );

    virtual bool IsConnectedUserInfoChangeAllowed(
        CBasePlayer *player
    );

private:
    CNetworkVar(
        bool,
        m_bTeamPlayEnabled
    );

    CNetworkVar(
        float,
        m_flGameStartTime
    );

    CUtlVector<EHANDLE>
        m_hRespawnableItemsAndWeapons;

    float m_tmNextPeriodicThink;
    float m_flRestartGameTime;

    bool m_bCompleteReset;
    bool m_bAwaitingReadyRestart;
    bool m_bHeardAllPlayersReady;

#ifndef CLIENT_DLL
    bool m_bChangelevelDone;

    BattleRoyaleRoundState
        m_eBattleRoyaleState;

    float m_flBattleRoyaleStateEndTime;
    float m_flBattleRoyaleRoundEndTime;

    int m_iBattleRoyaleStartingPlayers;
    int m_iLastBattleRoyaleCountdownSecond;
#endif
};

inline CHL2MPRules *HL2MPRules()
{
    return static_cast<CHL2MPRules *>(
        g_pGameRules
    );
}

#endif