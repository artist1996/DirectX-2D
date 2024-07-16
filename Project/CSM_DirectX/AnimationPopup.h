#pragma once
#include "AnimationEditor.h"
class AnimationPopup :
    public AnimationEditor
{
private:
    string  m_strName;
    wstring m_strKey;


public:
    virtual void Update();

public:
    AnimationPopup();
    virtual ~AnimationPopup();
};

