#pragma once
#include "SE_Sub.h"
class SE_TextureView :
    public SE_Sub
{
public:
    Ptr<CTexture> m_Texture;

    ImVec2        m_ImageRectMin; // Image ���� �»�� Pos

    ImVec2        m_MousePos;     // ���� Mouse Pos

    ImVec2        m_MouseLT;      // ���콺 ��ġ�� �ش��ϴ� Texture �� �»�� �ȼ� ��ǥ
    ImVec2        m_MouseRB;      // ���콺 ��ġ�� �ش��ϴ� Texture �� ���ϴ� �ȼ� ��ǥ

    set<Vec2>     m_PixelID;      // ��ϵ� ���� �ִ� �ȼ����� Ȯ���ϴ� �뵵

    float         m_WidthSize;
    float         m_WheelScale;   // Mouse Wheel
    float         m_Ratio;        // ���� �ػ� ��� ��� �̹����� ����

private:
    void WheelCheck();
    void SelectCheck();
    void DrawRect();
    void CalcSpriteSize(Vec2 _PixelPos);
    bool IsPixelOk(Vec2 _PixelPos);

    void SetInfo();

public:
    void SetTexture(Ptr<CTexture> _Texture);

public:
    virtual void Init() override;
    virtual void Update() override;

public:
    virtual void Deactivate() override;

public:
    SE_TextureView();
    virtual ~SE_TextureView();
};

