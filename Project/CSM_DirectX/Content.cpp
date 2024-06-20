#include "pch.h"
#include "Content.h"
#include "ImGui/imgui.h"

Content::Content()
{
}

Content::~Content()
{
}


void Content::Update()
{
	Vec4 vData;

	ImGui::Separator();
	ImGui::DragFloat4("Data", vData);
	ImGui::Separator();
}