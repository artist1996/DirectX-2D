#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

#include <Engine/CDistanceMgr.h>
#include <Engine/CObjectPoolMgr.h>

#include <Engine/CFSM.h>

#include "CPlayerMoveScript.h"


CPlayerScript::CPlayerScript()
	: CScript(SCRIPT_TYPE::PLAYERSCRIPT)
	, m_Texture(nullptr)
	, m_BuffPref(nullptr)
	, m_RandomShootPref(nullptr)
	, m_PistolPref(nullptr)
	, m_MuzzlePref(nullptr)
	, m_HammerPref(nullptr)
	, m_HeadShotEffectPref(nullptr)
	, m_WindmillPref(nullptr)
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
	, m_GroundPosY(0.f)
	, m_Time(0.f)
	, m_NextAttack(false)
	, m_Run(false)
	, m_Spawn(true)
	, m_Muzzel(true)
	, m_CheckRange(false)
	, m_GunHawkStandby(false)
	, m_HeadShotSpawn(true)
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
	GetOwner()->SetID(OBJ_ID::PLAYER);
	m_BuffPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\deathbyrevolver.pref");
	m_RandomShootPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\skill_randomshoot.pref");
	m_PistolPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\pistol.pref");
	m_MuzzlePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\muzzle.pref");
	m_HammerPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\revolverhammer_normal.pref");
	m_HeadShotEffectPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\headshoteffect.pref");
	m_WindmillPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\windmilleffect.pref");

	m_GunHawkFirstUpPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gunhawk0_up.pref");
	m_GunHawkFirstDownPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gunhawk0_down.pref");
	m_GunHawkSecondUpPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gunhawk1_up.pref");
	m_GunHawkSecondDownPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gunhawk1_down.pref");
	m_MachKickPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\skill_machkick.pref");
	m_JackSpikePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\skill_jackspike.pref");
	m_RisingShotPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\skill_risingshot.pref");

	m_Prefabs.DiagonalPistolPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\diagonalpistol.pref");
	m_Prefabs.DiagonalHeadShotPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\diagonalheadshot.pref");
	
	CDistanceMgr::GetInst()->Init();

	Animator2D()->Play((int)IDLE, 5.f, true);

	Collider2D()->SetOffset(Vec3(0.f, -0.5f, 1.f));

	SetSpeed(350.f);
}

void CPlayerScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	m_CheckRange = CDistanceMgr::GetInst()->IsInRange();
	m_Dir = GetOwner()->GetDir();
	SetPrevDirection(m_Dir);
	switch (m_State)
	{
	case CPlayerScript::STATE::IDLE:
		Idle(vPos);
		break;
	case CPlayerScript::STATE::MOVE:
		Move(vPos);
		break;
	case CPlayerScript::STATE::JUMP:
		Jump(vPos);
		break;
	case CPlayerScript::STATE::LANDING:
		Landing();
		break;
	case CPlayerScript::STATE::RUN:
		Run(vPos);
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
		Tackle(vPos);
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
	}

	RunTimeCheck();
	SkillTimeCheck();
	float JumpHeight = Rigidbody()->GetGravityVelocity().y;
	Vec3 vColliderScale = Collider2D()->GetScale();
	if (STATE::JUMP == m_State)
	{
		Transform()->SetRelativePos(Vec3(vPos.x, vPos.y, m_GroundPosY - vColliderScale.y * 0.5f));
	}
	else
	{
		Transform()->SetRelativePos(Vec3(vPos.x, vPos.y, vPos.y - vColliderScale.y * 0.5f));
	}
}

void CPlayerScript::RunTimeCheck()
{
	if (m_Run)
		m_Time += DT;

	if (0.2f <= m_Time)
	{
		m_Run = false;
		m_Time = 0.f;
	}
}

void CPlayerScript::AddForce()
{
	if (OBJ_DIR::DIR_RIGHT == m_Dir)
		Rigidbody()->AddForce(Vec3(-120000.f, 0.f, 0.f));
	else if (OBJ_DIR::DIR_LEFT == m_Dir)
		Rigidbody()->AddForce(Vec3(120000.f, 0.f, 0.f));
}

bool CPlayerScript::GroundCheck(Vec3& _Pos)
{
	if (_Pos.y <= m_GroundPosY)
	{
		Rigidbody()->SetGround(true);
		_Pos.y = m_GroundPosY;

		return true;
	}

	return false;
}

