#pragma once
#include <Engine/CScript.h>

class CInventoryInfoScript :
    public CScript
{
private:
    CGameObject* m_Owner;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CInventoryInfoScript);
    CInventoryInfoScript();
    virtual ~CInventoryInfoScript();
};

