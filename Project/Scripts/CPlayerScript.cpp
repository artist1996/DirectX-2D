#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

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
	, m_Dir(OBJ_DIR::DIR_LEFT)
	, m_State(STATE::IDLE)
	, m_Speed(500.f)
	, m_JumpHeight(0.f)
	, m_Time(0.f)
	, m_NextAttack(false)
	, m_Run(false)
	, m_Spawn(false)
	, m_Muzzel(true)
{
	SetName(L"CPlayerScript");

	AddScriptParam(SCRIPT_PARAM::FLOAT,"PlayerSpeed", &m_Speed);
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


	m_MoveObject = CLevelMgr::GetInst()->FindObjectByName(L"PlayerMove");
	m_JumpObject = CLevelMgr::GetInst()->FindObjectByName(L"PlayerJump");
	
	m_MoveScript = (CPlayerMoveScript*)m_MoveObject->FindScriptByName(L"CPlayerMoveScript");
	m_JumpScript = (CPlayerJumpScript*)m_JumpObject->FindScriptByName(L"CPlayerJumpScript");
	
	Animator2D()->Play((int)IDLE, 5.f, true);

	Collider2D()->SetOffset(Vec3(0.f, -0.44f, 1.f));
}

void CPlayerScript::Tick()
{
	Vec3 vMovePos = m_MoveObject->Transform()->GetRelativePos();
	float fJumpHeight = m_JumpObject->Transform()->GetRelativePos().y;

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

	Transform()->SetRelativePos(Vec3(vMovePos.x, vMovePos.y + fJumpHeight, vMovePos.z + fJumpHeight));
}

