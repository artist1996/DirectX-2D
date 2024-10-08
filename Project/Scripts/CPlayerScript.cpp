#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

#include <Engine/CDistanceMgr.h>
#include <Engine/CObjectPoolMgr.h>
#include <Engine/CFontMgr.h>

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
	, m_State(PLAYER_STATE::IDLE)
	, m_Speed(500.f)
	, m_GroundPosY(0.f)
	, m_Time(0.f)
	, m_BBQTime(0.f)
	, m_InvincibleTime(0.f)
	, m_SuperArmorTime(0.f)
	, m_NextAttack(false)
	, m_Run(false)
	, m_Spawn(true)
	, m_Muzzel(true)
	, m_CheckRange(false)
	, m_GunHawkStandby(false)
	, m_HeadShotSpawn(true)
	, m_CutinSpawn(false)
	, m_LineTwo(false)
	, m_Foot(false)
	, m_Color(true)
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
	m_CoolTime.fWesternFireCoolTime		= 5.f;
	m_CoolTime.fPunisherCoolTime		= 4.f;
	m_CoolTime.fBBQCoolTime				= 10.f;
	m_CoolTime.fDeathCrisisCoolTime		= 60.f;
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	GetOwner()->SetID(OBJ_ID::PLAYER);

	CDistanceMgr::GetInst()->Init();
	InitInfo();
	InitPrefabs();

	Animator2D()->Play((int)IDLE, 5.f, true);

	SetSpeed(350.f);

	//MeshRender()->GetMaterial()->SetScalarParam(INT_3, 1);

	GetOwner()->SetFont(L"Player");
	GetOwner()->SetFontScale(15.f);
	GetOwner()->SetFontColor(FONT_RGBA(255, 255, 255, 255));
	GetOwner()->SetFontOffset(Vec2(-25.f, -75.f));
	const vector<CGameObject*> vecChild = GetOwner()->GetChildren();

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		vecChild[i]->SetActive(false);
	}
}

void CPlayerScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	m_CheckRange = CDistanceMgr::GetInst()->IsInRange();
	m_Dir = GetOwner()->GetParent()->GetDir();

	switch (m_State)
	{
	case CPlayerScript::PLAYER_STATE::IDLE:
		Idle();
		break;
	case CPlayerScript::PLAYER_STATE::MOVE:
		Move();
		break;
	case CPlayerScript::PLAYER_STATE::JUMP:
		Jump();
		break;
	case CPlayerScript::PLAYER_STATE::LANDING:
		Landing();
		break;
	case CPlayerScript::PLAYER_STATE::RUN:
		Run();
		break;
	case CPlayerScript::PLAYER_STATE::DEAD:
		Dead();
		break;
	case CPlayerScript::PLAYER_STATE::AT_1:
		AT1();
		break;
	case CPlayerScript::PLAYER_STATE::AT_2:
		AT2();
		break;
	case CPlayerScript::PLAYER_STATE::AT_3:
		AT3();
		break;
	case CPlayerScript::PLAYER_STATE::AT_4:
		AT4();
		break;
	case CPlayerScript::PLAYER_STATE::DG_AT1:
		AT_DG1();
		break;
	case CPlayerScript::PLAYER_STATE::DG_AT2:
		AT_DG2();
		break;
	case CPlayerScript::PLAYER_STATE::DG_AT3:
		AT_DG3();
		break;
	case CPlayerScript::PLAYER_STATE::DG_AT4:
		AT_DG4();
		break;
	case CPlayerScript::PLAYER_STATE::SK_1:
		JackSpike();
		break;
	case CPlayerScript::PLAYER_STATE::SK_2:
		RisingShot();
		break;
	case CPlayerScript::PLAYER_STATE::SK_3:
		HeadShot();
		break;
	case CPlayerScript::PLAYER_STATE::SK_4:
		RandomShot();
		break;
	case CPlayerScript::PLAYER_STATE::SK_5:
		DeathByRevolver();
		break;
	case CPlayerScript::PLAYER_STATE::SK_6:
		WindMill();
		break;
	case CPlayerScript::PLAYER_STATE::SK_7:
		MachKick();
		break;
	case CPlayerScript::PLAYER_STATE::SK_8:
		break;
	case CPlayerScript::PLAYER_STATE::SK_9:
		break;
	case CPlayerScript::PLAYER_STATE::TACKLE:
		Tackle();
		break;
	case CPlayerScript::PLAYER_STATE::GUNHAWKSHOOT:
		GunHawkShoot();
		break;
	case CPlayerScript::PLAYER_STATE::GUNHAWKSTANDBY:
		GunHawkStandBy();
		break;
	case CPlayerScript::PLAYER_STATE::GUNHAWKLASTSHOOT:
		GunHawkLastShoot();
		break;
	case CPlayerScript::PLAYER_STATE::WESTERNFIRE:
		WesternFire();
		break;
	case CPlayerScript::PLAYER_STATE::PUNISHER:
		PuniSher();
		break;
	case CPlayerScript::PLAYER_STATE::PUNISHERSHOOT:
		PuniSherShoot();
		break;
	case CPlayerScript::PLAYER_STATE::BBQ:
		SkillBBQ();
		break;
	case CPlayerScript::PLAYER_STATE::BBQREADY:
		BBQReady();
		break;
	case CPlayerScript::PLAYER_STATE::BBQSHOOT:
		SkillBBQShoot();
		break;
	case CPlayerScript::PLAYER_STATE::DEATHCRISIS:
		DeathCrisis();
		break;
	case CPlayerScript::PLAYER_STATE::HIT:
		Hit();
		break;
	}

	RunTimeCheck();
	SkillTimeCheck();
	SetFontOffset();
	InvincibleCheck();
	SuperArmorCheck();

	//if (OBJ_DIR::DIR_LEFT == m_Dir)
	//	Transform()->SetRelativeScale(Vec3(350.f, 350.f, 1.f));
	//else
	//	Transform()->SetRelativeScale(Vec3(-350.f, 350.f, 1.f));
	
	ZaxisCheck();
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
		Rigidbody()->AddForce(Vec3(-90000.f, 0.f, 0.f));
	else if (OBJ_DIR::DIR_LEFT == m_Dir)
		Rigidbody()->AddForce(Vec3(90000.f, 0.f, 0.f));
}

bool CPlayerScript::GroundCheck()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (vPos.y < 0.f)
	{
		Rigidbody()->SetGround(true);
		Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
		return true;
	}

	return false;
}

void CPlayerScript::SetFontOffset()
{
	if(OBJ_DIR::DIR_RIGHT == GetOwner()->GetParent()->GetDir())
		GetOwner()->SetFontOffset(Vec2(-7.f, -80.f));
	else if(OBJ_DIR::DIR_LEFT == GetOwner()->GetParent()->GetDir())
		GetOwner()->SetFontOffset(Vec2(-27.f, -80.f));
}

void CPlayerScript::InvincibleCheck()
{
	INFO& info = GetOwner()->GetInfo();
	if (info.bInvincible)
	{
		m_InvincibleTime += DT;
		if (0.2f < m_InvincibleTime)
		{
			info.bInvincible = false;
			m_InvincibleTime = 0.f;
		}
	}
}

void CPlayerScript::ZaxisCheck()
{
	GetOwner()->Transform()->SetZAxis(GetOwner()->GetParent()->Transform()->GetRelativePos().y);
}

void CPlayerScript::InitInfo()
{
	INFO& info = GetOwner()->GetInfo();

	info.MaxHP = 5000.f;
	info.HP = 5000.f;
	info.MaxMP = 2000.f;
	info.MP = 2000.f;
	info.MaxFatigue = 156;
	info.Fatigue = 156;
	info.iGold = 1000000;
}

