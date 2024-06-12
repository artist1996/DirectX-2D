#include "pch.h"
#include "CFlipBookComponent.h"

#include "CTimeMgr.h"

#include "CDevice.h"
#include "CConstBuffer.h"

#include "CSprite.h"

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

void CFlipBookComponent::AddFlipBook(int _Idx, Ptr<CFlipBook> _FlipBook)
{
	if(m_vecFlipBook.size() <= _Idx)
		m_vecFlipBook.resize(_Idx + 1);

	m_vecFlipBook[_Idx] = _FlipBook;
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

void CFlipBookComponent::Binding()
{
	tSpriteInfo tInfo = {};

	if (nullptr != m_CurFrmSprite)
	{
		// 현재 표시해야하는 Sprite 의 정보를 Sprite 전용 상수버퍼를 통해서 GPU 에 전달
		tSpriteInfo tInfo = {};

		tInfo.vLeftTopUV = m_CurFrmSprite->GetLeftTopUV();
		tInfo.vSliceUV = m_CurFrmSprite->GetSliceUV();
		tInfo.vBackGroundUV = m_CurFrmSprite->GetBackgroundUV();
		tInfo.vOffsetUV = m_CurFrmSprite->GetOffsetUV();
		tInfo.UseFlipBook = 1;

		static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::SPRITE);

		pCB->SetData(&tInfo);
		pCB->Binding();

		// FlipBook Sprite 아틀라스 텍스쳐 전용 Register 번호 t10에 Binding
		Ptr<CTexture> pAtlas = m_CurFrmSprite->GetAtlasTexture();
		pAtlas->Binding(10);
	}
	
	else
	{
		Clear();
	}
}

void CFlipBookComponent::Clear()
{
	tSpriteInfo tInfo = {};
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::SPRITE);
	pCB->SetData(&tInfo);
	pCB->Binding();
}
