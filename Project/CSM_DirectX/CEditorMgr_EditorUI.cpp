#include "pch.h"
#include "CEditorMgr.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include <Engine/CDevice.h>

#include "ParamUI.h"

#include "Inspector.h"
#include "Content.h"
#include "Outliner.h"
#include "ListUI.h"
#include "MenuUI.h"

#include "SpriteEditor.h"
#include "SE_TextureView.h"
#include "SE_Info.h"
#include "SE_Create.h"

#include "AnimationEditor.h"
#include "AE_Preview.h"
#include "AE_Detail.h"
#include "AE_Create.h"
#include "AE_SpriteView.h"

#include "TileMapEditor.h"
#include "TE_Detail.h"
#include "TE_TextureView.h"
#include "TE_Renderer.h"

#include "CollisionMatrix.h"

#include "CreateGameObject.h"

void CEditorMgr::InitImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;
	//io.ConfigViewportsNoDefaultParent = true;
	//io.ConfigDockingAlwaysTabBar = true;
	//io.ConfigDockingTransparentPayload = true;
	//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
	//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

	ImGui::GetStyle();

	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();

	auto& colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 1.0f };
	colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

	// Border
	colors[ImGuiCol_Border] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.29f };
	colors[ImGuiCol_BorderShadow] = ImVec4{ 0.0f, 0.0f, 0.0f, 0.24f };

	// Text
	colors[ImGuiCol_Text] = ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
	colors[ImGuiCol_TextDisabled] = ImVec4{ 0.5f, 0.5f, 0.5f, 1.0f };

	// Headers
	colors[ImGuiCol_Header] = ImVec4{ 0.18f, 0.18f, 0.23f, 1.0f };
	colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
	colors[ImGuiCol_HeaderActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

	// Buttons
	colors[ImGuiCol_Button] = ImVec4{ 0.13f, 0.13f, 0.17f, 1.0f };
	colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
	colors[ImGuiCol_ButtonActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
	colors[ImGuiCol_CheckMark] = ImVec4{ 0.74f, 0.58f, 0.98f, 1.0f };

	// Popups
	colors[ImGuiCol_PopupBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 0.92f };

	// Slider
	colors[ImGuiCol_SliderGrab] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.54f };
	colors[ImGuiCol_SliderGrabActive] = ImVec4{ 0.74f, 0.58f, 0.98f, 0.54f };

	// Frame BG
	colors[ImGuiCol_FrameBg] = ImVec4{ 0.13f, 0.13f, 0.17f, 1.0f };
	colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
	colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

	// Tabs
	colors[ImGuiCol_Tab] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
	colors[ImGuiCol_TabHovered] = ImVec4{ 0.24f, 0.24f, 0.32f, 1.0f };
	colors[ImGuiCol_TabActive] = ImVec4{ 0.2f, 0.22f, 0.27f, 1.0f};
	colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };



	// Title
	colors[ImGuiCol_TitleBg] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
	colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

	// Scrollbar
	colors[ImGuiCol_ScrollbarBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 1.0f };

	// Seperator
	colors[ImGuiCol_Separator] = ImVec4{ 0.44f, 0.37f, 0.61f, 1.0f };
	//colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.74f, 0.58f, 0.98f, 1.0f };
	//colors[ImGuiCol_SeparatorActive] = ImVec4{ 0.84f, 0.58f, 1.0f, 1.0f };
	
	// Resize Grip
	colors[ImGuiCol_ResizeGrip] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.29f };
	colors[ImGuiCol_ResizeGripHovered] = ImVec4{ 0.74f, 0.58f, 0.98f, 0.29f };
	colors[ImGuiCol_ResizeGripActive] = ImVec4{ 0.84f, 0.58f, 1.0f, 0.29f };

	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(CEngine::GetInst()->GetMainWnd());
	ImGui_ImplDX11_Init(DEVICE, CONTEXT);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != nullptr);

	CreateEditorUI();
}

void CEditorMgr::ObserveContent()
{
	// ������ ��Ȳ�� �߻� �ߴ��� Ȯ��
	DWORD dwState = WaitForSingleObject(m_hNotifyHandle, 0);

	if (WAIT_OBJECT_0 == dwState)
	{
		// Content ���� ���� �ִ� ��� Asset�� �޸𸮿� �ε� �Ǿ� �ִ� Asset ����ȭ
		Content* pContent = (Content*)FindEditorUI("Content");
		pContent->Reload();
		
		// �ٽ� Content ������ �������� �߻��Ǵ��� Ȯ��
		FindNextChangeNotification(m_hNotifyHandle);
	}
}


