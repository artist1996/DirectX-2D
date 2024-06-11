#pragma once
#include "CAsset.h"

class CSprite :
    public CAsset
{
private:
    Ptr<CTexture> m_Atlas;
    Vec2          m_LeftTop; // UV ÁÂÇ¥°è
    Vec2          m_Slice;   // UV ÁÂÇ¥°è

public:
    void Create(Ptr<CTexture> _Atlas, Vec2 _LeftTopPixel, Vec2 _SlicePixel);

public:
    Ptr<CTexture> GetAtlasTexture() { return m_Atlas; }
    Vec2 GetLeftTopUV()             { return m_LeftTop; }
    Vec2 GetSliceUV()               { return m_Slice; }

public:
    virtual int Load(const wstring& _FilePath) override { return S_OK; }
    virtual int Save(const wstring& _FilePath) override { return S_OK; }

public:
    CSprite();
    virtual ~CSprite();
};

