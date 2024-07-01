#include "pch.h"
#include "TransformUI.h"

#include <Engine/CTransform.h>

TransformUI::TransformUI()
	: ComponentUI(COMPONENT_TYPE::TRANSFORM)
{
}

TransformUI::~TransformUI()
{
}

void TransformUI::Update()
{
	Title();

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
	ImGui::DragFloat3("##Rotation", vRot, 0.01f);

	pTrans->SetRelativePos(vPos);
	pTrans->SetRelativeScale(vScale);
	pTrans->SetRelativeRotation(vRot);

	bool IS = pTrans->IsIndependentScale();

	// Independent Scale
	ImGui::Text("Ignore Parent");
	ImGui::SameLine(100);
	if (ImGui::Checkbox("##TransIS", &IS))
	{
		pTrans->SetIndipendentScale(IS);
	}
}