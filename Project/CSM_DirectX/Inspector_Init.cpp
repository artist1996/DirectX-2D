#include "pch.h"
#include "Inspector.h"

#include <Engine/CLevelMgr.h>
#include <Engine/Clevel.h>
#include <Engine/CLayer.h>

#include "TransformUI.h"
#include "Collider2DUI.h"
#include "CameraUI.h"
#include "FlipBookComUI.h"
#include "MeshRenderUI.h"
#include "TileMapUI.h"
#include "ParticleSystemUI.h"
#include "Light2DUI.h"

#include "MeshUI.h"
#include "MeshDataUI.h"
#include "MaterialUI.h"
#include "PrefabUI.h"
#include "TextureUI.h"
#include "SpriteUI.h"
#include "FlipBookUI.h"
#include "SoundUI.h"
#include "GraphicShaderUI.h"
#include "ComputeShaderUI.h"
#include "RigidbodyUI.h"

#include "ScriptUI.h"

void Inspector::Init()
{
	CreateComponentUI();
	CreateAssetUI();

	if (nullptr == m_TargetObject)
	{
		SetTargetObject(CLevelMgr::GetInst()->FindObjectByName(L"Player"));
		//SetTargetObject(CLevelMgr::GetInst()->FindObjectByName(L"MainCamera"));
		//SetTargetObject(CLevelMgr::GetInst()->FindObjectByName(L"Directional"));
		return;
	}
}

void Inspector::CreateComponentUI()
{
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM] = new TransformUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]->SetName("TrasnformUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]->SetChildSize(ImVec2(0.f, 130.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]);

	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D] = new Light2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D]->SetName("Light2DUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D]->SetChildSize(ImVec2(0.f, 200.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D]);

	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D] = new Collider2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]->SetName("Collider2DUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]->SetChildSize(ImVec2(0.f, 100.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]);

	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA] = new CameraUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]->SetName("CameraUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]->SetChildSize(ImVec2(0.f, 200.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]);

	m_arrComUI[(UINT)COMPONENT_TYPE::FLIPBOOKCOMPONENT] = new FlipBookComUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::FLIPBOOKCOMPONENT]->SetName("FlipBookComUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::FLIPBOOKCOMPONENT]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::FLIPBOOKCOMPONENT]->SetChildSize(ImVec2(0.f, 400.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::FLIPBOOKCOMPONENT]);

	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER] = new MeshRenderUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER]->SetName("MeshRenderUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER]->SetChildSize(ImVec2(0.f, 100.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER]);

	m_arrComUI[(UINT)COMPONENT_TYPE::TILEMAP] = new TileMapUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::TILEMAP]->SetName("TileMapUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::TILEMAP]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::TILEMAP]->SetChildSize(ImVec2(0.f, 100.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::TILEMAP]);

	m_arrComUI[(UINT)COMPONENT_TYPE::PARTICLE_SYSTEM] = new ParticleSystemUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::PARTICLE_SYSTEM]->SetName("ParticleSystemUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::PARTICLE_SYSTEM]->SetChildBorder(true);
	m_arrComUI[(UINT)COMPONENT_TYPE::PARTICLE_SYSTEM]->SetChildSize(ImVec2(0.f, 100.f));
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::PARTICLE_SYSTEM]);

	m_arrComUI[(UINT)COMPONENT_TYPE::RIGIDBODY] = new RigidbodyUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::RIGIDBODY]->SetName("RigidbodyUI");
	m_arrComUI[(UINT)COMPONENT_TYPE::RIGIDBODY]->SetChildBorder(true);
	AddChild(m_arrComUI[(UINT)COMPONENT_TYPE::RIGIDBODY]);
}

void Inspector::CreateAssetUI()
{
	AssetUI* pUI = nullptr;	

	pUI = new MeshUI;
	pUI->SetName("MeshUI");
	AddChild(pUI);
	m_arrAssetUI[(UINT)ASSET_TYPE::MESH] = pUI;

	pUI = new MeshDataUI;
	pUI->SetName("MeshDataUI");
	AddChild(pUI);
	m_arrAssetUI[(UINT)ASSET_TYPE::MESH_DATA] = pUI;

	pUI = new MaterialUI;
	pUI->SetName("MaterialUI");
	AddChild(pUI);
	m_arrAssetUI[(UINT)ASSET_TYPE::MATERIAL] = pUI;

	pUI = new PrefabUI;
	pUI->SetName("PrefabUI");
	AddChild(pUI);
	m_arrAssetUI[(UINT)ASSET_TYPE::PREFAB] = pUI;

	pUI = new TextureUI;
	pUI->SetName("TextureUI");
	AddChild(pUI);
	m_arrAssetUI[(UINT)ASSET_TYPE::TEXTURE] = pUI;

	pUI = new SpriteUI;
	pUI->SetName("SpriteUI");
	AddChild(pUI);
	m_arrAssetUI[(UINT)ASSET_TYPE::SPRITE] = pUI;

	pUI = new FlipBookUI;
	pUI->SetName("FlipBookUI");
	AddChild(pUI);
	m_arrAssetUI[(UINT)ASSET_TYPE::FLIPBOOK] = pUI;

	pUI = new SoundUI;
	pUI->SetName("SoundUI");
	AddChild(pUI);
	m_arrAssetUI[(UINT)ASSET_TYPE::SOUND] = pUI;

	pUI = new GraphicShaderUI;
	pUI->SetName("GraphicShaderUI");
	AddChild(pUI);
	m_arrAssetUI[(UINT)ASSET_TYPE::GRAPHIC_SHADER] = pUI;

	pUI = new ComputeShaderUI;
	pUI->SetName("ComputeShaderUI");
	AddChild(pUI);
	m_arrAssetUI[(UINT)ASSET_TYPE::COMPUTE_SHADER] = pUI;
}

void Inspector::CreateScriptUI(UINT _Count)
{
	for (UINT i = 0; i < _Count; ++i)
	{
		ScriptUI* pScriptUI = new ScriptUI;
		
		char szScriprtUIName[255] = {};
		sprintf_s(szScriprtUIName, 255, "ScriptUI##%d", (int)m_vecScriptUI.size());
		pScriptUI->SetName(szScriprtUIName);

		AddChild(pScriptUI);
		m_vecScriptUI.push_back(pScriptUI);
	}
}