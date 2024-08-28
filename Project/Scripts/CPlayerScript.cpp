#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

#include <Engine/CDistanceMgr.h>
#include <Engine/CObjectPoolMgr.h>

#include <Engine/CFSM.h>

#include "CPlayerMoveScript.h"
#include "CPlayerJumpScript.h"


CPlayerScript::CPlayerScript()
	: CScript(SCRIPT_TYPE::PLAYERSCRIPT)
	, m_MoveObject(nullptr)
	, m_JumpObject(nullptr)
	, m_MoveScript(nullptr)
	, m_JumpScript(nullptr)
	, m_Texture(nullptr)
	, m_BuffPref(nullptr)
	, m_RandomShootPref(nullptr)
	, m_PistolPref(nullptr)
	, m_MuzzlePref(nullptr)
	, m_HammerPref(nullptr)
	, m_HeadShotEffectPref(nullptr)
	, m_WindmillPref(nullptr)
	, m_HeadShotPref(nullptr)
	, m_GunHawkFirstUpPref(nullptr)
	, m_GunHawkFirstDownPref(nullptr)
	, m_GunHawkSecondUpPref(nullptr)
	, m_GunHawkSecondDownPref(nullptr)
	, m_MachKickPref(nullptr)
	, m_JackSpikePref(nullptr)
	, m_RisingShotPref(nullptr)
	, m_Dir(OBJ_DIR::DIR_LEFT)
	, m_State(STATE::IDLE)
	, m_Speed(500.f)
	, m_JumpHeight(0.f)
	, m_Time(0.f)
	, m_NextAttack(false)
	, m_Run(false)
	, m_Spawn(true)
	, m_Muzzel(true)
	, m_CheckRange(false)
	, m_CoolTime{}
	, m_UseSkill{}
	, m_Prefabs{}
{
	SetName(L"CPlayerScript");

	AddScriptParam(SCRIPT_PARAM::FLOAT,"PlayerSpeed", &m_Speed);

	m_CoolTime.fHeadShotCoolTime		= 5.f;
	m_CoolTime.fDeathByRevolverCoolTime = 10.f;
	m_CoolTime.fRandomShootCoolTime		= 23.f;
	m_CoolTime.fWindMillCoolTime		= 7.f;
	m_CoolTime.fGunHawkCoolTime			= 31.f;
	m_CoolTime.fMachKickCoolTime		= 7.f;
	m_CoolTime.fJackSpikeCoolTime		= 3.f;
	m_CoolTime.fRisingShotCoolTime		= 3.f;
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Begin()
{
	MeshRender()->GetDynamicMaterial();

	m_BuffPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\deathbyrevolver.pref");
	m_RandomShootPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\skill_randomshoot.pref");
	m_PistolPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\pistol.pref");
	m_MuzzlePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\muzzle.pref");
	m_HammerPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\revolverhammer_normal.pref");
	m_HeadShotEffectPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\headshoteffect.pref");
	m_WindmillPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\windmilleffect.pref");
	m_HeadShotPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\skill_headshot.pref");
	m_GunHawkFirstUpPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gunhawk0_up.pref");
	m_GunHawkFirstDownPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gunhawk0_down.pref");
	m_GunHawkSecondUpPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gunhawk1_up.pref");
	m_GunHawkSecondDownPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gunhawk1_down.pref");
	m_MachKickPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\skill_machkick.pref");
	m_JackSpikePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\skill_jackspike.pref");
	m_RisingShotPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\skill_risingshot.pref");

	m_Prefabs.DiagonalPistolPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\diagonalpistol.pref");
	m_Prefabs.DiagonalHeadShotPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\diagonalheadshot.pref");

	m_MoveObject = CLevelMgr::GetInst()->FindObjectByName(L"PlayerMove");
	m_JumpObject = CLevelMgr::GetInst()->FindObjectByName(L"PlayerJump");
	
	m_MoveScript = (CPlayerMoveScript*)m_MoveObject->FindScriptByName(L"CPlayerMoveScript");
	m_JumpScript = (CPlayerJumpScript*)m_JumpObject->FindScriptByName(L"CPlayerJumpScript");
	
	CDistanceMgr::GetInst()->Init();

	Animator2D()->Play((int)IDLE, 5.f, true);

	Collider2D()->SetOffset(Vec3(0.f, -0.44f, 1.f));
}

void CPlayerScript::Tick()
{
	Vec3 vMovePos = m_MoveObject->Transform()->GetRelativePos();
	float fJumpHeight = m_JumpObject->Transform()->GetRelativePos().y;

	m_CheckRange = CDistanceMgr::GetInst()->IsInRange();

	switch (m_State)
	{
	case CPlayerScript::STATE::IDLE:
		Idle();
		break;
	case CPlayerScript::STATE::MOVE:
		Move();
		break;
	case CPlayerScript::STATE::JUMP:
		Jump();
		break;
	case CPlayerScript::STATE::LANDING:
		Landing();
		break;
	case CPlayerScript::STATE::RUN:
		Run();
		break;
	case CPlayerScript::STATE::DEAD:
		Dead();
		break;
	case CPlayerScript::STATE::AT_1:
		AT1();
		break;
	case CPlayerScript::STATE::AT_2:
		AT2();
		break;
	case CPlayerScript::STATE::AT_3:
		AT3();
		break;
	case CPlayerScript::STATE::AT_4:
		AT4();
		break;
	case CPlayerScript::STATE::DG_AT1:
		AT_DG1();
		break;
	case CPlayerScript::STATE::DG_AT2:
		AT_DG2();
		break;
	case CPlayerScript::STATE::DG_AT3:
		AT_DG3();
		break;
	case CPlayerScript::STATE::DG_AT4:
		AT_DG4();
		break;
	case CPlayerScript::STATE::SK_1:
		JackSpike();
		break;
	case CPlayerScript::STATE::SK_2:
		RisingShot();
		break;
	case CPlayerScript::STATE::SK_3:
		HeadShot();
		break;
	case CPlayerScript::STATE::SK_4:
		RandomShot();
		break;
	case CPlayerScript::STATE::SK_5:
		DeathByRevolver();
		break;
	case CPlayerScript::STATE::SK_6:
		WindMill();
		break;
	case CPlayerScript::STATE::SK_7:
		MachKick();
		break;
	case CPlayerScript::STATE::SK_8:
		break;
	case CPlayerScript::STATE::SK_9:
		break;
	case CPlayerScript::STATE::TACKLE:
		Tackle();
		break;
	case CPlayerScript::STATE::GUNHAWKSHOOT:
		GunHawkShoot();
		break;
	case CPlayerScript::STATE::GUNHAWKSTANDBY:
		GunHawkStandBy();
		break;
	case CPlayerScript::STATE::GUNHAWKLASTSHOOT:
		GunHawkLastShoot();
		break;
	case CPlayerScript::STATE::END:
		break;
	default:
		break;
	}
	
	if (m_Run)
		m_Time += DT;
	
	if (0.5f <= m_Time)
	{
		m_Run = false;
		m_Time = 0.f;
	}

	SkillTimeCheck();
	Transform()->SetRelativePos(Vec3(vMovePos.x, vMovePos.y + fJumpHeight, vMovePos.z + fJumpHeight));
	Vec3 vPos = Transform()->GetWorldPos();
}

void CPlayerScript::Idle()
{
	Vec3 vRot = Transform()->GetRelativeRotation();

	Collider2D()->SetOffset(Vec3(0.f, -0.44f, 1.f));

	m_JumpScript->SetJump(false);

	if (KEY_TAP(KEY::LEFT))
	{
		m_Dir = OBJ_DIR::DIR_LEFT;
		vRot = Vec3(0.f, 0.f, 0.f);
		if (!m_Run)
		{
			m_State = STATE::MOVE;
			Animator2D()->Play((int)STATE::MOVE, 8.f, true);
			m_Run = true;
		}
		else
		{
			m_State = STATE::RUN;
			Animator2D()->Play((int)STATE::RUN, 8.f, true);
			m_Run = false;
		}
	}
	else if (KEY_PRESSED(KEY::LEFT))
	{
		m_Dir = OBJ_DIR::DIR_LEFT;
		m_State = STATE::MOVE;
		vRot = Vec3(0.f, 0.f, 0.f);

		m_State = STATE::MOVE;
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		m_Dir = OBJ_DIR::DIR_RIGHT;
		SetState(STATE::MOVE);
		vRot.y = XM_PI;

		if (!m_Run)
		{
			m_State = STATE::MOVE;
			Animator2D()->Play((int)STATE::MOVE, 8.f, true);
			m_Run = true;
		}
		else
		{
			m_State = STATE::RUN;
			Animator2D()->Play((int)STATE::RUN, 8.f, true);
			m_Run = false;
		}
	}
	else if (KEY_PRESSED(KEY::RIGHT))
	{
		m_Dir = OBJ_DIR::DIR_RIGHT;
		SetState(STATE::MOVE);
		vRot.y = XM_PI;

		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}
	
	if (KEY_TAP(KEY::UP))
	{
		m_State = STATE::MOVE;
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}
	else if (KEY_PRESSED(KEY::UP))
	{
		m_State = STATE::MOVE;
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}

	if (KEY_TAP(KEY::DOWN))
	{
		m_State = STATE::MOVE;
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}
	else if (KEY_PRESSED(KEY::DOWN))
	{
		m_State = STATE::MOVE;
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}
	
	if (KEY_TAP(KEY::X))
	{
		if (m_CheckRange)
		{
			m_State = STATE::DG_AT1;
			Animator2D()->Play((int)STATE::DG_AT1, 15.f, true);
			SetMoveable(false);
			CreateMuzzelOfRevolverDiagonal();
			CreateDiagonalPistol();
		}

		else
		{
			m_State = STATE::AT_1;
			Animator2D()->Play((int)STATE::AT_1, 15.f, false);
			SetMoveable(false);
			CreateMuzzelOfRevolverNormal();
			CreatePistol();
		}

		m_JumpScript->SetJump(true);
	}
	else if (KEY_PRESSED(KEY::DOWN) && KEY_TAP(KEY::X))
	{
		m_State = STATE::DG_AT1;
		Animator2D()->Play((int)STATE::DG_AT1, 15.f, false);
		SetMoveable(false);
	}

	if (KEY_TAP(KEY::C))
	{
		m_State = STATE::JUMP;
		Animator2D()->Play((int)STATE::JUMP, 5.f, false);
	}

	// Skill
	Stylish();

	Transform()->SetRelativeRotation(vRot);
}

void CPlayerScript::Move()
{
	// ATTACK
	if (KEY_RELEASED(KEY::LEFT))
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
	}

	if (KEY_RELEASED(KEY::RIGHT))
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
	}
	
	if (KEY_RELEASED(KEY::UP))
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
	}
	
	if (KEY_RELEASED(KEY::DOWN))
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
	}

	if (KEY_PRESSED(KEY::DOWN) && KEY_TAP(KEY::X))
	{
		m_State = STATE::DG_AT1;
		Animator2D()->Play((int)STATE::DG_AT1, 15.f, true);
		SetMoveable(false);
		CreateMuzzelOfRevolverDiagonal();
		CreateDiagonalPistol();

		m_JumpScript->SetJump(true);
	}

	else if (KEY_TAP(KEY::X))
	{
		m_State = STATE::AT_1;
		Animator2D()->Play((int)STATE::AT_1, 15.f, false);
		SetMoveable(false);
		m_JumpScript->SetJump(true);
	}

	// JUMP
	if (KEY_TAP(KEY::C))
	{
		m_State = STATE::JUMP;
		Animator2D()->Play((int)STATE::JUMP, 5.f, false);
	}

	// SKILL
	Stylish();
}

