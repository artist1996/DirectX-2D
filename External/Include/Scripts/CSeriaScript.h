#pragma once
#include <Engine/CScript.h>
class CSeriaScript :
    public CScript
{
private:
    float   m_Time;
    bool    m_Active;
    int     m_Prev;

private:
    void MouseCheck();
    void Click();

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    
public:
    CLONE(CSeriaScript);
    CSeriaScript();
    virtual ~CSeriaScript();
};

