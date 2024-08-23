#include "pch.h"
#include "CPlayerScript.h"
#include "CMissileScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

#include "CPlayerMoveScript.h"
#include "CPlayerJumpScript.h"

CPlayerScript::CPlayerScript()
	: CScript(SCRIPT_TYPE::PLAYERSCRIPT)
	, m_MoveObject(nullptr)
	, m_JumpObject(nullptr)
	, m_MoveScript(nullptr)
	, m_JumpScript(nullptr)
	, m_Texture(nullptr)
	, m_MissilePref(nullptr)
	, m_Dir(OBJ_DIR::DIR_RIGHT)
	, m_State(STATE::IDLE)
	, m_Speed(500.f)
	, m_JumpHeight(0.f)
	, m_Time(0.f)
	, m_NextAttack(false)
	, m_Run(false)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT,"PlayerSpeed", &m_Speed);
	AddScriptParam(SCRIPT_PARAM::PREFAB, "Missile", &m_MissilePref);
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Begin()
{
	MeshRender()->GetDynamicMaterial();
	//m_MissilePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"MissilePref");

	m_MoveObject = CLevelMgr::GetInst()->FindObjectByName(L"PlayerMove");
	m_JumpObject = CLevelMgr::GetInst()->FindObjectByName(L"PlayerJump");

	m_MoveScript = (CPlayerMoveScript*)m_MoveObject->FindScriptByName(L"CPlayerMoveScript");
	m_JumpScript = (CPlayerJumpScript*)m_JumpObject->FindScriptByName(L"CPlayerJumpScript");


	Animator2D()->Play((int)IDLE, 5.f, true);
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
	case CPlayerScript::STATE::SK_1:
		break;
	case CPlayerScript::STATE::SK_2:
		break;
	case CPlayerScript::STATE::SK_3:
		break;
	case CPlayerScript::STATE::SK_4:
		break;
	case CPlayerScript::STATE::SK_5:
		break;
	case CPlayerScript::STATE::SK_6:
		break;
	case CPlayerScript::STATE::SK_7:
		break;
	case CPlayerScript::STATE::SK_8:
		break;
	case CPlayerScript::STATE::SK_9:
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

	Transform()->SetRelativePos(Vec3(vMovePos.x, vMovePos.y + fJumpHeight, vMovePos.z));
}

void CPlayerScript::Idle()
{
	Vec3 vRot = Transform()->GetRelativeRotation();

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
		m_Dir = OBJ_DIR::DIR_LEFT;
		m_State = STATE::MOVE;	
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
		m_Dir = OBJ_DIR::DIR_LEFT;
		m_State = STATE::MOVE;
		vRot.y = XM_PI;

		m_State = STATE::MOVE;
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
	}
	if (KEY_TAP(KEY::C))
	{
		m_State = STATE::JUMP;
		Animator2D()->Play((int)STATE::JUMP, 5.f, false);
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

	if (KEY_TAP(KEY::X))
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
}

void CPlayerScript::AT1()
{
	if (KEY_TAP(KEY::X) && !Animator2D()->IsFinish())
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
		Animator2D()->Play((int)AT_3, 17.f, true);
		m_State = STATE::AT_3;
		m_NextAttack = false;
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
	if (Animator2D()->IsFinish())
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);	
		SetMoveable(true);
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
	if (KEY_RELEASED(KEY::LEFT))
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
	}
	else if (KEY_RELEASED(KEY::RIGHT))
	{
		m_State = STATE::IDLE;
		Animator2D()->Play((int)IDLE, 5.f, true);
	}

	if (KEY_TAP(KEY::C))
	{
		m_State = STATE::JUMP;
		Animator2D()->Play((int)STATE::JUMP, 5.f, false);
	}
}

void CPlayerScript::Dead()
{
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