void CPlayerScript::Idle()
{
	Vec3 vRot = Transform()->GetRelativeRotation();

	Collider2D()->SetOffset(Vec3(0.f, -0.44f, 1.f));

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
		m_State = STATE::AT_1;
		Animator2D()->Play((int)STATE::AT_1, 15.f, false);
		SetMoveable(false);

		CreatePistol();
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

	if (KEY_TAP(KEY::Z))
	{
		SetState(STATE::SK_1);
		Animator2D()->Play((int)ANIMATION_NUM::JACKSPIKE, 11.f, false);
		SetMoveable(false);
	}
	
	if (KEY_TAP(KEY::S))
	{
		SetState(STATE::SK_2);
		Animator2D()->Play((int)ANIMATION_NUM::AT_3, 20.f, false);
		SetMoveable(false);
	}

	if (KEY_TAP(KEY::A))
	{
		SetState(STATE::SK_3);
		Animator2D()->Play((int)ANIMATION_NUM::AT_3, 25.f, false);
		SetMoveable(false);
	}

	if (KEY_TAP(KEY::G))
	{
		SetState(STATE::SK_4);
		Animator2D()->Play((int)ANIMATION_NUM::RANDOMSHOT, 30.f, false);
		SetMoveable(false);

		//Vec3 vPos = Transform()->GetWorldPos();
	}

	if (KEY_TAP(KEY::SPACE))
	{
		SetState(STATE::SK_5);
		Animator2D()->Play((int)ANIMATION_NUM::DEATHBYREVOLVER, 17.f, false);
		SetMoveable(false);

		CGameObject* pBuff = m_BuffPref->Instantiate();

		Vec3 vPos = Transform()->GetWorldPos();
		CGameObject* pCam = CLevelMgr::GetInst()->FindObjectByName(L"MainCamera");
		
		pBuff->Transform()->SetRelativePos(Vec3(vPos.x, pCam->Transform()->GetWorldPos().y, vPos.z + 100.f));
		pBuff->Transform()->SetRelativeScale(Vec3(470.f, 768.f, 1.f));
		pBuff->Transform()->SetRelativeRotation(vRot);
		pBuff->MeshRender()->GetMaterial()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DAlphaBlendShader"));
		
		CreateObject(pBuff, 0);
	}

	if (KEY_TAP(KEY::D))
	{
		SetState(STATE::SK_6);
		Animator2D()->Play((int)ANIMATION_NUM::WINDMILL, 20.f, false);
		CreateWindMill();
	}

	if (KEY_TAP(KEY::F))
	{
		SetState(STATE::SK_7);
		Animator2D()->Play((int)ANIMATION_NUM::MACHKICK, 20.f, false);
		SetMoveable(false);
	}
	if (KEY_TAP(KEY::Q))
	{
		SetState(STATE::GUNHAWKSHOOT);
		Animator2D()->Play((int)ANIMATION_NUM::GUNHAWKSHOOT, 15.f, false);
		SetMoveable(false);
		CreateGunHawkFirst();
	}

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
	}

	else if (KEY_TAP(KEY::X))
	{
		m_State = STATE::AT_1;
		Animator2D()->Play((int)STATE::AT_1, 15.f, false);
		SetMoveable(false);
	}

	// JUMP
	if (KEY_TAP(KEY::C))
	{
		m_State = STATE::JUMP;
		Animator2D()->Play((int)STATE::JUMP, 5.f, false);
	}

	// SKILL
	if (KEY_TAP(KEY::Z))
	{
		SetState(STATE::SK_1);
		Animator2D()->Play((int)ANIMATION_NUM::JACKSPIKE, 7.f, false);
		SetMoveable(false);
	}

	if (KEY_TAP(KEY::S))
	{
		SetState(STATE::SK_2);
		Animator2D()->Play((int)ANIMATION_NUM::AT_3, 20.f, false);
		SetMoveable(false);
	}

	if (KEY_TAP(KEY::A))
	{
		SetState(STATE::SK_3);
		Animator2D()->Play((int)ANIMATION_NUM::DG_AT3, 25.f, false);
		CreateHeadShotEffect();
		SetMoveable(false);
	}

	if (KEY_TAP(KEY::G))
	{
		SetState(STATE::SK_4);
		Animator2D()->Play((int)ANIMATION_NUM::RANDOMSHOT, 25.f, false);
		SetMoveable(false);
	}

	if (KEY_TAP(KEY::D))
	{
		SetState(STATE::SK_6);
		Animator2D()->Play((int)ANIMATION_NUM::WINDMILL, 20.f, false);
	}

	if (KEY_TAP(KEY::F))
	{
		SetState(STATE::SK_7);
		Animator2D()->Play((int)ANIMATION_NUM::MACHKICK, 20.f, false);
		SetMoveable(false);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		SetState(STATE::SK_5);
		Animator2D()->Play((int)ANIMATION_NUM::DEATHBYREVOLVER, 17.f, false);
		SetMoveable(false);
	}
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
		CreateHammerOfRevolver();
	}
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
		CreateHammerOfRevolver();
	}

	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		Animator2D()->Play((int)IDLE, 5.f, true);
		m_State = STATE::IDLE;
		SetMoveable(true);
	}
}

void CPlayerScript::AT3()
{
	//if (KEY_TAP(KEY::X) && !Animator2D()->IsFinish())
	//{
	//	m_NextAttack = true;
	//}
	//
	//if (m_NextAttack && Animator2D()->IsFinish())
	//{
	//	Animator2D()->Play((int)AT_2, 17.f, true);
	//	m_State = STATE::AT_4;
	//	m_NextAttack = false;
	//	CreatePistol();
	//	return;
	//}
	//
	//else if (!m_NextAttack && Animator2D()->IsFinish())
	//{
	//	Animator2D()->Play((int)IDLE, 5.f, true);
	//	m_State = STATE::IDLE;
	//	SetMoveable(true);
	//}

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
}

