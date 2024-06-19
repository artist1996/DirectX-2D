#pragma once
#include <Engine/CScript.h>

class CEditorCameraScript :
    public CScript
{
private:
    float m_Speed;

private:
    void OrthoGraphicMove();
    void PerspectiveMove();

public:
    virtual void Tick() override;


public:
    CLONE(CEditorCameraScript);
    CEditorCameraScript();
    virtual ~CEditorCameraScript();
};

