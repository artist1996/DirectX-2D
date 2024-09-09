#include "pch.h"
#include "CRandomShootScript.h"

CRandomShootScript::CRandomShootScript()
	: CScript(SCRIPT_TYPE::RANDOMSHOOTSCRIPT)
	, m_Count(0)
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
	Collider2D()->SetRender(false);

	GetOwner()->SetID(OBJ_ID::RANDOMSHOOT);
}

void CRandomShootScript::Tick()
{
	if (Animator2D()->IsFinish())
	{
		DisconnectObject(GetOwner());
		Animator2D()->Reset();
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

		info.HP -= 10.f;

		if (L"juris" == _OtherObj->GetName())
		{			
			_OtherObj->FSM()->ChangeState(L"Stiffness");
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
		}
	}
}
