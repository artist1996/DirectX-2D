#include "pch.h"
#include "TransformUI.h"

#include <Engine/CTransform.h>

TransformUI::TransformUI()
{
}

TransformUI::~TransformUI()
{
}

void TransformUI::Update()
{
	CTransform* pTrans = GetTargetObject()->Transform();

	Vec3 vPos   = pTrans->GetRelativePos();
	Vec3 vScale = pTrans->GetRelativeScale();
	Vec3 vRot   = pTrans->GetRelativeRotation();

	ImGui::Text("Position");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Position", vPos);

	ImGui::Text("Scale");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Scale", vScale);

	ImGui::Text("Rotation");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Rotation", vRot, 0.01);

	pTrans->SetRelativePos(vPos);
	pTrans->SetRelativeScale(vScale);
	pTrans->SetRelativeRotation(vRot);
}