#include "pch.h"
#include "CWindmillScript.h"

CWindmillScript::CWindmillScript()
	: CScript(SCRIPT_TYPE::WINDMILLSCRIPT)
{
}

CWindmillScript::~CWindmillScript()
{
}

void CWindmillScript::Begin()
{
	Animator2D()->Play(0, 20.f, false);
	Collider2D()->SetActive(false);
}

void CWindmillScript::Tick()
{
	if (Animator2D()->IsFinish())
	{
		DeleteObject(GetOwner());
	}
}