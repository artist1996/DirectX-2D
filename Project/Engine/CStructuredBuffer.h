#pragma once
#include "CEntity.h"

enum SB_TYPE
{
    SRV_ONLY,
    SRV_UAV,
};

class CStructuredBuffer :
    public CEntity
{
private:
    ComPtr<ID3D11Buffer>              m_SB;           // CStructuredBuffer
    ComPtr<ID3D11Buffer>              m_SB_Write;     // Write Buffer
    ComPtr<ID3D11Buffer>              m_SB_Read;      // Read Buffer
                                      
    ComPtr<ID3D11ShaderResourceView>  m_SRV;          // Shader Resource View
    ComPtr<ID3D11UnorderedAccessView> m_UAV;          // Unordered Access View
                                                     
    D3D11_BUFFER_DESC                 m_Desc;         // Buffer Desc
    
    bool                              m_SysMemMove;   // Write Read Check
    SB_TYPE                           m_Type;         // Only SRV or SRV | UAV

    UINT                              m_ElementCount; // Buffer 원소 개수
    UINT                              m_ElementSize;  // Buffer 의 Byte

public:
    UINT GetElementCount() { return m_ElementCount; }
    UINT GetElementSize()  { return m_ElementSize; }
    UINT GetBufferSize()   { return m_ElementSize * m_ElementCount; }

    void SetData(void* _pData, UINT _DataSize = 0);
    void GetData(void* _pData, UINT _DataSize = 0);
    void Binding(UINT _RegisterNum);
    void Bind_CS_UAV(UINT _RegisterNum);
    

public:
    int Create(UINT _ElementSize, UINT _ElementCount, SB_TYPE _Type, bool _SysMemMove = false, void* _InitData = nullptr);


public:
    CLONE_DISABLE(CStructuredBuffer);
    CStructuredBuffer();
    virtual ~CStructuredBuffer();
};