void CPlayerScript::Idle(Vec3& _Pos)
{
	Vec3 vRot = Transform()->GetRelativeRotation();

	Vec3 vOffset = Collider2D()->GetOffset();

	Collider2D()->SetScale(Vec3(75.f, 136.f, 1.f));
	Collider2D()->SetOffset(Vec3(-8.f, -48.f, 1.f));

	if (KEY_TAP(KEY::LEFT))
	{
		SetDirection(OBJ_DIR::DIR_LEFT);
		vRot = Vec3(0.f, 0.f, 0.f);
		if (!m_Run)
		{
			SetState(STATE::MOVE);
			Animator2D()->Play((int)STATE::MOVE, 8.f, true);
			m_Run = true;
		}
		else
		{
			SetSpeed(500.f);
			SetState(STATE::RUN);
			Animator2D()->Play((int)STATE::RUN, 8.f, true);
			m_Run = false;
		}
	}
	else if (KEY_PRESSED(KEY::LEFT))
	{
		vRot = Vec3(0.f, 0.f, 0.f);
		SetDirection(OBJ_DIR::DIR_LEFT);
		SetState(STATE::MOVE);
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		vRot.y = XM_PI;
		SetDirection(OBJ_DIR::DIR_RIGHT);
		SetState(STATE::MOVE);

		if (!m_Run)
		{
			m_State = STATE::MOVE;
			Animator2D()->Play((int)STATE::MOVE, 8.f, true);
			m_Run = true;
		}
		else
		{
			SetSpeed(500.f);
			m_State = STATE::RUN;
			Animator2D()->Play((int)STATE::RUN, 8.f, true);
			m_Run = false;
		}
	}
	else if (KEY_PRESSED(KEY::RIGHT))
	{
		SetDirection(OBJ_DIR::DIR_RIGHT);
		SetState(STATE::MOVE);
		vRot.y = XM_PI;

		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}
	
	if (KEY_TAP(KEY::UP))
	{
		SetState(STATE::MOVE);
		//SetDirection(OBJ_DIR::DIR_UP);
		SetTBDirection(OBJ_DIR::DIR_UP);
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}
	else if (KEY_PRESSED(KEY::UP))
	{
		SetState(STATE::MOVE);
		//SetDirection(OBJ_DIR::DIR_UP);
		SetTBDirection(OBJ_DIR::DIR_UP);
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}

	if (KEY_TAP(KEY::DOWN))
	{
		SetState(STATE::MOVE);
		//SetDirection(OBJ_DIR::DIR_DOWN);
		SetTBDirection(OBJ_DIR::DIR_DOWN);
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}
	else if (KEY_PRESSED(KEY::DOWN))
	{
		SetState(STATE::MOVE);
		//SetDirection(OBJ_DIR::DIR_DOWN);
		SetTBDirection(OBJ_DIR::DIR_DOWN);
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}
	
	if (KEY_TAP(KEY::X))
	{
		if (m_CheckRange)
		{
			SetState(STATE::DG_AT1);
			Animator2D()->Play((int)STATE::DG_AT1, 15.f, true);
			CreateMuzzelOfRevolverDiagonal();
			CreateDiagonalPistol();
		}

		else
		{
			SetState(STATE::AT_1);
			Animator2D()->Play((int)STATE::AT_1, 15.f, false);
			CreateMuzzelOfRevolverNormal();
			CreatePistol();
		}
	}
	else if (KEY_PRESSED(KEY::DOWN) && KEY_TAP(KEY::X))
	{
		SetState(STATE::DG_AT1);
		Animator2D()->Play((int)STATE::DG_AT1, 15.f, false);
	}

	if (KEY_TAP(KEY::C))
	{
		SetState(STATE::JUMP);
		Animator2D()->Play((int)STATE::JUMP, 5.f, false);
		Rigidbody()->Jump();
		SetGroundPos(_Pos.y);
	}

	// Skill
	Stylish();

	Transform()->SetRelativeRotation(vRot);
}

