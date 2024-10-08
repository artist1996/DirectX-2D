#pragma once
#include <Engine/CScript.h>

class CInventorySlotScript :
    public CScript
{
private:
    Ptr<CTexture> m_NormalTex;
    Ptr<CTexture> m_HoverTex;

    bool          m_Normal;
    bool          m_Hoverd;

private:
    void MouseCheck();

public:
    virtual void Begin() override;
    virtual void Tick()  override;

public:
    virtual void SaveToFile(FILE* _pFile) override   {}
    virtual void LoadFromFile(FILE* _pFile) override {}

public:
    CLONE(CInventorySlotScript);
    CInventorySlotScript();
    virtual ~CInventorySlotScript();
};