void CPlayerScript::InitPrefabs()
{
	m_BuffPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\deathbyrevolver.pref");
	m_RandomShootPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\skill_randomshoot.pref");
	m_PistolPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\pistolground.pref");
	m_MuzzlePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\muzzle.pref");
	m_HammerPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\revolverhammer_normal.pref");
	m_HeadShotEffectPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\headshoteffect.pref");
	m_WindmillPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\windmilleffect.pref");

	m_GunHawkFirstUpPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gunhawk0_up.pref");
	m_GunHawkFirstDownPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gunhawk0_down.pref");
	m_GunHawkSecondUpPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gunhawk1_up.pref");
	m_GunHawkSecondDownPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\gunhawk1_down.pref");
	m_MachKickPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\machkickground.pref");
	m_JackSpikePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\jackspikeground.pref");
	m_RisingShotPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\risingshotground.pref");

	m_Prefabs.DiagonalPistolPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\diagonalpistolground.pref");
	m_Prefabs.DiagonalHeadShotPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\diagonalheadshotground.pref");
	m_Prefabs.HeadShotPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\headshotground.pref");
	m_Prefabs.WesternFirePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\westernfire.pref");
	m_Prefabs.PunisherPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\punisherground.pref");
	m_Prefabs.PunisherPistolPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\punisherpistol.pref");
	m_Prefabs.BBQPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\bbqground.pref");
	m_Prefabs.DeathCrisisCutinPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\deathcrisiscutin.pref");
	m_Prefabs.DeathCrisisLineOnePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\deathcrisislineone.pref");
	m_Prefabs.DeathCrisisLineTwoPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\deathcrisislinetwo.pref");
	m_Prefabs.DeathCrisisBigBoomPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\deathcrisisbigboom.pref");
	m_Prefabs.DeathCrisisBoomTwoPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\deathcrisisboomtwo.pref");
}

void CPlayerScript::Idle()
{
	Vec3 vRot = Transform()->GetRelativeRotation();

	Vec3 vOffset = Collider2D()->GetOffset();

	Collider2D()->SetScale(Vec3(75.f, 136.f, 1.f));

	GetOwner()->GetParent()->SetSpeed(400.f);
	SetSuperArmor(false);
	if (KEY_TAP(KEY::LEFT))
	{
		SetDirection(OBJ_DIR::DIR_LEFT);
		vRot = Vec3(0.f, 0.f, 0.f);
		if (!m_Run)
		{
			SetState(PLAYER_STATE::MOVE);
			Animator2D()->Play((int)PLAYER_STATE::MOVE, 8.f, true);
			m_Run = true;
		}
		else
		{
			SetSpeed(500.f);
			SetState(PLAYER_STATE::RUN);
			Animator2D()->Play((int)PLAYER_STATE::RUN, 8.f, true);
			m_Run = false;
		}
	}
	else if (KEY_PRESSED(KEY::LEFT))
	{
		vRot = Vec3(0.f, 0.f, 0.f);
		SetDirection(OBJ_DIR::DIR_LEFT);
		SetState(PLAYER_STATE::MOVE);
		Animator2D()->Play((int)PLAYER_STATE::MOVE, 8.f, true);
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		vRot.y = XM_PI;
		SetDirection(OBJ_DIR::DIR_RIGHT);
		SetState(PLAYER_STATE::MOVE);
		if (!m_Run)
		{
			m_State = PLAYER_STATE::MOVE;
			Animator2D()->Play((int)PLAYER_STATE::MOVE, 8.f, true);
			m_Run = true;
		}
		else
		{
			SetSpeed(500.f);
			m_State = PLAYER_STATE::RUN;
			Animator2D()->Play((int)PLAYER_STATE::RUN, 8.f, true);
			m_Run = false;
		}
	}
	else if (KEY_PRESSED(KEY::RIGHT))
	{
		SetDirection(OBJ_DIR::DIR_RIGHT);
		SetState(PLAYER_STATE::MOVE);
		vRot.y = XM_PI;

		Animator2D()->Play((int)PLAYER_STATE::MOVE, 8.f, true);
	}
	
	if (KEY_TAP(KEY::UP))
	{
		SetState(PLAYER_STATE::MOVE);
		SetTBDirection(OBJ_DIR::DIR_UP);
		Animator2D()->Play((int)PLAYER_STATE::MOVE, 8.f, true);
	}
	else if (KEY_PRESSED(KEY::UP))
	{
		SetState(PLAYER_STATE::MOVE);
		SetTBDirection(OBJ_DIR::DIR_UP);
		Animator2D()->Play((int)PLAYER_STATE::MOVE, 8.f, true);
	}

	if (KEY_TAP(KEY::DOWN))
	{
		SetState(PLAYER_STATE::MOVE);
		SetTBDirection(OBJ_DIR::DIR_DOWN);
		Animator2D()->Play((int)PLAYER_STATE::MOVE, 8.f, true);
	}
	else if (KEY_PRESSED(KEY::DOWN))
	{
		SetState(PLAYER_STATE::MOVE);
		SetTBDirection(OBJ_DIR::DIR_DOWN);
		Animator2D()->Play((int)PLAYER_STATE::MOVE, 8.f, true);
	}
	
	if (KEY_TAP(KEY::X))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\wrevolverb.ogg")->Play(1, 0.5f, true);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_draw1.ogg")->Play(1, 1.f, true);
		if (m_CheckRange)
		{
			SetState(PLAYER_STATE::DG_AT1);
			Animator2D()->Play((int)PLAYER_STATE::DG_AT1, 15.f, true);
			CreateMuzzelOfRevolverDiagonal();
			CreateDiagonalPistol();
		}

		else
		{
			SetState(PLAYER_STATE::AT_1);
			Animator2D()->Play((int)PLAYER_STATE::AT_1, 15.f, false);
			CreateMuzzelOfRevolverNormal();
			CreatePistol();
		}
	}
	else if (KEY_PRESSED(KEY::DOWN) && KEY_TAP(KEY::X))
	{
		SetState(PLAYER_STATE::DG_AT1);
		Animator2D()->Play((int)PLAYER_STATE::DG_AT1, 15.f, false);
	}

	if (KEY_TAP(KEY::C))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_jump.ogg")->Play(1, 1.f, false);
		SetState(PLAYER_STATE::JUMP);
		Animator2D()->Play((int)PLAYER_STATE::JUMP, 5.f, false);
		Rigidbody()->Jump();
	}

	// Skill
	Stylish();
}

void CPlayerScript::Move()
{
	bool* bMoveable = GetOwner()->GetMoveable();

	// ATTACK
	//if (KEY_PRESSED(KEY::LEFT)
	// && bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	//{
	//	_Pos += Vec3(-1.f, 0.f, 0.f) * m_Speed * DT;
	//}

	if (KEY_RELEASED(KEY::LEFT))
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}

	//if (KEY_PRESSED(KEY::RIGHT)
	//	&& bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	//{
	//	_Pos += Vec3(1.f, 0.f, 0.f) * m_Speed * DT;
	//}

	if (KEY_RELEASED(KEY::RIGHT))
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}
	//if (KEY_PRESSED(KEY::UP)
	//	&& bMoveable[(UINT)PLATFORM_TYPE::UP])
	//{
	//	_Pos += Vec3(0.f, 1.f, 0.f) * m_Speed * DT;
	//}

	if (KEY_RELEASED(KEY::UP))
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}
	//if (KEY_PRESSED(KEY::DOWN)
	//	&& bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	//{
	//	_Pos += Vec3(0.f, -1.f, 0.f) * m_Speed * DT;
	//}

	if (KEY_RELEASED(KEY::DOWN))
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}

	if (KEY_PRESSED(KEY::DOWN) && KEY_TAP(KEY::X))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\wrevolverb.ogg")->Play(1, 0.5f, true);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_draw1.ogg")->Play(1, 1.f, true);
		SetState(PLAYER_STATE::DG_AT1);
		Animator2D()->Play((int)PLAYER_STATE::DG_AT1, 15.f, true);
		CreateMuzzelOfRevolverDiagonal();
		CreateDiagonalPistol();
		GetOwner()->GetParent()->SetMove(false);
	}

	else if (KEY_TAP(KEY::X))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\wrevolverb.ogg")->Play(1, 0.5f, true);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_draw1.ogg")->Play(1, 1.f, true);
		SetState(PLAYER_STATE::AT_1);
		Animator2D()->Play((int)PLAYER_STATE::AT_1, 15.f, false);
		GetOwner()->GetParent()->SetMove(false);
	}

	// JUMP
	if (KEY_TAP(KEY::C))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_jump.ogg")->Play(1, 1.f, false);
		SetState(PLAYER_STATE::JUMP);
		Animator2D()->Play((int)PLAYER_STATE::JUMP, 5.f, false);
		Rigidbody()->Jump();
	}

	// SKILL
	Stylish();
}

