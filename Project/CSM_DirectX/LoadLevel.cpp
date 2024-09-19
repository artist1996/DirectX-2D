#include "pch.h"
#include "LoadLevel.h"

#include <Engine/CPathMgr.h>
#include <Engine/CObjectPoolMgr.h>
#include <Engine/components.h>
#include <Engine/CGameObject.h>
#include <Engine/CLevelMgr.h>

#include <Scripts/CLoadingScript.h>

#include "CEditorMgr.h"
#include "CLevelSaveLoad.h"
#include "CTestLevel.h"

std::atomic<bool> Complete = false;

LoadLevel::LoadLevel()
	: m_thread()
	, m_mtx()
	, m_Complete(false)
	, m_Time(0.f)
{
}

LoadLevel::~LoadLevel()
{
	if (m_thread.joinable())
	{
		m_thread.join();
	}
}

void LoadLevel::Init()
{
	wstring strPath = CPathMgr::GetInst()->GetContentPath();

	CGameObject* CamObj = new CGameObject;
	CamObj->SetName(L"MainCamera");
	CamObj->AddComponent(new CTransform);
	CamObj->AddComponent(new CCamera);
	
	CamObj->Camera()->SetPriority(0);
	
	CamObj->Camera()->SetLayerAll();
	CamObj->Camera()->SetLayer(31, false);
	CamObj->Camera()->SetFar(100000.f);
	CamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	AddObject(0, CamObj);
	
	// Light2D Object
	CGameObject* pLight2D = new CGameObject;
	pLight2D->SetName(L"Directional");
	pLight2D->AddComponent(new CTransform);
	pLight2D->AddComponent(new CLight2D);
	pLight2D->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	pLight2D->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	pLight2D->Light2D()->SetLightColor(Vec4(1.f, 1.f, 1.f, 1.f));
	pLight2D->Light2D()->SetAngle(XM_PI / 2.f);
	pLight2D->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight2D->Light2D()->SetRadius(500.f);
	
	AddObject(0, pLight2D);

	CGameObject* pLoading = new CGameObject;
	pLoading->SetName(L"Loading");
	pLoading->AddComponent(new CTransform);
	pLoading->AddComponent(new CMeshRender);
	pLoading->Transform()->SetRelativePos(Vec3(0.f, 0.f, 1000.f));
	pLoading->Transform()->SetRelativeScale(Vec3(1280.f, 768.f, 1.f));
	pLoading->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pLoading->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"LoadingMtrl"));

	AddObject(0, pLoading);

	CGameObject* pGage = new CGameObject;
	pGage->SetName(L"LoadingGage");
	pGage->AddComponent(new CTransform);
	pGage->AddComponent(new CMeshRender);
	pGage->AddComponent(new CLoadingScript);
	pGage->Transform()->SetRelativePos(8.f, -264.f, 1.f);
	pGage->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));
	pGage->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pGage->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"LoadingGageMtrl"));

	AddObject(0, pGage);

	ChangeLevel(this, PLAY);
	m_thread = std::thread(&LoadLevel::Load, this, ref(m_mtx));
}

void LoadLevel::Tick()
{
	CLevel::Tick();
	if (Complete)
	{
		m_Time += DT;

		if (5.f < m_Time)
		{
			CLevel* pLevel = CLevelMgr::GetInst()->FindLevel(LEVEL_TYPE::SERIAROOM);
			ChangeLevel(pLevel, PLAY);
			CGameObject* pEntity = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::PLAYER);
			pEntity->Transform()->SetRelativePos(Vec3(0.f, -50.f, 0.f));
			pEntity->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
			CreateObject(pEntity, 4);
		}
	}
}

void LoadLevel::Load(std::mutex& _mtx)
{
	std::lock_guard<std::mutex> lock(_mtx);

	//Reload();
	CEditorMgr::GetInst()->Init();
	CTestLevel::CreateTestLevel();
	CObjectPoolMgr::GetInst()->Init();
	CTaskMgr::GetInst()->AddTask(tTask{ ASSET_CHANGED });
	Complete.store(true);
}

