#include "pch.h"
#include "CGameObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "components.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_Owner(nullptr)
	, m_Target(nullptr)
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1)	// ���� ���� �� ��� ���̾� �Ҽӵ� �ƴϴ�(�����ȿ� ���� ���� ����)
	, m_Dead(false)
	, m_Moveable{ true,true,true,true }
	, m_Dir(OBJ_DIR::DIR_RIGHT)
	, m_TBDir(OBJ_DIR::END)
	, m_PrevDir(OBJ_DIR::END)
	, m_ID(OBJ_ID::END)
	, m_Info{}
{
}

CGameObject::CGameObject(const CGameObject& _Origin)
	: CEntity(_Origin)
	, m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1)
	, m_Dead(false)
	, m_Moveable{ true,true,true,true }
	, m_Dir(_Origin.m_Dir)
	, m_TBDir(_Origin.m_TBDir)
	, m_PrevDir(_Origin.m_PrevDir)
	, m_ID(_Origin.m_ID)
	, m_Owner(_Origin.m_Owner)
	, m_Target(_Origin.m_Target)
	, m_Info(_Origin.m_Info)
{
	// Component ����
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == _Origin.m_arrCom[i])
			continue;

		CComponent* pComponent = _Origin.m_arrCom[i]->Clone();
		AddComponent(pComponent);
		pComponent->Init();
	}

	// Script ����
	for (size_t i = 0; i < _Origin.m_vecScript.size(); ++i)
	{
		AddComponent(_Origin.m_vecScript[i]->Clone());
	}

	// Child Object ����
	for (size_t i = 0; i < _Origin.m_vecChildren.size(); ++i)
	{
		AddChild(_Origin.m_vecChildren[i]->Clone());
	}
}

CGameObject::~CGameObject()
{
	Delete_Array(m_arrCom);
	Delete_Vec(m_vecScript);
	Delete_Vec(m_vecChildren);
}

void CGameObject::AddComponent(CComponent* _Component)
{
	COMPONENT_TYPE Type = _Component->GetComponentType();

	if (COMPONENT_TYPE::SCRIPT == Type)
	{
		m_vecScript.push_back((CScript*)_Component);
		_Component->SetOwner(this);
	}

	else
	{
		//assert(nullptr == m_arrCom[(UINT)Type]);

		m_arrCom[(UINT)Type] = _Component;
		m_arrCom[(UINT)Type]->SetOwner(this);

		CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(_Component);

		assert(!(pRenderCom && m_RenderCom));

		if (pRenderCom)
		{
			m_RenderCom = pRenderCom;
		}
	}
}

CScript* CGameObject::FindScriptByName(const wstring& _strName)
{

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		if (_strName == m_vecScript[i]->GetName())
			return m_vecScript[i];
	}

	return nullptr;
}

void CGameObject::ChangeLayer(CGameObject* _Object, int _Idx)
{
	if (m_Parent)
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLayer* pLayer = pLevel->GetLayer(m_LayerIdx);

		if (!m_vecChildren.empty())
		{
			for (size_t i = 0; i < m_vecChildren.size(); ++i)
			{
				CGameObject* pChild = m_vecChildren[i];
				pChild->DeregisterChild();
				pChild->m_LayerIdx = -1;
				CreateObject(pChild, m_LayerIdx);
			}
		}

		pLayer->DeregisterObject(this);
		DeregisterChild();
		pLevel->AddObject(_Idx, this);
	}

	else
	{
		if (-1 != m_LayerIdx)
		{
			CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			CLayer* pLayer = pLevel->GetLayer(m_LayerIdx);

			if (!m_vecChildren.empty())
			{
				for (size_t i = 0; i < m_vecChildren.size(); ++i)
				{
					CGameObject* pChild = m_vecChildren[i];
					pChild->DeregisterChild();
					pChild->m_LayerIdx = -1;
					CreateObject(pChild, m_LayerIdx);
				}
			}

			DisconnectWithLayer();

			pLevel->AddObject(_Idx, this, true);
			
			pLayer = pLevel->GetLayer(_Idx);
			pLayer->RegisterGameObject(this);
		}
	}
}

void CGameObject::AddChild(CGameObject* _ChildObject)
{
	// �θ� ������Ʈ�� Level �� �����ְ�, AddChild �Ǵ� �ڽ� ������Ʈ�� ������ �Ҽӵ��� ���� ���
	if (-1 != m_LayerIdx && -1 == _ChildObject->m_LayerIdx)
	{
		assert(nullptr);
	}

	// �ڽ����� ������ ������Ʈ�� �̹� �θ� �ִ� ���
	if (_ChildObject->GetParent())
	{
		_ChildObject->DeregisterChild();
	}

	// �ڽ����� ������ ������Ʈ�� �ֻ��� �θ� ������Ʈ�� ���
	else
	{
		if (-1 != _ChildObject->m_LayerIdx)
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			if (nullptr != pCurLevel)
			{
				CLayer* pLayer = pCurLevel->GetLayer(_ChildObject->m_LayerIdx);
				pLayer->DeregisterObjectAsParent(_ChildObject);
			}
		}
	}

	m_vecChildren.push_back(_ChildObject);
	_ChildObject->m_Parent = this;

	CLevelMgr::GetInst()->LevelChanged();
}

void CGameObject::DisconnectWithLayer()
{
	if (nullptr == m_Parent)
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLayer* pLayer = pLevel->GetLayer(m_LayerIdx);
		pLayer->DisconnectWithObject(this);
	}

	m_LayerIdx = -1;
}

void CGameObject::DeregisterChild()
{
	vector<CGameObject*>::iterator iter = m_Parent->m_vecChildren.begin();

	for (; iter != m_Parent->m_vecChildren.end(); ++iter)
	{
		if ((*iter) == this)
		{
			m_Parent->m_vecChildren.erase(iter);
			m_Parent = nullptr;
			return;
		}
	}

	assert(nullptr);
}

bool CGameObject::IsAncestor(CGameObject* _Object)
{
	CGameObject* pObject = m_Parent;

	while (pObject)
	{
		if (pObject == _Object)
			return true;
		else
			pObject = pObject->GetParent();
	}

	return false;
}

void CGameObject::Begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrCom[i])
			continue;

		m_arrCom[i]->Begin();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->Begin();
	}

	// �ڽ� ������Ʈ
	for (size_t i = 0; i < m_vecChildren.size(); ++i)
	{
		m_vecChildren[i]->Begin();
	}
}

void CGameObject::Tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if(nullptr != m_arrCom[i])
			m_arrCom[i]->Tick();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->Tick();
	}

	// �ڽ� ������Ʈ
	for (size_t i = 0; i < m_vecChildren.size(); ++i)
	{
		m_vecChildren[i]->Tick();
	}
}

void CGameObject::FinalTick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->FinalTick();
	}

	// ���̾� ���
	assert(-1 != m_LayerIdx);
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = pLevel->GetLayer(m_LayerIdx);
	pLayer->RegisterGameObject(this);

	// �ڽ� ������Ʈ
	vector<CGameObject*>::iterator iter = m_vecChildren.begin();
	for (; iter != m_vecChildren.end(); )
	{
		(*iter)->FinalTick();

		if ((*iter)->IsDead())
			iter = m_vecChildren.erase(iter);
		else
			++iter;
	}
}

void CGameObject::Render()
{
	if (m_RenderCom)
		m_RenderCom->Render();
}