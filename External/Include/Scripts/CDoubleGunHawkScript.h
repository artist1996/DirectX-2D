#pragma once
#include <Engine/CScript.h>

enum class GUNHAWK_TYPE
{
    TYPE_ONE,
    TYPE_TWO,

    END,
};

class CDoubleGunHawkScript :
    public CScript
{
private:
    GUNHAWK_TYPE m_Type;
    Vec3         m_Dir;

    float        m_Time;
    float        m_StopTime;

    bool         m_Move;
    bool         m_Stop;
    bool         m_ReverseMove;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)      override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)   override;

public:
    virtual void SaveToFile(FILE* _pFile)  override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CDoubleGunHawkScript);
    CDoubleGunHawkScript();
    virtual ~CDoubleGunHawkScript();
};

