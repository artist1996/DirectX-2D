#pragma once
#include <Engine/CScript.h>

class CPlayerMoveScript :
    public CScript
{
private:
    Vec3  m_vOffset;
    float m_Speed;

private:
    void AddForce();

public:
    virtual void Begin() override;
    virtual void Tick() override;
        
public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)      override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)   override;

public:
    CLONE(CPlayerMoveScript);
    CPlayerMoveScript();
    virtual ~CPlayerMoveScript();
};

