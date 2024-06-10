#include "pch.h"
#include "CSprite.h"

CSprite::CSprite()
	: CAsset(ASSET_TYPE::SPRITE)
{
}

CSprite::~CSprite()
{
}

void CSprite::Create(Ptr<CTexture> _Atlas, Vec2 _LeftTopPixel, Vec2 _SlicePixel)
{
	m_Atlas = _Atlas;

	assert(m_Atlas);

	UINT Width = m_Atlas->Width();
	UINT Height = m_Atlas->Height();

	m_LeftTop = Vec2(_LeftTopPixel.x / (float)Width, _LeftTopPixel.y / (float)Height);
	m_Slice = Vec2(_SlicePixel.x / (float)Width, _SlicePixel.y / (float)Height);
}