void CPlayerScript::AT1()
{
	GetOwner()->GetParent()->SetMove(false);
	if (KEY_TAP(KEY::X))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\wrevolverb.ogg")->Play(1, 0.5f, true);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_draw1.ogg")->Play(1, 1.f, true);
		m_NextAttack = true;
	}

	if (!m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)IDLE, 5.f, true);
		SetState(PLAYER_STATE::IDLE);
		GetOwner()->GetParent()->SetMove(true);
	}
	
	else if (m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)AT_2, 10.f, true);
		SetState(PLAYER_STATE::AT_2);
		m_NextAttack = false;
		CreatePistol();
		CreateMuzzelOfRevolverNormal();
	}

	Stylish();
}

void CPlayerScript::AT2()
{
	GetOwner()->GetParent()->SetMove(false);

	if (KEY_TAP(KEY::X) && !Animator2D()->IsFinish())
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\wrevolverb.ogg")->Play(1, 0.5f, true);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_draw1.ogg")->Play(1, 1.f, true);
		m_NextAttack = true;
	}

	if (m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)AT_2, 10.f, true);
		SetState(PLAYER_STATE::AT_3);
		m_NextAttack = false;
		CreatePistol();
		CreateMuzzelOfRevolverNormal();
	}

	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)IDLE, 5.f, true);
		SetState(PLAYER_STATE::IDLE);
		GetOwner()->GetParent()->SetMove(true);
	}

	Stylish();
}

void CPlayerScript::AT3()
{
	GetOwner()->GetParent()->SetMove(false);
	if (KEY_TAP(KEY::X) && !Animator2D()->IsFinish() && !m_NextAttack)
	{
		m_NextAttack = true;
	}

	if (m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)AT_3, 17.f, true);
		SetState(PLAYER_STATE::AT_4);
		m_NextAttack = true;
	}

	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)IDLE, 5.f, true);
		SetState(PLAYER_STATE::IDLE);
		GetOwner()->GetParent()->SetMove(true);
	}

	Stylish();
}

void CPlayerScript::AT4()
{
	GetOwner()->GetParent()->SetMove(false);
	if (m_NextAttack && 5 == Animator2D()->GetCurFrameIndex())
	{
		CreatePistol();
		CreateMuzzelOfRevolver();
		m_NextAttack = false;
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\wrevolverb.ogg")->Play(1, 0.5f, true);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_draw1.ogg")->Play(1, 1.f, true);
	}

	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}

	Stylish();
}

void CPlayerScript::AT_DG1()
{
	GetOwner()->GetParent()->SetMove(false);
	if (KEY_TAP(KEY::X))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\wrevolverb.ogg")->Play(1, 0.5f, true);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_draw1.ogg")->Play(1, 1.f, true);
		m_NextAttack = true;
	}
	
	if(m_NextAttack && Animator2D()->IsFinish())
	{
		if (m_CheckRange)
		{
			SetState(PLAYER_STATE::DG_AT2);
			Animator2D()->Play((int)PLAYER_STATE::DG_AT2, 10.f, true);
			CreateDiagonalPistol();
			CreateMuzzelOfRevolverDiagonal();
			m_NextAttack = false;
		}
		else
		{
			if (KEY_PRESSED(KEY::DOWN))
			{
				SetState(PLAYER_STATE::DG_AT2);
				Animator2D()->Play((int)PLAYER_STATE::DG_AT2, 10.f, true);
			}
			else if (KEY_RELEASED(KEY::DOWN))
			{
				SetState(PLAYER_STATE::AT_2);
				Animator2D()->Play((int)PLAYER_STATE::AT_2, 10.f, true);
			}
			CreateDiagonalPistol();
			CreateMuzzelOfRevolverDiagonal();
			m_NextAttack = false;
		}
	}
	
	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)PLAYER_STATE::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}

	Stylish();
}

void CPlayerScript::AT_DG2()
{
	GetOwner()->GetParent()->SetMove(false);
	if (KEY_TAP(KEY::X))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\wrevolverb.ogg")->Play(1, 0.5f, true);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_draw1.ogg")->Play(1, 1.f, true);
		m_NextAttack = true;
	}

	if (m_NextAttack && Animator2D()->IsFinish())
	{
		if (m_CheckRange)
		{
			SetState(PLAYER_STATE::DG_AT3);
			Animator2D()->Play((int)PLAYER_STATE::DG_AT2, 10.f, true);
			CreateDiagonalPistol();
			CreateMuzzelOfRevolverDiagonal();
			m_NextAttack = false;
		}

		if (KEY_PRESSED(KEY::DOWN))
		{
			SetState(PLAYER_STATE::DG_AT3);
			Animator2D()->Play((int)PLAYER_STATE::DG_AT2, 10.f, true);
			CreateDiagonalPistol();
			CreateMuzzelOfRevolverDiagonal();
		}
		else if(KEY_RELEASED(KEY::DOWN))
		{
			SetState(PLAYER_STATE::AT_2);
			Animator2D()->Play((int)PLAYER_STATE::AT_2, 10.f, true);
		}
		
		m_NextAttack = false;
	}

	else if(!m_NextAttack && Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}

	Stylish();
}

void CPlayerScript::AT_DG3()
{
	GetOwner()->GetParent()->SetMove(false);
	if (KEY_TAP(KEY::X))
	{
		m_NextAttack = true;
	}

	if (m_NextAttack && Animator2D()->IsFinish())
	{
		if (m_CheckRange)
		{
			SetState(PLAYER_STATE::DG_AT4);
			Animator2D()->Play((int)PLAYER_STATE::DG_AT3, 17.f, true);
		}

		else
		{
			if (KEY_PRESSED(KEY::DOWN))
			{
				SetState(PLAYER_STATE::DG_AT4);
				Animator2D()->Play((int)PLAYER_STATE::DG_AT3, 17.f, true);
			}

			else if (KEY_RELEASED(KEY::DOWN))
			{
				SetState(PLAYER_STATE::AT_2);
				Animator2D()->Play((int)PLAYER_STATE::AT_3, 10.f, true);
			}
		}
	}

	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}

	Stylish();
}

void CPlayerScript::AT_DG4()
{
	GetOwner()->GetParent()->SetMove(false);
	if (m_NextAttack && 5 == Animator2D()->GetCurFrameIndex())
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\wrevolverb.ogg")->Play(1, 0.5f, true);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_draw1.ogg")->Play(1, 1.f, true);
		CreateDiagonalPistol();
		CreateMuzzelOfRevolverDiagonal();
		m_NextAttack = false;
	}

	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}

	Stylish();
}

void CPlayerScript::Tackle()
{
	INFO& info = GetOwner()->GetParent()->GetInfo();

	info.bTackle = true;

	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);

		info.bTackle = false;
	}
}

void CPlayerScript::Jump()
{
	if (GroundCheck())
	{
		SetState(PLAYER_STATE::LANDING);
		Animator2D()->Play((int)LANDING, 3.f, false);
	}
}

void CPlayerScript::Landing()
{
	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}
}

void CPlayerScript::Hit()
{
	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}
}

