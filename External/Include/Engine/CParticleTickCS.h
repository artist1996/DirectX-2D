#pragma once
#include "CComputeShader.h"
#include "CStructuredBuffer.h"

class CParticleTickCS :
    public CComputeShader
{
private:
    CStructuredBuffer* m_ParticleBuffer;

public:
    void SetParticleBuffer(CStructuredBuffer* _Buffer) { m_ParticleBuffer = _Buffer; }

public:
    virtual int Binding()       override;
    virtual void CalcGroupNum() override;
    virtual void Clear()        override;

public:
    CParticleTickCS();
    virtual ~CParticleTickCS();
};

