#pragma once
#include <Engine/CScript.h>

class CPlayerScript :
    public CScript
{
private:
    enum STATE    { IDLE, MOVE, AT_1, AT_2, AT_3,
                    JUMP, LANDING, RUN, DEAD,
                    SK_1, SK_2, SK_3, SK_4, SK_5, SK_6, SK_7, SK_8, SK_9, END, };

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
    void Idle();
    void Move();
    void AT1();
    void AT2();
    void AT3();
    void Run();
    void Jump();
    void Landing();
    void Dead();

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

