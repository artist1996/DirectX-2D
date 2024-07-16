#pragma once
#include "AnimationEditor.h"

class SpriteEditor :
    public AnimationEditor
{
private:
    class TreeUI* m_Tree;

    string        m_strName;

    bool          m_Active;

public:
    virtual void Update() override;
    
    void RenewTree();

    

public:
    SpriteEditor();
    virtual ~SpriteEditor();
};