void CPlayerScript::Move(Vec3& _Pos)
{
	bool* bMoveable = GetOwner()->GetMoveable();

	// ATTACK
	if (KEY_PRESSED(KEY::LEFT)
	 && bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		_Pos += Vec3(-1.f, 0.f, 0.f) * m_Speed * DT;
	}

	else if (KEY_RELEASED(KEY::LEFT))
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}

	if (KEY_PRESSED(KEY::RIGHT)
		&& bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		_Pos += Vec3(1.f, 0.f, 0.f) * m_Speed * DT;
	}

	else if (KEY_RELEASED(KEY::RIGHT))
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}
	if (KEY_PRESSED(KEY::UP)
		&& bMoveable[(UINT)PLATFORM_TYPE::UP])
	{
		_Pos += Vec3(0.f, 1.f, 0.f) * m_Speed * DT;
	}

	else if (KEY_RELEASED(KEY::UP))
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}
	if (KEY_PRESSED(KEY::DOWN)
		&& bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		_Pos += Vec3(0.f, -1.f, 0.f) * m_Speed * DT;
	}

	else if (KEY_RELEASED(KEY::DOWN))
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}

	if (KEY_PRESSED(KEY::DOWN) && KEY_TAP(KEY::X))
	{
		SetState(STATE::DG_AT1);
		Animator2D()->Play((int)STATE::DG_AT1, 15.f, true);
		CreateMuzzelOfRevolverDiagonal();
		CreateDiagonalPistol();
	}

	else if (KEY_TAP(KEY::X))
	{
		SetState(STATE::AT_1);
		Animator2D()->Play((int)STATE::AT_1, 15.f, false);
	}

	// JUMP
	if (KEY_TAP(KEY::C))
	{
		SetState(STATE::JUMP);
		Animator2D()->Play((int)STATE::JUMP, 5.f, false);
		Rigidbody()->Jump();
		SetGroundPos(_Pos.y);
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
		SetState(STATE::IDLE);
	}
	
	else if (m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)AT_2, 10.f, true);
		SetState(STATE::AT_2);
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
		SetState(STATE::AT_3);
		m_NextAttack = false;
		CreatePistol();
		CreateMuzzelOfRevolverNormal();
	}

	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)IDLE, 5.f, true);
		SetState(STATE::IDLE);
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
		SetState(STATE::AT_4);
		m_NextAttack = true;
	}

	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)IDLE, 5.f, true);
		SetState(STATE::IDLE);
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
		SetState(STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
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
			SetState(STATE::DG_AT2);
			Animator2D()->Play((int)STATE::DG_AT2, 10.f, true);
			CreateDiagonalPistol();
			CreateMuzzelOfRevolverDiagonal();
			m_NextAttack = false;
		}
		else
		{
			if (KEY_PRESSED(KEY::DOWN))
			{
				SetState(STATE::DG_AT2);
				Animator2D()->Play((int)STATE::DG_AT2, 10.f, true);
			}
			else if (KEY_RELEASED(KEY::DOWN))
			{
				SetState(STATE::AT_2);
				Animator2D()->Play((int)STATE::AT_2, 10.f, true);
			}
			CreateDiagonalPistol();
			CreateMuzzelOfRevolverDiagonal();
			m_NextAttack = false;
		}
	}
	
	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)STATE::IDLE, 5.f, true);
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
		if (m_CheckRange)
		{
			SetState(STATE::DG_AT3);
			Animator2D()->Play((int)STATE::DG_AT2, 10.f, true);
			CreateDiagonalPistol();
			CreateMuzzelOfRevolverDiagonal();
			m_NextAttack = false;
		}

		if (KEY_PRESSED(KEY::DOWN))
		{
			SetState(STATE::DG_AT3);
			Animator2D()->Play((int)STATE::DG_AT2, 10.f, true);
			CreateDiagonalPistol();
			CreateMuzzelOfRevolverDiagonal();
		}
		else if(KEY_RELEASED(KEY::DOWN))
		{
			SetState(STATE::AT_2);
			Animator2D()->Play((int)STATE::AT_2, 10.f, true);
		}
		
		m_NextAttack = false;
	}

	else if(!m_NextAttack && Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
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
			SetState(STATE::DG_AT4);
			Animator2D()->Play((int)STATE::DG_AT3, 17.f, true);
		}

		else
		{
			if (KEY_PRESSED(KEY::DOWN))
			{
				SetState(STATE::DG_AT4);
				Animator2D()->Play((int)STATE::DG_AT3, 17.f, true);
			}

			else if (KEY_RELEASED(KEY::DOWN))
			{
				SetState(STATE::AT_2);
				Animator2D()->Play((int)STATE::AT_3, 10.f, true);
			}
		}
	}

	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
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
		SetState(STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}

	Stylish();
}