void CPlayerScript::AT1()
{
	if (KEY_TAP(KEY::X))
	{
		m_NextAttack = true;
	}

	if (!m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)IDLE, 5.f, true);
		m_State = STATE::IDLE;
		SetMoveable(true);
	}
	
	else if (m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)AT_2, 10.f, true);
		m_State = STATE::AT_2;
		m_NextAttack = false;
		CreatePistol();
		CreateMuzzelOfRevolverNormal();
	}

	Stylish();
}

void CPlayerScript::AT2()
{
	if (KEY_TAP(KEY::X) && !Animator2D()->IsFinish())
	{
		m_NextAttack = true;
	}

	if (m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)AT_2, 10.f, true);
		m_State = STATE::AT_3;
		m_NextAttack = false;
		CreatePistol();
		CreateMuzzelOfRevolverNormal();
	}

	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)IDLE, 5.f, true);
		m_State = STATE::IDLE;
		SetMoveable(true);
	}

	Stylish();
}

void CPlayerScript::AT3()
{
	if (KEY_TAP(KEY::X) && !Animator2D()->IsFinish() && !m_NextAttack)
	{
		m_NextAttack = true;
	}

	if (m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)AT_3, 17.f, true);
		m_State = STATE::AT_4;
		m_NextAttack = true;
	}

	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)IDLE, 5.f, true);
		m_State = STATE::IDLE;
		SetMoveable(true);
	}

	Stylish();
}

