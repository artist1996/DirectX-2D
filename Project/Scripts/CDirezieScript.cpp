#include "pch.h"
#include "CDirezieScript.h"

#include <Engine/CFontMgr.h>
#include <Engine/CObjectPoolMgr.h>
#include <States/CDirezieIdleState.h>
#include <States/CDirezieTraceState.h>
#include <States/CDirezieAttack01State.h>
#include <States/CDirezieAttack02State.h>
#include <States/CDirezieAttack03State.h>
#include <States/CDirezieAttack04State.h>
#include <States/CDirezieAttack05State.h>
#include <States/CDirezieHideState.h>
#include <States/CDirezieHitState.h>
#include <States/CDirezieStiffnessState.h>
#include <States/CDirezieFlyState.h>
#include <States/CDirezieAirHitState.h>
#include <States/CDirezieFallState.h>
#include <States/CDirezieWakeUpState.h>
#include <States/CDirezieDownHitState.h>

CDirezieScript::CDirezieScript()
	: CScript(SCRIPT_TYPE::DIREZIESCRIPT)
	, m_WindPref(nullptr)
	, m_Damage(0.f)
	, m_Count(1.f)
	, m_DamageHP(0.f)
	, m_IsDamage(false)
{
}

CDirezieScript::~CDirezieScript()
{
}

float CDirezieScript::Lerp(float _start, float _end, float _t)
{
	return _start + (_end - _start) * _t;
}

void CDirezieScript::InitInfo()
{
	INFO info = {};

	info.MaxHP = 3700.f;
	info.HP = 3700.f;

	m_DamageHP = info.HP;

	GetOwner()->SetInfo(info);
}

void CDirezieScript::Begin()
{
	InitInfo();

	Vec3 vPos = Transform()->GetRelativePos();

	MeshRender()->GetDynamicMaterial();

	GetOwner()->SetFont(L"보스-검은 질병의 디레지에");
	GetOwner()->SetFontScale(15.f);
	GetOwner()->SetFontColor(FONT_RGBA(216, 74, 229, 255));
	GetOwner()->SetFontOffset(Vec2(-50.f, -100.f));

	FSM()->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, CObjectPoolMgr::GetInst()->GetPlayerEntity());
	FSM()->AddState(L"Idle", new CDirezieIdleState);
	FSM()->AddState(L"Trace", new CDirezieTraceState);
	FSM()->AddState(L"Hide", new CDirezieHideState);
	FSM()->AddState(L"Attack01", new CDirezieAttack01State);
	FSM()->AddState(L"Attack02", new CDirezieAttack02State);
	FSM()->AddState(L"Attack03", new CDirezieAttack03State);
	FSM()->AddState(L"Attack04", new CDirezieAttack04State);
	FSM()->AddState(L"Attack05", new CDirezieAttack05State);
	FSM()->AddState(L"GroundHit", new CDirezieHitState);
	FSM()->AddState(L"Stiffness", new CDirezieStiffnessState);
	FSM()->AddState(L"Fly", new CDirezieFlyState);
	FSM()->AddState(L"AirHit", new CDirezieAirHitState);
	FSM()->AddState(L"Fall", new CDirezieFallState);
	FSM()->AddState(L"WakeUp", new CDirezieWakeUpState);
	FSM()->AddState(L"DownHit", new CDirezieDownHitState);

	m_WindPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\direziewind.pref");
	
	CreateObject(m_WindPref->Instantiate(), 8);

	FSM()->ChangeState(L"Idle");
}

void CDirezieScript::Tick()
{
	if (nullptr == GetOwner()->GetParent())
		return;

	OBJ_DIR Dir = GetOwner()->GetParent()->GetDir();
	INFO& info = GetOwner()->GetInfo();

	if (OBJ_DIR::DIR_LEFT == Dir)
	{
		GetOwner()->SetFontOffset(Vec2(-100.f, -100.f));
	}

	else
	{
		GetOwner()->SetFontOffset(Vec2(-50.f, -100.f));
	}

	//if (info.bSuperArmor)
	//	MeshRender()->GetMaterial()->SetScalarParam(INT_3, 1);
	//else
	//	MeshRender()->GetMaterial()->SetScalarParam(INT_3, 0);
}

void CDirezieScript::Damage(float _Attack)
{
	GetOwner()->GetInfo().HP -= _Attack;
}

void CDirezieScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDirezieScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDirezieScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}