void CPlayerScript::Tackle(Vec3& _Pos)
{
	if (m_Dir == OBJ_DIR::DIR_LEFT)
	{
		_Pos += Vec3(-1.f, 0.f, 0.f) * m_Speed * 2.f * DT;
	}

	else if (m_Dir == OBJ_DIR::DIR_RIGHT)
	{
		_Pos += Vec3(1.f, 0.f, 0.f) * m_Speed * 2.f * DT;
	}

	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}
}

void CPlayerScript::Jump(Vec3& _Pos)
{
	if (GroundCheck(_Pos))
	{
		SetState(STATE::LANDING);
		Animator2D()->Play((int)LANDING, 3.f, false);
	}
}

void CPlayerScript::Landing()
{
	if (Animator2D()->IsFinish())
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
	}
}

void CPlayerScript::Run(Vec3& _Pos)
{
	Collider2D()->SetScale(Vec3(75.f, 136.f, 1.f));
	Collider2D()->SetOffset(Vec3(-8.f, -48.f, 1.f));

	bool* bMoveable = GetOwner()->GetMoveable();

	if (KEY_PRESSED(KEY::UP)
		&& bMoveable[(UINT)PLATFORM_TYPE::UP])
	{
		_Pos += Vec3(0.f, 1.f, 0.f) * m_Speed * DT;
	}
	
	if (KEY_PRESSED(KEY::DOWN)
		&& bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	{
		_Pos += Vec3(0.f, -1.f, 0.f) * m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::LEFT)
		&& bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	{
		_Pos += Vec3(-1.f, 0.f, 0.f) * m_Speed * DT;
	}

	else if (KEY_RELEASED(KEY::LEFT))
	{
		SetState(STATE::IDLE);
		SetSpeed(350.f);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}

	if (KEY_PRESSED(KEY::RIGHT)
		&& bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	{
		_Pos += Vec3(1.f, 0.f, 0.f) * m_Speed * DT;
	}

	else if (KEY_RELEASED(KEY::RIGHT))
	{
		SetState(STATE::IDLE);
		SetSpeed(350.f);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}

	if (KEY_TAP(KEY::C))
	{
		SetState(STATE::JUMP);
		Animator2D()->Play((int)STATE::JUMP, 5.f, false);
		Rigidbody()->Jump();
		SetGroundPos(_Pos.y);
	}

	if (KEY_TAP(KEY::X))
	{
		SetState(STATE::TACKLE);
		Animator2D()->Play((int)ANIMATION_NUM::TACKLE, 7.f, false);
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
	}
}

void CPlayerScript::JackSpike()
{
	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
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
		m_Spawn = true;
	}

	Stylish();
}

void CPlayerScript::HeadShot()
{
	if (m_HeadShotSpawn && 3 <= Animator2D()->GetCurFrameIndex())
	{
		if (m_CheckRange)
		{
			CreateDiagonalHeadShot();
			CreateDiagonalHeadShotEffect();
			m_HeadShotSpawn = false;
		}

		else if (KEY_PRESSED(KEY::DOWN))
		{
			CreateDiagonalHeadShot();
			CreateDiagonalHeadShotEffect();
			m_HeadShotSpawn = false;
		}

		else
		{
			CreateHeadShot();
			CreateHeadShotEffect();
			m_HeadShotSpawn = false;
		}
	}

	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		m_HeadShotSpawn = true;
	}
}

void CPlayerScript::RandomShot()
{
	CreateRandomShoot();

	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		m_Spawn = true;
	}
}

void CPlayerScript::WindMill()
{
	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
	}

	Stylish();
}

void CPlayerScript::MachKick()
{
	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
	}
}

void CPlayerScript::GunHawkShoot()
{
	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
	}

	Stylish();
}

void CPlayerScript::GunHawkStandBy()
{
	if (m_GunHawkStandby)
	{
		AddForce();
		m_GunHawkStandby = false;
	}

	if (!Animator2D()->IsFinish() && KEY_TAP(KEY::Q))
	{
		SetState(STATE::GUNHAWKLASTSHOOT);
		Animator2D()->Play((int)ANIMATION_NUM::GUNHAWKSHOOT, 7.f, true);
		CreateGunHawkSecond();
	}

	else if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
	}
}

