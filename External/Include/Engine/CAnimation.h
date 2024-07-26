#pragma once
#include "CAsset.h"

#include "CSprite.h"

class CAnimation :
    public CAsset
{
private:
    vector<Ptr<CSprite>> m_vecSprite;

public:
    void AddSprite(Ptr<CSprite> _Sprite)     { m_vecSprite.push_back(_Sprite); }
    void Insert(Ptr<CSprite> _CurSprite, Ptr<CSprite> m_InsertSprite);
    Ptr<CSprite> GetSprite(int _Idx)         { return m_vecSprite[_Idx]; }
    int GetMaxFrameCount()                   { return (int)m_vecSprite.size(); }
    Ptr<CSprite> erase(Ptr<CSprite> _Sprite);

    const vector<Ptr<CSprite>>& GetSprites() { return m_vecSprite; }

public:
    virtual int Load(const wstring& _FilePath);
    virtual int Save(const wstring& _FilePath);


public:
    CAnimation();
    virtual ~CAnimation();
};