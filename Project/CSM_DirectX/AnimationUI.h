#pragma once
#include "EditorUI.h"

class AnimationUI :
    public EditorUI
{
private:
    Ptr<CFlipBook>                   m_FlipBook;
    Ptr<CSprite>                     m_TargetSprite;

    class AnimationEditor*           m_arrChild[2];
    
    string                           m_strName;
    
public:
    virtual void Update() override;
    void SetDefaultFlipBook(Ptr<CFlipBook> _FlipBook) { m_FlipBook = _FlipBook; }

    virtual void Init() override;
    Ptr<CFlipBook> GetTargetFlipBook() { return m_FlipBook; }

public:
    AnimationUI();
    virtual ~AnimationUI();
};