void CEditorMgr::ImGuiProgress()
{
	// Start ImGui
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// ParamUI ID Reset
	ParamUI::ResetID();

	// ImGui Tick
	ImGuiTick();

	// ImGui Render    
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

void CEditorMgr::CreateEditorUI()
{
	EditorUI* pUI = nullptr;

	pUI = new Inspector;
	pUI->SetName("Inspector");
	pUI->Init();
	m_mapUI.insert(make_pair(pUI->GetName(), pUI));

	EditorUI* pContent = new Content;
	pContent->SetName("Content");
	pContent->Init();
	m_mapUI.insert(make_pair(pContent->GetName(), pContent));

	EditorUI* pList = new ListUI;
	pList->SetName("List");
	pList->SetActive(false);
	pList->SetModal(true);
	m_mapUI.insert(make_pair(pList->GetName(), pList));

	EditorUI* pOutliner = new Outliner;
	pOutliner->SetName("Outliner");
	m_mapUI.insert(make_pair(pOutliner->GetName(), pOutliner));

	EditorUI* pMenu = new MenuUI;
	pMenu->SetName("MainMenu");
	pMenu->Init();
	m_mapUI.insert(make_pair(pMenu->GetName(), pMenu));

	EditorUI* pTextureView = new SE_TextureView;
	pTextureView->Init();
	pTextureView->SetName("SE_TextureView");
	m_mapUI.insert(make_pair(pTextureView->GetName(), pTextureView));

	EditorUI* pSpriteInfo = new SE_Info;
	pSpriteInfo->Init();
	pSpriteInfo->SetName("SE_Info");
	m_mapUI.insert(make_pair(pSpriteInfo->GetName(), pSpriteInfo));

	EditorUI* pCreateSprite = new SE_Create;
	pCreateSprite->Init();
	pCreateSprite->SetName("SE_Create");
	pCreateSprite->SetModal(true);
	m_mapUI.insert(make_pair(pCreateSprite->GetName(), pCreateSprite));

	EditorUI* pSpriteEditor = new SpriteEditor;
	pSpriteEditor->Init();
	pSpriteEditor->SetName("Sprite Editor");
	m_mapUI.insert(make_pair(pSpriteEditor->GetName(), pSpriteEditor));

	EditorUI* pPreview = new AE_Preview;
	pPreview->Init();
	pPreview->SetName("AE_Preview");
	m_mapUI.insert(make_pair(pPreview->GetName(), pPreview));

	EditorUI* pAEDetail = new AE_Detail;
	pAEDetail->Init();
	pAEDetail->SetName("AE_Detail");
	m_mapUI.insert(make_pair(pAEDetail->GetName(), pAEDetail));

	EditorUI* pAECreate = new AE_Create;
	pAECreate->SetName("AE_Create");
	m_mapUI.insert(make_pair(pAECreate->GetName(), pAECreate));

	EditorUI* pSV = new AE_SpriteView;
	pSV->SetName("AE_SpriteView");
	m_mapUI.insert(make_pair(pSV->GetName(), pSV));

	EditorUI* pAnimationEditor = new AnimationEditor;
	pAnimationEditor->Init();
	pAnimationEditor->SetName("Animation Editor");
	m_mapUI.insert(make_pair(pAnimationEditor->GetName(), pAnimationEditor));

	EditorUI* pTileDetail = new TE_Detail;
	pTileDetail->SetName("TE_Detail");
	m_mapUI.insert(make_pair(pTileDetail->GetName(), pTileDetail));

	EditorUI* pTETextureView = new TE_TextureView;
	pTETextureView->SetName("TE_TextureView");
	m_mapUI.insert(make_pair(pTETextureView->GetName(), pTETextureView));

	EditorUI* pTERenderer = new TE_Renderer;
	pTERenderer->SetName("TE_Renderer");
	m_mapUI.insert(make_pair(pTERenderer->GetName(), pTERenderer));

	EditorUI* pTileMapEditor = new TileMapEditor;
	pTileMapEditor->SetName("TileMap Editor");
	pTileMapEditor->Init();
	m_mapUI.insert(make_pair(pTileMapEditor->GetName(), pTileMapEditor));

	EditorUI* pCollisionMatrix = new CollisionMatrix;
	pCollisionMatrix->SetName("Layer Collision Matrix");
	pCollisionMatrix->Init();
	m_mapUI.insert(make_pair(pCollisionMatrix->GetName(), pCollisionMatrix));

	EditorUI* pCreateGameObject = new CreateGameObject;
	pCreateGameObject->SetName("Create GameObject");
	pCreateGameObject->Init();
	m_mapUI.insert(make_pair(pCreateGameObject->GetName(), pCreateGameObject));	
}

EditorUI* CEditorMgr::FindEditorUI(const string& _strName)
{
	map<string, EditorUI*>::iterator iter = m_mapUI.find(_strName);

	if (iter == m_mapUI.end())
		return nullptr;

	return iter->second;
}