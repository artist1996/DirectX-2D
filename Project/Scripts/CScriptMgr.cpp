#include "pch.h"
#include "CScriptMgr.h"

#include "CBuffScript.h"
#include "CCameraMoveScript.h"
#include "CDiagonalHeadShotScript.h"
#include "CDiagonalPistolScript.h"
#include "CDoubleGunHawkScript.h"
#include "CDummyScript.h"
#include "CEffectScript.h"
#include "CGunHawkExplodeScript.h"
#include "CHammerScript.h"
#include "CHeadShotEffectScript.h"
#include "CHeadShotScript.h"
#include "CHyungteoScript.h"
#include "CIroncageScript.h"
#include "CJackSpikeScript.h"
#include "CMachKickScript.h"
#include "CMeltKnightScript.h"
#include "CMonsterMoveScript.h"
#include "CMuzzleScript.h"
#include "CParticleScript.h"
#include "CPistolScript.h"
#include "CPlatformScript.h"
#include "CPlayerMoveScript.h"
#include "CPlayerScript.h"
#include "CRandomShootScript.h"
#include "CRisingShotScript.h"
#include "CSeriaRoomGateScript.h"
#include "CSeriaScript.h"
#include "CWindmillScript.h"
#include "LeshphonGateScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBuffScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CDiagonalHeadShotScript");
	_vec.push_back(L"CDiagonalPistolScript");
	_vec.push_back(L"CDoubleGunHawkScript");
	_vec.push_back(L"CDummyScript");
	_vec.push_back(L"CEffectScript");
	_vec.push_back(L"CGunHawkExplodeScript");
	_vec.push_back(L"CHammerScript");
	_vec.push_back(L"CHeadShotEffectScript");
	_vec.push_back(L"CHeadShotScript");
	_vec.push_back(L"CHyungteoScript");
	_vec.push_back(L"CIroncageScript");
	_vec.push_back(L"CJackSpikeScript");
	_vec.push_back(L"CMachKickScript");
	_vec.push_back(L"CMeltKnightScript");
	_vec.push_back(L"CMonsterMoveScript");
	_vec.push_back(L"CMuzzleScript");
	_vec.push_back(L"CParticleScript");
	_vec.push_back(L"CPistolScript");
	_vec.push_back(L"CPlatformScript");
	_vec.push_back(L"CPlayerMoveScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CRandomShootScript");
	_vec.push_back(L"CRisingShotScript");
	_vec.push_back(L"CSeriaRoomGateScript");
	_vec.push_back(L"CSeriaScript");
	_vec.push_back(L"CWindmillScript");
	_vec.push_back(L"LeshphonGateScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBuffScript" == _strScriptName)
		return new CBuffScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CDiagonalHeadShotScript" == _strScriptName)
		return new CDiagonalHeadShotScript;
	if (L"CDiagonalPistolScript" == _strScriptName)
		return new CDiagonalPistolScript;
	if (L"CDoubleGunHawkScript" == _strScriptName)
		return new CDoubleGunHawkScript;
	if (L"CDummyScript" == _strScriptName)
		return new CDummyScript;
	if (L"CEffectScript" == _strScriptName)
		return new CEffectScript;
	if (L"CGunHawkExplodeScript" == _strScriptName)
		return new CGunHawkExplodeScript;
	if (L"CHammerScript" == _strScriptName)
		return new CHammerScript;
	if (L"CHeadShotEffectScript" == _strScriptName)
		return new CHeadShotEffectScript;
	if (L"CHeadShotScript" == _strScriptName)
		return new CHeadShotScript;
	if (L"CHyungteoScript" == _strScriptName)
		return new CHyungteoScript;
	if (L"CIroncageScript" == _strScriptName)
		return new CIroncageScript;
	if (L"CJackSpikeScript" == _strScriptName)
		return new CJackSpikeScript;
	if (L"CMachKickScript" == _strScriptName)
		return new CMachKickScript;
	if (L"CMeltKnightScript" == _strScriptName)
		return new CMeltKnightScript;
	if (L"CMonsterMoveScript" == _strScriptName)
		return new CMonsterMoveScript;
	if (L"CMuzzleScript" == _strScriptName)
		return new CMuzzleScript;
	if (L"CParticleScript" == _strScriptName)
		return new CParticleScript;
	if (L"CPistolScript" == _strScriptName)
		return new CPistolScript;
	if (L"CPlatformScript" == _strScriptName)
		return new CPlatformScript;
	if (L"CPlayerMoveScript" == _strScriptName)
		return new CPlayerMoveScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CRandomShootScript" == _strScriptName)
		return new CRandomShootScript;
	if (L"CRisingShotScript" == _strScriptName)
		return new CRisingShotScript;
	if (L"CSeriaRoomGateScript" == _strScriptName)
		return new CSeriaRoomGateScript;
	if (L"CSeriaScript" == _strScriptName)
		return new CSeriaScript;
	if (L"CWindmillScript" == _strScriptName)
		return new CWindmillScript;
	if (L"LeshphonGateScript" == _strScriptName)
		return new LeshphonGateScript;
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
	case (UINT)SCRIPT_TYPE::DIAGONALHEADSHOTSCRIPT:
		return new CDiagonalHeadShotScript;
		break;
	case (UINT)SCRIPT_TYPE::DIAGONALPISTOLSCRIPT:
		return new CDiagonalPistolScript;
		break;
	case (UINT)SCRIPT_TYPE::DOUBLEGUNHAWKSCRIPT:
		return new CDoubleGunHawkScript;
		break;
	case (UINT)SCRIPT_TYPE::DUMMYSCRIPT:
		return new CDummyScript;
		break;
	case (UINT)SCRIPT_TYPE::EFFECTSCRIPT:
		return new CEffectScript;
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
	case (UINT)SCRIPT_TYPE::HYUNGTEOSCRIPT:
		return new CHyungteoScript;
		break;
	case (UINT)SCRIPT_TYPE::IRONCAGESCRIPT:
		return new CIroncageScript;
		break;
	case (UINT)SCRIPT_TYPE::JACKSPIKESCRIPT:
		return new CJackSpikeScript;
		break;
	case (UINT)SCRIPT_TYPE::MACHKICKSCRIPT:
		return new CMachKickScript;
		break;
	case (UINT)SCRIPT_TYPE::MELTKNIGHTSCRIPT:
		return new CMeltKnightScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERMOVESCRIPT:
		return new CMonsterMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::MUZZLESCRIPT:
		return new CMuzzleScript;
		break;
	case (UINT)SCRIPT_TYPE::PARTICLESCRIPT:
		return new CParticleScript;
		break;
	case (UINT)SCRIPT_TYPE::PISTOLSCRIPT:
		return new CPistolScript;
		break;
	case (UINT)SCRIPT_TYPE::PLATFORMSCRIPT:
		return new CPlatformScript;
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
	case (UINT)SCRIPT_TYPE::SERIAROOMGATESCRIPT:
		return new CSeriaRoomGateScript;
		break;
	case (UINT)SCRIPT_TYPE::SERIASCRIPT:
		return new CSeriaScript;
		break;
	case (UINT)SCRIPT_TYPE::WINDMILLSCRIPT:
		return new CWindmillScript;
		break;
	case (UINT)SCRIPT_TYPE::ESHPHONGATESCRIPT:
		return new LeshphonGateScript;
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

	case SCRIPT_TYPE::DIAGONALHEADSHOTSCRIPT:
		return L"CDiagonalHeadShotScript";
		break;

	case SCRIPT_TYPE::DIAGONALPISTOLSCRIPT:
		return L"CDiagonalPistolScript";
		break;

	case SCRIPT_TYPE::DOUBLEGUNHAWKSCRIPT:
		return L"CDoubleGunHawkScript";
		break;

	case SCRIPT_TYPE::DUMMYSCRIPT:
		return L"CDummyScript";
		break;

	case SCRIPT_TYPE::EFFECTSCRIPT:
		return L"CEffectScript";
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

	case SCRIPT_TYPE::HYUNGTEOSCRIPT:
		return L"CHyungteoScript";
		break;

	case SCRIPT_TYPE::IRONCAGESCRIPT:
		return L"CIroncageScript";
		break;

	case SCRIPT_TYPE::JACKSPIKESCRIPT:
		return L"CJackSpikeScript";
		break;

	case SCRIPT_TYPE::MACHKICKSCRIPT:
		return L"CMachKickScript";
		break;

	case SCRIPT_TYPE::MELTKNIGHTSCRIPT:
		return L"CMeltKnightScript";
		break;

	case SCRIPT_TYPE::MONSTERMOVESCRIPT:
		return L"CMonsterMoveScript";
		break;

	case SCRIPT_TYPE::MUZZLESCRIPT:
		return L"CMuzzleScript";
		break;

	case SCRIPT_TYPE::PARTICLESCRIPT:
		return L"CParticleScript";
		break;

	case SCRIPT_TYPE::PISTOLSCRIPT:
		return L"CPistolScript";
		break;

	case SCRIPT_TYPE::PLATFORMSCRIPT:
		return L"CPlatformScript";
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

	case SCRIPT_TYPE::SERIAROOMGATESCRIPT:
		return L"CSeriaRoomGateScript";
		break;

	case SCRIPT_TYPE::SERIASCRIPT:
		return L"CSeriaScript";
		break;

	case SCRIPT_TYPE::WINDMILLSCRIPT:
		return L"CWindmillScript";
		break;

	case SCRIPT_TYPE::ESHPHONGATESCRIPT:
		return L"LeshphonGateScript";
		break;

	}
	return nullptr;
}