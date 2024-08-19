#include "pch.h"
#include "CScriptMgr.h"

#include "CCameraMoveScript.h"
#include "CMissileScript.h"
#include "CPlatformScript.h"
#include "CPlayerJumpScript.h"
#include "CPlayerMoveScript.h"
#include "CPlayerScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CPlatformScript");
	_vec.push_back(L"CPlayerJumpScript");
	_vec.push_back(L"CPlayerMoveScript");
	_vec.push_back(L"CPlayerScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CPlatformScript" == _strScriptName)
		return new CPlatformScript;
	if (L"CPlayerJumpScript" == _strScriptName)
		return new CPlayerJumpScript;
	if (L"CPlayerMoveScript" == _strScriptName)
		return new CPlayerMoveScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::PLATFORMSCRIPT:
		return new CPlatformScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERJUMPSCRIPT:
		return new CPlayerJumpScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERMOVESCRIPT:
		return new CPlayerMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::PLATFORMSCRIPT:
		return L"CPlatformScript";
		break;

	case SCRIPT_TYPE::PLAYERJUMPSCRIPT:
		return L"CPlayerJumpScript";
		break;

	case SCRIPT_TYPE::PLAYERMOVESCRIPT:
		return L"CPlayerMoveScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	}
	return nullptr;
}