void CPlayerScript::AT4()
{
	if (m_NextAttack && 5 == Animator2D()->GetCurFrameIndex())
	{
		CreatePistol();
		CreateMuzzelOfRevolver();
		m_NextAttack = false;
	}

	if (Animator2D()->IsFinish())
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
		SetMoveable(true);
	}

	Stylish();
}

void CPlayerScript::AT_DG1()
{
	if (KEY_TAP(KEY::X))
	{
		m_NextAttack = true;
	}
	
	if(m_NextAttack && Animator2D()->IsFinish())
	{
		if (m_CheckRange)
		{
			m_State = STATE::DG_AT2;
			Animator2D()->Play((int)STATE::DG_AT2, 10.f, true);
			CreateDiagonalPistol();
			CreateMuzzelOfRevolverDiagonal();
			m_NextAttack = false;
		}
		else
		{
			if (KEY_PRESSED(KEY::DOWN))
			{
				m_State = STATE::DG_AT2;
				Animator2D()->Play((int)STATE::DG_AT2, 10.f, true);
			}
			else if (KEY_RELEASED(KEY::DOWN))
			{
				m_State = STATE::AT_2;
				Animator2D()->Play((int)STATE::AT_2, 10.f, true);
			}
			CreateDiagonalPistol();
			CreateMuzzelOfRevolverDiagonal();
			m_NextAttack = false;
		}
	}
	
	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)STATE::IDLE, 5.f, true);
		SetMoveable(true);
	}

	Stylish();
}