void CPlayerScript::Run()
{
	Collider2D()->SetScale(Vec3(75.f, 136.f, 1.f));
	GetOwner()->GetParent()->SetSpeed(500.f);

	//bool* bMoveable = GetOwner()->GetMoveable();

	//if (KEY_PRESSED(KEY::UP)
	//	&& bMoveable[(UINT)PLATFORM_TYPE::UP])
	//{
	//	_Pos += Vec3(0.f, 1.f, 0.f) * m_Speed * DT;
	//}
	//
	//if (KEY_PRESSED(KEY::DOWN)
	//	&& bMoveable[(UINT)PLATFORM_TYPE::BOTTOM])
	//{
	//	_Pos += Vec3(0.f, -1.f, 0.f) * m_Speed * DT;
	//}
	//
	//if (KEY_PRESSED(KEY::LEFT)
	//	&& bMoveable[(UINT)PLATFORM_TYPE::LEFT])
	//{
	//	_Pos += Vec3(-1.f, 0.f, 0.f) * m_Speed * DT;
	//}

	if (KEY_RELEASED(KEY::LEFT))
	{
		SetState(PLAYER_STATE::IDLE);
		SetSpeed(350.f);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}

	//if (KEY_PRESSED(KEY::RIGHT)
	//	&& bMoveable[(UINT)PLATFORM_TYPE::RIGHT])
	//{
	//	_Pos += Vec3(1.f, 0.f, 0.f) * m_Speed * DT;
	//}

	if (KEY_RELEASED(KEY::RIGHT))
	{
		SetState(PLAYER_STATE::IDLE);
		SetSpeed(350.f);
		Animator2D()->Play((int)IDLE, 5.f, true);
	}

	if (KEY_TAP(KEY::C))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_jump.ogg")->Play(1, 1.f, false);
		SetState(PLAYER_STATE::JUMP);
		Animator2D()->Play((int)PLAYER_STATE::JUMP, 5.f, false);
		Rigidbody()->Jump();
	}

	if (KEY_TAP(KEY::X))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\wrevolverb.ogg")->Play(1, 0.5f, true);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gun_draw1.ogg")->Play(1, 1.f, true);
		SetState(PLAYER_STATE::TACKLE);
		Animator2D()->Play((int)ANIMATION_NUM::TACKLE, 10.f, false);
		GetOwner()->GetParent()->SetMove(false);
	}

	Stylish();
}

void CPlayerScript::Dead()
{
}

void CPlayerScript::DeathCrisis()
{
	GetOwner()->GetParent()->SetMove(false);

	CreateDeathCrisis();
	DeathCrisisMove();

	if (46 == Animator2D()->GetCurFrameIndex())
	{
		CreateDeathCrisisCutin();
	}

	if (Animator2D()->IsFinish())
	{
		CGameObject* pObj = GetOwner()->FindChildByName(L"deathcrisisgun");
		pObj->SetActive(false);
		pObj->Animator2D()->Reset();
		pObj = GetOwner()->FindChildByName(L"deathcrisisguntwo");
		pObj->SetActive(false);
		pObj->Animator2D()->Reset();
		pObj = GetOwner()->FindChildByName(L"feather");
		pObj->SetActive(false);
		pObj->Animator2D()->Reset();
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		CGameObject* pBlack = CLevelMgr::GetInst()->FindObjectByName(L"black");
		DeleteObject(pBlack);
		
		if (OBJ_DIR::DIR_LEFT == m_Dir)
			GetOwner()->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		else
			GetOwner()->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));

		GetOwner()->GetParent()->SetMove(true);
		m_CutinSpawn = false;
	}
}

void CPlayerScript::DeathCrisisMove()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vParentPos = GetOwner()->GetParent()->Transform()->GetRelativePos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		if (5 == Animator2D()->GetCurFrameIndex() && !m_Foot)
		{
			CGameObject* pObj = GetOwner()->FindChildByName(L"deathcrisisfoot");
			pObj->SetActive(true);
			pObj->Animator2D()->Play(0, 5.f, false);
			m_Foot = true;
		}
		else if (6 == Animator2D()->GetCurFrameIndex())
			m_Foot = true;

		else if (7 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(-500.f, vParentPos.y, vParentPos.z);
		}
		else if (!m_Foot && 17 == Animator2D()->GetCurFrameIndex())
		{
			CGameObject* pObj = GetOwner()->FindChildByName(L"deathcrisisfoot");
			pObj->SetActive(true);
			pObj->Animator2D()->Play(0, 5.f, false);
			m_Foot = true;
		}	
		else if (20 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(-200.f, vParentPos.y - 200.f, vParentPos.z);
			m_Foot = false;
			CGameObject* pObj = GetOwner()->FindChildByName(L"deathcrisisfoot");
			pObj->SetActive(true);
			pObj->Animator2D()->Play(0, 5.f, false);
		}
		else if (21 <= Animator2D()->GetCurFrameIndex() && 26 >= Animator2D()->GetCurFrameIndex())
		{
			vPos += Vec3(1.f, 1.f, 1.f) * 600.f * DT;
		}
		else if (23 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(-500.f, -100.f, vParentPos.z);
		}
		else if (29 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(-200.f, 300.f, vParentPos.z);
		}
		else if (34 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(100.f, 200.f, 1.f);
		}
		else if (38 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(0.f, 0.f, 1.f);
		}
		else if (46 <= Animator2D()->GetCurFrameIndex() && 49 == Animator2D()->GetCurFrameIndex())
		{
			vPos += Vec3(1.f, 0.f, 0.f) * 500.f * DT;
		}
		else if (56 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(0.f, 0.f, 1.f);
		}
	}
	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		if (5 == Animator2D()->GetCurFrameIndex() && !m_Foot)
		{
			CGameObject* pObj = GetOwner()->FindChildByName(L"deathcrisisfoot");
			pObj->SetActive(true);
			pObj->Animator2D()->Play(0, 5.f, false);
			m_Foot = true;
		}
		else if (6 == Animator2D()->GetCurFrameIndex())
			m_Foot = true;
		else if (7 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(500.f, vParentPos.y, vParentPos.z);
		}
		else if (!m_Foot && 17 == Animator2D()->GetCurFrameIndex())
		{
			CGameObject* pObj = GetOwner()->FindChildByName(L"deathcrisisfoot");
			pObj->SetActive(true);
			pObj->Animator2D()->Play(0, 5.f, false);
			m_Foot = true;
		}
		else if (20 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(200.f, vParentPos.y - 200.f, vParentPos.z);
			m_Foot = false;
			CGameObject* pObj = GetOwner()->FindChildByName(L"deathcrisisfoot");
			pObj->SetActive(true);
			pObj->Animator2D()->Play(0, 5.f, false);
		}
		else if (21 <= Animator2D()->GetCurFrameIndex() && 26 >= Animator2D()->GetCurFrameIndex())
		{
			vPos += Vec3(-1.f, 1.f, 1.f) * 600.f * DT;
		}
		else if (23 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(-500.f, -100.f, vParentPos.z);
		}
		else if (29 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(-200.f, 300.f, vParentPos.z);
		}
		else if (34 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(100.f, 200.f, 1.f);
		}
		else if (38 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(0.f, 0.f, 1.f);
		}
		else if (46 <= Animator2D()->GetCurFrameIndex() && 49 == Animator2D()->GetCurFrameIndex())
		{
			vPos += Vec3(-1.f, 0.f, 0.f) * 500.f * DT;
		}
		else if (56 == Animator2D()->GetCurFrameIndex())
		{
			vPos = Vec3(0.f, 0.f, 1.f);
		}
	}

	Transform()->SetRelativePos(vPos);
}

void CPlayerScript::DeathByRevolver()
{
	GetOwner()->GetParent()->SetMove(false);

	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}
}

void CPlayerScript::JackSpike()
{
	GetOwner()->GetParent()->SetMove(false);
	SetSuperArmor(true);

	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}

	Stylish();
}

void CPlayerScript::RisingShot()
{
	GetOwner()->GetParent()->SetMove(false);

	if (m_Spawn && 3 <= Animator2D()->GetCurFrameIndex())
	{
		CreateRisingShot();
		CreateMuzzelOfRevolver();
		m_Spawn = false;
	}

	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		m_Spawn = true;
		GetOwner()->GetParent()->SetMove(true);
	}

	Stylish();
}

void CPlayerScript::HeadShot()
{
	GetOwner()->GetParent()->SetMove(false);

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
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		m_HeadShotSpawn = true;
		GetOwner()->GetParent()->SetMove(true);
	}
}

void CPlayerScript::RandomShot()
{
	GetOwner()->GetParent()->SetMove(false);
	CreateRandomShoot();

	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		m_Spawn = true;
		GetOwner()->GetParent()->SetMove(true);
	}
}

void CPlayerScript::WindMill()
{
	GetOwner()->GetParent()->SetMove(false);
	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}

	Stylish();
}

void CPlayerScript::MachKick()
{
	GetOwner()->GetParent()->SetMove(false);
	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}
}

void CPlayerScript::GunHawkShoot()
{
	GetOwner()->GetParent()->SetMove(false);
	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}

	Stylish();
}

