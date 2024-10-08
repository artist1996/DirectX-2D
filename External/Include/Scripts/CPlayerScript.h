#pragma once
#include <Engine/CScript.h>

struct tPlayerPrefab
{
    Ptr<CPrefab> HeadShotEffectPref;
    Ptr<CPrefab> BuffPref;
    Ptr<CPrefab> RandomShootPref;
    Ptr<CPrefab> PistolPref;
    Ptr<CPrefab> DiagonalPistolPref;
    Ptr<CPrefab> MuzzlePref;
    Ptr<CPrefab> HammerPref;
    Ptr<CPrefab> WindmillPref;
    Ptr<CPrefab> HeadShotPref;
    Ptr<CPrefab> DiagonalHeadShotPref;
    Ptr<CPrefab> GunHawkFirstUpPref;
    Ptr<CPrefab> GunHawkFirstDownPref;
    Ptr<CPrefab> GunHawkSecondUpPref;
    Ptr<CPrefab> GunHawkSecondDownPref;
    Ptr<CPrefab> MachKickPref;
    Ptr<CPrefab> JackSpikePref;
    Ptr<CPrefab> RisingShotPref;
    Ptr<CPrefab> WesternFirePref;
    Ptr<CPrefab> PunisherPref;
    Ptr<CPrefab> PunisherPistolPref;
    Ptr<CPrefab> BBQPref;
    Ptr<CPrefab> DeathCrisisCutinPref;
    Ptr<CPrefab> DeathCrisisLineTwoPref;
    Ptr<CPrefab> DeathCrisisLineOnePref;
    Ptr<CPrefab> DeathCrisisGunHawk0Pref;
    Ptr<CPrefab> DeathCrisisBigBoomPref;
    Ptr<CPrefab> DeathCrisisBoomTwoPref;
};

struct tPlayerSkillTime
{
    float fHeadShotTime;
    float fDeathByRevolverTime;
    float fRandomShootTime;
    float fWindMillTime;
    float fGunHawkTime;
    float fMachKickTime;
    float fJackSpikeTime;
    float fRisingShotTime;
    float fWesternFireTime;
    float fPunisherTime;
    float fBBQTime;
    float fDeathCrisisTime;

    float fHeadShotCoolTime;
    float fDeathByRevolverCoolTime;
    float fRandomShootCoolTime;
    float fWindMillCoolTime;
    float fGunHawkCoolTime;
    float fMachKickCoolTime;
    float fJackSpikeCoolTime;
    float fRisingShotCoolTime;
    float fWesternFireCoolTime;
    float fPunisherCoolTime;
    float fBBQCoolTime;
    float fDeathCrisisCoolTime;
};

struct tPlayerUseSkill
{
    bool bHeadShot;
    bool bDeathByRevolver;
    bool bRandShoot;
    bool bWindMill;
    bool bGunHawk;
    bool bMachKick;
    bool bJackSpike;
    bool bRisingShot;
    bool bWesternFire;
    bool bPunisher;
    bool bBBQ;
    bool bDeathCrisis;
};

