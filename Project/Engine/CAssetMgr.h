#pragma once

#include "CPathMgr.h"

class CAsset;
class CTexture;

class CAssetMgr
	: public CSingleton<CAssetMgr>
{
	SINGLE(CAssetMgr);
private:
	map<wstring, Ptr<CAsset>> m_mapAsset[(UINT)ASSET_TYPE::END];

public:
	void Init();

public:
	template<typename T>
	Ptr<T> Load(const wstring& _Key, const wstring& _RelativePath);

	Ptr<CAsset> FindAsset(ASSET_TYPE _Type, const wstring& _Key);

	template <typename T>
	void AddAsset(const wstring& _Key, Ptr<T> _Asset);

	template <typename T>
	Ptr<T> FindAsset(const wstring& _Key);

	// _Flags : D3D11_BIND_FLAG
	Ptr<CTexture> CreateTexture(const wstring& _strKey, UINT _Width, UINT _Height
							  , DXGI_FORMAT _Format, UINT _Flags
							  , D3D11_USAGE _Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT);

	Ptr<CTexture> CreateTexutre(const wstring& _Key, ComPtr<ID3D11Texture2D> _Tex2D);
};

template<typename T>
Ptr<T> CAssetMgr::Load(const wstring& _Key, const wstring& _RelativePath)
{
	// ���� Ű�� ���� Ȯ��
	Ptr<T> Asset = FindAsset<T>(_Key);

	if (nullptr != Asset)
	{
		return Asset;
	}
	
	// ���� Ű ���� ������ ��������
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _RelativePath;

	Asset = new T;

	// �ε� ���� �� ���� ó��
	if (FAILED(Asset->Load(strFilePath)))
	{
		MessageBox(nullptr, L"�� �� ���� �ؽ��� ����", L"�ؽ��� �ε� ����", MB_OK);
		return nullptr;
	}
	
	// Asset �� �ڽ��� Ű���� ��θ� �˰� �Ѵ�.
	Asset->m_Key = _Key;
	Asset->m_RelativePath = _RelativePath;

	// �ʿ� ���
	ASSET_TYPE Type = GetAssetType<T>();
	m_mapAsset[(UINT)Type].insert(make_pair(_Key, Asset.Get()));

	// �ε��� ���� �ּ� ��ȯ
	return Asset;
}


template<typename T>
Ptr<T> CAssetMgr::FindAsset(const wstring& _Key)
{
	ASSET_TYPE Type = GetAssetType<T>();
	
	map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)Type].find(_Key);
	
	if (iter == m_mapAsset[(UINT)Type].end())
		return nullptr;

	return (T*)iter->second.Get();
}

template<typename T>
void CAssetMgr::AddAsset(const wstring& _Key, Ptr<T> _Asset)
{
	ASSET_TYPE Type = GetAssetType<T>();
	
	assert(!FindAsset(Type, _Key).Get());
	
	m_mapAsset[(UINT)Type].insert(make_pair(_Key, _Asset.Get()));
}