#pragma once
#include "EditorUI.h"

class Inspector :
    public EditorUI
{
private:
    class CGameObject* m_TargetObject;
    class ComponentUI* m_arrComUI[(UINT)COMPONENT_TYPE::END];

public:
    virtual void Update() override;

    void SetTargetObject(CGameObject* _Target);

public:
    Inspector();
    virtual ~Inspector();
};

