#include "pch.h"
#include "CAssetMgr.h"
#include "CAsset.h"

CAssetMgr::CAssetMgr()
{
}

CAssetMgr::~CAssetMgr()
{
}

void CAssetMgr::Init()
{
	// Vertex Buffer ����	(�ﰢ�� �׸� �� ���� 3��)
	Vtx arrVtx[4] = {};
	UINT arrIdx[6] = {};
	
	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVtx[0].vUV = Vec2(0.f, 0.f);
	
	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVtx[1].vUV = Vec2(1.f, 0.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVtx[2].vUV = Vec2(1.f, 1.f);
	
	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVtx[3].vUV = Vec2(0.f, 1.f);
	
	// Index Buffer ����
	arrIdx[0] = 0; arrIdx[1] = 1; arrIdx[2] = 2;
	arrIdx[3] = 0; arrIdx[4] = 2; arrIdx[5] = 3;
	
	Ptr<CMesh> pMesh = nullptr;
	pMesh = new CMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 6);
	AddAsset(L"RectMesh", pMesh);
	
	Ptr<CGraphicShader> pShader = nullptr;
	pShader = new CGraphicShader;
	pShader->CreateVertexShader(L"shader\\test.fx", "VS_Test");
	pShader->CreatePixelShader(L"shader\\test.fx", "PS_Test");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	AddAsset(L"TestShader", pShader);
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
	m_mapAsset[(UINT)ASSET_TYPE::TEXTURE].insert(make_pair(_Key, pTexture.Get()));
	
	return pTexture;
}
