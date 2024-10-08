#pragma once
#include <Engine/CScript.h>

class CStorePanelScript :
    public CScript
{
private:
    Vec3 m_ClickPos;

private:
    void MouseCheck();

private:
    void Click();
    void Move();

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CStorePanelScript);
    CStorePanelScript();
    virtual ~CStorePanelScript();
};

