#pragma once
#include <Engine/CScript.h>

class CPlayerMoveScript :
    public CScript
{
private:
    enum STATE       { ST_IDLE, ST_MOVE, ST_RUN, ST_END, };

private:
    STATE        m_State;
    
    float        m_Speed;
    bool         m_MoveAble;
    bool         m_TapMove;


private:
    void Idle();
    void Move();
    void Run();
    
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

