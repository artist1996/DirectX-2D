#include "pch.h"
#include "CJackSpikeScript.h"

CJackSpikeScript::CJackSpikeScript()
	: CScript(SCRIPT_TYPE::JACKSPIKESCRIPT)
	, m_Time(0.f)
{
}

CJackSpikeScript::~CJackSpikeScript()
{
}

void CJackSpikeScript::Begin()
{
}

void CJackSpikeScript::Tick()
{
	m_Time += DT;

	if (0.15f < m_Time)
	{
		DeleteObject(GetOwner());
	}
}