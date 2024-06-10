#pragma once
#include "CAsset.h"
class CSprite :
    public CAsset
{
private:
    Ptr<CTexture> m_Atlas;
    Vec2          m_LeftTop; // UV ��ǥ��
    Vec2          m_Slice;   // UV ��ǥ��

public:
    void Create(Ptr<CTexture> _Atlas, Vec2 _LeftTopPixel, Vec2 _SlicePixel);

public:
    CSprite();
    virtual ~CSprite();
};

