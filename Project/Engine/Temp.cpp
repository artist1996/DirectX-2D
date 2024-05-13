#include "pch.h"
#include "Temp.h"

#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"

#include "CEntity.h"
#include "CMesh.h"
#include "CConstBuffer.h"
#include "CGraphicShader.h"

tTransform		g_ObjTrans = {};

int TempInit()
{
	g_ObjTrans.Scale = Vec4(1.f, 1.f, 1.f, 1.f);

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
	
	CMesh* pRectMesh = CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh");
	CGraphicShader* pShader = CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"TestShader");
	
	pShader->Binding();
	pRectMesh->Render();
}

void TempRelease()
{
}