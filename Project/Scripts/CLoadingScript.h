#pragma once
#include <Engine/CScript.h>

class CLoadingScript :
    public CScript
{
private:
    float m_Rot;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CLoadingScript);
    CLoadingScript();
    virtual ~CLoadingScript();
};