void CPlayerScript::AT_DG2()
{
	if (KEY_TAP(KEY::X))
	{
		m_NextAttack = true;
	}

	if (m_NextAttack && Animator2D()->IsFinish())
	{
		if (KEY_PRESSED(KEY::DOWN))
		{
			m_State = STATE::DG_AT3;
			Animator2D()->Play((int)STATE::DG_AT2, 10.f, true);
			CreateDiagonalPistol();
			CreateMuzzelOfRevolverDiagonal();
		}
		else if(KEY_RELEASED(KEY::DOWN))
		{
			m_State = STATE::AT_2;
			Animator2D()->Play((int)STATE::AT_2, 10.f, true);
		}
		
		m_NextAttack = false;
	}

	else if(!m_NextAttack && Animator2D()->IsFinish())
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
		SetMoveable(true);
	}

	Stylish();
}

void CPlayerScript::AT_DG3()
{
	if (KEY_TAP(KEY::X))
	{
		m_NextAttack = true;
	}

	if (m_NextAttack && Animator2D()->IsFinish())
	{
		if (m_CheckRange)
		{
			m_State = STATE::DG_AT4;
			Animator2D()->Play((int)STATE::DG_AT3, 17.f, true);
		}

		else
		{
			if (KEY_PRESSED(KEY::DOWN))
			{
				m_State = STATE::DG_AT4;
				Animator2D()->Play((int)STATE::DG_AT3, 17.f, true);
			}

			else if (KEY_RELEASED(KEY::DOWN))
			{
				m_State = STATE::AT_2;
				Animator2D()->Play((int)STATE::AT_3, 10.f, true);
			}
		}
	}

	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
		SetMoveable(true);
	}

	Stylish();
}

void CPlayerScript::AT_DG4()
{
	if (m_NextAttack && 5 == Animator2D()->GetCurFrameIndex())
	{
		CreateDiagonalPistol();
		CreateMuzzelOfRevolverDiagonal();
		m_NextAttack = false;
	}

	if (Animator2D()->IsFinish())
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
		SetMoveable(true);
	}

	Stylish();
}

void CPlayerScript::Tackle()
{
	if (Animator2D()->IsFinish())
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
		m_MoveScript->SetState(MOVE_STATE::ST_IDLE);
		SetMoveable(true);
		m_MoveScript->SetSpeed(500.f);
	}
}

void CPlayerScript::Jump()
{
	m_JumpScript->SetJump(true);

	if (!m_JumpScript->IsNormalJump() && Animator2D()->IsFinish())
	{
		m_State = STATE::LANDING;
		Animator2D()->Play((int)LANDING, 3.f, false);
	}
}

void CPlayerScript::Landing()
{
	if (Animator2D()->IsFinish())
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
		m_JumpScript->SetJump(false);
	}
}

void CPlayerScript::Run()
{
	Collider2D()->SetOffset(Vec3(-0.5f, -0.44f, 1.f));
	m_MoveScript->SetSpeed(600.f);

	if (KEY_RELEASED(KEY::LEFT))
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
		m_MoveScript->SetSpeed(500.f);
	}
	else if (KEY_RELEASED(KEY::RIGHT))
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
		m_MoveScript->SetSpeed(500.f);
	}

	if (KEY_TAP(KEY::C))
	{
		m_State = STATE::JUMP;
		Animator2D()->Play((int)STATE::JUMP, 5.f, false);
		m_MoveScript->SetSpeed(500.f);
	}

	if (KEY_TAP(KEY::X))
	{
		SetState(STATE::TACKLE);
		Animator2D()->Play((int)ANIMATION_NUM::TACKLE, 7.f, false);
		m_MoveScript->SetState(MOVE_STATE::ST_TACKLE);
		m_MoveScript->SetSpeed(700.f);
	}

	Stylish();
}

void CPlayerScript::Dead()
{
}

void CPlayerScript::DeathByRevolver()
{
	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		SetMoveable(true);
	}
}

void CPlayerScript::JackSpike()
{
	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		SetMoveable(true);
	}

	Stylish();
}

void CPlayerScript::RisingShot()
{
	if (m_Spawn && 3 <= Animator2D()->GetCurFrameIndex())
	{
		CreateRisingShot();
		CreateMuzzelOfRevolver();
		m_Spawn = false;
	}

	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		SetMoveable(true);
		m_Spawn = true;
	}

	Stylish();
}

void CPlayerScript::HeadShot()
{
	if (m_Spawn && 3 <= Animator2D()->GetCurFrameIndex())
	{
		if (m_CheckRange)
		{
			CreateDiagonalHeadShot();
			CreateDiagonalHeadShotEffect();
			m_Spawn = false;
		}

		else if (KEY_PRESSED(KEY::DOWN))
		{
			CreateDiagonalHeadShot();
			CreateDiagonalHeadShotEffect();
			m_Spawn = false;
		}

		else
		{
			CreateHeadShot();
			CreateHeadShotEffect();
			m_Spawn = false;
		}
	}

	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		SetMoveable(true);
		m_Spawn = true;
	}
}

