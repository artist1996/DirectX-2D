#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "components.h"

#include "CAssetMgr.h"
#include "assets.h"

#include "CCollisionMgr.h"

#include "CMaterial.h"

CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
	, m_LevelChanged(false)
{
}

CLevelMgr::~CLevelMgr()
{
	Delete_Vec(m_vecLevel);
	//SAFE_DELETE(m_CurLevel);
}

CGameObject* CLevelMgr::FindObjectByName(const wstring& _strName)
{
	if (m_CurLevel)
	{
		return m_CurLevel->FindObjectByName(_strName);
	}

	return nullptr;
}

void CLevelMgr::Init()
{
}

void CLevelMgr::Progress()
{
	m_LevelChanged = false;

	if (nullptr == m_CurLevel)
		return;

	if (LEVEL_STATE::PLAY == m_CurLevel->GetState())
	{
		m_CurLevel->Tick();
	}

	m_CurLevel->ClearObject();

	m_CurLevel->FinalTick();
}

bool CLevelMgr::ChangeLevel(CLevel* _NextLevel)
{
	if (m_CurLevel == _NextLevel)
		return false;

	if (nullptr != m_CurLevel)
		delete m_CurLevel;

	m_CurLevel = _NextLevel;

	LevelChanged();

	return true;
}

void CLevelMgr::ChangeCurLevel(LEVEL_TYPE _Type)
{
	m_CurLevel = m_vecLevel[(UINT)_Type];

	LevelChanged();
}

void CLevelMgr::LevelChanged()
{
	CTaskMgr::GetInst()->AddTask(tTask{ TASK_TYPE::LEVEL_CHANGED });
}

CGameObject* CLevelMgr::GetPlayer()
{
	CGameObject* pObject = FindObjectByName(L"Player");
	return pObject;
}

CGameObject* CLevelMgr::GetPlayerJump()
{
	CGameObject* pObject = FindObjectByName(L"PlayerJump");
	return pObject;
}

CGameObject* CLevelMgr::GetPlayerMove()
{
	CGameObject* pObject = FindObjectByName(L"PlayerMove");
	return pObject;
}
