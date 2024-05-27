#include "pch.h"
#include "CAssetMgr.h"

void CAssetMgr::Init()
{
	CreateEngineMesh();

	CreateEngineTexture();

	CreateEngineGraphicShader();

	CreateEngineComputeShader();

	CreateEngineMaterial();
}

void CAssetMgr::CreateEngineMesh()
{
	// Vertex Buffer 생성	(삼각형 그릴 것 정점 3개)
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

	// Index Buffer 생성
	arrIdx[0] = 0; arrIdx[1] = 1; arrIdx[2] = 2;
	arrIdx[3] = 0; arrIdx[4] = 2; arrIdx[5] = 3;

	Ptr<CMesh> pMesh = nullptr;
	pMesh = new CMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 6);
	AddAsset(L"RectMesh", pMesh);
}

void CAssetMgr::CreateEngineMaterial()
{
	Ptr<CMaterial> pMtrl = nullptr;

	pMtrl = new CMaterial;

	pMtrl->SetShader(FindAsset<CGraphicShader>(L"Std2DShader"));
	AddAsset(L"Std2DMtrl", pMtrl);
}

void CAssetMgr::CreateEngineTexture()
{
}

void CAssetMgr::CreateEngineGraphicShader()
{
	Ptr<CGraphicShader> pShader = nullptr;
	pShader = new CGraphicShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	AddAsset(L"Std2DShader", pShader);
}

void CAssetMgr::CreateEngineComputeShader()
{
}