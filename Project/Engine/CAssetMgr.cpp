#include "pch.h"
#include "CAssetMgr.h"
#include "CAsset.h"

CAssetMgr::CAssetMgr()
	: m_Changed(false)
{
}

CAssetMgr::~CAssetMgr()
{
}

void CAssetMgr::Tick()
{
	if (m_Changed)
		m_Changed = false;
}

Ptr<CAsset> CAssetMgr::FindAsset(ASSET_TYPE _Type, const wstring& _Key)
{
	map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)_Type].find(_Key);

	if (iter == m_mapAsset[(UINT)_Type].end())
		return nullptr;

	return iter->second;
}

Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _strKey, UINT _Width, UINT _Height, DXGI_FORMAT _Format, UINT _Flags, D3D11_USAGE _Usage)
{
	// �ߺ� Ű �˻�
	Ptr<CTexture> pTexture = FindAsset<CTexture>(_strKey);

	assert(!pTexture.Get());

	pTexture = new CTexture;

	if (FAILED(pTexture->Create(_Width, _Height, _Format, _Flags, _Usage)))
	{
		MessageBox(nullptr, L"�ؽ��� ���� ����", L"�ؽ��� ���� ����", MB_OK);
		return nullptr;
	}

	pTexture->m_Key = _strKey;
	pTexture->SetEngineAsset();
	m_mapAsset[(UINT)ASSET_TYPE::TEXTURE].insert(make_pair(_strKey, pTexture.Get()));
	
	return pTexture;
}

Ptr<CTexture> CAssetMgr::CreateTexutre(const wstring& _Key, ComPtr<ID3D11Texture2D> _Tex2D)
{
	// �ߺ� Ű �˻�
	Ptr<CTexture> pTexture = FindAsset<CTexture>(_Key);
	assert(!pTexture.Get());

	pTexture = new CTexture;

	if (FAILED(pTexture->Create(_Tex2D)))
	{
		MessageBox(nullptr, L"�ؽ��� ���� ����", L"�ؽ��� ���� ����", MB_OK);
		return nullptr;
	}

	// �ʿ� ���
	pTexture->m_Key = _Key;
	pTexture->SetEngineAsset();
	m_mapAsset[(UINT)ASSET_TYPE::TEXTURE].insert(make_pair(_Key, pTexture.Get()));
	
	return pTexture;
}

void CAssetMgr::GetAssetNames(ASSET_TYPE _Type, vector<string>& _vecOut)
{
	for (const auto& pair : m_mapAsset[(UINT)_Type])
	{
		_vecOut.push_back(string(pair.first.begin(), pair.first.end()));
	}
}

void CAssetMgr::DeleteAsset(ASSET_TYPE _Type, const wstring& _Key)
{
	// Ȥ�� �ٸ� ������ ������ �� �� ������ AssetMgr ������ erase
	map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)_Type].find(_Key);
	assert(iter != m_mapAsset[(UINT)_Type].end());
	m_mapAsset[(UINT)_Type].erase(iter);

	// Asset ���� �˸�
	CTaskMgr::GetInst()->AddTask(tTask{ TASK_TYPE::ASSET_CHANGED });
}