#pragma once
#include <Engine/CScript.h>

class CDirezieScript :
    public CScript
{
private:
    Ptr<CPrefab> m_WindPref;
    float        m_Damage;
    float        m_Count;
    float        m_DamageHP;

    float        m_Time;
    bool         m_Color;

    bool         m_IsDamage;
    bool         m_Dead;

private:
    float Lerp(float _start, float _end, float _t);
    void  InitInfo();

public:
    void Damage(float _Attack);

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)      override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)   override;

public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CDirezieScript);
    CDirezieScript();
    virtual ~CDirezieScript();
};

