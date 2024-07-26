#pragma once
#include "AE_Sub.h"
class AE_Detail :
    public AE_Sub
{
private:
    Ptr<CSprite>    m_Sprite;
    vector<CSprite> m_vecSprite;
    
    
    int             m_CurFrameIdx;

    float           m_FPS;

private:
    void ShowInfo();
    void ShowImage();
    void PlayOrStop();
    void SpriteList();
    void AddSprite();

    void SelectSprite(DWORD_PTR _Param);

public:
    void SetCurFrameIdx(int _Idx) { m_CurFrameIdx = _Idx; }

public:
    virtual void Init() override;
    virtual void Update() override;

public:
    AE_Detail();
    virtual ~AE_Detail();
};

