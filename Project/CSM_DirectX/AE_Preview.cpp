#include "pch.h"
#include "AE_Preview.h"

#include <Engine/CTimeMgr.h>

#include "AE_Detail.h"

AE_Preview::AE_Preview()
	: m_CurFrmIdx(0)
	, m_FPS(0.f)
	, m_AccTime(0.f)
	, m_Play(false)
	, m_Finish()
{
}

AE_Preview::~AE_Preview()
{
}

void AE_Preview::Init()
{
}

void AE_Preview::Update()
{
	if (nullptr == GetAnimation() || GetAnimation()->GetSprites().empty())
		return;

	if (m_Finish)
	{
		if (!m_Play)
			return;

		Reset();
	}

	if (nullptr != GetAnimation())
	{
		float MaxTime = 1.f / m_FPS;

		if (m_Play)
			m_AccTime += EngineDT;

		if (MaxTime < m_AccTime)
		{
			m_AccTime -= MaxTime;
			++m_CurFrmIdx;

			if (GetAnimation()->GetMaxFrameCount() <= m_CurFrmIdx)
			{
				--m_CurFrmIdx;
				m_Finish = true;
			}
		}

		m_Sprite = GetAnimation()->GetSprite(m_CurFrmIdx);
	}

	Preview();
}

void AE_Preview::Reset()
{
	m_CurFrmIdx = 0;
	m_AccTime = 0.f;
	m_Finish = false;
}

void AE_Preview::Preview()
{
	if (nullptr == m_Sprite)
		return;

	// ÀÌ¹ÌÁö	
	ImVec2 uv_min = ImVec2(0.0f, 0.0f);
	ImVec2 uv_max = ImVec2(1.0f, 1.0f);

	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

	ImGui::Image(m_Sprite->GetAtlasTexture()->GetSRV().Get(), ImVec2(300.f, 300.f)
			   , uv_min, uv_max, tint_col, border_col);
}
