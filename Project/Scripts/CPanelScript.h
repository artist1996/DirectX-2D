#pragma once
#include <Engine/CScript.h>

class CPanelScript :
    public CScript
{
private:
    Vec3 m_ClickPos;
    bool m_Active;

private:
    void MouseCheck();

private:
    void ShortCut();
    void Click();
    void Move();

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile) override   {}
    virtual void LoadFromFile(FILE* _pFile) override {}
    
public:
    CLONE(CPanelScript);
    CPanelScript();
    virtual ~CPanelScript();
};

