#include "pch.h"
#include "CPlayerJumpScript.h"

CPlayerJumpScript::CPlayerJumpScript()
	: CScript(SCRIPT_TYPE::PLAYERJUMPSCRIPT)
{
}

CPlayerJumpScript::~CPlayerJumpScript()
{
}

void CPlayerJumpScript::Begin()
{
}

void CPlayerJumpScript::Tick()
{
	if(KEY_TAP(KEY::C))
		Jump();

	AxisCheck();
}

void CPlayerJumpScript::SaveToFile(FILE* _pFile)
{
}

void CPlayerJumpScript::LoadFromFile(FILE* _pFile)
{
}

void CPlayerJumpScript::Jump()
{
	Rigidbody()->Jump();
}

void CPlayerJumpScript::AxisCheck()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (!Rigidbody()->IsGround() && vPos.y < 0.f)
	{
		Rigidbody()->SetGround(true);
		Transform()->SetRelativePos(Vec3(0.f,0.f,0.f));
	}
}
