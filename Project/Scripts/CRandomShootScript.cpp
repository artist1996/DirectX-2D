#include "pch.h"
#include "CRandomShootScript.h"

#include <Engine/CLevelMgr.h>
#include "CDirezieScript.h"
#include "CMonsterDamageFontScript.h"

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

		if (info.bDead)
			return;
	
		int Rand = CRandomMgr::GetInst()->GetRandom(1);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_hit_01.ogg")->Play(1, 0.2f, true);

		if (L"MonsterMove" != _OtherObj->GetName() && 6 == _OtherObj->GetLayerIdx() && OBJ_DIR::DIR_LEFT == _OtherObj->GetParent()->GetDir())
		{
			Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();
			Ptr<CPrefab> pDamage = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\monsterdamage.pref");
			CGameObject* pObj = pDamage->Instantiate();
			pObj->Transform()->SetRelativePos(Vec3(vOtherPos.x + 100.f, vOtherPos.y, vOtherPos.z));

			if (0 == Rand)
			{
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(3864871);
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
			}
			else
			{
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(5234684);
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
			}
			CreateObject(pObj, 0);
		}
		else if (L"MonsterMove" != _OtherObj->GetName() && 6 == _OtherObj->GetLayerIdx() && OBJ_DIR::DIR_RIGHT == _OtherObj->GetParent()->GetDir())
		{
			Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();
			Ptr<CPrefab> pDamage = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\monsterdamage.pref");
			CGameObject* pObj = pDamage->Instantiate();
			pObj->Transform()->SetRelativePos(Vec3(vOtherPos.x - 100.f, vOtherPos.y, vOtherPos.z));
			if (0 == Rand)
			{
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(3864871);
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
			}
			else
			{
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(5234684);
				static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
			}
			CreateObject(pObj, 0);
		}

		if (L"juris" == _OtherObj->GetName())
		{			
			_OtherObj->FSM()->ChangeState(L"Stiffness");
			if (info.bReflection)
			{
				CLevelMgr::GetInst()->FindObjectByName(L"Player")->GetInfo().HP -= 20.f;
			}
			else
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
		}

		else if (L"meltknight" == _OtherObj->GetName())
		{
			info.HP -= 20.f;
		}
		info.HP -= 20.f;
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
