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
    CSprite();
    virtual ~CSprite();
};

