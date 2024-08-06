#pragma once
#include "CRenderComponent.h"

#include "CParticleTickCS.h"

class CStructuredBuffer;

class CParticleSystem :
    public CRenderComponent
{
private:
    CStructuredBuffer*   m_ParticleBuffer;
    Ptr<CParticleTickCS> m_TickCS;
    Ptr<CTexture>        m_ParticleTex;

    int                  m_MaxParticleCount;

public:
    void SetParticleTexture(Ptr<CTexture> _Texture) { m_ParticleTex = _Texture; }

public:
    virtual void FinalTick() override;
    virtual void Render()    override;
    virtual void SaveToFile(FILE* _File)   override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CParticleSystem);
    CParticleSystem();
    virtual ~CParticleSystem();
};

