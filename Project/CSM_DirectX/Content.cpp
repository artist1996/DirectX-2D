#include "pch.h"
#include "Content.h"
#include "ImGui/imgui.h"

#include "TreeUI.h"

Content::Content()
{
	TreeUI* pTree = new TreeUI;
	pTree->SetName("ContentTree");
	AddChild(pTree);

	pTree->AddNode("Parent");	
}

Content::~Content()
{
}


void Content::Update()
{

}