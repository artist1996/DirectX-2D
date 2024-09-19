#include "pch.h"
#include "CScriptMgr.h"

#include "CBBQScript.h"
#include "CBossCurHPBarScript.h"
#include "CBossCurHPFontScript.h"
#include "CBossHUDScript.h"
#include "CBossMaxHPBarScript.h"
#include "CBossNextHPBarScript.h"
#include "CBuffScript.h"
#include "CCameraMoveScript.h"
#include "CDiagonalHeadShotScript.h"
#include "CDiagonalPistolScript.h"
#include "CDirezieScript.h"
#include "CDirezieWindScript.h"
#include "CDoubleGunHawkScript.h"
#include "CDummyScript.h"
#include "CEffectScript.h"
#include "CGatlinggunPistolScript.h"
#include "CGatlinggunScript.h"
#include "CGunHawkExplodeScript.h"
#include "CHammerScript.h"
#include "CHeadShotEffectScript.h"
#include "CHeadShotScript.h"
#include "CHyungteoPunchScript.h"
#include "CHyungteoScript.h"
#include "CHyungteoStingScript.h"
#include "CIroncageScript.h"
#include "CJackSpikeScript.h"
#include "CJurisScript.h"
#include "CLoadingScript.h"
#include "CMachKickScript.h"
#include "CMeltKnightScript.h"
#include "CMonsterHPBarScript.h"
#include "CMonsterHPFontScript.h"
#include "CMonsterHUDScript.h"
#include "CMonsterMoveScript.h"
#include "CMonsterNextHPBarScript.h"
#include "CMonsterWhiteBarScript.h"
#include "CMuzzleScript.h"
#include "CNamedMonsterFaceHUDScript.h"
#include "CNamedMonsterHUDScript.h"
#include "CParticleScript.h"
#include "CPistolScript.h"
#include "CPlatformScript.h"
#include "CPlayerFatigueHUDScript.h"
#include "CPlayerHUDButtonScript.h"
#include "CPlayerHUDScript.h"
#include "CPlayerMoveScript.h"
#include "CPlayerMPHUDScript.h"
#include "CPlayerScript.h"
#include "CPlayerUIScript.h"
#include "CPunisherPistolScript.h"
#include "CPunisherScript.h"
#include "CRandomShootScript.h"
#include "CRisingShotScript.h"
#include "CSeriaRoomGateScript.h"
#include "CSeriaScript.h"
#include "CSkillGroundScript.h"
#include "CSkillIconScript.h"
#include "CUICameraScript.h"
#include "CWindmillScript.h"
#include "LeshphonGateScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBBQScript");
	_vec.push_back(L"CBossCurHPBarScript");
	_vec.push_back(L"CBossCurHPFontScript");
	_vec.push_back(L"CBossHUDScript");
	_vec.push_back(L"CBossMaxHPBarScript");
	_vec.push_back(L"CBossNextHPBarScript");
	_vec.push_back(L"CBuffScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CDiagonalHeadShotScript");
	_vec.push_back(L"CDiagonalPistolScript");
	_vec.push_back(L"CDirezieScript");
	_vec.push_back(L"CDirezieWindScript");
	_vec.push_back(L"CDoubleGunHawkScript");
	_vec.push_back(L"CDummyScript");
	_vec.push_back(L"CEffectScript");
	_vec.push_back(L"CGatlinggunPistolScript");
	_vec.push_back(L"CGatlinggunScript");
	_vec.push_back(L"CGunHawkExplodeScript");
	_vec.push_back(L"CHammerScript");
	_vec.push_back(L"CHeadShotEffectScript");
	_vec.push_back(L"CHeadShotScript");
	_vec.push_back(L"CHyungteoPunchScript");
	_vec.push_back(L"CHyungteoScript");
	_vec.push_back(L"CHyungteoStingScript");
	_vec.push_back(L"CIroncageScript");
	_vec.push_back(L"CJackSpikeScript");
	_vec.push_back(L"CJurisScript");
	_vec.push_back(L"CLoadingScript");
	_vec.push_back(L"CMachKickScript");
	_vec.push_back(L"CMeltKnightScript");
	_vec.push_back(L"CMonsterHPBarScript");
	_vec.push_back(L"CMonsterHPFontScript");
	_vec.push_back(L"CMonsterHUDScript");
	_vec.push_back(L"CMonsterMoveScript");
	_vec.push_back(L"CMonsterNextHPBarScript");
	_vec.push_back(L"CMonsterWhiteBarScript");
	_vec.push_back(L"CMuzzleScript");
	_vec.push_back(L"CNamedMonsterFaceHUDScript");
	_vec.push_back(L"CNamedMonsterHUDScript");
	_vec.push_back(L"CParticleScript");
	_vec.push_back(L"CPistolScript");
	_vec.push_back(L"CPlatformScript");
	_vec.push_back(L"CPlayerFatigueHUDScript");
	_vec.push_back(L"CPlayerHUDButtonScript");
	_vec.push_back(L"CPlayerHUDScript");
	_vec.push_back(L"CPlayerMoveScript");
	_vec.push_back(L"CPlayerMPHUDScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CPlayerUIScript");
	_vec.push_back(L"CPunisherPistolScript");
	_vec.push_back(L"CPunisherScript");
	_vec.push_back(L"CRandomShootScript");
	_vec.push_back(L"CRisingShotScript");
	_vec.push_back(L"CSeriaRoomGateScript");
	_vec.push_back(L"CSeriaScript");
	_vec.push_back(L"CSkillGroundScript");
	_vec.push_back(L"CSkillIconScript");
	_vec.push_back(L"CUICameraScript");
	_vec.push_back(L"CWindmillScript");
	_vec.push_back(L"LeshphonGateScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBBQScript" == _strScriptName)
		return new CBBQScript;
	if (L"CBossCurHPBarScript" == _strScriptName)
		return new CBossCurHPBarScript;
	if (L"CBossCurHPFontScript" == _strScriptName)
		return new CBossCurHPFontScript;
	if (L"CBossHUDScript" == _strScriptName)
		return new CBossHUDScript;
	if (L"CBossMaxHPBarScript" == _strScriptName)
		return new CBossMaxHPBarScript;
	if (L"CBossNextHPBarScript" == _strScriptName)
		return new CBossNextHPBarScript;
	if (L"CBuffScript" == _strScriptName)
		return new CBuffScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CDiagonalHeadShotScript" == _strScriptName)
		return new CDiagonalHeadShotScript;
	if (L"CDiagonalPistolScript" == _strScriptName)
		return new CDiagonalPistolScript;
	if (L"CDirezieScript" == _strScriptName)
		return new CDirezieScript;
	if (L"CDirezieWindScript" == _strScriptName)
		return new CDirezieWindScript;
	if (L"CDoubleGunHawkScript" == _strScriptName)
		return new CDoubleGunHawkScript;
	if (L"CDummyScript" == _strScriptName)
		return new CDummyScript;
	if (L"CEffectScript" == _strScriptName)
		return new CEffectScript;
	if (L"CGatlinggunPistolScript" == _strScriptName)
		return new CGatlinggunPistolScript;
	if (L"CGatlinggunScript" == _strScriptName)
		return new CGatlinggunScript;
	if (L"CGunHawkExplodeScript" == _strScriptName)
		return new CGunHawkExplodeScript;
	if (L"CHammerScript" == _strScriptName)
		return new CHammerScript;
	if (L"CHeadShotEffectScript" == _strScriptName)
		return new CHeadShotEffectScript;
	if (L"CHeadShotScript" == _strScriptName)
		return new CHeadShotScript;
	if (L"CHyungteoPunchScript" == _strScriptName)
		return new CHyungteoPunchScript;
	if (L"CHyungteoScript" == _strScriptName)
		return new CHyungteoScript;
	if (L"CHyungteoStingScript" == _strScriptName)
		return new CHyungteoStingScript;
	if (L"CIroncageScript" == _strScriptName)
		return new CIroncageScript;
	if (L"CJackSpikeScript" == _strScriptName)
		return new CJackSpikeScript;
	if (L"CJurisScript" == _strScriptName)
		return new CJurisScript;
	if (L"CLoadingScript" == _strScriptName)
		return new CLoadingScript;
	if (L"CMachKickScript" == _strScriptName)
		return new CMachKickScript;
	if (L"CMeltKnightScript" == _strScriptName)
		return new CMeltKnightScript;
	if (L"CMonsterHPBarScript" == _strScriptName)
		return new CMonsterHPBarScript;
	if (L"CMonsterHPFontScript" == _strScriptName)
		return new CMonsterHPFontScript;
	if (L"CMonsterHUDScript" == _strScriptName)
		return new CMonsterHUDScript;
	if (L"CMonsterMoveScript" == _strScriptName)
		return new CMonsterMoveScript;
	if (L"CMonsterNextHPBarScript" == _strScriptName)
		return new CMonsterNextHPBarScript;
	if (L"CMonsterWhiteBarScript" == _strScriptName)
		return new CMonsterWhiteBarScript;
	if (L"CMuzzleScript" == _strScriptName)
		return new CMuzzleScript;
	if (L"CNamedMonsterFaceHUDScript" == _strScriptName)
		return new CNamedMonsterFaceHUDScript;
	if (L"CNamedMonsterHUDScript" == _strScriptName)
		return new CNamedMonsterHUDScript;
	if (L"CParticleScript" == _strScriptName)
		return new CParticleScript;
	if (L"CPistolScript" == _strScriptName)
		return new CPistolScript;
	if (L"CPlatformScript" == _strScriptName)
		return new CPlatformScript;
	if (L"CPlayerFatigueHUDScript" == _strScriptName)
		return new CPlayerFatigueHUDScript;
	if (L"CPlayerHUDButtonScript" == _strScriptName)
		return new CPlayerHUDButtonScript;
	if (L"CPlayerHUDScript" == _strScriptName)
		return new CPlayerHUDScript;
	if (L"CPlayerMoveScript" == _strScriptName)
		return new CPlayerMoveScript;
	if (L"CPlayerMPHUDScript" == _strScriptName)
		return new CPlayerMPHUDScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CPlayerUIScript" == _strScriptName)
		return new CPlayerUIScript;
	if (L"CPunisherPistolScript" == _strScriptName)
		return new CPunisherPistolScript;
	if (L"CPunisherScript" == _strScriptName)
		return new CPunisherScript;
	if (L"CRandomShootScript" == _strScriptName)
		return new CRandomShootScript;
	if (L"CRisingShotScript" == _strScriptName)
		return new CRisingShotScript;
	if (L"CSeriaRoomGateScript" == _strScriptName)
		return new CSeriaRoomGateScript;
	if (L"CSeriaScript" == _strScriptName)
		return new CSeriaScript;
	if (L"CSkillGroundScript" == _strScriptName)
		return new CSkillGroundScript;
	if (L"CSkillIconScript" == _strScriptName)
		return new CSkillIconScript;
	if (L"CUICameraScript" == _strScriptName)
		return new CUICameraScript;
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
	case (UINT)SCRIPT_TYPE::BBQSCRIPT:
		return new CBBQScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSCURHPBARSCRIPT:
		return new CBossCurHPBarScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSCURHPFONTSCRIPT:
		return new CBossCurHPFontScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSHUDSCRIPT:
		return new CBossHUDScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSMAXHPBARSCRIPT:
		return new CBossMaxHPBarScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSNEXTHPBARSCRIPT:
		return new CBossNextHPBarScript;
		break;
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
	case (UINT)SCRIPT_TYPE::DIREZIESCRIPT:
		return new CDirezieScript;
		break;
	case (UINT)SCRIPT_TYPE::DIREZIEWINDSCRIPT:
		return new CDirezieWindScript;
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
	case (UINT)SCRIPT_TYPE::GATLINGGUNPISTOLSCRIPT:
		return new CGatlinggunPistolScript;
		break;
	case (UINT)SCRIPT_TYPE::GATLINGGUNSCRIPT:
		return new CGatlinggunScript;
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
	case (UINT)SCRIPT_TYPE::HYUNGTEOPUNCHSCRIPT:
		return new CHyungteoPunchScript;
		break;
	case (UINT)SCRIPT_TYPE::HYUNGTEOSCRIPT:
		return new CHyungteoScript;
		break;
	case (UINT)SCRIPT_TYPE::HYUNGTEOSTINGSCRIPT:
		return new CHyungteoStingScript;
		break;
	case (UINT)SCRIPT_TYPE::IRONCAGESCRIPT:
		return new CIroncageScript;
		break;
	case (UINT)SCRIPT_TYPE::JACKSPIKESCRIPT:
		return new CJackSpikeScript;
		break;
	case (UINT)SCRIPT_TYPE::JURISSCRIPT:
		return new CJurisScript;
		break;
	case (UINT)SCRIPT_TYPE::LOADINGSCRIPT:
		return new CLoadingScript;
		break;
	case (UINT)SCRIPT_TYPE::MACHKICKSCRIPT:
		return new CMachKickScript;
		break;
	case (UINT)SCRIPT_TYPE::MELTKNIGHTSCRIPT:
		return new CMeltKnightScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERHPBARSCRIPT:
		return new CMonsterHPBarScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERHPFONTSCRIPT:
		return new CMonsterHPFontScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERHUDSCRIPT:
		return new CMonsterHUDScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERMOVESCRIPT:
		return new CMonsterMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERNEXTHPBARSCRIPT:
		return new CMonsterNextHPBarScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERWHITEBARSCRIPT:
		return new CMonsterWhiteBarScript;
		break;
	case (UINT)SCRIPT_TYPE::MUZZLESCRIPT:
		return new CMuzzleScript;
		break;
	case (UINT)SCRIPT_TYPE::NAMEDMONSTERFACEHUDSCRIPT:
		return new CNamedMonsterFaceHUDScript;
		break;
	case (UINT)SCRIPT_TYPE::NAMEDMONSTERHUDSCRIPT:
		return new CNamedMonsterHUDScript;
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
	case (UINT)SCRIPT_TYPE::PLAYERFATIGUEHUDSCRIPT:
		return new CPlayerFatigueHUDScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERHUDBUTTONSCRIPT:
		return new CPlayerHUDButtonScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERHUDSCRIPT:
		return new CPlayerHUDScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERMOVESCRIPT:
		return new CPlayerMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERMPHUDSCRIPT:
		return new CPlayerMPHUDScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERUISCRIPT:
		return new CPlayerUIScript;
		break;
	case (UINT)SCRIPT_TYPE::PUNISHERPISTOLSCRIPT:
		return new CPunisherPistolScript;
		break;
	case (UINT)SCRIPT_TYPE::PUNISHERSCRIPT:
		return new CPunisherScript;
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
	case (UINT)SCRIPT_TYPE::SKILLGROUNDSCRIPT:
		return new CSkillGroundScript;
		break;
	case (UINT)SCRIPT_TYPE::SKILLICONSCRIPT:
		return new CSkillIconScript;
		break;
	case (UINT)SCRIPT_TYPE::UICAMERASCRIPT:
		return new CUICameraScript;
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
	case SCRIPT_TYPE::BBQSCRIPT:
		return L"CBBQScript";
		break;

	case SCRIPT_TYPE::BOSSCURHPBARSCRIPT:
		return L"CBossCurHPBarScript";
		break;

	case SCRIPT_TYPE::BOSSCURHPFONTSCRIPT:
		return L"CBossCurHPFontScript";
		break;

	case SCRIPT_TYPE::BOSSHUDSCRIPT:
		return L"CBossHUDScript";
		break;

	case SCRIPT_TYPE::BOSSMAXHPBARSCRIPT:
		return L"CBossMaxHPBarScript";
		break;

	case SCRIPT_TYPE::BOSSNEXTHPBARSCRIPT:
		return L"CBossNextHPBarScript";
		break;

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

	case SCRIPT_TYPE::DIREZIESCRIPT:
		return L"CDirezieScript";
		break;

	case SCRIPT_TYPE::DIREZIEWINDSCRIPT:
		return L"CDirezieWindScript";
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

	case SCRIPT_TYPE::GATLINGGUNPISTOLSCRIPT:
		return L"CGatlinggunPistolScript";
		break;

	case SCRIPT_TYPE::GATLINGGUNSCRIPT:
		return L"CGatlinggunScript";
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

	case SCRIPT_TYPE::HYUNGTEOPUNCHSCRIPT:
		return L"CHyungteoPunchScript";
		break;

	case SCRIPT_TYPE::HYUNGTEOSCRIPT:
		return L"CHyungteoScript";
		break;

	case SCRIPT_TYPE::HYUNGTEOSTINGSCRIPT:
		return L"CHyungteoStingScript";
		break;

	case SCRIPT_TYPE::IRONCAGESCRIPT:
		return L"CIroncageScript";
		break;

	case SCRIPT_TYPE::JACKSPIKESCRIPT:
		return L"CJackSpikeScript";
		break;

	case SCRIPT_TYPE::JURISSCRIPT:
		return L"CJurisScript";
		break;

	case SCRIPT_TYPE::LOADINGSCRIPT:
		return L"CLoadingScript";
		break;

	case SCRIPT_TYPE::MACHKICKSCRIPT:
		return L"CMachKickScript";
		break;

	case SCRIPT_TYPE::MELTKNIGHTSCRIPT:
		return L"CMeltKnightScript";
		break;

	case SCRIPT_TYPE::MONSTERHPBARSCRIPT:
		return L"CMonsterHPBarScript";
		break;

	case SCRIPT_TYPE::MONSTERHPFONTSCRIPT:
		return L"CMonsterHPFontScript";
		break;

	case SCRIPT_TYPE::MONSTERHUDSCRIPT:
		return L"CMonsterHUDScript";
		break;

	case SCRIPT_TYPE::MONSTERMOVESCRIPT:
		return L"CMonsterMoveScript";
		break;

	case SCRIPT_TYPE::MONSTERNEXTHPBARSCRIPT:
		return L"CMonsterNextHPBarScript";
		break;

	case SCRIPT_TYPE::MONSTERWHITEBARSCRIPT:
		return L"CMonsterWhiteBarScript";
		break;

	case SCRIPT_TYPE::MUZZLESCRIPT:
		return L"CMuzzleScript";
		break;

	case SCRIPT_TYPE::NAMEDMONSTERFACEHUDSCRIPT:
		return L"CNamedMonsterFaceHUDScript";
		break;

	case SCRIPT_TYPE::NAMEDMONSTERHUDSCRIPT:
		return L"CNamedMonsterHUDScript";
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

	case SCRIPT_TYPE::PLAYERFATIGUEHUDSCRIPT:
		return L"CPlayerFatigueHUDScript";
		break;

	case SCRIPT_TYPE::PLAYERHUDBUTTONSCRIPT:
		return L"CPlayerHUDButtonScript";
		break;

	case SCRIPT_TYPE::PLAYERHUDSCRIPT:
		return L"CPlayerHUDScript";
		break;

	case SCRIPT_TYPE::PLAYERMOVESCRIPT:
		return L"CPlayerMoveScript";
		break;

	case SCRIPT_TYPE::PLAYERMPHUDSCRIPT:
		return L"CPlayerMPHUDScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::PLAYERUISCRIPT:
		return L"CPlayerUIScript";
		break;

	case SCRIPT_TYPE::PUNISHERPISTOLSCRIPT:
		return L"CPunisherPistolScript";
		break;

	case SCRIPT_TYPE::PUNISHERSCRIPT:
		return L"CPunisherScript";
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

	case SCRIPT_TYPE::SKILLGROUNDSCRIPT:
		return L"CSkillGroundScript";
		break;

	case SCRIPT_TYPE::SKILLICONSCRIPT:
		return L"CSkillIconScript";
		break;

	case SCRIPT_TYPE::UICAMERASCRIPT:
		return L"CUICameraScript";
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