void CPlayerScript::GunHawkStandBy()
{
	GetOwner()->GetParent()->SetMove(false);

	if (m_GunHawkStandby)
	{
		GetOwner()->GetParent()->SetForce(true);
		//AddForce();
		m_GunHawkStandby = false;
	}

	if (!Animator2D()->IsFinish() && KEY_TAP(KEY::Q))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_dgunhawk_third.ogg")->Play(1, 0.7f, true);
		SetState(PLAYER_STATE::GUNHAWKLASTSHOOT);
		Animator2D()->Play((int)ANIMATION_NUM::GUNHAWKSHOOT, 7.f, true);
		GetOwner()->GetParent()->SetForce(false);
		CreateGunHawkSecond();
		
	}

	else if (Animator2D()->IsFinish())
	{
		GetOwner()->GetParent()->SetForce(false);
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}
}

void CPlayerScript::GunHawkLastShoot()
{
	GetOwner()->GetParent()->SetMove(false);
	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
	}

	Stylish();
}

void CPlayerScript::WesternFire()
{
	GetOwner()->GetParent()->SetMove(false);

	if (m_Spawn && 3 <= Animator2D()->GetCurFrameIndex())
	{
		if (m_CheckRange)
		{
			CreateDiagonalHeadShot();
			CreateDiagonalHeadShotEffect();
		}

		else if (KEY_PRESSED(KEY::DOWN))
		{
			CreateDiagonalHeadShot();
			CreateDiagonalHeadShotEffect();
		}

		else
		{
			CreateHeadShot();
			CreateHeadShotEffect();
		}

		m_Spawn = false;
	}

	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
		m_Spawn = true;
	}

	Stylish();
}

void CPlayerScript::PuniSher()
{
	GetOwner()->GetParent()->SetMove(false);

	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
		m_Spawn = true;
	}
}

void CPlayerScript::PuniSherShoot()
{
	GetOwner()->GetParent()->SetMove(false);

	if (0 == Animator2D()->GetCurFrameIndex())
		m_Spawn = true;
	if (5 == Animator2D()->GetCurFrameIndex() && m_Spawn)
	{
		CreatePunisherPistol();
		m_Spawn = false;
	}
	else if (6 == Animator2D()->GetCurFrameIndex())
		m_Spawn = true;

	else if (7 == Animator2D()->GetCurFrameIndex() && m_Spawn)
	{
		CreatePunisherPistol();
		m_Spawn = false;
	}
	else if (8 == Animator2D()->GetCurFrameIndex())
		m_Spawn = true;
	else if (9 == Animator2D()->GetCurFrameIndex() && m_Spawn)
	{
		CreatePunisherPistol();
		m_Spawn = false;
	}

	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
		m_Spawn = true;
	}
}

void CPlayerScript::SkillBBQ()
{
	GetOwner()->GetParent()->SetMove(false);
	if (Animator2D()->IsFinish())
	{
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
		m_Spawn = true;
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gatling_shot.ogg")->Stop();
	}
}

void CPlayerScript::BBQReady()
{
	GetOwner()->GetParent()->SetMove(false);
	if (Animator2D()->IsFinish())
	{
		GetOwner()->GetChildren()[0]->Animator2D()->Play(1, 8.f, true);
		SetState(PLAYER_STATE::BBQSHOOT);
		Animator2D()->Play((int)ANIMATION_NUM::BBQSHOOT, 5.f, true);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gatling_shot.ogg")->Play(0, 0.5f, false);
	}
}

void CPlayerScript::SkillBBQShoot()
{
	GetOwner()->GetParent()->SetMove(false);
	m_BBQTime += DT;
	if (2.f < m_BBQTime)
	{
		m_BBQTime = 0.f;
		GetOwner()->GetChildren()[0]->SetActive(false);
		//GetOwner()->GetChildren()[0]->Animator2D()->Play(0, 8.f, false);
		SetState(PLAYER_STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		GetOwner()->GetParent()->SetMove(true);
		m_Spawn = true;
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gatling_shot.ogg")->Stop();
	}
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
	if (m_UseSkill.bWesternFire)
	{
		m_CoolTime.fWesternFireTime += DT;

		if (m_CoolTime.fWesternFireCoolTime <= m_CoolTime.fWesternFireTime)
		{
			m_UseSkill.bWesternFire = false;
			m_CoolTime.fWesternFireTime = 0.f;
		}
	}
	if (m_UseSkill.bPunisher)
	{
		m_CoolTime.fPunisherTime += DT;

		if (m_CoolTime.fPunisherCoolTime <= m_CoolTime.fPunisherTime)
		{
			m_UseSkill.bPunisher = false;
			m_CoolTime.fPunisherTime = 0.f;
		}
	}
	if (m_UseSkill.bBBQ)
	{
		m_CoolTime.fBBQTime += DT;

		if (m_CoolTime.fBBQCoolTime <= m_CoolTime.fBBQTime)
		{
			m_UseSkill.bBBQ = false;
			m_CoolTime.fBBQTime = 0.f;
		}
	}
	if (m_UseSkill.bDeathCrisis)
	{
		m_CoolTime.fDeathCrisisTime += DT;

		if (m_CoolTime.fDeathCrisisCoolTime <= m_CoolTime.fDeathCrisisTime)
		{
			m_UseSkill.bDeathCrisis = false;
			m_CoolTime.fDeathCrisisTime = 0.f;
		}
	}
}

void CPlayerScript::SuperArmorCheck()
{
	INFO& info = GetOwner()->GetInfo();
	if (info.bSuperArmor)
	{
		m_SuperArmorTime += DT;
		MeshRender()->GetMaterial()->SetScalarParam(INT_3, 1);
		if(m_Color)
			MeshRender()->GetMaterial()->SetScalarParam(VEC4_1, Vec4(1.f, 0.f, 0.f, 0.1f));
		else
			MeshRender()->GetMaterial()->SetScalarParam(VEC4_1, Vec4(1.f, 1.f, 0.f, 0.1f));
	}
	else
	{
		MeshRender()->GetMaterial()->SetScalarParam(INT_3, 0);
	}

	if (0.2f < m_SuperArmorTime)
	{
		if (m_Color)
			m_Color = false;
		else
			m_Color = true;
		m_SuperArmorTime = 0.f;
	}
}

void CPlayerScript::Stylish()
{
	if (!m_UseSkill.bJackSpike && KEY_TAP(KEY::Z))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_jspike_01.ogg")->Play(1, 1.f, true);
		SetState(PLAYER_STATE::SK_1);
		Animator2D()->Play((int)ANIMATION_NUM::JACKSPIKE, 11.f, false);
		CreateJackSpike();
		m_UseSkill.bJackSpike = true;
	}

	if (!m_UseSkill.bHeadShot && KEY_TAP(KEY::A))
	{
		SetState(PLAYER_STATE::SK_3);
		if(KEY_PRESSED(KEY::DOWN))
			Animator2D()->Play((int)ANIMATION_NUM::DG_AT3, 25.f, false);
		else
			Animator2D()->Play((int)ANIMATION_NUM::AT_3, 25.f, false);

		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_hshot_01.ogg")->Play(1, 1.f, true);

		m_UseSkill.bHeadShot = true;
		SetSuperArmor(true);
	}

	if (!m_UseSkill.bRisingShot && KEY_TAP(KEY::S))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_risingshot.ogg")->Play(1, 1.f, true);
		SetState(PLAYER_STATE::SK_2);
		Animator2D()->Play((int)ANIMATION_NUM::AT_3, 20.f, false);
		m_UseSkill.bRisingShot = true;
	}

	if (!m_UseSkill.bWindMill && KEY_TAP(KEY::D))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_windmill_01.ogg")->Play(1, 1.f, true);
		SetState(PLAYER_STATE::SK_6);
		Animator2D()->Play((int)ANIMATION_NUM::WINDMILL, 20.f, false);
		CreateWindMill();
		m_UseSkill.bWindMill = true;
		SetSuperArmor(true);
	}

	if (!m_UseSkill.bMachKick && KEY_TAP(KEY::F))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_mach_01.ogg")->Play(1, 1.f, true);
		SetState(PLAYER_STATE::SK_7);
		Animator2D()->Play((int)ANIMATION_NUM::MACHKICK, 20.f, false);
		CreateMachKick();
		m_UseSkill.bMachKick = true;
		SetSuperArmor(true);
	}

	if (!m_UseSkill.bRandShoot && KEY_TAP(KEY::G))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_rshot.ogg")->Play(1, 1.f, false);
		SetState(PLAYER_STATE::SK_4);
		Animator2D()->Play((int)ANIMATION_NUM::RANDOMSHOT, 30.f, false);
		m_UseSkill.bRandShoot = true;
		SetSuperArmor(true);
	}

	if (!m_UseSkill.bDeathByRevolver && KEY_TAP(KEY::SPACE))
	{
		SetState(PLAYER_STATE::SK_5);
		Animator2D()->Play((int)ANIMATION_NUM::DEATHBYREVOLVER, 17.f, false);
		CreateDeathByRevolver();
		m_UseSkill.bDeathByRevolver = true;
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_db_revolver.ogg")->Play(1, 0.7f, true);
	}

	if (!m_UseSkill.bGunHawk && KEY_TAP(KEY::Q))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_dgunhawk_sec.ogg")->Play(1, 1.f, true);
		SetState(PLAYER_STATE::GUNHAWKSHOOT);
		Animator2D()->Play((int)ANIMATION_NUM::GUNHAWKSHOOT, 7.f, false);
		CreateGunHawkFirst();
		m_UseSkill.bGunHawk = true;
	}

	if (!m_UseSkill.bWesternFire && KEY_TAP(KEY::H))
	{
		SetState(PLAYER_STATE::WESTERNFIRE);

		GetOwner()->GetParent()->SetMove(false);

		if (m_CheckRange)
			Animator2D()->Play((int)ANIMATION_NUM::DG_AT3, 25.f, false);
		else
			Animator2D()->Play((int)ANIMATION_NUM::AT_3, 25.f, false);

		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_hshot_03.ogg")->Play(1, 1.f, false);

		CreateWesternFire();
		m_Spawn = true;
		m_UseSkill.bWesternFire = true;
		SetSuperArmor(true);
	}

	if (!m_UseSkill.bPunisher && KEY_TAP(KEY::W))
	{
		SetState(PLAYER_STATE::PUNISHER);
		Animator2D()->Play((int)ANIMATION_NUM::PUNISHER, 12.f, false);
		CreatePunisher();
		m_UseSkill.bPunisher = true;
	}
	
	if (!m_UseSkill.bBBQ && KEY_TAP(KEY::E))
	{
		SetState(PLAYER_STATE::BBQ);
		Animator2D()->Play((int)ANIMATION_NUM::JACKSPIKE, 11.f, false);
		CreateBBQ();
		m_UseSkill.bBBQ = true;
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_bbq_01.ogg")->Play(1, 0.7f, true);
		SetSuperArmor(true);
	}
	if (false == m_UseSkill.bDeathCrisis && KEY_TAP(KEY::CTRL))
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\deathcrisisfirst.ogg")->Play(1, 1.f, true);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\death_crisis_1st.ogg")->Play(1, 1.f, false);
		SetState(PLAYER_STATE::DEATHCRISIS);
		GetOwner()->GetParent()->SetMove(false);
		Animator2D()->Play((int)ANIMATION_NUM::DEATHCRISIS, 13.f, false);
		m_UseSkill.bDeathCrisis = true;
		if (OBJ_DIR::DIR_LEFT == m_Dir)
		{
			GetOwner()->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
			//GetOwner()->GetParent()->SetDir(OBJ_DIR::DIR_LEFT);
		}
		else
		{
			GetOwner()->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
			//GetOwner()->GetParent()->SetDir(OBJ_DIR::DIR_RIGHT);
		}

		Ptr<CPrefab> BlackPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\black.pref");
		CGameObject* pBlack = BlackPref->Instantiate();
		CreateObject(pBlack, 0);

		CGameObject* pObj = GetOwner()->FindChildByName(L"deathcrisisgun");
		pObj->SetActive(true);
		pObj->Animator2D()->Play(0, 13.f, false);
		pObj = GetOwner()->FindChildByName(L"deathcrisisguntwo");
		pObj->SetActive(true);
		pObj->Animator2D()->Play(0, 13.f, false);
		pObj = GetOwner()->FindChildByName(L"feather");
		pObj->SetActive(true);
		pObj->Animator2D()->Play(0, 13.f, true);

		SetSuperArmor(true);
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

	CreateObject(pBuff, 0);
}

