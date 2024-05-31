#include "pch.h"
#include "CLayer.h"
#include "CGameObject.h"

CLayer::CLayer(int _LayerIdx)
	: m_LayerIdx(_LayerIdx)
{
}

CLayer::~CLayer()
{
	Delete_Vec(m_Parents);
}

void CLayer::Begin()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->Begin();
	}
}

void CLayer::Tick()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->Tick();
	}
}

void CLayer::FinalTick()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->FinalTick();
	}
}

void CLayer::AddObject(CGameObject* _Object)
{
	// 1. ������Ʈ�� �ٸ� ���̾� �Ҽ��� ���
	if (-1 != _Object->GetLayerIdx())
	{
		// ������ �Ҽӵ� ���̾�� �������;��Ѵ�.
	}

	// 2. �θ� ������Ʈ�� �ִ� ���
	if (_Object->GetParent())
	{
		_Object->m_LayerIdx = m_LayerIdx;
	}

	else
	{
		m_Parents.push_back(_Object);
	}
}