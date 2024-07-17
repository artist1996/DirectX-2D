#include "pch.h"
#include "CTestLevel.h"

#include <Engine/CAssetMgr.h>
#include <Engine/assets.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Engine/CCollisionMgr.h>

#include <Scripts/CPlayerScript.h>
#include <Scripts/CMissileScript.h>
#include <Scripts/CCameraMoveScript.h>


void CTestLevel::CreateTestLevel()
{
	// Std2DMtrl
	Ptr<CMaterial> pMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl");
	Ptr<CMaterial> pAlphaBlendMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<CMaterial> pDebugShapeMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DebugShapeMtrl");

	Ptr<CTexture> pTexture = CAssetMgr::GetInst()->Load<CTexture>(L"PlayerTex", L"texture\\Character.png");
	pAlphaBlendMtrl->SetTexParam(TEX_0, pTexture);

	CLevel* pLevel = new CLevel;
	ChangeLevel(pLevel, PLAY);

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
	pLevel->AddObject(0, CamObj);

	pLevel->GetLayer(0)->SetName(L"Default");
	pLevel->GetLayer(1)->SetName(L"Background");
	pLevel->GetLayer(2)->SetName(L"Tile");
	pLevel->GetLayer(3)->SetName(L"Player");
	pLevel->GetLayer(4)->SetName(L"Monster");
	pLevel->GetLayer(5)->SetName(L"PlayerProjectile");
	pLevel->GetLayer(6)->SetName(L"MonsterProjectile");

	// Light2D Object
	CGameObject* pLight2D = new CGameObject;
	pLight2D->SetName(L"Directional");
	pLight2D->AddComponent(new CTransform);
	pLight2D->AddComponent(new CLight2D);
	pLight2D->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	pLight2D->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	pLight2D->Light2D()->SetLightColor(Vec4(1.f, 1.f, 1.f, 1.f));
	pLight2D->Light2D()->SetAngle(XM_PI / 2.f);
	pLight2D->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLight2D->Light2D()->SetRadius(500.f);

	pLevel->AddObject(0, pLight2D);

	// Player Object
	CGameObject* pPlayer = new CGameObject;
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new CTransform);
	pPlayer->AddComponent(new CCollider2D);
	pPlayer->AddComponent(new CFlipBookComponent);
	pPlayer->AddComponent(new CMeshRender);
	pPlayer->AddComponent(new CPlayerScript);

	pPlayer->Transform()->SetRelativePos(0.f, 0.f, 100.f);
	pPlayer->Transform()->SetRelativeScale(200.f, 200.f, 1.f);

	pPlayer->Collider2D()->SetIndependentScale(true);
	pPlayer->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlayer->Collider2D()->SetScale(Vec3(200.f, 200.f, 1.f));

	pPlayer->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(pMtrl);

	pPlayer->FlipBookComponent()->AddFlipBook(5, CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Link_MoveDown"));
	pPlayer->FlipBookComponent()->Play(5, 10, true);


	// TileMap
	CGameObject* pTileMap = new CGameObject;
	pTileMap->SetName(L"Tile");
	pTileMap->AddComponent(new CTransform);
	pTileMap->AddComponent(new CTileMap);

	pTileMap->Transform()->SetRelativePos(Vec3(-500.f, 250.f, 500.f));

	pTileMap->TileMap()->SetRowCol(4, 4);
	pTileMap->TileMap()->SetTileSize(Vec2(64.f, 64.f));

	Ptr<CTexture> pTileAtlas = CAssetMgr::GetInst()->Load<CTexture>(L"TileAtlasTex", L"texture\\TILE.bmp");
	pTileMap->TileMap()->SetAtlasTexture(pTileAtlas);
	pTileMap->TileMap()->SetAtlasTileSize(Vec2(64.f, 64.f));

	pLevel->AddObject(2, pTileMap);

	//pObject->MeshRender()->GetMaterial()->SetScalarParam(INT_1, 0);
	//pObject->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, 0.01f);
	//pObject->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, Vec4(0.f, 1.f, 0.f, 1.f));

	// Child Object
	CGameObject* pChild = new CGameObject;
	pChild->SetName(L"Child");

	pChild->AddComponent(new CTransform);
	pChild->AddComponent(new CCollider2D);
	pChild->AddComponent(new CMeshRender);

	pChild->Transform()->SetIndependentScale(true);
	pChild->Transform()->SetRelativePos(50.f, 0.f, 0.f);
	pChild->Transform()->SetRelativeScale(100.f, 100.f, 1.f);

	pChild->Collider2D()->SetIndependentScale(true);
	pChild->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pChild->Collider2D()->SetScale(Vec3(100.f, 100.f, 1.f));

	pChild->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pChild->MeshRender()->SetMaterial(pMtrl);

	//pPlayer->AddChild(pLight2D);
	pPlayer->AddChild(pChild);
	pLevel->AddObject(3, pPlayer);

	// GrayFilter Object
	//CGameObject* pGrayFilterObj = new CGameObject;
	//pGrayFilterObj->SetName(L"GrayFilter");
	//pGrayFilterObj->AddComponent(new CTransform);
	//pGrayFilterObj->AddComponent(new CMeshRender);
	//pGrayFilterObj->Transform()->SetRelativeScale(Vec3(150.f, 150.f, 0.f));
	//pGrayFilterObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pGrayFilterObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"GrayFilterMtrl"));
	//pLevel->AddObject(0, pGrayFilterObj);

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
	//pLevel->AddObject(4, pMonster);

	CCollisionMgr::GetInst()->CollisionCheck(3, 4);
	CCollisionMgr::GetInst()->CollisionCheck(4, 5);

	//pMtrl->Save(L"material\\std2d.mtrl");
}
