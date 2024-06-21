#include "pch.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CGameObject.h"

CLevel::CLevel()
	: m_Layer{}
	, m_State(LEVEL_STATE::STOP)
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i] = new CLayer(i);
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
		m_Layer[0]->Begin();
	}
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
}

void CLevel::ClearObject()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->ClearObject();
	}
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
		Begin();
	}
		
	m_State = _NextState;

	// Play -> Stop (최초 레벨이 시작되는 시점으로 복구가 가능해야 한다.)
}