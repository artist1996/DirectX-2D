#pragma once
#include "EditorUI.h"

#include "TileMapEditor.h"

class TE_Sub :
    public EditorUI
{
private:
    TileMapEditor* m_Owner;
    Ptr<CTexture>  m_Texture;
    
public:
    class TE_Detail* GetDetail()           { return m_Owner->GetDetail(); }
    class TE_TextureView* GetTextureView() { return m_Owner->GetTextureView(); }
    class TE_Renderer* GetRenderer()       { return m_Owner->GetRenderer(); }

public:
    void SetTexture(Ptr<CTexture> _Texture) { m_Texture = _Texture; }
    Ptr<CTexture> GetTexture()              { return m_Texture; }

public:
    virtual void Init() override;
    virtual void Update() override;

public:
    TE_Sub();
    virtual ~TE_Sub();

    friend class TileMapEditor;
};

