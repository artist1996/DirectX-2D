#pragma once
#include "ComponentUI.h"
class FontUI :
    public ComponentUI
{
private:
    string m_strFont;
    float  m_Scale;

    Vec4   m_Color;

public:
    virtual void Update() override;

public:
    FontUI();
    virtual ~FontUI();
};