void CPlayerScript::RandomShot()
{
	CreateRandomShoot();

	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		SetMoveable(true);
		m_Spawn = true;
	}
}

void CPlayerScript::WindMill()
{
	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		SetMoveable(true);
	}

	Stylish();
}

void CPlayerScript::MachKick()
{
	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		SetMoveable(true);
	}
}

void CPlayerScript::GunHawkShoot()
{
	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		SetMoveable(true);
	}

	Stylish();
}

void CPlayerScript::GunHawkStandBy()
{
	if (!Animator2D()->IsFinish() && KEY_TAP(KEY::Q))
	{
		SetState(STATE::GUNHAWKLASTSHOOT);
		Animator2D()->Play((int)ANIMATION_NUM::GUNHAWKSHOOT, 7.f, true);
		CreateGunHawkSecond();
		SetMoveable(false);
	}

	else if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		SetMoveable(true);
	}
}

void CPlayerScript::GunHawkLastShoot()
{
	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		SetMoveable(true);
	}

	Stylish();
}

void CPlayerScript::SkillTimeCheck()
{
	if (m_UseSkill.bHeadShot)
	{
		m_CoolTime.fHeadShotTime += DT;
		
		if (m_CoolTime.fHeadShotCoolTime <= m_CoolTime.fHeadShotTime)
		{
			m_UseSkill.bHeadShot = false;
			m_CoolTime.fHeadShotTime = 0.f;
		}
	}
	if (m_UseSkill.bDeathByRevolver)
	{
		m_CoolTime.fDeathByRevolverTime += DT;

		if (m_CoolTime.fDeathByRevolverCoolTime <= m_CoolTime.fDeathByRevolverTime)
		{
			m_UseSkill.bDeathByRevolver = false;
			m_CoolTime.fDeathByRevolverTime = 0.f;
		}
	}
	if (m_UseSkill.bWindMill)
	{
		m_CoolTime.fWindMillTime += DT;

		if (m_CoolTime.fWindMillCoolTime <= m_CoolTime.fWindMillTime)
		{
			m_UseSkill.bWindMill = false;
			m_CoolTime.fWindMillTime = 0.f;
		}
	}
	if (m_UseSkill.bRandShoot)
	{
		m_CoolTime.fRandomShootTime += DT;

		if (m_CoolTime.fRandomShootCoolTime <= m_CoolTime.fRandomShootTime)
		{
			m_UseSkill.bRandShoot = false;
			m_CoolTime.fRandomShootTime = 0.f;
		}
	}
	if (m_UseSkill.bGunHawk)
	{
		m_CoolTime.fGunHawkTime += DT;

		if (m_CoolTime.fGunHawkCoolTime <= m_CoolTime.fGunHawkTime)
		{
			m_UseSkill.bGunHawk = false;
			m_CoolTime.fGunHawkTime = 0.f;
		}
	}
	if (m_UseSkill.bMachKick)
	{
		m_CoolTime.fMachKickTime += DT;

		if (m_CoolTime.fMachKickCoolTime <= m_CoolTime.fMachKickTime)
		{
			m_UseSkill.bMachKick = false;
			m_CoolTime.fMachKickTime = 0.f;
		}
	}
	if (m_UseSkill.bJackSpike)
	{
		m_CoolTime.fJackSpikeTime += DT;

		if (m_CoolTime.fJackSpikeCoolTime <= m_CoolTime.fJackSpikeTime)
		{
			m_UseSkill.bJackSpike = false;
			m_CoolTime.fJackSpikeTime = 0.f;
		}
	}
	if (m_UseSkill.bRisingShot)
	{
		m_CoolTime.fRisingShotTime += DT;

		if (m_CoolTime.fRisingShotCoolTime <= m_CoolTime.fRisingShotTime)
		{
			m_UseSkill.bRisingShot = false;
			m_CoolTime.fRisingShotTime = 0.f;
		}
	}
}