void CPlayerScript::CreateRandomShoot()
{
	Vec3 vPos = Transform()->GetWorldPos();
	int CurIdx = Animator2D()->GetCurFrameIndex();

	if (m_Spawn && CurIdx == 0)
	{
		//CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		CGameObject* pObject = m_RandomShootPref->Instantiate();

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
		//CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		CGameObject* pObject = m_RandomShootPref->Instantiate();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 100.f, vPos.y, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI));
		CreateObject(pObject, 7);
	
		//pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		CGameObject* pObject = m_RandomShootPref->Instantiate();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 120.f, vPos.y - 30.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.12f));
		CreateObject(pObject, 7);
		
		//pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		CGameObject* pObject = m_RandomShootPref->Instantiate();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 110.f, vPos.y - 40.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.2f));
		CreateObject(pObject, 7);
	
		//pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		CGameObject* pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		CGameObject* pObject = m_RandomShootPref->Instantiate();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 120.f, vPos.y, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI));
		CreateObject(pObject, 7);
	
		//pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		CGameObject* pObject = m_RandomShootPref->Instantiate();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 110.f, vPos.y + 20.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.12f));
		CreateObject(pObject, 7);
	
		//pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		CGameObject* pObject = m_RandomShootPref->Instantiate();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 80.f, vPos.y - 70.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.2f));
		CreateObject(pObject, 7);
	
		//pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		CGameObject* pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		CGameObject* pObject = m_RandomShootPref->Instantiate();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 110.f, vPos.y + 20.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI));
		CreateObject(pObject, 7);
	
		//pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		CGameObject* pObject = m_RandomShootPref->Instantiate();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 90.f, vPos.y + 10.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.12f));
		CreateObject(pObject, 7);
	
		//pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		CGameObject* pObject = m_RandomShootPref->Instantiate();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 60.f, vPos.y - 40.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.2f));
		CreateObject(pObject, 7);
	
		//pObject = CObjectPoolMgr::GetInst()->GetObj(OBJ_ID::RANDOMSHOOT);
		pObject = m_RandomShootPref->Instantiate();
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
	Vec3 vPos = Collider2D()->GetWorldPos();
	Vec3 vScale = Collider2D()->GetScale();

	if (0 <= Animator2D()->GetCurFrameIndex())
	{
		if (OBJ_DIR::DIR_LEFT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x - 175.f, vPos.y - vScale.y * 0.5f, vPos.z));
			pObject->SetDir(OBJ_DIR::DIR_LEFT);
		}

		else if (OBJ_DIR::DIR_RIGHT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x + 175.f, vPos.y - vScale.y * 0.5f, vPos.z));
			pObject->SetDir(OBJ_DIR::DIR_RIGHT);
		}

		pObject->SetInitPos(vPos);

		CreateObject(pObject, 7);
	}
}

void CPlayerScript::CreateDiagonalPistol()
{
	Vec3 vPos = Collider2D()->GetWorldPos();
	Vec3 vScale = Collider2D()->GetScale();
	
	CGameObject* pObject = m_Prefabs.DiagonalPistolPref->Instantiate();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 175.f, vPos.y - vScale.y * 0.5f, vPos.z));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 175.f, vPos.y - vScale.y * 0.5f, vPos.z));
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

	if (PLAYER_STATE::DG_AT4 == m_State)
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

	m_CoolTime.fHeadShotTime = 0.f;
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
	CGameObject* pObject = m_Prefabs.HeadShotPref->Instantiate();

	Vec3 vPos = Collider2D()->GetWorldPos();
	Vec3 vScale = Collider2D()->GetScale();

	if (0 <= Animator2D()->GetCurFrameIndex())
	{
		if (OBJ_DIR::DIR_LEFT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x - 175.f, vPos.y - vScale.y * 0.5f, vPos.z));
			pObject->SetDir(OBJ_DIR::DIR_LEFT);
		}

		else if (OBJ_DIR::DIR_RIGHT == m_Dir)
		{
			pObject->Transform()->SetRelativePos(Vec3(vPos.x + 175.f, vPos.y - vScale.y * 0.5f, vPos.z));
			pObject->SetDir(OBJ_DIR::DIR_RIGHT);
		}

		pObject->SetInitPos(vPos);

		CreateObject(pObject, 7);
	}
}