void LoadLevel::Reload()
{
	// Content 폴더에 있는 모든 Asset File들의 경로를 알아낸다.
	wstring ContentPath = CPathMgr::GetInst()->GetContentPath();
	FindAssetName(ContentPath, L"*.*");

	// 알아낸 Asset File 들의 경로를 통해 Asset 들을 AssetMgr에 Loading 한다.
	for (size_t i = 0; i < m_vecAssetPath.size(); ++i)
	{
		LoadAsset(m_vecAssetPath[i]);
	}

	// AssetMgr에는 존재 하지만 Content 폴더 내에 없는 Asset은 AssetMgr 에서 삭제 해준다.	
	wstring strContentPath = CPathMgr::GetInst()->GetContentPath();

	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		const map<wstring, Ptr<CAsset>>& mapAssets = CAssetMgr::GetInst()->GetAssets((ASSET_TYPE)i);

		for (const auto& pair : mapAssets)
		{
			if (pair.second->IsEngineAsset())
				continue;

			wstring strRelativePath = pair.second->GetKey();

			// 절대경로로 Asset File이 존재 하는지 확인한다.
			if (!std::filesystem::exists(strContentPath + strRelativePath))
			{
				// Asset 들은 스마트포인터로 관리하고 있기 때문에 RefCount 를 확인 후 1보다 크다면 다른 곳에서도 참조중이므로
				// 바로 삭제하지 않는다.
				if (pair.second->GetRefCount() <= 1)
				{
					CTaskMgr::GetInst()->AddTask(tTask{ TASK_TYPE::DELETE_ASSET, (DWORD_PTR)pair.second.Get() });
				}
				else
				{
					int ret = MessageBox(nullptr, L"다른 곳에서 참조되고 있을 수 있습니다.\n 그래도 삭제 하시겠습니까?", L"Error", MB_YESNO);
					if (ret == IDYES)
					{
						CTaskMgr::GetInst()->AddTask(tTask{ TASK_TYPE::DELETE_ASSET, (DWORD_PTR)pair.second.Get() });
					}
				}
			}
		}
	}
}

void LoadLevel::FindAssetName(const wstring& _FolderPath, const wstring& _Filter)
{
	WIN32_FIND_DATA tFindData = {};

	// 경로에 맞는 File 및 폴더를 탐색 할 수 있는 커널 오브젝트 생성
	wstring strFindPath = _FolderPath + _Filter;
	HANDLE hFinder = FindFirstFile(strFindPath.c_str(), &tFindData);

	assert(hFinder != INVALID_HANDLE_VALUE);

	// 탐색 커널 오브젝트를 이용 해 다음 파일을 반복해서 찾아낸다.
	while (FindNextFile(hFinder, &tFindData))
	{
		// 변수 이름은 FileName 이지만 FolderName 포함
		wstring strFindName = tFindData.cFileName;

		// 탐색한 File이 폴더 인지 식별해준다.
		if (tFindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			// Window 폴더 내엔 .. 이란 이름을 가진 보이지 않는 폴더가 존재한다. 상위 폴더로 접근 하는 폴더기 때문에 continue 해준다.
			if (strFindName == L"..")
				continue;
			// 다른 File 들을 다 찾아내야 하기 때문에 재귀함수를 통해 재귀적으로 모든 파일들을 찾아온다.
			FindAssetName(_FolderPath + strFindName + L"\\", _Filter);
		}
		// File 이라면 FolderPath 와 찾아낸 FileName 을 결합해 상대 경로를 받아 온 후 vector에 push_back 해준다
		else
		{
			wstring RelativePath = CPathMgr::GetInst()->GetRelativePath(_FolderPath + strFindName);
			m_vecAssetPath.push_back(RelativePath);
		}
	}

	// 커널 오브젝트 사용 후 메모리를 해제 해준다.
	FindClose(hFinder);
}

void LoadLevel::LoadAsset(const path& _Path)
{
	path ext = _Path.extension();

	if (ext == L".mesh")
		CAssetMgr::GetInst()->Load<CMesh>(_Path, _Path);
	//else if (ext == L".mdat")
		//CAssetMgr::GetInst()->Load<CMeshData>(_Path, _Path);
	else if (ext == L".mtrl")
		CAssetMgr::GetInst()->Load<CMaterial>(_Path, _Path);
	else if (ext == L".pref")
		CAssetMgr::GetInst()->Load<CPrefab>(_Path, _Path);
	else if (ext == L".png" || ext == L".jpg" || ext == L".jpeg" || ext == L".bmp" || ext == L".dds" || ext == L".tga"
		|| ext == L".PNG" || ext == L".JPG" || ext == L".JPEG" || ext == L".BMP" || ext == L".DDS" || ext == L".TGA")
		CAssetMgr::GetInst()->Load<CTexture>(_Path, _Path);
	else if (ext == L".mp3" || ext == L".mp4" || ext == L".ogg" || ext == L".wav"
		|| ext == L".MP3" || ext == L".MP4" || ext == L".OGG" || ext == L".WAV")
		CAssetMgr::GetInst()->Load<CSound>(_Path, _Path);
	else if (ext == L".sprite")
		CAssetMgr::GetInst()->Load<CSprite>(_Path, _Path);
	else if (ext == L".anim")
		CAssetMgr::GetInst()->Load<CAnimation>(_Path, _Path);
}
