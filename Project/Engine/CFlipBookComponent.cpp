#include "pch.h"
#include "CFlipBookComponent.h"

#include "CTimeMgr.h"

CFlipBookComponent::CFlipBookComponent()
	: CComponent(COMPONENT_TYPE::FLIPBOOKCOMPONENT)
	, m_CurFlipBook(nullptr) 
	, m_CurFrmSprite(nullptr)
	, m_CurFrmIdx(0)
	, m_MaxFrm(0)
	, m_FPS(0.f)
	, m_AccTime(0.f)
	, m_Repeat(false)
	, m_Finish(false)
{
}

CFlipBookComponent::~CFlipBookComponent()
{
}

void CFlipBookComponent::FinalTick()
{
	if (m_Finish)
	{
		if (!m_Repeat)
			return;

		Reset();
	}

	if (nullptr != m_CurFlipBook)
	{
		float MaxTime = 1.f / m_FPS;
		
		m_AccTime += DT;
		
		if (MaxTime < m_AccTime)
		{
			m_AccTime -= MaxTime;
			++m_CurFrmIdx;

			if (m_CurFlipBook->GetMaxFrameCount() <= m_CurFrmIdx)
			{
				--m_CurFrmIdx;
				m_Finish = true;
			}
		}

		m_CurFrmSprite = m_CurFlipBook->GetSprite(m_CurFrmIdx);
	}
	
}

Ptr<CFlipBook> CFlipBookComponent::FindFlipBook(const wstring& _Key)
{
	for (size_t i = 0; i < m_vecFlipBook.size(); ++i)
	{
		if (m_vecFlipBook[i]->GetKey() == _Key)
			return m_vecFlipBook[i];
	}

	return nullptr;
}

void CFlipBookComponent::Play(int _FlipBookIdx, float _FPS, bool _Repeat)
{
	m_CurFlipBook = m_vecFlipBook[_FlipBookIdx];
	
	if (nullptr == m_CurFlipBook)
		return;

	m_CurFrmIdx = 0;
	m_AccTime = 0.f;
	m_FPS = _FPS;
	m_Repeat = _Repeat;
}

void CFlipBookComponent::Reset()
{
	m_CurFrmIdx = 0;
	m_AccTime = 0.f;
	m_Finish = false;
}