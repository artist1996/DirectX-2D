#include "pch.h"
#include "CScriptMgr.h"

#include "CBuffScript.h"
#include "CCameraMoveScript.h"
#include "CDoubleGunHawkScript.h"
#include "CGunHawkExplodeScript.h"
#include "CHammerScript.h"
#include "CHeadShotEffectScript.h"
#include "CHeadShotScript.h"
#include "CJackSpikeScript.h"
#include "CMachKickScript.h"
#include "CMuzzleScript.h"
#include "CPistolScript.h"
#include "CPlatformScript.h"
#include "CPlayerJumpScript.h"
#include "CPlayerMoveScript.h"
#include "CPlayerScript.h"
#include "CRandomShootScript.h"
#include "CRisingShotScript.h"
#include "CWindmillScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBuffScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CDoubleGunHawkScript");
	_vec.push_back(L"CGunHawkExplodeScript");
	_vec.push_back(L"CHammerScript");
	_vec.push_back(L"CHeadShotEffectScript");
	_vec.push_back(L"CHeadShotScript");
	_vec.push_back(L"CJackSpikeScript");
	_vec.push_back(L"CMachKickScript");
	_vec.push_back(L"CMuzzleScript");
	_vec.push_back(L"CPistolScript");
	_vec.push_back(L"CPlatformScript");
	_vec.push_back(L"CPlayerJumpScript");
	_vec.push_back(L"CPlayerMoveScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CRandomShootScript");
	_vec.push_back(L"CRisingShotScript");
	_vec.push_back(L"CWindmillScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBuffScript" == _strScriptName)
		return new CBuffScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CDoubleGunHawkScript" == _strScriptName)
		return new CDoubleGunHawkScript;
	if (L"CGunHawkExplodeScript" == _strScriptName)
		return new CGunHawkExplodeScript;
	if (L"CHammerScript" == _strScriptName)
		return new CHammerScript;
	if (L"CHeadShotEffectScript" == _strScriptName)
		return new CHeadShotEffectScript;
	if (L"CHeadShotScript" == _strScriptName)
		return new CHeadShotScript;
	if (L"CJackSpikeScript" == _strScriptName)
		return new CJackSpikeScript;
	if (L"CMachKickScript" == _strScriptName)
		return new CMachKickScript;
	if (L"CMuzzleScript" == _strScriptName)
		return new CMuzzleScript;
	if (L"CPistolScript" == _strScriptName)
		return new CPistolScript;
	if (L"CPlatformScript" == _strScriptName)
		return new CPlatformScript;
	if (L"CPlayerJumpScript" == _strScriptName)
		return new CPlayerJumpScript;
	if (L"CPlayerMoveScript" == _strScriptName)
		return new CPlayerMoveScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CRandomShootScript" == _strScriptName)
		return new CRandomShootScript;
	if (L"CRisingShotScript" == _strScriptName)
		return new CRisingShotScript;
	if (L"CWindmillScript" == _strScriptName)
		return new CWindmillScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BUFFSCRIPT:
		return new CBuffScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::DOUBLEGUNHAWKSCRIPT:
		return new CDoubleGunHawkScript;
		break;
	case (UINT)SCRIPT_TYPE::GUNHAWKEXPLODESCRIPT:
		return new CGunHawkExplodeScript;
		break;
	case (UINT)SCRIPT_TYPE::HAMMERSCRIPT:
		return new CHammerScript;
		break;
	case (UINT)SCRIPT_TYPE::HEADSHOTEFFECTSCRIPT:
		return new CHeadShotEffectScript;
		break;
	case (UINT)SCRIPT_TYPE::HEADSHOTSCRIPT:
		return new CHeadShotScript;
		break;
	case (UINT)SCRIPT_TYPE::JACKSPIKESCRIPT:
		return new CJackSpikeScript;
		break;
	case (UINT)SCRIPT_TYPE::MACHKICKSCRIPT:
		return new CMachKickScript;
		break;
	case (UINT)SCRIPT_TYPE::MUZZLESCRIPT:
		return new CMuzzleScript;
		break;
	case (UINT)SCRIPT_TYPE::PISTOLSCRIPT:
		return new CPistolScript;
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
	case (UINT)SCRIPT_TYPE::RANDOMSHOOTSCRIPT:
		return new CRandomShootScript;
		break;
	case (UINT)SCRIPT_TYPE::RISINGSHOTSCRIPT:
		return new CRisingShotScript;
		break;
	case (UINT)SCRIPT_TYPE::WINDMILLSCRIPT:
		return new CWindmillScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BUFFSCRIPT:
		return L"CBuffScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::DOUBLEGUNHAWKSCRIPT:
		return L"CDoubleGunHawkScript";
		break;

	case SCRIPT_TYPE::GUNHAWKEXPLODESCRIPT:
		return L"CGunHawkExplodeScript";
		break;

	case SCRIPT_TYPE::HAMMERSCRIPT:
		return L"CHammerScript";
		break;

	case SCRIPT_TYPE::HEADSHOTEFFECTSCRIPT:
		return L"CHeadShotEffectScript";
		break;

	case SCRIPT_TYPE::HEADSHOTSCRIPT:
		return L"CHeadShotScript";
		break;

	case SCRIPT_TYPE::JACKSPIKESCRIPT:
		return L"CJackSpikeScript";
		break;

	case SCRIPT_TYPE::MACHKICKSCRIPT:
		return L"CMachKickScript";
		break;

	case SCRIPT_TYPE::MUZZLESCRIPT:
		return L"CMuzzleScript";
		break;

	case SCRIPT_TYPE::PISTOLSCRIPT:
		return L"CPistolScript";
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

	case SCRIPT_TYPE::RANDOMSHOOTSCRIPT:
		return L"CRandomShootScript";
		break;

	case SCRIPT_TYPE::RISINGSHOTSCRIPT:
		return L"CRisingShotScript";
		break;

	case SCRIPT_TYPE::WINDMILLSCRIPT:
		return L"CWindmillScript";
		break;

	}
	return nullptr;
}