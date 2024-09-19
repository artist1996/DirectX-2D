#pragma once
#include <Engine/CScript.h>
class CPlayerHUDButtonScript :
    public CScript
{
private:
    HUD_TYPE      m_Type;
    Ptr<CTexture> m_NormalTex;
    Ptr<CTexture> m_HoverTex;
    Ptr<CTexture> m_ClickTex;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void SaveToFile(FILE* _pFile);
    virtual void LoadFromFile(FILE* _pFile);

public:
    CLONE(CPlayerHUDButtonScript);
    CPlayerHUDButtonScript();
    virtual ~CPlayerHUDButtonScript();
};