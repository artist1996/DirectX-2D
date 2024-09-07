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
#include <Engine/CObjectPoolMgr.h>

#include <Scripts/CPlayerScript.h>
#include <Scripts/CCameraMoveScript.h>
#include <Scripts/CPlatformScript.h>
#include <Scripts/CPlayerMoveScript.h>

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

	wstring strPath = CPathMgr::GetInst()->GetContentPath();

	CLevel* pLevel = CLevelSaveLoad::LoadLevel(strPath + L"level\\seria_room.lv");
	CLevelMgr::GetInst()->AddLevel(pLevel);
	
	//ChangeLevel(pLevel, STOP);

	
	pLevel = CLevelSaveLoad::LoadLevel(strPath + L"level\\hendonmyer.lv");
	CLevelMgr::GetInst()->AddLevel(pLevel);

	pLevel = CLevelSaveLoad::LoadLevel(strPath + L"level\\leshphon1.lv");
	CLevelMgr::GetInst()->AddLevel(pLevel);

	pLevel = CLevelSaveLoad::LoadLevel(strPath + L"level\\leshphon2.lv");
	CLevelMgr::GetInst()->AddLevel(pLevel);

	//ChangeCurLevel(LEVEL_TYPE::LESHPHON1);
	ChangeCurLevel(LEVEL_TYPE::LESHPHON2);
	//ChangeCurLevel(LEVEL_TYPE::HENDONMYER);
	//ChangeCurLevel(LEVEL_TYPE::SERIAROOM);
	CGameObject* pEntity = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::PLAYER);
	pEntity->Transform()->SetRelativePos(Vec3(650.f, -50.f, 0.f));
	pEntity->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	
	CreateObject(pEntity, 4);
	//CLevel* pNewLevel = new CLevel;
	//ChangeLevel(pNewLevel, LEVEL_STATE::STOP);
	//
	//CGameObject* CamObj = new CGameObject;
	//CamObj->SetName(L"MainCamera");
	//CamObj->AddComponent(new CTransform);
	//CamObj->AddComponent(new CCamera);
	//CamObj->AddComponent(new CCameraMoveScript);
	//
	//CamObj->Camera()->SetPriority(0);
	//
	//CamObj->Camera()->SetLayerAll();
	//CamObj->Camera()->SetLayer(31, false);
	//CamObj->Camera()->SetFar(100000.f);
	//CamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	//CamObj->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	//pNewLevel->AddObject(0, CamObj);
	//
	//pLevel->GetLayer(0)->SetName(L"Default");
	//pLevel->GetLayer(1)->SetName(L"Background");
	//pLevel->GetLayer(2)->SetName(L"Tile");
	//pLevel->GetLayer(3)->SetName(L"Platform");
	//pLevel->GetLayer(4)->SetName(L"Player");
	//pLevel->GetLayer(5)->SetName(L"Movement");
	//pLevel->GetLayer(6)->SetName(L"Monster");
	//pLevel->GetLayer(7)->SetName(L"PlayerProjectile");
	//pLevel->GetLayer(8)->SetName(L"Gate");
	//
	//// Light2D Object
	//CGameObject* pLight2D = new CGameObject;
	//pLight2D->SetName(L"Directional");
	//pLight2D->AddComponent(new CTransform);
	//pLight2D->AddComponent(new CLight2D);
	//pLight2D->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	//pLight2D->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	//pLight2D->Light2D()->SetLightColor(Vec4(1.f, 1.f, 1.f, 1.f));
	//pLight2D->Light2D()->SetAngle(XM_PI / 2.f);
	//pLight2D->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	//pLight2D->Light2D()->SetRadius(500.f);
	//
	//pNewLevel->AddObject(0, pLight2D);
	//
	////// Player Object
	//CGameObject* pPlayer = new CGameObject;
	//pPlayer->SetName(L"Player");
	//pPlayer->AddComponent(new CTransform);
	//pPlayer->AddComponent(new CCollider2D);
	//pPlayer->AddComponent(new CAnimator2D);
	//pPlayer->AddComponent(new CMeshRender);
	//pPlayer->AddComponent(new CPlayerScript);
	//pPlayer->AddComponent(new CRigidbody);
	//
	//pPlayer->Transform()->SetRelativePos(0.f, 0.f, 100.f);
	//pPlayer->Transform()->SetRelativeScale(350.f, 350.f, 1.f);
	//
	//pPlayer->Collider2D()->SetIndependentScale(true);
	//pPlayer->Collider2D()->SetOffset(Vec3(0.f, -0.24f, 0.f));
	//pPlayer->Collider2D()->SetScale(Vec3(50.f, 100.f, 1.f));
	//
	//pPlayer->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pPlayer->MeshRender()->SetMaterial(pMtrl);
	//
	//pPlayer->Rigidbody()->UseGravity(false);
	//
	//pPlayer->Animator2D()->AddAnimation(0, CAssetMgr::GetInst()->FindAsset<CAnimation>(L"Animation\\player\\idle\\gunner_idle.anim"));
	//
	//pLevel->AddObject(4, pPlayer);
	//
	//// TileMap
	//CGameObject* pTileMap = new CGameObject;
	//pTileMap->SetName(L"Tile");
	//pTileMap->AddComponent(new CTransform);
	//pTileMap->AddComponent(new CTileMap);
	//
	//pTileMap->Transform()->SetRelativePos(Vec3(-500.f, 250.f, 500.f));
	//
	//pTileMap->TileMap()->SetRowCol(4, 4);
	//pTileMap->TileMap()->SetTileSize(Vec2(224.f, 120.f));
	//
	//Ptr<CTexture> pTileAtlas = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\tile\\isys_fake\\isys_fake.png");
	//pTileMap->TileMap()->SetAtlasTexture(pTileAtlas);
	//pTileMap->TileMap()->SetAtlasTileSize(Vec2(224.f,120.f));
	//
	//pLevel->AddObject(2, pTileMap);
	//
	//// Particle
	//CGameObject* pParticle = new CGameObject;
	//pParticle->SetName(L"Particle");
	//pParticle->AddComponent(new CTransform);
	//pParticle->AddComponent(new CParticleSystem);
	//
	//pParticle->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	//
	//pLevel->AddObject(0, pParticle);
	//
	//
	//// Platform
	//CGameObject* pPlatform = new CGameObject;
	//pPlatform->SetName(L"Platform");
	//pPlatform->AddComponent(new CTransform);
	//pPlatform->AddComponent(new CMeshRender);
	//pPlatform->AddComponent(new CCollider2D);
	//pPlatform->AddComponent(new CPlatformScript);
	//
	//pPlatform->Transform()->SetRelativePos(Vec3(0.f, -300.f, 100.f));
	//pPlatform->Transform()->SetRelativeScale(Vec3(300.f, 100.f, 1.f));
	//
	//pPlatform->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pPlatform->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	//
	//pPlatform->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	//
	//pLevel->AddObject(3, pPlatform);
	//
	//CGameObject* pPlayerMove = new CGameObject;
	//pPlayerMove->SetName(L"PlayerMove");
	//pPlayerMove->AddComponent(new CTransform);
	//pPlayerMove->AddComponent(new CCollider2D);
	//pPlayerMove->AddComponent(new CPlayerMoveScript);
	//
	//pPlayerMove->Transform()->SetRelativePos(Vec3(0.f, 0.f, 300.f));
	//pPlayerMove->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));
	//
	//pPlayerMove->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	//pPlayerMove->Collider2D()->SetOffset(Vec3(0.f, -1.f, 1.f));
	//
	//pLevel->AddObject(5, pPlayerMove);
	//
	//CGameObject* pPlayerJump = new CGameObject;
	//pPlayerJump->SetName(L"PlayerJump");
	//pPlayerJump->AddComponent(new CTransform);
	//pPlayerJump->AddComponent(new CRigidbody);
	//pPlayerJump->AddComponent(new CPlayerJumpScript);
	//
	//pPlayerJump->Transform()->SetRelativePos(Vec3(0.f, 0.f, 300.f));
	//pPlayerJump->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	//
	//pLevel->AddObject(5, pPlayerJump);
}

void CTestLevel::CreatePrefab()
{
}