void CPlayerScript::CreateDiagonalHeadShot()
{
	Vec3 vPos = Collider2D()->GetWorldPos();
	Vec3 vScale = Collider2D()->GetScale();

	CGameObject* pObject = m_Prefabs.DiagonalHeadShotPref->Instantiate();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 175.f, vPos.y - vScale.y * 0.5f, vPos.z));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 175.f, vPos.y - vScale.y * 0.5f, vPos.z));
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
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		GunHawkUp->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		GunHawkDown->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
	}

	GunHawkUp->SetDir(m_Dir);
	GunHawkDown->SetDir(m_Dir);
	GunHawkUp->SetInitPos(vPos);
	GunHawkDown->SetInitPos(vPos);
	GunHawkUp->Transform()->SetRelativeScale(Vec3(150.f, 75.f, 1.f));
	GunHawkDown->Transform()->SetRelativeScale(Vec3(150.f, 75.f, 1.f));
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
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		GunHawkUp->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		GunHawkDown->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
	}

	GunHawkUp->SetDir(m_Dir);
	GunHawkDown->SetDir(m_Dir);
	GunHawkUp->SetInitPos(vPos);
	GunHawkDown->SetInitPos(vPos);
	GunHawkUp->Transform()->SetRelativeScale(Vec3(150.f, 75.f, 1.f));
	GunHawkDown->Transform()->SetRelativeScale(Vec3(150.f, 75.f, 1.f));

	CreateObject(GunHawkUp, 7);
	CreateObject(GunHawkDown, 7);
}

void CPlayerScript::CreateMachKick()
{
	CGameObject* pObject = m_MachKickPref->Instantiate();

	Vec3 vColPos = Collider2D()->GetWorldPos();
	Vec3 vScale = Collider2D()->GetScale();
	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 75.f, vColPos.y - vScale.y * 0.5f, vPos.z));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 75.f, vColPos.y - vScale.y * 0.5f, vPos.z));
	}

	//pObject->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));

	CreateObject(pObject, 7);
}

void CPlayerScript::CreateJackSpike()
{
	CGameObject* pObject = m_JackSpikePref->Instantiate();
	Vec3 vColPos = Collider2D()->GetWorldPos();
	Vec3 vScale = Collider2D()->GetScale();
	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 50.f, vColPos.y - vScale.y * 0.5f, vPos.z));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vColPos.y - vScale.y * 0.5f, vPos.z));
	}

	CreateObject(pObject, 7);
}

void CPlayerScript::CreateRisingShot()
{
	Vec3 vPos = Collider2D()->GetWorldPos();
	Vec3 vScale = Collider2D()->GetScale();

	CGameObject* pObject = m_RisingShotPref->Instantiate();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 175.f, vPos.y - vScale.y * 0.5f, vPos.z));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 175.f, vPos.y - vScale.y * 0.5f, vPos.z));
	}

	pObject->SetDir(m_Dir);
	pObject->SetOwner(GetOwner());
	CreateObject(pObject, 7);
}

void CPlayerScript::CreateWesternFire()
{
	CGameObject* pObject = m_Prefabs.WesternFirePref->Instantiate();
	//Vec3 vPos = pObject->Transform()->GetRelativePos();
	Vec3 vColPos = Collider2D()->GetWorldPos();
	
	if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		GetOwner()->GetParent()->SetDir(OBJ_DIR::DIR_LEFT);
		GetOwner()->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		//GetOwner()->GetParent()->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	}
	else
	{
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		GetOwner()->GetParent()->SetDir(OBJ_DIR::DIR_RIGHT);
		GetOwner()->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		//GetOwner()->GetParent()->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
	}
	pObject->Transform()->SetRelativePos(Vec3(vColPos.x - 30.f, vColPos.y + 30.f, vColPos.z));
	CreateObject(pObject, 0);
}

void CPlayerScript::CreatePunisher()
{
	CGameObject* pObject = m_Prefabs.PunisherPref->Instantiate();
	Vec3 vColPos = Collider2D()->GetWorldPos();
	Vec3 vScale = Collider2D()->GetScale();
	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 50.f, vColPos.y - vScale.y * 0.5f, vPos.z));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vColPos.y - vScale.y * 0.5f, vPos.z));
	}

	CreateObject(pObject, 7);
}

void CPlayerScript::CreatePunisherPistol()
{
	CGameObject* pObject = m_Prefabs.PunisherPistolPref->Instantiate();

	Vec3 vColPos = Collider2D()->GetWorldPos();
	Vec3 vScale = Collider2D()->GetScale();
	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 145.f, (vColPos.y - vScale.y * 0.5f) + 50.f, vPos.z));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 4.223697f));
		pObject->SetDir(OBJ_DIR::DIR_LEFT);
	}
	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 145.f, (vColPos.y - vScale.y * 0.5f) + 50.f, vPos.z));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 5.061455f));
		pObject->SetDir(OBJ_DIR::DIR_RIGHT);
	}

	CreateObject(pObject, 7);
}

void CPlayerScript::CreateBBQ()
{
	CGameObject* pObject = m_Prefabs.BBQPref->Instantiate();
	Vec3 vColPos = Collider2D()->GetWorldPos();
	Vec3 vScale = Collider2D()->GetScale();
	Vec3 vPos = Transform()->GetWorldPos();

	if (OBJ_DIR::DIR_LEFT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 50.f, vColPos.y - vScale.y * 0.5f, vPos.z));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vColPos.y - vScale.y * 0.5f, vPos.z));
	}

	CreateObject(pObject, 7);
}

void CPlayerScript::CreateDeathCrisisCutin()
{
	if (!m_CutinSpawn)
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisCutinPref->Instantiate();
		CreateObject(pObj, 31);
		m_CutinSpawn = true;
	}
}

