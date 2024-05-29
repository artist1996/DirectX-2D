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

	// Rect Mesh
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

	// Circle Mesh
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;

	UINT Slice = 40;
	float fTheta = XM_2PI / Slice; // 360도 에서 Slice 만큼 나눈 세타각
	float Radius = 0.5f;		   // 반지름

	// 중심점
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vUV = Vec2(0.5f, 0.5f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	vecVtx.push_back(v);

	float Angle = 0.f;

	// 테두리
	for (size_t i = 0; i < Slice + 1; ++i)
	{
		v.vPos = Vec3(Radius * cosf(Angle), Radius * sinf(Angle), 0.f);
		v.vUV = Vec2(v.vPos.x + 0.5f, -(v.vPos.y - 0.5f));
		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		vecVtx.push_back(v);
		
		Angle += fTheta;	// 반복 마다 Theta 값을 더 해줘서 각을 넓혀줌
	}

	// Index Buffer
	
	// Circle은 항상 원점 중심으로 각을 늘리며 그리기 때문에 계속 0번째 Idx를 첫번째로 push_back 해준다.
	for (size_t i = 0; i < Slice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	// Mesh 생성	
	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());	// 배열의 첫번째 주소와, 정점의 개수 전달
	AddAsset(L"CircleMesh", pMesh);
}

void CAssetMgr::CreateEngineMaterial()
{
	Ptr<CMaterial> pMtrl = nullptr;

	// Std2DMtrl
	pMtrl = new CMaterial;

	pMtrl->SetShader(FindAsset<CGraphicShader>(L"Std2DShader"));
	AddAsset(L"Std2DMtrl", pMtrl);

	// Std2DAlphaBlendMtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindAsset<CGraphicShader>(L"Std2DAlphaBlendShader"));
	AddAsset(L"Std2DAlphaBlendMtrl", pMtrl);

	// DebugShapeMtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindAsset<CGraphicShader>(L"DebugShapeShader"));
	AddAsset(L"DebugShapeMtrl", pMtrl);
}

void CAssetMgr::CreateEngineTexture()
{
}

void CAssetMgr::CreateEngineGraphicShader()
{
	// Std2DShader
	Ptr<CGraphicShader> pShader = nullptr;
	pShader = new CGraphicShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");
	pShader->SetRSType(RS_TYPE::CULL_NONE);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED); 

	AddAsset(L"Std2DShader", pShader);

	// Std2DAlphaBlend
	pShader = new CGraphicShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE); // 투명한것들이 적용 되는 것들은 다 따로 렌더링 방식을
	pShader->SetBSType(BS_TYPE::ALPHABLEND);	   // 지정 해줘야 하고 렌더링을 뒤로 미뤄야 하기 때문에 깊이값 검사 하지 않음
	
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);	// 알파블렌드 이기 때문에 반투명

	AddAsset(L"Std2DAlphaBlendShader", pShader);

	// DebugShapeShader
	pShader = new CGraphicShader;
	pShader->CreateVertexShader(L"shader\\debug.fx", "VS_DebugShape");
	pShader->CreatePixelShader(L"shader\\debug.fx", "PS_DebugShape");
	//pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetRSType(RS_TYPE::WIRE_FRAME);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);

	AddAsset(L"DebugShapeShader", pShader);
}

void CAssetMgr::CreateEngineComputeShader()
{
}