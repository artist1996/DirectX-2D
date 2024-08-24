#include "pch.h"
#include "CFSM.h"

#include "CState.h"

CFSM::CFSM()
	: CComponent(COMPONENT_TYPE::STATEMACHINE)
	, m_CurState(nullptr)
{
}

CFSM::~CFSM()
{
	Delete_Map(m_mapState);
}


void CFSM::FinalTick()
{
	if (!m_CurState)
		return;

	m_CurState->FinalTick();
}

void CFSM::AddState(const wstring& _strName, CState* _State)
{
	assert(!FindState(_strName));

	_State->m_Owner = this;

	m_mapState.insert(make_pair(_strName, _State));
}

void CFSM::ChangeState(const wstring& _strName)
{
	if (m_CurState && (_strName == m_CurState->GetName()))
		return;

	if (nullptr != m_CurState)
		m_CurState->Exit();

	m_CurState = FindState(_strName);

	assert(m_CurState);

	m_CurState->Enter();
}

CState* CFSM::FindState(const wstring& _strName)
{
	map<wstring,CState*>::iterator iter = m_mapState.find(_strName);

	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}
