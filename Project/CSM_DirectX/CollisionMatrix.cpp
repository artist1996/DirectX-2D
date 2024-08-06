#include "pch.h"
#include "CollisionMatrix.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CCollisionMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

CollisionMatrix::CollisionMatrix()
{
	SetActive(false);
}

CollisionMatrix::~CollisionMatrix()
{
}

void CollisionMatrix::Init()
{
}

void CollisionMatrix::Update()
{
	UINT* CollisionMatrix = CCollisionMgr::GetInst()->GetCollisionMatrix();

	UINT Count = 0;

	for (UINT Row = 0; Row < MAX_LAYER / 4; ++Row)
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	
		CLayer* pLayer = pLevel->GetLayer(Row);

		string strLayerName = string(pLayer->GetName().begin(), pLayer->GetName().end());

		if (strLayerName.empty())
			ImGui::Text("None");
		else
			ImGui::Text(strLayerName.c_str());


		for(UINT Col = MAX_LAYER / 4 - Row - 1; Col < MAX_LAYER / 4; --Col)
		{		
			char szBuff[255] = {};
			bool bCheck = false;
			sprintf_s(szBuff, 255, "##LayerCheckBox%s%d", strLayerName.c_str(), Col);
		
			if (CollisionMatrix[Row] & (1 << Col + Row))
				bCheck = true;
			else
				bCheck = false;

			if (Col == MAX_LAYER / 4 - Row - 1)
				ImGui::SameLine(150);
			else
				ImGui::SameLine();
		
			if (ImGui::Checkbox(szBuff, &bCheck))
			{
				if (bCheck)
				{
					CCollisionMgr::GetInst()->CollisionCheck(Row, Col + Row);
				}
				else
				{
					CCollisionMgr::GetInst()->CollisionUnCheck(Row, Col + Row);
				}				
			}
		}	
	}
}