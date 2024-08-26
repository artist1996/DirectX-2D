#pragma once
#include <Engine/CScript.h>

enum MOVE_STATE { ST_IDLE, ST_MOVE, ST_RUN, ST_TACKLE, ST_END, };

class CPlayerMoveScript :
    public CScript
{
private:
    class CPlayerScript*      m_EntityScript;
    class CPlayerJumpScript*  m_JumpScript;
    MOVE_STATE                m_State;
                             
    float                     m_Speed;
    bool                      m_MoveAble;
    bool                      m_TapMove;

private:
    void Idle();
    void Move();
    void Run();
    void Tackle();

private:
    void CorrectionSpeed();
    
public:
    void SetMoveable(bool _Set) { m_MoveAble = _Set; }
    bool IsMoveable()           { return m_MoveAble; }

    void SetState(MOVE_STATE _State) { m_State = _State; }
    void SetSpeed(float _Speed) { m_Speed = _Speed; }

public:
    virtual void Begin() override;
    virtual void Tick() override;
        
public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CLONE(CPlayerMoveScript);
    CPlayerMoveScript();
    virtual ~CPlayerMoveScript();
};