void CPlayerScript::CreateDeathCrisis()
{
	CGameObject* pCam = CLevelMgr::GetInst()->FindObjectByName(L"MainCamera");

	Vec3 vPos = pCam->Transform()->GetRelativePos();
	Vec3 vWorldPos = GetOwner()->Transform()->GetWorldPos();

	if (!m_LineTwo && 0 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y - 200.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI / 2.5f));
		pObj->Transform()->SetRelativeScale(Vec3(1500.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (1 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 2 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y - 100.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI / 1.5f));
		pObj->Transform()->SetRelativeScale(Vec3(1500.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (3 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 4 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 100.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 5.497787f));
		pObj->Transform()->SetRelativeScale(Vec3(1200.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisLineOnePref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 600.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		pObj->Transform()->SetRelativeScale(Vec3(3000.f, 100.f, 1.f));
		CreateObject(pObj, 7);

		m_LineTwo = true;
	}
	else if (5 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 6 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 200.f, vPos.y + 50.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 3.926991f));
		pObj->Transform()->SetRelativeScale(Vec3(1500.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		m_LineTwo = true;
	}
	else if (7 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 8 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		pObj->Transform()->SetRelativeScale(Vec3(1800.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisLineOnePref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 600.f, vPos.y + 300.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 5.497787f));
		pObj->Transform()->SetRelativeScale(Vec3(3000.f, 100.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (9 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 10 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 1.570796f));
		pObj->Transform()->SetRelativeScale(Vec3(900.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisBoomTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vWorldPos.x, vWorldPos.y, 300.f));
		pObj->Transform()->SetRelativeScale(Vec3(1000.f, 1000.f, 1.f));
		CreateObject(pObj, 0);
		m_LineTwo = true;
	}
	else if (11 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 12 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x, vPos.y + 50.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.5f));
		pObj->Transform()->SetRelativeScale(Vec3(900.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisLineOnePref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 600.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		pObj->Transform()->SetRelativeScale(Vec3(3000.f, 100.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (13 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 14 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 50.f, vPos.y + 75.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 5.497787f));
		pObj->Transform()->SetRelativeScale(Vec3(1700.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (15 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 16 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 50.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 1.570796f));
		pObj->Transform()->SetRelativeScale(Vec3(900.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisLineOnePref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 600.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		pObj->Transform()->SetRelativeScale(Vec3(3000.f, 100.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (17 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 18 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		pObj->Transform()->SetRelativeScale(Vec3(1200.f, 200.f, 1.f));
		CreateObject(pObj, 0);

		pObj = m_Prefabs.DeathCrisisLineOnePref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 350.f, vPos.y + 300.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 5.497787f));
		pObj->Transform()->SetRelativeScale(Vec3(3000.f, 100.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (19 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 20 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y - 20.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 2.356194f));
		pObj->Transform()->SetRelativeScale(Vec3(1200.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisBoomTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vWorldPos.x, vWorldPos.y, 300.f));
		pObj->Transform()->SetRelativeScale(Vec3(1000.f, 1000.f, 1.f));
		CreateObject(pObj, 0);
		m_LineTwo = true;
	}
	else if (21 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}

	if (!m_LineTwo && 22 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y - 200.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI / 2.5f));
		pObj->Transform()->SetRelativeScale(Vec3(1500.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisLineOnePref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 600.f, vPos.y - 300.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.785398f));
		pObj->Transform()->SetRelativeScale(Vec3(3000.f, 100.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (23 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 24 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y - 100.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI / 1.5f));
		pObj->Transform()->SetRelativeScale(Vec3(1500.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisBoomTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vWorldPos.x, vWorldPos.y, 300.f));
		pObj->Transform()->SetRelativeScale(Vec3(800.f, 800.f, 1.f));
		CreateObject(pObj, 0);
		m_LineTwo = true;
		m_LineTwo = true;
	}
	else if (25 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 26 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 250.f, vPos.y + 100.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 5.497787f));
		pObj->Transform()->SetRelativeScale(Vec3(1200.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisLineOnePref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 600.f, vPos.y + 300.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 5.497787f));
		pObj->Transform()->SetRelativeScale(Vec3(3000.f, 100.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (27 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 28 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 200.f, vPos.y + 50.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 3.926991f));
		pObj->Transform()->SetRelativeScale(Vec3(1500.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (29 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 30 == Animator2D()->GetCurFrameIndex())
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\deathcrisisthird.ogg")->Play(1, 1.f, false);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\death_crisis_2nd.ogg")->Play(1, 0.5f, false);
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		pObj->Transform()->SetRelativeScale(Vec3(1800.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisLineOnePref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 600.f, vPos.y - 300.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 2.356194f));
		pObj->Transform()->SetRelativeScale(Vec3(3000.f, 100.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (31 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 32 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 1.570796f));
		pObj->Transform()->SetRelativeScale(Vec3(900.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisBoomTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vWorldPos.x, vWorldPos.y, 300.f));
		pObj->Transform()->SetRelativeScale(Vec3(700.f, 800.f, 1.f));
		CreateObject(pObj, 0);
		m_LineTwo = true;
	}
	else if (33 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 34 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 200.f, vPos.y + 50.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.5f));
		pObj->Transform()->SetRelativeScale(Vec3(900.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisLineOnePref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 600.f, vPos.y - 300.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 5.497787f));
		pObj->Transform()->SetRelativeScale(Vec3(3000.f, 100.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (35 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 36 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 75.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 5.497787f));
		pObj->Transform()->SetRelativeScale(Vec3(1700.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (37 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 38 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 100.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 1.570796f));
		pObj->Transform()->SetRelativeScale(Vec3(900.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (39 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 40 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 120.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		pObj->Transform()->SetRelativeScale(Vec3(1200.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (41 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 42 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y - 20.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 2.356194f));
		pObj->Transform()->SetRelativeScale(Vec3(1200.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisLineOnePref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 600.f, vPos.y + 300.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 4.101524f));
		pObj->Transform()->SetRelativeScale(Vec3(3000.f, 100.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (43 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 44 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y - 100.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI / 1.5f));
		pObj->Transform()->SetRelativeScale(Vec3(1500.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (45 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 46 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 100.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 5.497787f));
		pObj->Transform()->SetRelativeScale(Vec3(1200.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (47 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 48 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 160.f, vPos.y + 50.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 3.926991f));
		pObj->Transform()->SetRelativeScale(Vec3(1500.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (49 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 50 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		pObj->Transform()->SetRelativeScale(Vec3(1800.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisBoomTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vWorldPos.x, vWorldPos.y, 300.f));
		pObj->Transform()->SetRelativeScale(Vec3(1100.f, 900.f, 1.f));
		CreateObject(pObj, 0);

		m_LineTwo = true;
	}
	else if (51 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 52 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 200.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 1.570796f));
		pObj->Transform()->SetRelativeScale(Vec3(900.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisLineOnePref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 600.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		pObj->Transform()->SetRelativeScale(Vec3(3000.f, 100.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (53 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 54 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 200.f, vPos.y + 50.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.5f));
		pObj->Transform()->SetRelativeScale(Vec3(900.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (55 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 56 == Animator2D()->GetCurFrameIndex())
	{
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\deathcrisissecond.ogg")->Play(1, 1.f, false);
		CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\death_crisis_finish.ogg")->Play(1, 1.f, false);
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 75.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 5.497787f));
		pObj->Transform()->SetRelativeScale(Vec3(1700.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		pObj = m_Prefabs.DeathCrisisBoomTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vWorldPos.x, vWorldPos.y, 300.f));
		pObj->Transform()->SetRelativeScale(Vec3(1000.f, 1000.f, 1.f));
		CreateObject(pObj, 0);

		pObj = m_Prefabs.DeathCrisisBigBoomPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x, vPos.y, 1.f));
		pObj->Transform()->SetRelativeScale(Vec3(500.f, 500.f, 1.f));
		CreateObject(pObj, 7);

		m_LineTwo = true;
	}
	else if (57 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 58 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 300.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 1.570796f));
		pObj->Transform()->SetRelativeScale(Vec3(900.f, 200.f, 1.f));
		CreateObject(pObj, 7);

		m_LineTwo = true;
	}
	else if (59 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 60 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x - 200.f, vPos.y, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		pObj->Transform()->SetRelativeScale(Vec3(1200.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (61 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
	else if (!m_LineTwo && 62 == Animator2D()->GetCurFrameIndex())
	{
		CGameObject* pObj = m_Prefabs.DeathCrisisLineTwoPref->Instantiate();
		pObj->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y - 20.f, vPos.z));
		pObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 2.356194f));
		pObj->Transform()->SetRelativeScale(Vec3(1200.f, 200.f, 1.f));
		CreateObject(pObj, 7);
		m_LineTwo = true;
	}
	else if (63 == Animator2D()->GetCurFrameIndex())
	{
		m_LineTwo = false;
	}
}

void CPlayerScript::SetSuperArmor(bool _Set)
{
	INFO& _info = GetOwner()->GetInfo();

	_info.bSuperArmor = _Set;
	m_Color = true;
}

void CPlayerScript::ChangeStateDoubleGunHawkStandBy()
{
	CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_dgunhawk_gun_02.ogg")->Play(1, 0.7f, true);
	Animator2D()->Play((int)ANIMATION_NUM::GUNHAWKSTANDBY, 1.f, false);
	SetState(PLAYER_STATE::GUNHAWKSTANDBY);
	m_GunHawkStandby = true;
}

void CPlayerScript::ChangeStatePunisherShoot()
{
	Animator2D()->Play((int)ANIMATION_NUM::PUNISHERSHOOT, 10.f, false);
	SetState(PLAYER_STATE::PUNISHERSHOOT);
}

void CPlayerScript::ChangeStateBBQReady()
{
	GetOwner()->GetChildren()[0]->SetActive(true);
	GetOwner()->GetChildren()[0]->Animator2D()->Play(0, 8.f, false);
	Animator2D()->Play((int)ANIMATION_NUM::BBQREADY, 8.f, false);
	SetState(PLAYER_STATE::BBQREADY);
}

void CPlayerScript::ChangeStateHit()
{
	if (PLAYER_STATE::HIT == m_State)
		return;

	SetState(PLAYER_STATE::HIT);
	Animator2D()->Play((int)ANIMATION_NUM::HIT, 10.f, false);
	GetOwner()->GetParent()->SetMove(false);
	CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\player\\gn_dmg_04.ogg")->Play(1, 1.f, false);
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