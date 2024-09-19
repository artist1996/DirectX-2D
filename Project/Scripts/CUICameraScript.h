#pragma once
#include <Engine/CScript.h>

class CUICameraScript :
    public CScript
{
private:
    CGameObject* m_Target;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CUICameraScript);
    CUICameraScript();
    virtual ~CUICameraScript();
};

