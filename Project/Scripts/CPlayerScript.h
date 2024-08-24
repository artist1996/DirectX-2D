#pragma once
#include <Engine/CScript.h>

class CPlayerScript :
    public CScript
{
private:
    enum STATE    { IDLE, MOVE, AT_1, AT_2, AT_3,
                    JUMP, LANDING, RUN, DG_AT1, DG_AT2, DG_AT3, DG_AT4,
                    SK_1, SK_2, SK_3, SK_4, SK_5, SK_6, SK_7, SK_8, SK_9, AT_4, DEAD, END, };

    enum class ANIMATION_NUM { IDLE, MOVE, AT_1, AT_2, AT_3, JUMP, LANDING, RUN, DG_AT1, DG_AT2, DG_AT3,
                               JACKSPIKE, RANDOMSHOT, DEATHBYREVOLVER, WINDMILL, MACHKICK, };

private:
    class CPlayerMoveScript* m_MoveScript;
    class CPlayerJumpScript* m_JumpScript;

    class CGameObject*       m_MoveObject;
    class CGameObject*       m_JumpObject;

    Ptr<CTexture>            m_Texture;
    Ptr<CPrefab>             m_MissilePref;
                             
    OBJ_DIR                  m_Dir;
    STATE                    m_State;
                             
    float                    m_Speed;
    float                    m_JumpHeight;
                             
    float                    m_Time;
                             
    bool                     m_NextAttack;
    bool                     m_Run;

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

    // Stylish Skill
    void Stylish();
public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;
    
    void SetMoveable(bool _Set);

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CLONE(CPlayerScript);
    CPlayerScript();
    virtual ~CPlayerScript();
};