class CPlayerScript :
    public CScript
{
private:
    enum PLAYER_STATE {
        IDLE, MOVE, AT_1, AT_2, AT_3,
        JUMP, LANDING, RUN, DG_AT1, DG_AT2, DG_AT3, DG_AT4,
        SK_1, SK_2, SK_3, SK_4, SK_5, SK_6, SK_7, SK_8, SK_9, AT_4, DEAD, TACKLE,
        GUNHAWKSHOOT, GUNHAWKSTANDBY, GUNHAWKLASTSHOOT, WESTERNFIRE, PUNISHER, PUNISHERSHOOT, BBQ, BBQREADY, BBQSHOOT,
        DEATHCRISIS, HIT,
        END,
    };

    enum class ANIMATION_NUM {
        IDLE, MOVE, AT_1, AT_2, AT_3,
        JUMP, LANDING, RUN, DG_AT1, DG_AT2, DG_AT3,
        JACKSPIKE, RANDOMSHOT, DEATHBYREVOLVER, WINDMILL,
        MACHKICK, TACKLE, GUNHAWKSHOOT, GUNHAWKSTANDBY, PUNISHER, PUNISHERSHOOT, BBQREADY, BBQSHOOT, DEATHCRISIS, HIT,
    };

private:
    Ptr<CTexture>            m_Texture;

    Ptr<CPrefab>             m_BuffPref;
    Ptr<CPrefab>             m_RandomShootPref;
    Ptr<CPrefab>             m_PistolPref;
    Ptr<CPrefab>             m_MuzzlePref;
    Ptr<CPrefab>             m_HammerPref;
    Ptr<CPrefab>             m_HeadShotEffectPref;
    Ptr<CPrefab>             m_WindmillPref;
    Ptr<CPrefab>             m_GunHawkFirstUpPref;
    Ptr<CPrefab>             m_GunHawkFirstDownPref;
    Ptr<CPrefab>             m_GunHawkSecondUpPref;
    Ptr<CPrefab>             m_GunHawkSecondDownPref;
    Ptr<CPrefab>             m_MachKickPref;
    Ptr<CPrefab>             m_JackSpikePref;
    Ptr<CPrefab>             m_RisingShotPref;
                             
    OBJ_DIR                  m_Dir;
    PLAYER_STATE             m_State;
    
    tPlayerSkillTime         m_CoolTime;
    tPlayerUseSkill          m_UseSkill;
    tPlayerPrefab            m_Prefabs;

    float                    m_Speed;
    float                    m_GroundPosY;
                             
    float                    m_Time;
    float                    m_BBQTime;
    float                    m_InvincibleTime;
    float                    m_SuperArmorTime;
                             
    bool                     m_NextAttack;
    bool                     m_Run;

    bool                     m_Spawn;
    bool                     m_HeadShotSpawn;
    bool                     m_Muzzel;
    bool                     m_CheckRange;
    bool                     m_CutinSpawn;
    bool                     m_LineTwo;

    bool                     m_GunHawkStandby;
    bool                     m_Foot;
    bool                     m_Color;

private:
    void InitInfo();
    void InitPrefabs();

private:
    void SetState(PLAYER_STATE _State)         { m_State = _State; }
    void SetDirection(OBJ_DIR _Dir)     { GetOwner()->SetDir(_Dir); }
    void SetTBDirection(OBJ_DIR _Dir)   { GetOwner()->SetTBDir(_Dir); }
    void SetPrevDirection(OBJ_DIR _Dir) { GetOwner()->SetPrevDir(_Dir); }
    void SetSpeed(float _Speed)         { m_Speed = _Speed; }
    void RunTimeCheck();
    void AddForce();
    void SetGroundPos(float _PosY)  { m_GroundPosY = _PosY; }
    bool GroundCheck();
    void SetFontOffset();
    void InvincibleCheck();
    void ZaxisCheck();

private:
    void Idle();
    void Move();
    void AT1();
    void AT2();
    void AT3();
    void AT4();

    void AT_DG1();
    void AT_DG2();
    void AT_DG3();
    void AT_DG4();

    void Tackle();

    void Run();
    void Jump();
    void Landing();
    void Hit();
    void Dead();
    void DeathCrisis();
    void DeathCrisisMove();

    // Skill
    void DeathByRevolver();
    void JackSpike();
    void RisingShot();
    void HeadShot();
    void RandomShot();
    void WindMill();
    void MachKick();
    void GunHawkShoot();
    void GunHawkStandBy();
    void GunHawkLastShoot();
    void WesternFire();
    void PuniSher();
    void PuniSherShoot();
    void SkillBBQ();
    void BBQReady();
    void SkillBBQShoot();

    // Skill TimeCheck
    void SkillTimeCheck();
    void SuperArmorCheck();
    
    // Stylish Skill
    void Stylish();

    // Create Effect
    void CreateDeathByRevolver();
    void CreateRandomShoot();
    void CreatePistol();
    void CreateDiagonalPistol();
    void CreateWindMill();
    void CreateMuzzelOfRevolverNormal();
    void CreateMuzzelOfRevolver();
    void CreateMuzzelOfRevolverDiagonal();
    void CreateHammerOfRevolver();
    void CreateHeadShotEffect();
    void CreateDiagonalHeadShotEffect();
    void CreateHeadShot();
    void CreateDiagonalHeadShot();
    void CreateGunHawkFirst();
    void CreateGunHawkSecond();
    void CreateMachKick();
    void CreateJackSpike();
    void CreateRisingShot();
    void CreateWesternFire();
    void CreatePunisher();
    void CreatePunisherPistol();
    void CreateBBQ();
    void CreateDeathCrisisCutin();
    void CreateDeathCrisis();

    void SetSuperArmor(bool _Set);

public:
    void ChangeStateDoubleGunHawkStandBy();
    void ChangeStatePunisherShoot();
    void ChangeStateBBQReady();
    void ChangeStateHit();
    const tPlayerSkillTime& GetSkillTime() { return m_CoolTime; }
    const tPlayerUseSkill& GetUseSkill()   { return m_UseSkill; }
    const PLAYER_STATE& GetState()         { return m_State; }

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

    OBJ_DIR      GetDir()   { return GetOwner()->GetDir(); }
    OBJ_DIR      GetTBDir() { return GetOwner()->GetPrevDir(); }

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)      override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)   override;

public:
    CLONE(CPlayerScript);
    CPlayerScript();
    virtual ~CPlayerScript();
};