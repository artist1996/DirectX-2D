#include "pch.h"
#include "CFlipBook.h"

#include "CAssetMgr.h"

CFlipBook::CFlipBook()
	: CAsset(ASSET_TYPE::FLIPBOOK)
{
}

CFlipBook::~CFlipBook()
{
}

int CFlipBook::Save(const wstring& _FilePath)
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

int CFlipBook::Load(const wstring& _FilePath)
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