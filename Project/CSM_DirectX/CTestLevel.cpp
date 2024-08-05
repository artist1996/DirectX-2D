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
#include <Engine/CSetColorCS.h>
#include <Engine/CStructuredBuffer.h>

#include <Scripts/CPlayerScript.h>
#include <Scripts/CMissileScript.h>
#include <Scripts/CCameraMoveScript.h>
#include <Scripts/CPlatformScript.h>;

#include "CLevelSaveLoad.h"

void CTestLevel::CreateTestLevel()
{
	// Std2DMtrl
	Ptr<CMaterial> pMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl");
	Ptr<CMaterial> pAlphaBlendMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<CMaterial> pDebugShapeMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DebugShapeMtrl");
	
	Ptr<CTexture> pTexture = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\Character.png");
	pAlphaBlendMtrl->SetTexParam(TEX_0, pTexture);
	
	Ptr<CTexture> pTestTex = CAssetMgr::GetInst()->CreateTexture(L"ComputeShaderTestTex",
																 1024, 1024,
																 DXGI_FORMAT_R8G8B8A8_UNORM,
																 D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE);

	Ptr<CTexture> pBackground_SeiraRoomTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\background\\seriaroom.png");

	//pMtrl->SetTexParam(TEX_0, pBackground_SeiraRoomTex);

	CSetColorCS cs;
	cs.SetTexture(pTestTex);
	cs.SetClearColor(Vec4(0.f, 0.f, 1.f, 1.f));
	cs.Execute();
	
	CStructuredBuffer* pBuffer = new CStructuredBuffer;
	pBuffer->Create(sizeof(tParticle), 1, SB_TYPE::SRV_UAV, true);

	tParticle Particle = {};
	tParticle Particle2 = {};

	Particle.Active = true;
	Particle.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	pBuffer->SetData(&Particle, sizeof(tParticle));

	pBuffer->GetData(&Particle2);
	delete pBuffer;

	//pMtrl->SetTexParam(TEX_0, pBackground_SeiraRoomTex);

	//CreatePrefab();
	//
	//wstring strLoadLevelPath = CPathMgr::GetInst()->GetContentPath();
	//strLoadLevelPath += L"level\\Temp.lv";
	//CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(strLoadLevelPath);
	//
	//ChangeLevel(pLoadedLevel, LEVEL_STATE::STOP);
	//
	//CCollisionMgr::GetInst()->CollisionCheck(3, 4);
	//CCollisionMgr::GetInst()->CollisionCheck(4, 5);

	//return;
	
	//return;

	CLevel* pLevel = new CLevel;
	ChangeLevel(pLevel, LEVEL_STATE::STOP);

	//CGameObject* BGSeria = new CGameObject;
	//BGSeria->SetName(L"BG_Seria");
	//BGSeria->AddComponent(new CTransform);
	//BGSeria->AddComponent(new CMeshRender);
	//BGSeria->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//BGSeria->MeshRender()->SetMaterial(pMtrl);
	//pLevel->AddObject(1, BGSeria);

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
	
	//// Light2D Object
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
	pPlayer->AddComponent(new CAnimator2D);
	pPlayer->AddComponent(new CMeshRender);
	pPlayer->AddComponent(new CPlayerScript);
	pPlayer->AddComponent(new CRigidbody);
	
	pPlayer->Transform()->SetRelativePos(0.f, 0.f, 100.f);
	pPlayer->Transform()->SetRelativeScale(300.f, 300.f, 1.f);
	
	pPlayer->Collider2D()->SetIndependentScale(true);
	pPlayer->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlayer->Collider2D()->SetScale(Vec3(200.f, 200.f, 1.f));
	
	pPlayer->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(pMtrl);
	
	//pPlayer->FlipBookComponent()->AddFlipBook(5, CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Link_MoveDown"));
	//pPlayer->FlipBookComponent()->Play(5, 10, true);
	pPlayer->Rigidbody()->UseGravity(true);
	
	pLevel->AddObject(3, pPlayer);
	
	// TileMap
	CGameObject* pTileMap = new CGameObject;
	pTileMap->SetName(L"Tile");
	pTileMap->AddComponent(new CTransform);
	pTileMap->AddComponent(new CTileMap);
	
	pTileMap->Transform()->SetRelativePos(Vec3(-500.f, 250.f, 500.f));
	
	pTileMap->TileMap()->SetRowCol(4, 4);
	pTileMap->TileMap()->SetTileSize(Vec2(224.f, 120.f));
	
	Ptr<CTexture> pTileAtlas = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\tile\\isys_fake\\isys_fake.png");
	pTileMap->TileMap()->SetAtlasTexture(pTileAtlas);
	pTileMap->TileMap()->SetAtlasTileSize(Vec2(224.f,120.f));
	
	pLevel->AddObject(2, pTileMap);

	// Particle
	CGameObject* pParticle = new CGameObject;
	pParticle->SetName(L"Particle");
	pParticle->AddComponent(new CTransform);
	pParticle->AddComponent(new CParticleSystem);
	
	pLevel->AddObject(0, pParticle);
	
	
	// Platform
	CGameObject* pPlatform = new CGameObject;
	pPlatform->SetName(L"Platform");
	pPlatform->AddComponent(new CTransform);
	pPlatform->AddComponent(new CMeshRender);
	pPlatform->AddComponent(new CCollider2D);
	pPlatform->AddComponent(new CPlatformScript);
	
	pPlatform->Transform()->SetRelativePos(Vec3(0.f, -300.f, 100.f));
	pPlatform->Transform()->SetRelativeScale(Vec3(300.f, 100.f, 1.f));
	
	pPlatform->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pPlatform->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	
	pPlatform->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	
	pLevel->AddObject(4, pPlatform);
	
	//pObject->MeshRender()->GetMaterial()->SetScalarParam(INT_1, 0);
	//pObject->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, 0.01f);
	//pObject->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, Vec4(0.f, 1.f, 0.f, 1.f));
	
	// Child Object
	//CGameObject* pChild = new CGameObject;
	//pChild->SetName(L"Child");
	//
	//pChild->AddComponent(new CTransform);
	//pChild->AddComponent(new CCollider2D);
	//pChild->AddComponent(new CMeshRender);
	//
	//pChild->Transform()->SetIndependentScale(true);
	//pChild->Transform()->SetRelativePos(50.f, 0.f, 0.f);
	//pChild->Transform()->SetRelativeScale(100.f, 100.f, 1.f);
	//
	//pChild->Collider2D()->SetIndependentScale(true);
	//pChild->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	//pChild->Collider2D()->SetScale(Vec3(100.f, 100.f, 1.f));
	//
	//pChild->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pChild->MeshRender()->SetMaterial(pMtrl);
	//
	////pPlayer->AddChild(pLight2D);
	//pPlayer->AddChild(pChild);
	//pLevel->AddObject(3, pPlayer);
	
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
	CGameObject* pMonster = new CGameObject;
	pMonster->SetName(L"Monster");
	pMonster->AddComponent(new CTransform);
	pMonster->AddComponent(new CMeshRender);
	pMonster->AddComponent(new CCollider2D);
	pMonster->Transform()->SetRelativePos(-300.f, 0.f, 200.f);
	pMonster->Transform()->SetRelativeScale(200.f, 200.f, 1.f);
	
	pMonster->Collider2D()->SetIndependentScale(true);
	pMonster->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pMonster->Collider2D()->SetScale(Vec3(220.f, 220.f, 1.f));
	
	pMonster->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pMonster->MeshRender()->SetMaterial(pMtrl);
	
	pLevel->AddObject(4, pMonster);
	
	//
	//wstring strLevelPath = CPathMgr::GetInst()->GetContentPath();
	//strLevelPath += L"level\\Temp.lv";
	//CLevelSaveLoad::SaveLevel(strLevelPath, pLevel);
	
	//ChangeLevel(pLevel, LEVEL_STATE::PLAY);
	
	//pMtrl->Save(L"material\\std2d.mtrl");
	
	CCollisionMgr::GetInst()->CollisionCheck(3, 4);
	CCollisionMgr::GetInst()->CollisionCheck(4, 5);
}

void CTestLevel::CreatePrefab()
{
	//CGameObject* pObject = new CGameObject;
	//pObject->SetName(L"Missile");
	//pObject->AddComponent(new CTransform);
	//pObject->AddComponent(new CMeshRender);
	//pObject->AddComponent(new CMissileScript);
	//
	//pObject->Transform()->SetRelativeScale(100.f, 100.f, 1.f);
	//pObject->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObject->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	//Ptr<CPrefab> pPrefab = new CPrefab;
	//pPrefab->SetProtoObject(pObject);
	//CAssetMgr::GetInst()->AddAsset<CPrefab>(L"MissilePref", pPrefab);
	//
	//wstring FilePath = CPathMgr::GetInst()->GetContentPath();
	//pPrefab->Save(FilePath + L"prefab\\Missile.pref");
}
