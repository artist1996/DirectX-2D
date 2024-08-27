#pragma once
#include <Engine/CScript.h>

class CGunHawkExplodeScript :
    public CScript
{
private:

public:
    virtual void Begin() override;
    virtual void Tick()  override;

public:
    virtual void SaveToFile(FILE* _pFile)   override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CGunHawkExplodeScript);
    CGunHawkExplodeScript();
    virtual ~CGunHawkExplodeScript();
};