void CPlayerScript::Stylish()
{
	if (!m_UseSkill.bJackSpike && KEY_TAP(KEY::Z))
	{
		SetState(STATE::SK_1);
		Animator2D()->Play((int)ANIMATION_NUM::JACKSPIKE, 11.f, false);
		CreateJackSpike();
		SetMoveable(false);
		m_UseSkill.bJackSpike = true;

		m_JumpScript->SetJump(true);
	}

	if (!m_UseSkill.bHeadShot && KEY_TAP(KEY::A))
	{
		SetState(STATE::SK_3);
		if(KEY_PRESSED(KEY::DOWN))
			Animator2D()->Play((int)ANIMATION_NUM::DG_AT3, 25.f, false);
		else
			Animator2D()->Play((int)ANIMATION_NUM::AT_3, 25.f, false);

		SetMoveable(false);
		m_UseSkill.bHeadShot = true;
		
		m_JumpScript->SetJump(true);
	}

	if (!m_UseSkill.bRisingShot && KEY_TAP(KEY::S))
	{
		SetState(STATE::SK_2);
		Animator2D()->Play((int)ANIMATION_NUM::AT_3, 20.f, false);
		SetMoveable(false);
		m_UseSkill.bRisingShot = true;

		m_JumpScript->SetJump(true);
	}

	if (!m_UseSkill.bWindMill && KEY_TAP(KEY::D))
	{
		SetState(STATE::SK_6);
		Animator2D()->Play((int)ANIMATION_NUM::WINDMILL, 20.f, false);
		CreateWindMill();
		m_UseSkill.bWindMill = true;

		m_JumpScript->SetJump(true);
	}

	if (!m_UseSkill.bMachKick && KEY_TAP(KEY::F))
	{
		SetState(STATE::SK_7);
		Animator2D()->Play((int)ANIMATION_NUM::MACHKICK, 20.f, false);
		CreateMachKick();
		SetMoveable(false);
		m_UseSkill.bMachKick = true;

		m_JumpScript->SetJump(true);
	}

	if (!m_UseSkill.bRandShoot && KEY_TAP(KEY::G))
	{
		SetState(STATE::SK_4);
		Animator2D()->Play((int)ANIMATION_NUM::RANDOMSHOT, 30.f, false);
		SetMoveable(false);
		m_UseSkill.bRandShoot = true;

		m_JumpScript->SetJump(true);
	}

	if (!m_UseSkill.bDeathByRevolver && KEY_TAP(KEY::SPACE))
	{
		SetState(STATE::SK_5);
		Animator2D()->Play((int)ANIMATION_NUM::DEATHBYREVOLVER, 17.f, false);
		SetMoveable(false);
		CreateDeathByRevolver();
		m_UseSkill.bDeathByRevolver = true;

		m_JumpScript->SetJump(true);
	}

	if (!m_UseSkill.bGunHawk && KEY_TAP(KEY::Q))
	{
		SetState(STATE::GUNHAWKSHOOT);
		Animator2D()->Play((int)ANIMATION_NUM::GUNHAWKSHOOT, 7.f, false);
		SetMoveable(false);
		CreateGunHawkFirst();
		m_UseSkill.bGunHawk = true;

		m_JumpScript->SetJump(true);
	}
}

void CPlayerScript::CreateDeathByRevolver()
{
	Vec3 vRot = Transform()->GetRelativeRotation();

	CGameObject* pBuff = m_BuffPref->Instantiate();

	Vec3 vPos = Transform()->GetWorldPos();
	CGameObject* pCam = CLevelMgr::GetInst()->FindObjectByName(L"MainCamera");

	pBuff->Transform()->SetRelativePos(Vec3(vPos.x, pCam->Transform()->GetWorldPos().y, vPos.z + 100.f));
	pBuff->Transform()->SetRelativeScale(Vec3(470.f, 768.f, 1.f));
	pBuff->Transform()->SetRelativeRotation(vRot);
	pBuff->MeshRender()->GetMaterial()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DAlphaBlendShader"));

	CreateObject(pBuff, 0);
}

void CPlayerScript::CreateRandomShoot()
{
	Vec3 vPos = Transform()->GetWorldPos();
	int CurIdx = Animator2D()->GetCurFrameIndex();

	if (m_Spawn && CurIdx == 0)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_2PI, 0.f));

		CreateObject(pObject, 7);

		m_Spawn = false;
	}

	if (CurIdx == 1)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 3)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 60.f, vPos.y + 130.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 1.7f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 60.f, vPos.y - 130.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.7f));
		CreateObject(pObject, 7);

		m_Spawn = false;
	}

	if (CurIdx == 4)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 6)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 100.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 1.75f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y - 100.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
		CreateObject(pObject, 7);

		m_Spawn = false;
	}

	if (CurIdx == 7)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 8)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y + 100.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI / 4.f));
		CreateObject(pObject, 7);

		m_Spawn = false;
	}

	if (CurIdx == 9)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 12)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_2PI, 0.f));
		CreateObject(pObject, 7);

		m_Spawn = false;
	}

	if (CurIdx == 13)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 15)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 60.f, vPos.y + 130.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 1.7f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 60.f, vPos.y - 130.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.7f));
		CreateObject(pObject, 7);

		m_Spawn = false;
	}

	if (CurIdx == 16)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 18)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 100.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 1.75f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y - 100.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
		CreateObject(pObject, 7);

		m_Spawn = false;
	}

	if (CurIdx == 19)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 20)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y + 100.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI / 4.f));
		CreateObject(pObject, 7);

		m_Spawn = false;
	}

	if (CurIdx == 21)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 24)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_2PI, 0.f));
		CreateObject(pObject, 7);

		m_Spawn = false;
	}

	if (CurIdx == 25)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 27)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 60.f, vPos.y + 130.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 1.7f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 60.f, vPos.y - 130.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.7f));
		CreateObject(pObject, 7);

		m_Spawn = false;
	}

	if (CurIdx == 28)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 30)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 100.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 1.75f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y - 100.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
		CreateObject(pObject, 7);

		m_Spawn = false;
	}

	if (CurIdx == 31)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 32)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y + 100.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI / 4.f));
		CreateObject(pObject, 7);

		m_Spawn = false;
	}
}

