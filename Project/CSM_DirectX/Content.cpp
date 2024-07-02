#include "pch.h"
#include "Content.h"
#include "ImGui/imgui.h"

#include "TreeUI.h"
#include <Engine/CAssetMgr.h>
#include <Engine/assets.h>

Content::Content()
	: m_Tree(nullptr)
{
	m_Tree = new TreeUI;
	m_Tree->SetName("ContentTree");
	AddChild(m_Tree);

	m_Tree->SetShowRoot(false);
	m_Tree->AddClickedDelegate(this, (DELEGATE_1)&Content::AssetClicked);

	RenewContent();
}

Content::~Content()
{
}


void Content::Update()
{

}

void Content::RenewContent()
{
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
	Ptr<CAsset> pAsset = (CAsset*)pNode->GetData();
}
