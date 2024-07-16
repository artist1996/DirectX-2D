#pragma once
#include "EditorUI.h"


class MenuUI :
    public EditorUI
{
private:

public:
    virtual void Tick() override;
    virtual void Update() override;

private:
    void File();
    void Level();
    void GameObject();
    void Assets();

    void CreateAnimation();

    wstring GetAssetKey(ASSET_TYPE _Type, const wstring& _strKey);
public:
    MenuUI();
    virtual ~MenuUI();
};

