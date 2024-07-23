#pragma once
#include <Engine/CScript.h>


class CPlayerScript :
    public CScript
{
private:
    float         m_Speed;
    Ptr<CTexture> m_Texture;

    Ptr<CPrefab>  m_MissilePref;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CLONE(CPlayerScript);
    CPlayerScript();
    virtual ~CPlayerScript();
};

