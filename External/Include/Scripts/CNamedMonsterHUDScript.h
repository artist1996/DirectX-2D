#pragma once
#include <Engine/CScript.h>

class CNamedMonsterHUDScript :
    public CScript
{
private:
    CGameObject* m_pTarget;

public:
    void Font();

public:
    virtual void Begin() override;
    virtual void Tick() override;
    
public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CNamedMonsterHUDScript);
    CNamedMonsterHUDScript();
    virtual ~CNamedMonsterHUDScript();
};

