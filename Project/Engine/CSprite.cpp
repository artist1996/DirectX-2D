#include "pch.h"
#include "CSprite.h"

CSprite::CSprite()
	: CAsset(ASSET_TYPE::SPRITE)
{
}

CSprite::~CSprite()
{
}

void CSprite::SetLeftTopUV(Vec2 _LeftTop)
{
	Vec2 AtlasResolution = Vec2((float)m_Atlas->Width(), (float)m_Atlas->Height());
	m_LeftTopUV = _LeftTop / AtlasResolution;
}

void CSprite::SetSliceUV(Vec2 _Slice)
{
	Vec2 AtlasResolution = Vec2((float)m_Atlas->Width(), (float)m_Atlas->Height());
	m_SliceUV = _Slice / AtlasResolution;
}

void CSprite::SetBackgroundUV(Vec2 _Background)
{
	Vec2 AtlasResolution = Vec2((float)m_Atlas->Width(), (float)m_Atlas->Height());
	m_BackgroundUV = _Background / AtlasResolution;
}

void CSprite::SetOffsetUV(Vec2 _Offset)
{
	Vec2 AtlasResolution = Vec2((float)m_Atlas->Width(), (float)m_Atlas->Height());
	m_OffsetUV = _Offset / AtlasResolution;
}

void CSprite::Create(Ptr<CTexture> _Atlas, Vec2 _LeftTopPixel, Vec2 _SlicePixel)
{
	m_Atlas = _Atlas;

	assert(m_Atlas);

	UINT Width = m_Atlas->Width();
	UINT Height = m_Atlas->Height();

	m_LeftTopUV = Vec2(_LeftTopPixel.x / (float)Width, _LeftTopPixel.y / (float)Height);
	m_SliceUV = Vec2(_SlicePixel.x / (float)Width, _SlicePixel.y / (float)Height);
}