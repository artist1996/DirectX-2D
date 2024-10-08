#include "pch.h"
#include "CDoubleGunHawkScript.h"
#include <Engine/CLevelMgr.h>

#include "CPlayerScript.h"
#include "CMonsterDamageFontScript.h"

CDoubleGunHawkScript::CDoubleGunHawkScript()
	: CScript(SCRIPT_TYPE::DOUBLEGUNHAWKSCRIPT)
	, m_Type(GUNHAWK_TYPE::END)
	, m_Time(0.f)
	, m_StopTime(1.f)
	, m_Force(600.f)
	, m_Accel(0.f)
	, m_Friction(500.f)
	, m_Mass(1.f)
	, m_Move(true)
	, m_ReverseMove(false)
	, m_Stop(false)
	, m_HitTime(0.f)
	, m_Hit(false)
	, m_DamageTime(0.f)
{
	AddScriptParam(SCRIPT_PARAM::VEC3, "DIRECTION", &m_Dir);
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_Type);
}

CDoubleGunHawkScript::~CDoubleGunHawkScript()
{
}

void CDoubleGunHawkScript::Begin()
{
	MeshRender()->GetDynamicMaterial();

	Animator2D()->Play(0, 30.f, true);

	MeshRender()->GetMaterial()->SetScalarParam(INT_3, 1);

	m_Accel = m_Force / m_Mass;
	
	if (GUNHAWK_TYPE::TYPE_ONE == m_Type)
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gunhawk_12.ogg")->Play(0, 0.4f, false);
	else
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gunhawk_3.ogg")->Play(0, 0.4f, false);

	CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gunhawk_gun.ogg")->Play(0, 0.1f, false);
}

void CDoubleGunHawkScript::Tick()
{
	Vec3 InitPos = GetOwner()->GetInitPos();
	Vec3 vPos = Transform()->GetRelativePos();
	
	if (m_Move)
	{
		//m_Accel = (m_Force * 1.2f) / m_Mass;

		if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
		{
			vPos.x += -m_Dir.x * m_Accel * 1.25f * DT;
			vPos.y += m_Dir.y * m_Accel / 14.f * DT;
		}

		else if (OBJ_DIR::DIR_RIGHT == GetOwner()->GetDir())
		{
			vPos.x += m_Dir.x * m_Accel * 1.25f * DT;
			vPos.y += m_Dir.y * m_Accel / 14.f * DT;
		}

		if (250.f < fabs(vPos.x - InitPos.x))
		{
			m_Move = false;
			m_ReverseMove = true;
		}
		m_Accel -= m_Friction * DT;
	}

	else if (m_Stop)
	{
		m_Time += DT;

		if (0.1f < m_Time)
		{
			m_Stop = false;
			m_ReverseMove = true;
		}
	}

	else if (m_ReverseMove)
	{
		//m_Accel = (m_Force * 1.5f) / m_Mass;

		if (OBJ_DIR::DIR_LEFT == GetOwner()->GetDir())
		{
			vPos.x -=  m_Dir.x * m_Accel * 1.5f * DT;
			vPos.y += m_Dir.y * m_Accel / 6.f * DT;
		}

		else if (OBJ_DIR::DIR_RIGHT == GetOwner()->GetDir())
		{
			vPos.x -= -m_Dir.x * m_Accel * 1.5f * DT;
			vPos.y += m_Dir.y * m_Accel / 6.f * DT;
		}
	
		if (1200.f < fabs(InitPos.x - vPos.x))
		{
			m_Move = false;
			m_Stop = true;

			DeleteObject(GetOwner());
			if (GUNHAWK_TYPE::TYPE_ONE == m_Type)
				CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gunhawk_12.ogg")->Stop();
			else
				CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gunhawk_3.ogg")->Stop();

			CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gunhawk_gun.ogg")->Stop();
		}

		m_Accel -= m_Friction * DT;
	}

	if (0.2f < m_HitTime)
		m_HitTime = 0.f;

	if (m_Hit)
	{
		m_DamageTime += DT;

		if (0.2f < m_DamageTime)
		{
			m_Hit = false;
			m_DamageTime = 0.f;
		}
	}

	Transform()->SetRelativePos(vPos);
}

void CDoubleGunHawkScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (L"Player" == _OtherObj->GetName())
	{
		if (GUNHAWK_TYPE::TYPE_ONE == m_Type && m_ReverseMove)
		{
			CPlayerScript* pScript = (CPlayerScript*)CLevelMgr::GetInst()->FindObjectByName(L"Player")->FindScriptByName(L"CPlayerScript");

			pScript->ChangeStateDoubleGunHawkStandBy();

			DeleteObject(GetOwner());
			_OtherCollider->MinusOverlapCount();
			CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gunhawk_12.ogg")->Stop();
			CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gunhawk_gun.ogg")->Stop();
		}
	}
}

void CDoubleGunHawkScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	INFO& info = _OtherObj->GetInfo();
	if (6 == _OtherObj->GetLayerIdx())
	{
		if (!m_Hit)
		{
			info.HP -= 20.f;
			m_Hit = true;
			int Rand = CRandomMgr::GetInst()->GetRandom(1);
			CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gunhawk_hit_01.ogg")->Play(1, 0.3f, true);

			if (L"MonsterMove" != _OtherObj->GetName() && 6 == _OtherObj->GetLayerIdx() && OBJ_DIR::DIR_LEFT == _OtherObj->GetParent()->GetDir())
			{
				Vec3 vOtherPos = _OtherObj->Transform()->GetWorldPos();
				Ptr<CPrefab> pDamage = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\monsterdamage.pref");
				CGameObject* pObj = pDamage->Instantiate();
				pObj->Transform()->SetRelativePos(Vec3(vOtherPos.x + 100.f, vOtherPos.y, vOtherPos.z));

				if (0 == Rand)
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(3416371);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
				}
				else
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(4167254);
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
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(3416371);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::NORMAL);
				}
				else
				{
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetDamge(4167254);
					static_cast<CMonsterDamageFontScript*>(pObj->GetScripts()[0])->SetType(FONT_TYPE::CRITICAL);
				}
				CreateObject(pObj, 0);
			}
		}
	}

	if (L"juris" == _OtherObj->GetName())
	{
		m_HitTime += DT;

		if (0.15f < m_HitTime)
		{
			if(!info.bReflection)
				_OtherObj->FSM()->ChangeState(L"Stiffness");
		}
	}

	if (L"hyungteo" == _OtherObj->GetName())
	{
		m_HitTime += DT;
		CRigidbody* pRB = _OtherObj->Rigidbody();

		if (pRB->IsGround())
		{
			if(0.15f < m_HitTime)
				_OtherObj->FSM()->ChangeState(L"Stiffness");
		}
		else
		{
			pRB->SetGround(true);
			pRB->SetJumpSpeed(10.f);
			pRB->SetMaxGravitySpeed(500.f);
			pRB->Jump();
			_OtherObj->FSM()->ChangeState(L"AirHit");
		}
	}

	if (L"direzie" == _OtherObj->GetName() && !info.bSuperArmor)
	{
		m_HitTime += DT;
		CRigidbody* pRB = _OtherObj->Rigidbody();

		if (_OtherObj->Rigidbody()->IsGround())
		{
			if (0.15f < m_HitTime)
				_OtherObj->FSM()->ChangeState(L"Stiffness");
		}
		else
		{
			pRB->SetGround(true);
			pRB->SetJumpSpeed(100.f);
			pRB->SetMaxGravitySpeed(300.f);
			pRB->Jump();
			_OtherObj->FSM()->ChangeState(L"AirHit");
		}
	}
}

void CDoubleGunHawkScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDoubleGunHawkScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Type, sizeof(GUNHAWK_TYPE), 1, _pFile);
	fwrite(&m_Dir, sizeof(Vec3), 1, _pFile);
	fwrite(&m_StopTime, sizeof(float), 1, _pFile);
}

void CDoubleGunHawkScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Type, sizeof(GUNHAWK_TYPE), 1, _pFile);
	fread(&m_Dir, sizeof(Vec3), 1, _pFile);
	fread(&m_StopTime, sizeof(float), 1, _pFile);
}
