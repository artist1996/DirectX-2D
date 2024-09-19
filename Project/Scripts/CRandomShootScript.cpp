#include "pch.h"
#include "CRandomShootScript.h"

#include <Engine/CLevelMgr.h>
#include "CDirezieScript.h"

CRandomShootScript::CRandomShootScript()
	: CScript(SCRIPT_TYPE::RANDOMSHOOTSCRIPT)
	, m_Count(0)
	, m_Hit(false)
{
}

CRandomShootScript::~CRandomShootScript()
{
}

void CRandomShootScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetScalarParam(INT_3, 1);
	Animator2D()->Play(0, 17.f, false);
//#ifdef _DEBUG
//	Collider2D()->SetActive(true);
//#endif
	Collider2D()->SetRender(true);

	GetOwner()->SetID(OBJ_ID::RANDOMSHOOT);
}

void CRandomShootScript::Tick()
{
	if (Animator2D()->IsFinish())
	{
		//m_Hit = false;
		//Animator2D()->Reset();
		//Collider2D()->ClearOverlapCount();
		DeleteObject(GetOwner());
	}
}

void CRandomShootScript::SaveToFile(FILE* _pFile)
{
}

void CRandomShootScript::LoadFromFile(FILE* _pFile)
{
}

void CRandomShootScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (6 == _OtherObj->GetLayerIdx())
	{
		INFO& info = _OtherObj->GetInfo();
	
		if (L"juris" == _OtherObj->GetName())
		{			
			_OtherObj->FSM()->ChangeState(L"Stiffness");
			info.HP -= 20.f;
		}
	
		else if (L"hyungteo" == _OtherObj->GetName())
		{
			CRigidbody* pRB = _OtherObj->Rigidbody();
	
			if (pRB->IsGround())
				_OtherObj->FSM()->ChangeState(L"Stiffness");
			else
			{
				pRB->SetGround(true);
				pRB->SetJumpSpeed(100.f);
				pRB->SetMaxGravitySpeed(200.f);
				pRB->Jump();
 				_OtherObj->FSM()->ChangeState(L"AirHit");
			}
			info.HP -= 20.f;
		}
	
		else if (L"direzie" == _OtherObj->GetName() && !info.bSuperArmor)
		{
			CRigidbody* pRB = _OtherObj->Rigidbody();
			if (pRB->IsGround())
				_OtherObj->FSM()->ChangeState(L"GroundHit");
			else
			{
				pRB->SetGround(true);
				pRB->SetJumpSpeed(50.f);
				pRB->SetMaxGravitySpeed(200.f);
				pRB->Jump();
				_OtherObj->FSM()->ChangeState(L"AirHit");
			}
			info.HP -= 20.f;
		}

		else if (L"meltknight" == _OtherObj->GetName())
		{
			info.HP -= 20.f;
		}
	}
}

void CRandomShootScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	//if (6 == _OtherObj->GetLayerIdx())
	//{
	//	INFO& info = _OtherObj->GetInfo();
	//	if (false == m_Hit)
	//	{
	//		info.HP -= 20.f;
	//		m_Hit = true;
	//	}
	//
	//	if (L"juris" == _OtherObj->GetName())
	//	{
	//		_OtherObj->FSM()->ChangeState(L"Stiffness");
	//	}
	//
	//	else if (L"hyungteo" == _OtherObj->GetName())
	//	{
	//		CRigidbody* pRB = _OtherObj->Rigidbody();
	//
	//		if (pRB->IsGround())
	//			_OtherObj->FSM()->ChangeState(L"Stiffness");
	//		else
	//		{
	//			pRB->SetGround(true);
	//			pRB->SetJumpSpeed(100.f);
	//			pRB->SetMaxGravitySpeed(200.f);
	//			pRB->Jump();
	//			_OtherObj->FSM()->ChangeState(L"AirHit");
	//		}
	//	}
	//
	//	else if (L"direzie" == _OtherObj->GetName() && !info.bSuperArmor)
	//	{
	//		CRigidbody* pRB = _OtherObj->Rigidbody();
	//		if (pRB->IsGround())
	//			_OtherObj->FSM()->ChangeState(L"GroundHit");
	//		else
	//		{
	//			pRB->SetGround(true);
	//			pRB->SetJumpSpeed(50.f);
	//			pRB->SetMaxGravitySpeed(200.f);
	//			pRB->Jump();
	//			_OtherObj->FSM()->ChangeState(L"AirHit");
	//		}
	//	}
	//}
}
