#pragma once
#include "EditorUI.h"

class Inspector :
    public EditorUI
{
private:
    class CGameObject* m_TargetObject;
    class ComponentUI* m_arrComUI[(UINT)COMPONENT_TYPE::END];

    Ptr<CAsset>        m_TargetAsset;
    class AssetUI*     m_arrAssetUI[(UINT)ASSET_TYPE::END];

private:
    void CreateComponentUI();
    void CreateAssetUI();

public:
    void SetTargetObject(CGameObject* _Target);
    void SetTargetAsset(Ptr<CAsset> _Asset);

public:
    virtual void Update() override;
    virtual void Init() override;

public:
    Inspector();
    virtual ~Inspector();
};