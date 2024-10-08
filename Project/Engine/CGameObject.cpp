#include "pch.h"
#include "CGameObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CFontMgr.h"
#include "components.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_Owner(nullptr)
	, m_Target(nullptr)
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1)	// ���� ���� �� ��� ���̾� �Ҽӵ� �ƴϴ�(�����ȿ� ���� ���� ����)
	, m_Dead(false)
	, m_GroundCollision(false)
	, m_Color(0.f)
	, m_FontScale(0.f)
	, m_Active(true)
{
}

CGameObject::CGameObject(const CGameObject& _Origin)
	: CEntity(_Origin)
	, m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1)
	, m_Dead(false)
	, m_Owner(_Origin.m_Owner)
	, m_Target(_Origin.m_Target)
	, m_GroundCollision(false)
	, m_Color(_Origin.m_Color)
	, m_strFont(_Origin.m_strFont)
	, m_FontScale(_Origin.m_FontScale)
	, m_Active(_Origin.m_Active)
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

CGameObject* CGameObject::FindChildByName(const wstring& _strName)
{
	for (size_t i = 0; i < m_vecChildren.size(); ++i)
	{
		if (_strName == m_vecChildren[i]->GetName())
			return m_vecChildren[i];
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

	if (m_strFont.empty() || !m_Active)
		return;

	Vec3 vScreenPos = CarculatePosition();

	CFontMgr::GetInst()->DrawFont(m_strFont.c_str(), vScreenPos.x + m_FontOffset.x, vScreenPos.y + m_FontOffset.y, m_FontScale, m_Color);
}

Vec3 CGameObject::CarculatePosition()
{
	Vec3 vPos = Transform()->GetWorldPos();

	CGameObject* pCam = CLevelMgr::GetInst()->FindObjectByName(L"MainCamera");

	const Matrix& matView = pCam->Camera()->GetViewMatrix();
	const Matrix& matProj = pCam->Camera()->GetProjMatrix();


	Vec4 vClipPos = Vec4(vPos, 1.f);
	vClipPos = XMVector4Transform(vClipPos, matView * matProj);

	Vec3 vNDC;
	vNDC.x = vClipPos.x / vClipPos.w;
	vNDC.y = vClipPos.y / vClipPos.w;
	vNDC.z = vClipPos.z / vClipPos.w;

	float Width = 1280.f;
	float Height = 768.f;

	Vec3 vScreenPos;
	vScreenPos.x = (vNDC.x * 0.5f + 0.5f) * Width;
	vScreenPos.y = (1.f - (vNDC.y * 0.5f + 0.5f)) * Height; // y�� ������� ��

	return vScreenPos;
}

void CGameObject::SetActive(bool _Set)
{
	m_Active = _Set;

	if (m_vecChildren.empty())
		return;

	for (size_t i = 0; i < m_vecChildren.size(); ++i)
	{
		m_vecChildren[i]->SetActive(_Set);
	}
}