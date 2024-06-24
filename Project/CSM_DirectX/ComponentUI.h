#pragma once
#include "EditorUI.h"

class ComponentUI :
    public EditorUI
{
private:
    class CGameObject*   m_TargetObject;
    const COMPONENT_TYPE m_Type;

public:
    void SetTargetObject(CGameObject* _Target);

    CGameObject* GetTargetObject() { return m_TargetObject; }
    void Title();

public:
    ComponentUI(COMPONENT_TYPE _Type);
    virtual ~ComponentUI();
};

