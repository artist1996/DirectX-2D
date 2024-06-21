#pragma once
#include "EditorUI.h"

class ComponentUI :
    public EditorUI
{
private:
    class CGameObject* m_TargetObject;

public:
    void SetTargetObject(CGameObject* _Target) { m_TargetObject = _Target; }

    CGameObject* GetTargetObject()             { return m_TargetObject; }

public:
    ComponentUI();
    virtual ~ComponentUI();
};