void CPlayerScript::CreatePistol()
{
	CGameObject* pObject = m_PistolPref->Instantiate();
	Vec3 vPos = Transform()->GetWorldPos();

	if (0 <= Animator2D()->GetCurFrameIndex())
	{
		if (OBJ_DIR::DIR_LEFT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x - 175.f, vPos.y + 40.f, vPos.z));
			pObject->SetDir(OBJ_DIR::DIR_LEFT);
		}

		else if (OBJ_DIR::DIR_RIGHT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x + 175.f, vPos.y + 40.f, vPos.z));
			pObject->SetDir(OBJ_DIR::DIR_RIGHT);
		}

		pObject->SetInitPos(vPos);

		CreateObject(pObject, 7);
	}
}

void CPlayerScript::CreateDiagonalPistol()
{
	Vec3 vPos = Transform()->GetWorldPos();

	CGameObject* pObject = m_Prefabs.DiagonalPistolPref->Instantiate();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 175.f, vPos.y - 35.f, vPos.z));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 175.f, vPos.y - 35.f, vPos.z));
	}

	pObject->SetDir(m_Dir);
	pObject->SetOwner(m_MoveObject);
	CreateObject(pObject, 7);
}

void CPlayerScript::CreateWindMill()
{
	CGameObject* pObject = m_WindmillPref->Instantiate();
	Vec3 vPos = Transform()->GetWorldPos();
	pObject->Transform()->SetRelativePos(Vec3(vPos.x, vPos.y - 20.f, vPos.z - 1.f));

	CreateObject(pObject, 7);
}

void CPlayerScript::CreateMuzzelOfRevolverNormal()
{
	CGameObject* pObject = m_MuzzlePref->Instantiate();

	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 160.f, vPos.y + 45.f, vPos.z - 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 160.f, vPos.y + 45.f, vPos.z - 1.f));
	}

	CreateObject(pObject, 0);
}

void CPlayerScript::CreateMuzzelOfRevolver()
{
	CGameObject* pObject = m_MuzzlePref->Instantiate();

	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 200.f, vPos.y + 40.f, vPos.z - 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 200.f, vPos.y + 40.f, vPos.z - 1.f));
	}

	CreateObject(pObject, 0);
}

void CPlayerScript::CreateMuzzelOfRevolverDiagonal()
{
	CGameObject* pObject = m_MuzzlePref->Instantiate();

	Vec3 vPos = Transform()->GetWorldPos();

	if (STATE::DG_AT4 == m_State)
	{
		if (OBJ_DIR::DIR_LEFT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x - 190.f, vPos.y - 30.f, vPos.z - 1.f));
			pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 2.25f));
		}

		else if (OBJ_DIR::DIR_RIGHT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x + 190.f, vPos.y - 30.f, vPos.z - 1.f));
			pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
		}
	}
	else
	{
		if (OBJ_DIR::DIR_LEFT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x - 158.f, vPos.y - 20.f, vPos.z - 1.f));
			pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 2.25f));
		}

		else if (OBJ_DIR::DIR_RIGHT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x + 158.f, vPos.y - 20.f, vPos.z - 1.f));
			pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
		}
	}

	CreateObject(pObject, 0);
}

void CPlayerScript::CreateHammerOfRevolver()
{
	CGameObject* pObject = m_HammerPref->Instantiate();

	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 68.f, vPos.y + 46.f, vPos.z + 100.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 68.f, vPos.y + 46.f, vPos.z + 100.f));
	}

	CreateObject(pObject, 0);
}

void CPlayerScript::CreateHeadShotEffect()
{
	CGameObject* pObject = m_HeadShotEffectPref->Instantiate();
	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 250.f, vPos.y + 38.f, vPos.z + 100.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 250.f, vPos.y + 38.f, vPos.z + 100.f));
	}

	CreateObject(pObject, 0);
}

void CPlayerScript::CreateDiagonalHeadShotEffect()
{
	CGameObject* pObject = m_HeadShotEffectPref->Instantiate();
	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 230.f, vPos.y - 50.f, vPos.z + 100.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 2.15f));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 250.f, vPos.y - 50.f, vPos.z + 100.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
	}

	CreateObject(pObject, 0);
}

void CPlayerScript::CreateHeadShot()
{
	CGameObject* pObject = m_HeadShotPref->Instantiate();
	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 175.f, vPos.y + 40.f, vPos.z));
		pObject->SetDir(OBJ_DIR::DIR_LEFT);
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 175.f, vPos.y + 40.f, vPos.z));
		pObject->SetDir(OBJ_DIR::DIR_RIGHT);
	}

	pObject->SetInitPos(vPos);

	CreateObject(pObject, 7);
}