void CPlayerScript::GunHawkLastShoot()
{
	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
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
		m_UseSkill.bJackSpike = true;
	}

	if (!m_UseSkill.bHeadShot && KEY_TAP(KEY::A))
	{
		SetState(STATE::SK_3);
		if(KEY_PRESSED(KEY::DOWN))
			Animator2D()->Play((int)ANIMATION_NUM::DG_AT3, 25.f, false);
		else
			Animator2D()->Play((int)ANIMATION_NUM::AT_3, 25.f, false);

		m_UseSkill.bHeadShot = true;
	}

	if (!m_UseSkill.bRisingShot && KEY_TAP(KEY::S))
	{
		SetState(STATE::SK_2);
		Animator2D()->Play((int)ANIMATION_NUM::AT_3, 20.f, false);
		m_UseSkill.bRisingShot = true;
	}

	if (!m_UseSkill.bWindMill && KEY_TAP(KEY::D))
	{
		SetState(STATE::SK_6);
		Animator2D()->Play((int)ANIMATION_NUM::WINDMILL, 20.f, false);
		CreateWindMill();
		m_UseSkill.bWindMill = true;
	}

	if (!m_UseSkill.bMachKick && KEY_TAP(KEY::F))
	{
		SetState(STATE::SK_7);
		Animator2D()->Play((int)ANIMATION_NUM::MACHKICK, 20.f, false);
		CreateMachKick();
		m_UseSkill.bMachKick = true;
	}

	if (!m_UseSkill.bRandShoot && KEY_TAP(KEY::G))
	{
		SetState(STATE::SK_4);
		Animator2D()->Play((int)ANIMATION_NUM::RANDOMSHOT, 30.f, false);
		m_UseSkill.bRandShoot = true;
	}

	if (!m_UseSkill.bDeathByRevolver && KEY_TAP(KEY::SPACE))
	{
		SetState(STATE::SK_5);
		Animator2D()->Play((int)ANIMATION_NUM::DEATHBYREVOLVER, 17.f, false);
		CreateDeathByRevolver();
		m_UseSkill.bDeathByRevolver = true;
	}

	if (!m_UseSkill.bGunHawk && KEY_TAP(KEY::Q))
	{
		SetState(STATE::GUNHAWKSHOOT);
		Animator2D()->Play((int)ANIMATION_NUM::GUNHAWKSHOOT, 7.f, false);
		CreateGunHawkFirst();
		m_UseSkill.bGunHawk = true;
	}
}

void CPlayerScript::CreateDeathByRevolver()
{
	Vec3 vRot = Transform()->GetRelativeRotation();

	CGameObject* pBuff = m_BuffPref->Instantiate();

	Vec3 vPos = Transform()->GetWorldPos();
	CGameObject* pCam = CLevelMgr::GetInst()->FindObjectByName(L"MainCamera");

	pBuff->Transform()->SetRelativePos(Vec3(vPos.x, pCam->Transform()->GetWorldPos().y, vPos.z + 500.f));
	pBuff->Transform()->SetRelativeScale(Vec3(470.f, 768.f, 1.f));
	pBuff->Transform()->SetRelativeRotation(vRot);
	//pBuff->MeshRender()->GetMaterial()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DAdditiveShader"));

	CreateObject(pBuff, 0);
}

