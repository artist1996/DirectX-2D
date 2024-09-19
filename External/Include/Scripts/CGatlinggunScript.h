#pragma once
#include <Engine/CScript.h>

class CGatlinggunScript :
    public CScript
{
private:
    Ptr<CPrefab> m_GatlinggunPistolPref;
    float        m_Time;
    bool         m_UpDown;

private:
    void CreatePistol();

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile)   override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CGatlinggunScript);
    CGatlinggunScript();
    virtual ~CGatlinggunScript();
};

