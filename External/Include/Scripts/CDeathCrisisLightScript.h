#pragma once
#include <Engine/CScript.h>

class CDeathCrisisLightScript :
    public CScript
{
private:

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CDeathCrisisLightScript);
    CDeathCrisisLightScript();
    virtual ~CDeathCrisisLightScript();
};

