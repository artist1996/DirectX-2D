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
	// Vertex Buffer 생성	(삼각형 그릴 것 정점 3개)
	Vtx arrVtx[4] = {};
	UINT arrIdx[6] = {};
	
	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	
	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	
	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	
	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	
	// Index Buffer 생성
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
	AddAsset(L"TestShader", pShader);
}

Ptr<CAsset> CAssetMgr::FindAsset(ASSET_TYPE _Type, const wstring& _Key)
{
	map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)_Type].find(_Key);

	if (iter == m_mapAsset[(UINT)_Type].end())
		return nullptr;

	return iter->second;
}
