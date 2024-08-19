#include "pch.h"
#include "CPlayerScript.h"

#include "CMissileScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

CPlayerScript::CPlayerScript()
	: CScript(SCRIPT_TYPE::PLAYERSCRIPT)
	, m_MoveObject(nullptr)
	, m_JumpObject(nullptr)
	, m_Texture(nullptr)
	, m_MissilePref(nullptr)
	, m_Dir(OBJ_DIR::DIR_RIGHT)
	, m_State(STATE::IDLE)
	, m_Speed(500.f)
	, m_JumpHeight(0.f)
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
		//Jump();
		break;
	case CPlayerScript::STATE::RUN:
		Run();
		break;
	case CPlayerScript::STATE::DEAD:
		Dead();
		break;
	case CPlayerScript::STATE::AT_1:
		break;
	case CPlayerScript::STATE::AT_2:
		break;
	case CPlayerScript::STATE::AT_3:
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
	
	Transform()->SetRelativePos(Vec3(vMovePos.x, vMovePos.y + fJumpHeight, vMovePos.z));
}

void CPlayerScript::Idle()
{
	Vec3 vRot = Transform()->GetRelativeRotation();

	if (KEY_TAP(KEY::LEFT))
	{
		m_Dir = OBJ_DIR::DIR_LEFT;
		m_State = STATE::MOVE;
		vRot = Vec3(0.f, 0.f, 0.f);
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}
	else if (KEY_PRESSED(KEY::LEFT))
	{
		m_Dir = OBJ_DIR::DIR_LEFT;
		m_State = STATE::MOVE;
		vRot = Vec3(0.f, 0.f, 0.f);
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		m_Dir = OBJ_DIR::DIR_LEFT;
		m_State = STATE::MOVE;	
		vRot.x = XM_PI;
		vRot.z = XM_PI;
		Animator2D()->Play((int)STATE::MOVE, 8.f, true);
	}
	else if (KEY_PRESSED(KEY::RIGHT))
	{
		m_Dir = OBJ_DIR::DIR_LEFT;
		m_State = STATE::MOVE;
		vRot.x = XM_PI;
		vRot.z = XM_PI;
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
		//Animator2D()->Play((int)STATE::AT_1, 15.f, true);
	}
	if (KEY_TAP(KEY::C))
	{
		//Animator2D()->Play((int)STATE::JUMP, 15.f, true);
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

	// SKILL

	// JUMP
	if (KEY_TAP(KEY::C))
	{
		//Rigidbody()->Jump();
		//Rigidbody()->UseGravity(true);
		////Animator2D()->Play((int)STATE::JUMP, 15.f, true);
	}
}

void CPlayerScript::Run()
{
}

void CPlayerScript::Jump()
{
	
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

void CPlayerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}
