#pragma once
#include "AssetUI.h"
class MaterialUI :
    public AssetUI
{
private:
    TEX_PARAM m_SelectTexParam;

public:
    virtual void Update() override;

private:
    void ShaderParameter();
    void ParameterTitle();

private:
    void ChangeTexture(DWORD_PTR _Param);
    void SelectShader(DWORD_PTR _ListUI);

public:
    MaterialUI();
    virtual ~MaterialUI();
};

