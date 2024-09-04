#pragma once
#include <Engine/CScript.h>

class CMonsterMoveScript :
    public CScript
{
private:
    float m_Speed;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;

public:
    virtual void SaveToFile(FILE* _pFile);
    virtual void LoadFromFile(FILE* _pFile);

public:
    CLONE(CMonsterMoveScript);
    CMonsterMoveScript();
    virtual ~CMonsterMoveScript();
};

