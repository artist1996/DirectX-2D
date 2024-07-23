#pragma once
#include "EditorUI.h"

class AnimationEditor :
    public EditorUI
{
private:
    Ptr<CTexture>  m_Texture;
    Ptr<CAnimation> m_Animation;
    Ptr<CSprite>   m_TargetSprite;

    string         m_strTexName;
    string         m_strSpriteName;

    ImVec2         m_LT;
    ImVec2         m_RB;

    ImVec2         m_StartPos;

    ImVec2         m_LeftTopPos;
    ImVec2         m_SlicePos;

    bool           m_DrawingRect;

public:
    void SetTargetSprite(Ptr<CSprite> _Sprite)   { m_TargetSprite = _Sprite; }
    void SetAnimation(Ptr<CAnimation> _Animation) { m_Animation = _Animation; }


    Ptr<CSprite> GetTargetSprite()               { return m_TargetSprite; }
    const string& GetTextureName()               { return m_strTexName; }
    void ClearEditor();

public:
    virtual void Deactivate() override;

private:
    void LoadTexture();
    void ShowTextureImage();
    void OpenLoadTexture();
    void EditSprite();
    void InputSpriteName();
    void SpriteInfo();


public:
    virtual void Update() override;

public:
    AnimationEditor();
    virtual ~AnimationEditor();
};