void CPlayerScript::AT_DG1()
{
	if (KEY_TAP(KEY::X))
	{
		m_NextAttack = true;
	}
	
	if(m_NextAttack && Animator2D()->IsFinish())
	{
		if (KEY_PRESSED(KEY::DOWN))
		{
			m_State = STATE::DG_AT2;
			Animator2D()->Play((int)STATE::DG_AT2, 10.f, true);
		}
		else if(KEY_RELEASED(KEY::DOWN))
		{
			m_State = STATE::AT_2;
			Animator2D()->Play((int)STATE::AT_2, 10.f, true);
		}

		m_NextAttack = false;
	}
	
	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)STATE::IDLE, 5.f, true);
		SetMoveable(true);
	}
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
}

void CPlayerScript::AT_DG3()
{
	if (KEY_TAP(KEY::X))
	{
		m_NextAttack = true;
	}

	if (m_NextAttack && Animator2D()->IsFinish())
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
		m_NextAttack = false;
	}

	else if (!m_NextAttack && Animator2D()->IsFinish())
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
		SetMoveable(true);
	}
}

void CPlayerScript::AT_DG4()
{
	if (Animator2D()->IsFinish())
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
		SetMoveable(true);
	}
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
}

void CPlayerScript::RisingShot()
{
	if (Animator2D()->IsFinish())
	{
		SetState(STATE::IDLE);
		Animator2D()->Play((int)ANIMATION_NUM::IDLE, 5.f, true);
		SetMoveable(true);
	}
}

void CPlayerScript::HeadShot()
{
	if (m_Spawn && 3 <= Animator2D()->GetCurFrameIndex())
	{
		CreateHeadShot();
		CreateHeadShotEffect();
		m_Spawn = false;
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
}

void CPlayerScript::GunHawkStandBy()
{
	if (!Animator2D()->IsFinish() && KEY_TAP(KEY::Q))
	{
		SetState(STATE::GUNHAWKLASTSHOOT);
		Animator2D()->Play((int)ANIMATION_NUM::GUNHAWKSHOOT, 15.f, true);
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
}

void CPlayerScript::Stylish()
{
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
		//pObject->Animator2D()->Play(0, 20.f, false);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_2PI, 0.f));

		CreateObject(pObject, 7);
		//pObject->Animator2D()->Play(0, 20.f, false);

		m_Spawn = false;
	}

	if (CurIdx == 1)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 3)
	{
		//CGameObject* pObject = m_RandomShootPref->Instantiate();
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 60.f, vPos.y + 130.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 1.7f));
		CreateObject(pObject, 7);

		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		//pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = pObject = m_RandomShootPref->Instantiate();
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 100.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 1.75f));
		CreateObject(pObject, 7);

		//pObject = pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = pObject = m_RandomShootPref->Instantiate();
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		CreateObject(pObject, 7);

		//pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = pObject = m_RandomShootPref->Instantiate();
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		CreateObject(pObject, 7);

		//pObject = m_RandomShootPref->Instantiate(); 
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
		//CGameObject* pObject = m_RandomShootPref->Instantiate();
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 60.f, vPos.y + 130.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 1.7f));
		CreateObject(pObject, 7);

		//pObject = m_RandomShootPref->Instantiate(); 
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
		//CGameObject* pObject = m_RandomShootPref->Instantiate(); 
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 100.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 1.75f));
		CreateObject(pObject, 7);

		//pObject = m_RandomShootPref->Instantiate(); 
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
		//CGameObject* pObject = pObject = m_RandomShootPref->Instantiate(); 
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		CreateObject(pObject, 7);

		//pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = m_RandomShootPref->Instantiate();
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		CreateObject(pObject, 7);

		//pObject = m_RandomShootPref->Instantiate(); 
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
		//CGameObject* pObject = m_RandomShootPref->Instantiate(); 
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 60.f, vPos.y + 130.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 1.7f));
		CreateObject(pObject, 7);

		//pObject = m_RandomShootPref->Instantiate(); 
		pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x + 60.f, vPos.y - 130.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI * 1.7f));
		CreateObject(pObject, 7);
		//pObject->Animator2D()->Play(0, 20.f, true);

		m_Spawn = false;
	}

	if (CurIdx == 28)
		m_Spawn = true;

	if (m_Spawn && CurIdx == 30)
	{
		//CGameObject* pObject = m_RandomShootPref->Instantiate();
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 100.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, XM_PI * 1.75f));
		CreateObject(pObject, 7);

		//pObject = m_RandomShootPref->Instantiate();
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
		//CGameObject* pObject = m_RandomShootPref->Instantiate(); 
		CGameObject* pObject = CObjectPoolMgr::GetInst()->GetRandomShoot();
		pObject->Transform()->SetRelativePos(Vec3(vPos.x - 150.f, vPos.y + 50.f, vPos.z));
		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));
		pObject->Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		CreateObject(pObject, 7);

		//pObject = m_RandomShootPref->Instantiate();
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

