#include "pch.h"
#include "Temp.h"

#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CEntity.h"
#include "CMesh.h"
#include "CConstBuffer.h"
#include "CGraphicShader.h"

tTransform		g_ObjTrans = {};

CMesh*			g_Mesh = nullptr;
CGraphicShader*	g_Shader = nullptr;

int TempInit()
{
	g_ObjTrans.Scale = Vec4(1.f, 1.f, 1.f, 1.f);

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

	g_Mesh = new CMesh;
	g_Mesh->Create(arrVtx, 4, arrIdx, 6);

	g_Shader = new CGraphicShader;
	g_Shader->CreateVertexShader(L"shader\\test.fx", "VS_Test");
	g_Shader->CreatePixelShader(L"shader\\test.fx", "PS_Test");

	return S_OK;
}

void TempTick()
{
	float DeltaTime = CTimeMgr::GetInst()->GetDeltaTime();

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT))
	{
		g_ObjTrans.Pos.x += DeltaTime * 1.f;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::LEFT))
	{
		g_ObjTrans.Pos.x -= DeltaTime * 1.f;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::UP))
	{
		g_ObjTrans.Pos.y += DeltaTime * 1.f;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::DOWN))
	{
		g_ObjTrans.Pos.y -= DeltaTime * 1.f;
	}
	
	CConstBuffer* pTransformCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pTransformCB->SetData(&g_ObjTrans);
}

void TempRender()
{
	CConstBuffer* pTransformCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pTransformCB->Binding();

	g_Shader->Binding();

	g_Mesh->Render();
}

void TempRelease()
{
	if (nullptr != g_Mesh)
		delete g_Mesh;

	if (nullptr != g_Shader)
		delete g_Shader;
}