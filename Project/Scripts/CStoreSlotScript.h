#pragma once
#include <Engine/CScript.h>

class CStoreSlotScript :
    public CScript
{
private:
    Ptr<CPrefab>  m_ItemPref;
    wstring       m_strFont;

    int           m_Price;

    bool          m_Normal;
    bool          m_Hoverd;

private:
    void Font();
    void MouseCheck();
    void Buy();
    void CheckHoved();

public:
    int GetPrice() { return m_Price; }

public:
    virtual void Begin() override;
    virtual void Tick()  override;

public:
    virtual void SaveToFile(FILE* _pFile) override;
    virtual void LoadFromFile(FILE* _pFile) override;

public:
    CLONE(CStoreSlotScript);
    CStoreSlotScript();
    virtual ~CStoreSlotScript();
};