void CPlayerScript::CreateWindMill()
{
	CGameObject* pObject = m_WindmillPref->Instantiate();
	Vec3 vPos = Transform()->GetWorldPos();
	pObject->Transform()->SetRelativePos(Vec3(vPos.x, vPos.y - 20.f, vPos.z - 1.f));

	CreateObject(pObject, 7);
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

void CPlayerScript::CreateGunHawkFirst()
{
	Vec3 vPos = Transform()->GetWorldPos();

	CGameObject* GunHawkUp = m_GunHawkFirstUpPref->Instantiate();
	CGameObject* GunHawkDown = m_GunHawkFirstDownPref->Instantiate();

	if(OBJ_DIR::DIR_LEFT == m_Dir)
	{
		GunHawkUp->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y - 5.f, vPos.z));
		GunHawkDown->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y - 5.f, vPos.z));
		GunHawkUp->Transform()->SetRelativeRotation(Vec3(XM_PI / 3.f, 0.f, 0.f));
		GunHawkDown->Transform()->SetRelativeRotation(Vec3(XM_PI / 3.f, 0.f, 0.f));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		GunHawkUp->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y - 5.f, vPos.z));
		GunHawkDown->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y - 5.f, vPos.z));
		GunHawkUp->Transform()->SetRelativeRotation(Vec3(XM_PI / 3.f, 0.f, 0.f));
		GunHawkDown->Transform()->SetRelativeRotation(Vec3(XM_PI / 3.f, 0.f, 0.f));
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
		GunHawkUp->Transform()->SetRelativeRotation(Vec3(XM_PI / 2.65f, 0.f, 0.f));
		GunHawkDown->Transform()->SetRelativeRotation(Vec3(XM_PI / 2.65f, 0.f, 0.f));
	}

	else if (OBJ_DIR::DIR_RIGHT == m_Dir)
	{
		GunHawkUp->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		GunHawkDown->Transform()->SetRelativePos(Vec3(vPos.x + 50.f, vPos.y, vPos.z));
		GunHawkUp->Transform()->SetRelativeRotation(Vec3(XM_PI / 2.65f, 0.f, 0.f));
		GunHawkDown->Transform()->SetRelativeRotation(Vec3(XM_PI / 2.65f, 0.f, 0.f));
	}

	GunHawkUp->SetDir(m_Dir);
	GunHawkDown->SetDir(m_Dir);
	GunHawkUp->SetInitPos(vPos);
	GunHawkDown->SetInitPos(vPos);
	CreateObject(GunHawkUp, 7);
	CreateObject(GunHawkDown, 7);
}

void CPlayerScript::ChangeStateDoubleGunHawkStandBy()
{
	Animator2D()->Play((int)ANIMATION_NUM::GUNHAWKSTANDBY, 1.f, false);
	SetState(STATE::GUNHAWKSTANDBY);
	m_MoveScript->SetState(MOVE_STATE::ST_FORCE);
	//m_MoveScript->Rigidbody()->AddForce(Vec3(10000.f, 0.f, 0.f));
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