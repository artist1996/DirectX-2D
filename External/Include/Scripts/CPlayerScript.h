#pragma once
#include <Engine/CScript.h>

struct tPlayerPrefab
{
    Ptr<CPrefab> HeadShotEffectPref;
    Ptr<CPrefab> BuffPref;
    Ptr<CPrefab> RandomShootPref;
    Ptr<CPrefab> PistolPref;
    Ptr<CPrefab> MuzzlePref;
    Ptr<CPrefab> HammerPref;
    Ptr<CPrefab> WindmillPref;
    Ptr<CPrefab> HeadShotPref;
    Ptr<CPrefab> GunHawkFirstUpPref;
    Ptr<CPrefab> GunHawkFirstDownPref;
    Ptr<CPrefab> GunHawkSecondUpPref;
    Ptr<CPrefab> GunHawkSecondDownPref;

};

class CPlayerScript :
    public CScript
{
private:
    enum STATE    { IDLE, MOVE, AT_1, AT_2, AT_3,
                    JUMP, LANDING, RUN, DG_AT1, DG_AT2, DG_AT3, DG_AT4,
                    SK_1, SK_2, SK_3, SK_4, SK_5, SK_6, SK_7, SK_8, SK_9, AT_4, DEAD, TACKLE,
                    GUNHAWKSHOOT, GUNHAWKSTANDBY, GUNHAWKLASTSHOOT, END, };

    enum class ANIMATION_NUM { IDLE, MOVE, AT_1, AT_2, AT_3, JUMP, LANDING, RUN, DG_AT1, DG_AT2, DG_AT3,
                               JACKSPIKE, RANDOMSHOT, DEATHBYREVOLVER, WINDMILL, MACHKICK, TACKLE, GUNHAWKSHOOT, GUNHAWKSTANDBY, };

private:
    class CPlayerMoveScript* m_MoveScript;
    class CPlayerJumpScript* m_JumpScript;

    class CGameObject*       m_MoveObject;
    class CGameObject*       m_JumpObject;

    Ptr<CTexture>            m_Texture;

    Ptr<CPrefab>             m_BuffPref;
    Ptr<CPrefab>             m_RandomShootPref;
    Ptr<CPrefab>             m_PistolPref;
    Ptr<CPrefab>             m_MuzzlePref;
    Ptr<CPrefab>             m_HammerPref;
    Ptr<CPrefab>             m_HeadShotEffectPref;
    Ptr<CPrefab>             m_WindmillPref;
    Ptr<CPrefab>             m_HeadShotPref;
    Ptr<CPrefab>             m_GunHawkFirstUpPref;
    Ptr<CPrefab>             m_GunHawkFirstDownPref;
    Ptr<CPrefab>             m_GunHawkSecondUpPref;
    Ptr<CPrefab>             m_GunHawkSecondDownPref;
                             
    OBJ_DIR                  m_Dir;
    STATE                    m_State;
    
    float                    m_Speed;
    float                    m_JumpHeight;
                             
    float                    m_Time;
                             
    bool                     m_NextAttack;
    bool                     m_Run;

    bool                     m_Spawn;
    bool                     m_Muzzel;

private:
    void SetState(STATE _State) { m_State = _State; }

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
    void Dead();

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

    // Stylish Skill
    void Stylish();

    // Create Effect
    void CreateRandomShoot();
    void CreatePistol();
    void CreateWindMill();
    void CreateMuzzelOfRevolver();
    void CreateHammerOfRevolver();
    void CreateHeadShotEffect();
    void CreateHeadShot();
    void CreateGunHawkFirst();
    void CreateGunHawkSecond();

public:
    void ChangeStateDoubleGunHawkStandBy();

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;
    
    void SetMoveable(bool _Set);
    OBJ_DIR GetDir() { return m_Dir; }

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;

public:
    CLONE(CPlayerScript);
    CPlayerScript();
    virtual ~CPlayerScript();
};

