#include "pch.h"
#include "ParamUI.h"

#include <Engine/CAssetMgr.h>

#include "ImGui/imgui.h"

#include "CEditorMgr.h"
#include "TreeUI.h"
#include "ListUI.h"

UINT ParamUI::g_ID = 0;

bool ParamUI::InputInt(int* _Data, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	char szID[255] = {};
	sprintf_s(szID, 255, "##Input%d", g_ID++);

	if (ImGui::InputInt(szID, _Data, 0))
	{
		return true;
	}

	return false;
}

bool ParamUI::DragInt(int* _Data, float _Step, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	char szID[255] = {};
	sprintf_s(szID, 255, "##Input%d", g_ID++);

	if (ImGui::DragInt(szID, _Data, _Step))
	{
		return true;
	}

	return false;
}

bool ParamUI::InputFloat(float* _Data, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	char szID[255] = {};
	sprintf_s(szID, 255, "##Input%d", g_ID++);

	if (ImGui::InputFloat(szID, _Data, 0))
	{
		return true;
	}

	return false;
}

bool ParamUI::DragFloat(float* _Data, float _Step, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	char szID[255] = {};
	sprintf_s(szID, 255, "##Input%d", g_ID++);

	if (ImGui::DragFloat(szID, _Data, _Step))
	{
		return true;
	}

	return false;
}

bool ParamUI::InputVec2(Vec2* _Data, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	char szID[255] = {};
	sprintf_s(szID, 255, "##Input%d", g_ID++);

	if (ImGui::InputFloat2(szID, *_Data, 0))
	{
		return true;
	}

	return false;
}

bool ParamUI::DragVec2(Vec2* _Data, float _Step, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	char szID[255] = {};
	sprintf_s(szID, 255, "##Input%d", g_ID++);

	if (ImGui::DragFloat2(szID, *_Data, _Step))
	{
		return true;
	}

	return false;
}

bool ParamUI::InputVec3(Vec3* _Data, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	char szID[255] = {};
	sprintf_s(szID, 255, "##Input%d", g_ID++);

	if (ImGui::InputFloat3(szID, *_Data, 0))
	{
		return true;
	}

	return false;
}

bool ParamUI::DragVec3(Vec3* _Data, float _Step, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	char szID[255] = {};
	sprintf_s(szID, 255, "##Input%d", g_ID++);

	if (ImGui::DragFloat3(szID, *_Data, _Step))
	{
		return true;
	}

	return false;
}

bool ParamUI::InputVec4(Vec4* _Data, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	char szID[255] = {};
	sprintf_s(szID, 255, "##Input%d", g_ID++);

	if (ImGui::InputFloat4(szID, *_Data, 0))
	{
		return true;
	}

	return false;
}

bool ParamUI::DragVec4(Vec4* _Data, float _Step, const string& _Desc)
{
	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	char szID[255] = {};
	sprintf_s(szID, 255, "##Input%d", g_ID++);

	if (ImGui::DragFloat4(szID, *_Data, _Step))
	{
		return true;
	}

	return false;
}

bool ParamUI::InputTexture(Ptr<CTexture>& _CurTex, const string& _Desc, EditorUI* _Inst, DELEGATE_1 _MemFunc)
{
	Ptr<CTexture> CurTex = _CurTex;

	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	// 이미지
	ImVec2 uv_min = ImVec2(0.0f, 0.0f);
	ImVec2 uv_max = ImVec2(1.0f, 1.0f);

	ImTextureID TexID = nullptr;
	if (nullptr != CurTex)
		TexID = CurTex->GetSRV().Get();

	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
	ImGui::Image(TexID, ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (Payload)
		{
			TreeNode** ppNode = (TreeNode**)Payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<CAsset> pAsset = (CAsset*)pNode->GetData();
			if (ASSET_TYPE::TEXTURE == pAsset->GetAssetType())
			{
				_CurTex = ((CTexture*)pAsset.Get());
			}
		}
		
		ImGui::EndDragDropTarget();
	}

	// DragDrop 으로 원본 텍스쳐가 바뀐경우
	if (CurTex != _CurTex)
		return true;

	// List Button
	if (nullptr == _Inst && nullptr == _MemFunc)
		return false;

	char szID[255] = {};
	sprintf_s(szID, 255, "##InputBtn%d", g_ID++);

	ImGui::SameLine();

	if (ImGui::Button(szID, ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)CEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Texture");
		vector<string> vecTexNames;
		CAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::TEXTURE, vecTexNames);
		pListUI->AddList(vecTexNames);
		pListUI->AddDelegate(_Inst, (DELEGATE_1)_MemFunc);
		pListUI->SetActive(true);

		return true;
	}
	

	return false;
}

bool ParamUI::InputPrefab(Ptr<CPrefab>& _CurPref, const string& _Desc, EditorUI* _Inst, DELEGATE_1 _MemFunc)
{
	Ptr<CPrefab> CurPrefab = _CurPref;

	ImGui::Text(_Desc.c_str());
	ImGui::SameLine(120);

	string PrefabName;

	if (CurPrefab.Get())
		PrefabName = string(CurPrefab->GetKey().begin(), CurPrefab->GetKey().end());

	char szID[255] = {};
	sprintf_s(szID, 255, "##PrefabKey%d", g_ID++);

	ImGui::SetNextItemWidth(150.f);
	ImGui::InputText(szID, (char*)PrefabName.c_str(), ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (Payload)
		{
			TreeNode** ppNode = (TreeNode**)Payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<CAsset> pAsset = (CAsset*)pNode->GetData();
			if (ASSET_TYPE::PREFAB == pAsset->GetAssetType())
			{
				_CurPref = ((CPrefab*)pAsset.Get());
			}
		}
		
		ImGui::EndDragDropTarget();
	}

	// DragDrop 으로 원본 텍스쳐가 바뀐경우
	if (CurPrefab != _CurPref)
		return true;

	// List Button
	if (nullptr == _Inst && nullptr == _MemFunc)
		return false;

	sprintf_s(szID, 255, "##InputBtn%d", g_ID++);

	ImGui::SameLine();

	if (ImGui::Button(szID, ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)CEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Prefab");
		vector<string> vecPrefabNames;
		CAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::PREFAB, vecPrefabNames);
		pListUI->AddList(vecPrefabNames);
		pListUI->AddDelegate(_Inst, (DELEGATE_1)_MemFunc);
		pListUI->SetActive(true);

		return true;
	}


	return false;
}