void CPlayerScript::CreateRandomShoot()
{
	Vec3 vPos = Transform()->GetWorldPos();
	int CurIdx = Animator2D()->GetCurFrameIndex();

	if (m_Spawn && CurIdx == 0)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
	
		if (OBJ_DIR::DIR_LEFT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x - 130.f, vPos.y, vPos.z));
			pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		}
	
		else if (OBJ_DIR::DIR_RIGHT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x + 130.f, vPos.y, vPos.z));
			pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		}
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
	
		CreateObject(pObject, 7);
	
		m_Spawn = false;
	}
	
	if (CurIdx == 1)
		m_Spawn = true;
	
	if (m_Spawn && CurIdx == 3)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 100.f, vPos.y, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI));
		CreateObject(pObject, 7);
	
		pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 110.f, vPos.y - 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		CreateObject(pObject, 7);
	
		m_Spawn = false;
	}
	
	if (CurIdx == 4)
		m_Spawn = true;
	
	if (m_Spawn && CurIdx == 6)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 120.f, vPos.y - 30.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.12f));
		CreateObject(pObject, 7);
		
		pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 110.f, vPos.y - 70.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
		CreateObject(pObject, 7);
		
		m_Spawn = false;
	}
	
	if (CurIdx == 7)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 8)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 110.f, vPos.y - 40.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.2f));
		CreateObject(pObject, 7);
	
		pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 70.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 2.2f));
		CreateObject(pObject, 7);
	
		m_Spawn = false;
	}

	if (CurIdx == 9)
		m_Spawn = true;
	
	if (m_Spawn && CurIdx == 12)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
	
		if (OBJ_DIR::DIR_LEFT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x - 110.f, vPos.y, vPos.z));
			pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		}
	
		else if (OBJ_DIR::DIR_RIGHT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y, vPos.z));
			pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		}
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
	
		CreateObject(pObject, 7);
	
		m_Spawn = false;
	}
	
	if (CurIdx == 13)
		m_Spawn = true;
	
	if (m_Spawn && CurIdx == 15)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 120.f, vPos.y, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI));
		CreateObject(pObject, 7);
	
		pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 140.f, vPos.y - 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		CreateObject(pObject, 7);
	
		m_Spawn = false;
	}
	
	if (CurIdx == 16)
		m_Spawn = true;
	
	if (m_Spawn && CurIdx == 18)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 110.f, vPos.y + 20.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.12f));
		CreateObject(pObject, 7);
	
		pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 120.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 2.2f));
		CreateObject(pObject, 7);
	
		m_Spawn = false;
	}
	
	if (CurIdx == 19)
		m_Spawn = true;
	
	if (m_Spawn && CurIdx == 20)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 80.f, vPos.y - 70.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.2f));
		CreateObject(pObject, 7);
	
		pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 120.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 2.2f));
		CreateObject(pObject, 7);
	
		m_Spawn = false;
	}
	
	if (CurIdx == 21)
		m_Spawn = true;
	
	if (m_Spawn && CurIdx == 24)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
	
		if (OBJ_DIR::DIR_LEFT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x - 100.f, vPos.y, vPos.z));
			pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		}
	
		else if (OBJ_DIR::DIR_RIGHT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x + 100.f, vPos.y, vPos.z));
			pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		}
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
	
		CreateObject(pObject, 7);
	
		m_Spawn = false;
	}
	
	if (CurIdx == 25)
		m_Spawn = true;
	
	if (m_Spawn && CurIdx == 27)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 110.f, vPos.y + 20.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI));
		CreateObject(pObject, 7);
	
		pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 130.f, vPos.y - 70.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		CreateObject(pObject, 7);
	
		m_Spawn = false;
	}
	
	if (CurIdx == 28)
		m_Spawn = true;
	
	if (m_Spawn && CurIdx == 30)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 90.f, vPos.y + 10.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.12f));
		CreateObject(pObject, 7);
	
		pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 140.f, vPos.y - 20.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
		CreateObject(pObject, 7);
	
		m_Spawn = false;
	}
	
	if (CurIdx == 31)
		m_Spawn = true;
	
	if (m_Spawn && CurIdx == 32)
	{
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 60.f, vPos.y - 40.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.2f));
		CreateObject(pObject, 7);
	
		pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 120.f, vPos.y + 60.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 2.25f));
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
	pObject->SetOwner(GetOwner());
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
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 250.f, vPos.y + 38.f, -100000.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 250.f, vPos.y + 38.f, -100000.f));
	}

	CreateObject(pObject, 0);
}

void CPlayerScript::CreateDiagonalHeadShotEffect()
{
	CGameObject* pObject = m_HeadShotEffectPref->Instantiate();
	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 230.f, vPos.y - 50.f, -100000.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 2.15f));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 250.f, vPos.y - 50.f, -100000.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.75f));
	}

	CreateObject(pObject, 0);
}

void CPlayerScript::CreateHeadShot()
{
	CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::HEADSHOT);
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
	pObject->SetOwner(GetOwner());
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
	m_GunHawkStandby = true;
}

void CPlayerScript::SaveToFile(FILE* _pFile)
{
	fwrite(&m_Speed, sizeof(float), 1, _pFile);
}

void CPlayerScript::LoadFromFile(FILE* _pFile)
{
	fread(&m_Speed, sizeof(float), 1, _pFile);
}

void CPlayerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}
