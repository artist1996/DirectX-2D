#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "components.h"

#include "CAssetMgr.h"
#include "assets.h"

CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
	if(nullptr != m_CurLevel)
		delete m_CurLevel;
}

void CLevelMgr::Init()
{
	m_CurLevel = new CLevel;

	CGameObject* CamObj = new CGameObject;
	CamObj->SetName(L"MainCamera");
	CamObj->AddComponent(new CTransform);
	CamObj->AddComponent(new CCamera);

	CamObj->Camera()->SetPriority(0);

	m_CurLevel->AddObject(0, CamObj);

	CGameObject* pObject = new CGameObject;
	pObject->SetName(L"Player");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);

	pObject->Transform()->SetRelativePos(-0.5f, 0.5f, 0.f);
	pObject->Transform()->SetRelativeScale(0.2f, 0.2f, 0.2f);
	pObject->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObject->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"TestShader"));

	m_CurLevel->AddObject(0, pObject);

	m_CurLevel->Begin();
}

void CLevelMgr::Progress()
{
	m_CurLevel->Tick();
	m_CurLevel->FinalTick();
}