#pragma once
#include <Engine/CScript.h>

class CBossHUDScript :
    public CScript
{
private:
    CGameObject* m_pTarget;

public:
    virtual void Begin() override;
    virtual void Tick() override;
    
public:
    virtual void SaveToFile(FILE* _pFile)   override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CBossHUDScript);
    CBossHUDScript();
    virtual ~CBossHUDScript();
};

