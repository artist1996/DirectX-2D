#pragma once
#include <Engine/CScript.h>

class CPlayerScript :
    public CScript
{
private:
    float         m_Speed;
    Ptr<CTexture> m_Texture;

public:
    virtual void Tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CLONE(CPlayerScript);
    CPlayerScript();
    virtual ~CPlayerScript();
};

