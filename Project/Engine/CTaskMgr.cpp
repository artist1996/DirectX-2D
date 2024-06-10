#include "pch.h"
#include "CTaskMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CGameObject.h"

CTaskMgr::CTaskMgr()
{}

CTaskMgr::~CTaskMgr()
{
}

void CTaskMgr::Tick()
{
	ClearGC();

	ExecuteTask();
}

void CTaskMgr::ClearGC()
{
	Delete_Vec(m_GC);
}

void CTaskMgr::ExecuteTask()
{
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		tTask& Task = m_vecTask[i];

		switch (Task.Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			int Layer = m_vecTask[i].Param_0;
			CGameObject* pObj = (CGameObject*)m_vecTask[i].Param_1;
			pCurLevel->AddObject(Layer, pObj);
		}
		break;
		case TASK_TYPE::DELETE_OBJECT:
		{
			CGameObject* pObject = (CGameObject*)m_vecTask[i].Param_0;
			if (pObject->m_Dead)
			{
				continue;
			}
		
			// GC ¿¡ ³Ö¾îÁÜ
			pObject->m_Dead = true;
			m_GC.push_back(pObject);
		}
		break;
		case TASK_TYPE::CHANGE_LEVEL:
		{
		}
		break;
		}

	}

	m_vecTask.clear();	
}