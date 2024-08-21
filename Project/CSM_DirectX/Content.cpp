#include "pch.h"
#include "Content.h"
#include "ImGui/imgui.h"

#include "CEditorMgr.h"
#include "Inspector.h"

#include "TreeUI.h"

#include <Engine/CAssetMgr.h>
#include <Engine/assets.h>
#include <Engine/CTaskMgr.h>
#include <Engine/CGameObject.h>

Content::Content()
	: m_Tree(nullptr)
{
	m_Tree = new TreeUI;
	m_Tree->SetName("ContentTree");
	AddChild(m_Tree);

	m_Tree->SetShowRoot(false);
	m_Tree->UseDrag(true);
	m_Tree->SetShowNameOnly(true);
	m_Tree->AddClickedDelegate(this, (DELEGATE_1)&Content::AssetClicked);
	m_Tree->AddPopupDelegate(this, (DELEGATE_1)&Content::PopupMenu);

	RenewContent();
}

Content::~Content()
{
}

void Content::Init()
{
	Reload();
}

void Content::Update()
{
	if (CAssetMgr::GetInst()->IsChanged())
		RenewContent();
}

void Content::RenewContent()
{
	// Ʈ���� ������ ���� ����
	m_Tree->Clear();

	// �θ��带 �������� ���� == ��Ʈ��� �Է�
	TreeNode* pRoot = m_Tree->AddNode(nullptr, "Root");
	
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		TreeNode* pNode = m_Tree->AddNode(pRoot, ToString((ASSET_TYPE)i));
		pNode->SetFrame(true);

		const map<wstring, Ptr<CAsset>>& mapAsset = CAssetMgr::GetInst()->GetAssets((ASSET_TYPE)i);

		for (const auto& pair : mapAsset)
		{
			m_Tree->AddNode(pNode, string(pair.first.begin(), pair.first.end()), (DWORD_PTR)pair.second.Get());
		}
	}
}

void Content::AssetClicked(DWORD_PTR _Param)
{
	TreeNode* pNode = (TreeNode*)_Param;
	if (pNode->IsFrame())
		return;

	Ptr<CAsset> pAsset = (CAsset*)pNode->GetData();
	Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");
	pInspector->SetTargetAsset(pAsset);
	//ImGui::SetWindowFocus(nullptr);
}

void Content::PopupMenu(DWORD_PTR _Param)
{
	TreeNode* pNode = (TreeNode*)_Param;
	
	Ptr<CAsset> pAsset = (CAsset*)pNode->GetData();

	if (ASSET_TYPE::PREFAB == pAsset->GetAssetType())
	{
		if (ImGui::MenuItem("Instantiate"))
		{
			Ptr<CPrefab> pPrefab = (CPrefab*)pAsset.Get();

			CGameObject* CloneObj = pPrefab->Instantiate();

			if (L"Player" == CloneObj->GetName())
				CreateObject(CloneObj, 3);

			
			ImGui::CloseCurrentPopup();
		}
	}

	ImGui::EndPopup();
}

void Content::Reload()
{
	// Content ������ �ִ� ��� Asset File���� ��θ� �˾Ƴ���.
	wstring ContentPath = CPathMgr::GetInst()->GetContentPath();
	FindAssetName(ContentPath, L"*.*");

	// �˾Ƴ� Asset File ���� ��θ� ���� Asset ���� AssetMgr�� Loading �Ѵ�.
	for (size_t i = 0; i < m_vecAssetPath.size(); ++i)
	{
		LoadAsset(m_vecAssetPath[i]);
	}

	// AssetMgr���� ���� ������ Content ���� ���� ���� Asset�� AssetMgr ���� ���� ���ش�.	
	wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
	
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		const map<wstring, Ptr<CAsset>>& mapAssets = CAssetMgr::GetInst()->GetAssets((ASSET_TYPE)i);
	
		for (const auto& pair : mapAssets)
		{
			if (pair.second->IsEngineAsset())
				continue;
	
			wstring strRelativePath = pair.second->GetKey();
	
			// �����η� Asset File�� ���� �ϴ��� Ȯ���Ѵ�.
			if (!std::filesystem::exists(strContentPath + strRelativePath))
			{
				// Asset ���� ����Ʈ�����ͷ� �����ϰ� �ֱ� ������ RefCount �� Ȯ�� �� 1���� ũ�ٸ� �ٸ� �������� �������̹Ƿ�
				// �ٷ� �������� �ʴ´�.
				if (pair.second->GetRefCount() <= 1)
				{
					CTaskMgr::GetInst()->AddTask(tTask{ TASK_TYPE::DELETE_ASSET, (DWORD_PTR)pair.second.Get() });
				}
				else
				{
					int ret = MessageBox(nullptr, L"�ٸ� ������ �����ǰ� ���� �� �ֽ��ϴ�.\n �׷��� ���� �Ͻðڽ��ϱ�?", L"Error", MB_YESNO);
					if (ret == IDYES)
					{
						CTaskMgr::GetInst()->AddTask(tTask{ TASK_TYPE::DELETE_ASSET, (DWORD_PTR)pair.second.Get() });
					}
				}
			}
		}
	}
}

void Content::FindAssetName(const wstring& _FolderPath, const wstring& _Filter)
{
	WIN32_FIND_DATA tFindData = {};
	
	// ��ο� �´� File �� ������ Ž�� �� �� �ִ� Ŀ�� ������Ʈ ����
	wstring strFindPath = _FolderPath + _Filter;
	HANDLE hFinder = FindFirstFile(strFindPath.c_str(), &tFindData);

	assert(hFinder != INVALID_HANDLE_VALUE);

	// Ž�� Ŀ�� ������Ʈ�� �̿� �� ���� ������ �ݺ��ؼ� ã�Ƴ���.
	while (FindNextFile(hFinder, &tFindData))
	{
		// ���� �̸��� FileName ������ FolderName ����
		wstring strFindName = tFindData.cFileName;

		// Ž���� File�� ���� ���� �ĺ����ش�.
		if (tFindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			// Window ���� ���� .. �̶� �̸��� ���� ������ �ʴ� ������ �����Ѵ�. ���� ������ ���� �ϴ� ������ ������ continue ���ش�.
			if (strFindName == L"..")
				continue;
			// �ٸ� File ���� �� ã�Ƴ��� �ϱ� ������ ����Լ��� ���� ��������� ��� ���ϵ��� ã�ƿ´�.
			FindAssetName(_FolderPath + strFindName + L"\\", _Filter);
		}
		// File �̶�� FolderPath �� ã�Ƴ� FileName �� ������ ��� ��θ� �޾� �� �� vector�� push_back ���ش�
		else
		{
			wstring RelativePath = CPathMgr::GetInst()->GetRelativePath(_FolderPath + strFindName);
			m_vecAssetPath.push_back(RelativePath);
		}
	}

	// Ŀ�� ������Ʈ ��� �� �޸𸮸� ���� ���ش�.
	FindClose(hFinder);
}

void Content::LoadAsset(const path& _Path)
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
