#include "pch.h"
#include "CPlayerJumpScript.h"

CPlayerJumpScript::CPlayerJumpScript()
	: CScript(SCRIPT_TYPE::PLAYERJUMPSCRIPT)
	, m_NormalJump(false)
	, m_Jump(false)
{
	SetName(L"CPlayerJumpScript");
}

CPlayerJumpScript::~CPlayerJumpScript()
{
}

void CPlayerJumpScript::Begin()
{
}

void CPlayerJumpScript::Tick()
{
	if(KEY_TAP(KEY::C) && !m_Jump)
		Jump();

	AxisCheck();
}

void CPlayerJumpScript::Jump()
{
	m_NormalJump = true;
	Rigidbody()->Jump();
	SetJump(true);
}

void CPlayerJumpScript::AxisCheck()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (!Rigidbody()->IsGround() && vPos.y < 0.f)
	{
		Rigidbody()->SetGround(true);
		Transform()->SetRelativePos(Vec3(0.f,0.f,0.f));
		SetJump(false);
		m_NormalJump = false;
	}
}

void CPlayerJumpScript::SaveToFile(FILE* _pFile)
{
}

void CPlayerJumpScript::LoadFromFile(FILE* _pFile)
{
}