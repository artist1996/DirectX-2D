#pragma once
#include <Engine/CScript.h>

class CInventoryGoldScript :
    public CScript
{
private:
    CGameObject* m_pTarget;
    wstring      m_strFont;
    
public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CInventoryGoldScript);
    CInventoryGoldScript();
    virtual ~CInventoryGoldScript();
};