void CPlayerScript::CreateDiagonalHeadShot()
{
	Vec3 vPos = Transform()->GetWorldPos();

	CGameObject* pObject = m_Prefabs.DiagonalHeadShotPref->Instantiate();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 175.f, vPos.y - 35.f, vPos.z));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 175.f, vPos.y - 35.f, vPos.z));
	}

	pObject->SetDir(m_Dir);
	pObject->SetOwner(m_MoveObject);
	CreateObject(pObject, 7);
}

void CPlayerScript::CreateGunHawkFirst()
{
	Vec3 vPos = Transform()->GetWorldPos();

	CGameObject* GunHawkUp = m_GunHawkFirstUpPref->Instantiate();
	CGameObject* GunHawkDown = m_GunHawkFirstDownPref->Instantiate();

	if(OBJ_DIR::DIR_LEFT == m_Dir)
	{
		GunHawkUp->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		GunHawkDown->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		GunHawkUp->Transform()->SetRelativeRotation(Vec3(XM_PI / 1.5f, 0.f, 0.f));
		GunHawkDown->Transform()->SetRelativeRotation(Vec3(XM_PI / 1.5f, 0.f, 0.f));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		GunHawkUp->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		GunHawkDown->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		GunHawkUp->Transform()->SetRelativeRotation(Vec3(XM_PI / 1.5f, 0.f, 0.f));
		GunHawkDown->Transform()->SetRelativeRotation(Vec3(XM_PI / 1.5f, 0.f, 0.f));
	}

	GunHawkUp->SetDir(m_Dir);
	GunHawkDown->SetDir(m_Dir);
	GunHawkUp->SetInitPos(vPos);
	GunHawkDown->SetInitPos(vPos);
	CreateObject(GunHawkUp, 7);
	CreateObject(GunHawkDown, 7);
}

void CPlayerScript::CreateGunHawkSecond()
{
	Vec3 vPos = Transform()->GetWorldPos();

	CGameObject* GunHawkUp = m_GunHawkSecondUpPref->Instantiate();
	CGameObject* GunHawkDown = m_GunHawkSecondDownPref->Instantiate();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		GunHawkUp->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		GunHawkDown->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		GunHawkUp->Transform()->SetRelativeRotation(Vec3(XM_PI / 1.6f, 0.f, 0.f));
		GunHawkDown->Transform()->SetRelativeRotation(Vec3(XM_PI / 1.6f, 0.f, 0.f));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		GunHawkUp->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		GunHawkDown->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		GunHawkUp->Transform()->SetRelativeRotation(Vec3(XM_PI / 1.55f, 0.f, 0.f));
		GunHawkDown->Transform()->SetRelativeRotation(Vec3(XM_PI / 1.55f, 0.f, 0.f));
	}

	GunHawkUp->SetDir(m_Dir);
	GunHawkDown->SetDir(m_Dir);
	GunHawkUp->SetInitPos(vPos);
	GunHawkDown->SetInitPos(vPos);
	CreateObject(GunHawkUp, 7);
	CreateObject(GunHawkDown, 7);
}

void CPlayerScript::CreateMachKick()
{
	CGameObject* pObject = m_MachKickPref->Instantiate();

	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 50.f, vPos.y - 50.f, vPos.z));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y - 50.f, vPos.z));
	}

	pObject->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));

	CreateObject(pObject, 7);
}

void CPlayerScript::CreateJackSpike()
{
	CGameObject* pObject = m_JackSpikePref->Instantiate();

	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 45.f, vPos.y - 20.f, vPos.z));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 45.f, vPos.y - 20.f, vPos.z));
	}

	CreateObject(pObject, 7);
}

void CPlayerScript::CreateRisingShot()
{
	CGameObject* pObject = m_RisingShotPref->Instantiate();
	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 175.f, vPos.y + 40.f, vPos.z));
		pObject->SetDir(OBJ_DIR::DIR_LEFT);
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 175.f, vPos.y + 40.f, vPos.z));
		pObject->SetDir(OBJ_DIR::DIR_RIGHT);
	}

	pObject->SetInitPos(vPos);

	CreateObject(pObject, 7);
}

void CPlayerScript::ChangeStateDoubleGunHawkStandBy()
{
	Animator2D()->Play((int)ANIMATION_NUM::GUNHAWKSTANDBY, 1.f, false);
	SetState(STATE::GUNHAWKSTANDBY);
	m_MoveScript->SetState(MOVE_STATE::ST_FORCE);
}

void CPlayerScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Speed, sizeof(float), 1, _pFile);
}

void CPlayerScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Speed, sizeof(float), 1, _pFile);
}

void CPlayerScript::SetMoveable(bool _Set)
{
	m_MoveScript->SetMoveable(_Set);
}

void CPlayerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}