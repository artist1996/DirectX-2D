#include "pch.h"
#include "TE_TextureView.h"

TE_TextureView::TE_TextureView()
{
}

TE_TextureView::~TE_TextureView()
{
}

void TE_TextureView::Init()
{
}

void TE_TextureView::Update()
{
	if (nullptr == GetTexture() || !IsActive())
		return;

	ImVec2 uv_min = ImVec2(0.0f, 0.0f);
	ImVec2 uv_max = ImVec2(1.0f, 1.0f);

	Vec2 vResolution = Vec2((float)GetTexture()->Width(), (float)GetTexture()->Height());

	
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

	ImGui::Image(GetTexture()->GetSRV().Get(), ImVec2(vResolution.x, vResolution.y)
		, uv_min
		, uv_max
		, tint_col, border_col);
}