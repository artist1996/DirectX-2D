#pragma once
#include "CEntity.h"
class CStructuredBuffer :
    public CEntity
{
private:
    ComPtr<ID3D11Buffer>             m_SB;           // CStructuredBuffer
    ComPtr<ID3D11ShaderResourceView> m_SRV;          // Shader Resource View
                                                    
    D3D11_BUFFER_DESC                m_Desc;         // Buffer Desc

    UINT                             m_ElementCount; // Buffer 원소 개수
    UINT                             m_ElementSize;  // Buffer 의 Byte

public:
    UINT GetElementCount() { return m_ElementCount; }
    UINT GetElementSize()  { return m_ElementSize; }
    UINT GetBufferSize()   { return m_ElementSize * m_ElementCount; }

    void SetData(void* _pData, UINT _DataSize = 0);
    void Binding(UINT _RegisterNum);
    

public:
    int Create(UINT _ElementSize, UINT _ElementCount, void* _InitData = nullptr);


public:
    CLONE_DISABLE(CStructuredBuffer);
    CStructuredBuffer();
    virtual ~CStructuredBuffer();
};

