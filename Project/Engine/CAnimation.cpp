#include "pch.h"
#include "CAnimation.h"

#include "CAssetMgr.h"

CAnimation::CAnimation()
	: CAsset(ASSET_TYPE::ANIMATION)
{
}

CAnimation::~CAnimation()
{
}

int CAnimation::Save(const wstring& _FilePath)
{
	// 颇老 俺规
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FilePath.c_str(), L"wb");
	
	if (nullptr == pFile)
		return E_FAIL;

	size_t SpriteCount = m_vecSprite.size();
	fwrite(&SpriteCount, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < SpriteCount; ++i)
	{
		SaveAssetRef(m_vecSprite[i], pFile);
	}

	fclose(pFile);

	return S_OK;
}

void CAnimation::Insert(Ptr<CSprite> _Sprite, Ptr<CSprite> m_InsertSprite)
{
	vector<Ptr<CSprite>>::iterator iter = m_vecSprite.begin();


	for (iter; iter != m_vecSprite.end(); ++iter)
	{
		if (_Sprite == (*iter))
		{
			m_vecSprite.insert(iter, m_InsertSprite);
			break;
		}
	}
}

Ptr<CSprite> CAnimation::erase(Ptr<CSprite> _Sprite)
{
	vector<Ptr<CSprite>>::iterator iter = m_vecSprite.begin();

	for (iter; iter != m_vecSprite.end(); ++iter)
	{
		if ((*iter) == _Sprite)
		{
			iter = m_vecSprite.erase(iter);

			if (iter != m_vecSprite.end())
				return (*iter);
			else
				return nullptr;
		}
	}
}

int CAnimation::Load(const wstring& _FilePath)
{
	// 颇老 俺规
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FilePath.c_str(), L"rb");

	if (nullptr == pFile)
		return E_FAIL;

	size_t SpriteCount = 0;

	fread(&SpriteCount, sizeof(size_t), 1, pFile);

	m_vecSprite.resize(SpriteCount);
	
	for (size_t i = 0; i < SpriteCount; ++i)
	{
		LoadAssetRef(m_vecSprite[i], pFile);
	}

	
	fclose(pFile);

	return S_OK;
}