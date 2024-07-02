#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "components.h"

#include "CAssetMgr.h"
#include "assets.h"

#include "CCollisionMgr.h"

#include "CPlayerScript.h"
#include "CCameraMoveScript.h"

#include "CMaterial.h"

CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
	if(nullptr != m_CurLevel)
		delete m_CurLevel;
}

CGameObject* CLevelMgr::FindObjectByName(const wstring& _strName)
{
	if (m_CurLevel)
	{
		return m_CurLevel->FindObjectByName(_strName);
	}

	return nullptr;
}

void CLevelMgr::Init()
{
	// Std2DMtrl
	Ptr<CMaterial> pMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl");
	Ptr<CMaterial> pAlphaBlendMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<CMaterial> pDebugShapeMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DebugShapeMtrl");

	Ptr<CTexture> pTexture = CAssetMgr::GetInst()->Load<CTexture>(L"PlayerTex", L"texture\\Character.png");
	pAlphaBlendMtrl->SetTexParam(TEX_0, pTexture);

	m_CurLevel = new CLevel;

	CGameObject* CamObj = new CGameObject;
	CamObj->SetName(L"MainCamera");
	CamObj->AddComponent(new CTransform);
	CamObj->AddComponent(new CCamera);
	CamObj->AddComponent(new CCameraMoveScript);

	CamObj->Camera()->SetPriority(0);

	CamObj->Camera()->SetLayerAll();
	CamObj->Camera()->SetLayer(31, false);
	CamObj->Camera()->SetFar(100000.f);
	CamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	//CamObj->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	m_CurLevel->AddObject(0, CamObj);

	m_CurLevel->GetLayer(0)->SetName(L"Default");
	m_CurLevel->GetLayer(1)->SetName(L"Background");
	m_CurLevel->GetLayer(2)->SetName(L"Tile");
	m_CurLevel->GetLayer(3)->SetName(L"Player");
	m_CurLevel->GetLayer(4)->SetName(L"Monster");
	m_CurLevel->GetLayer(5)->SetName(L"PlayerProjectile");
	m_CurLevel->GetLayer(6)->SetName(L"MonsterProjectile");

	// Light2D Object
	CGameObject* pLight2D = new CGameObject;
	pLight2D->SetName(L"Directional");
	pLight2D->AddComponent(new CTransform);
	pLight2D->AddComponent(new CLight2D);
	pLight2D->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	pLight2D->Light2D()->SetColor(Vec4(1.f, 1.f, 1.f, 1.f));
	pLight2D->Light2D()->SetAngle(XM_PI / 2.f);
	
	m_CurLevel->AddObject(0, pLight2D);

	// Player Object
	CGameObject* pObject = new CGameObject;
	pObject->SetName(L"Player");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CCollider2D);
	pObject->AddComponent(new CFlipBookComponent);
	pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CPlayerScript);

	pObject->Transform()->SetRelativePos(0.f, 0.f, 100.f);
	pObject->Transform()->SetRelativeScale(200.f, 200.f, 1.f);

	pObject->Collider2D()->SetIndependentScale(true);
	pObject->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pObject->Collider2D()->SetScale(Vec3(200.f, 200.f, 1.f));

	pObject->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObject->MeshRender()->SetMaterial(pMtrl);

	pObject->FlipBookComponent()->AddFlipBook(5, CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Link_MoveDown"));
	pObject->FlipBookComponent()->Play(5, 10, true);

	m_CurLevel->AddObject(3, pObject);

	CGameObject* pTileMap = new CGameObject;
	pTileMap->AddComponent(new CTransform);
	pTileMap->AddComponent(new CTileMap);
	
	pTileMap->Transform()->SetRelativePos(Vec3(-500.f, 250.f, 500.f));

	pTileMap->TileMap()->SetRowCol(4, 4);
	pTileMap->TileMap()->SetTileSize(Vec2(64.f, 64.f));

	Ptr<CTexture> pTileAtlas = CAssetMgr::GetInst()->Load<CTexture>(L"TileAtlasTex", L"texture\\TILE.bmp");
	pTileMap->TileMap()->SetAtlasTexture(pTileAtlas);
	pTileMap->TileMap()->SetAtlasTileSize(Vec2(64.f, 64.f));

	m_CurLevel->AddObject(2, pTileMap);

	//pObject->MeshRender()->GetMaterial()->SetScalarParam(INT_1, 0);
	//pObject->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, 0.01f);
	//pObject->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, Vec4(0.f, 1.f, 0.f, 1.f));
	
	// Child Object
	CGameObject* pChild = new CGameObject;
	pChild->SetName(L"Child");
	
	pChild->AddComponent(new CTransform);
	pChild->AddComponent(new CCollider2D);
	pChild->AddComponent(new CMeshRender);
	
	pChild->Transform()->SetIndipendentScale(true);
	pChild->Transform()->SetRelativePos(50.f, 0.f, 0.f);
	pChild->Transform()->SetRelativeScale(100.f, 100.f, 1.f);
	
	pChild->Collider2D()->SetIndependentScale(true);
	pChild->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pChild->Collider2D()->SetScale(Vec3(100.f, 100.f, 1.f));
	
	pChild->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pChild->MeshRender()->SetMaterial(pMtrl);
	
	m_CurLevel->AddObject(3, pChild);
	pObject->AddChild(pChild);


	// Monster Object
	//CGameObject* pMonster = new CGameObject;
	//pMonster->SetName(L"Monster");
	//pMonster->AddComponent(new CTransform);
	//pMonster->AddComponent(new CMeshRender);
	//pMonster->AddComponent(new CCollider2D);
	//pMonster->Transform()->SetRelativePos(-300.f, 0.f, 200.f);
	//pMonster->Transform()->SetRelativeScale(200.f, 200.f, 1.f);
	//
	//pMonster->Collider2D()->SetIndependentScale(true);
	//pMonster->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	//pMonster->Collider2D()->SetScale(Vec3(220.f, 220.f, 1.f));
	//
	//pMonster->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pMonster->MeshRender()->SetMaterial(pMtrl);
	//
	//m_CurLevel->AddObject(4, pMonster);

	CCollisionMgr::GetInst()->CollisionCheck(3, 4);
	CCollisionMgr::GetInst()->CollisionCheck(4, 5);
	
	//pMtrl->Save(L"material\\std2d.mtrl");

	//m_CurLevel->Begin();
}

void CLevelMgr::Progress()
{
	if (LEVEL_STATE::PLAY == m_CurLevel->GetState())
	{
		m_CurLevel->Tick();
	}

	m_CurLevel->ClearObject();

	m_CurLevel->FinalTick();
}