#include "pch.h"
#include "CLevel.h"
#include "CLevelMgr.h"

#include "CLayer.h"
#include "CCollisionMgr.h"
#include "CGameObject.h"
#include "CAssetMgr.h"

CLevel::CLevel()
	: m_Layer{}
	, m_Matrix{}
	, m_State(LEVEL_STATE::STOP)
	, m_BGM(nullptr)
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i] = new CLayer(i);
	}

	m_Layer[0]->SetName(L"Default");
	m_Layer[1]->SetName(L"Background");
	m_Layer[2]->SetName(L"Tile");
	m_Layer[3]->SetName(L"Platform");
	m_Layer[4]->SetName(L"Player");
	m_Layer[5]->SetName(L"Movement");
	m_Layer[6]->SetName(L"Monster");
	m_Layer[7]->SetName(L"PlayerProjectile");
	m_Layer[8]->SetName(L"MonsterProjectile");
	m_Layer[9]->SetName(L"Gate");
}

CLevel::CLevel(const CLevel& _Origin)
	: CEntity(_Origin)
	, m_Layer{}
	, m_Matrix{}
	, m_State(LEVEL_STATE::STOP)
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i] = _Origin.m_Layer[i]->Clone();
	}

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Matrix[i] = _Origin.m_Matrix[i];
	}
}

CLevel::~CLevel()
{
	Delete_Array(m_Layer);
}

void CLevel::Begin()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->Begin();
	}

	if(nullptr != m_BGM)
		m_BGM->Play(0, 0.7f, false);

	if (L"leshphon4" == GetName())
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\leshphon.mp3")->Stop();

	CCollisionMgr::GetInst()->CollisionCheckClear();

	CCollisionMgr::GetInst()->SetCollisionMatrix(m_Matrix);

	if (L"leshphon1" == GetName())
		CCollisionMgr::GetInst()->CollisionCheck(4, 8);
}

void CLevel::Tick()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->Tick();
	}
}

void CLevel::FinalTick()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->FinalTick();
	}
}

void CLevel::Exit()
{
	if (L"leshphon1" != GetName())
	{
		if(nullptr != m_BGM)
			m_BGM->Stop();
	}
}

CGameObject* CLevel::FindObjectByName(const wstring& _strName)
{
	
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		const vector<CGameObject*> vecParent = m_Layer[i]->GetParentObjects();

		static list<CGameObject*> queue;
		for (size_t i = 0; i < vecParent.size(); ++i)
		{
			queue.clear();
			queue.push_back(vecParent[i]);

			while (!queue.empty())
			{
				CGameObject* pObject = queue.front();
				queue.pop_front();

				const vector<CGameObject*> vecChild = pObject->GetChildren();
				for (size_t i = 0; i < vecChild.size(); ++i)
				{
					queue.push_back(vecChild[i]);
				}

				if (_strName == pObject->GetName())
					return pObject;
			}
		}
	}

	return nullptr;
}

void CLevel::AddObject(int _LayerIdx, CGameObject* _Object, bool _bMoveChild)
{
	m_Layer[_LayerIdx]->AddObject(_Object, _bMoveChild);
	CLevelMgr::GetInst()->LevelChanged();
}

void CLevel::RegisterAsParent(int _LayerIdx, CGameObject* _Object)
{
	m_Layer[_LayerIdx]->RegisterAsParent(_Object);
}

void CLevel::ClearObject()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->ClearObject();
	}
}

void CLevel::SetCollisionMatrix(UINT* _Matrix)
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Matrix[i] = _Matrix[i];
	}
}

void CLevel::CollisionCheck(UINT _Layer1, UINT _Layer2)
{
	UINT Row = _Layer1;
	UINT Col = _Layer2;

	if (Row > Col)
	{
		Row = _Layer2;
		Col = _Layer1;
	}

	m_Matrix[Row] |= (1 << Col);
}

void CLevel::CollisionUnCheck(UINT _Layer1, UINT _Layer2)
{
	UINT Row = _Layer1;
	UINT Col = _Layer2;

	if (Row > Col)
	{
		Row = _Layer2;
		Col = _Layer1;
	}

	m_Matrix[Row] &= ~(1 << Col);
}

void CLevel::ChangeLevelState(LEVEL_STATE _NextState)
{
	if (m_State == _NextState)
		return;

	// Stop -> Pause (X)
	if (STOP == m_State && PAUSE == _NextState)
		return;

	// Stop -> Play
	if (STOP == m_State && PLAY == _NextState)
	{
		m_State = _NextState;
		Begin();
	}		
	else
	{
		m_State = _NextState;
	}

	// Play -> Stop (최초 레벨이 시작되는 시점으로 복구가 가능해야 한다.)
}