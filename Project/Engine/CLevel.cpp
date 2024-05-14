#include "pch.h"
#include "CLevel.h"
#include "CLayer.h"

CLevel::CLevel()
	: m_Layer{}
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

void CLevel::AddObject(int _LayerIdx, CGameObject* _Object)
{
	m_Layer[_LayerIdx]->AddObject(_Object);
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

void CLevel::Render()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->Render();
	}
}