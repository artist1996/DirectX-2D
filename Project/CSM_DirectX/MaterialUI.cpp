#include "pch.h"
#include "MaterialUI.h"

MaterialUI::MaterialUI()
	: AssetUI(ASSET_TYPE::MATERIAL)
{
}

MaterialUI::~MaterialUI()
{
}

void MaterialUI::Update()
{
	Title();

	Ptr<CMaterial> pMtrl = (CMaterial*)GetAsset().Get();

	// Material Name
	OutputAssetName();

	// Shader

	Ptr<CGraphicShader> pShader = pMtrl->GetShader();
	
	string strShaderName;

	if (nullptr == pShader)
		strShaderName = "None";
	else
		strShaderName = string(pShader->GetKey().begin(), pShader->GetKey().end());

	ImGui::Text("Shader");
	ImGui::SameLine(100);
	ImGui::InputText("##GraphicShaderName", (char*)strShaderName.c_str(), strShaderName.length(), ImGuiInputTextFlags_ReadOnly);

	// Shader Parameter
}