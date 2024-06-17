#include "pch.h"
#include "CStructuredBuffer.h"

#include "CDevice.h"

CStructuredBuffer::CStructuredBuffer()
	: m_Desc{}
	, m_ElementCount(0)
	, m_ElementSize(0)
{
}

CStructuredBuffer::~CStructuredBuffer()
{
}

int CStructuredBuffer::Create(UINT _ElementCount, UINT _ElementSize, void* _InitData)
{
	// ComPtr 특성 상 대입 연산자가 아니면 Release 함수를 호출 하지 않기 때문에 생성 할 때마다 nullptr 대입 해 Release 호출
	m_SB = nullptr;
	m_SRV = nullptr;

	m_ElementCount = _ElementCount;
	m_ElementSize  = _ElementSize;

	// Desc 초기화
	m_Desc.BindFlags			 = D3D11_BIND_SHADER_RESOURCE;

	m_Desc.Usage				 = D3D11_USAGE_DYNAMIC;
	m_Desc.CPUAccessFlags		 = D3D11_CPU_ACCESS_WRITE;

	m_Desc.ByteWidth			 = m_ElementSize * m_ElementCount;

	m_Desc.MiscFlags			 = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	m_Desc.StructureByteStride	 = m_ElementSize;

	HRESULT hr = S_OK;
	
	if (nullptr == _InitData)
	{
		hr = DEVICE->CreateBuffer(&m_Desc, nullptr, m_SB.GetAddressOf());
	}

	else
	{
		D3D11_SUBRESOURCE_DATA tSub = {};
		tSub.pSysMem = _InitData;
		hr = DEVICE->CreateBuffer(&m_Desc, &tSub, m_SB.GetAddressOf());
	}

	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// Create Shader Resource View

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};

	SRVDesc.ViewDimension = D3D_SRV_DIMENSION_BUFFER;
	SRVDesc.BufferEx.NumElements = m_ElementCount;

	if (FAILED(DEVICE->CreateShaderResourceView(m_SB.Get(), &SRVDesc, m_SRV.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CStructuredBuffer::SetData(void* _pData, UINT _DataSize)
{
	assert(_DataSize <= m_Desc.ByteWidth);

	if (0 == _DataSize)
	{
		_DataSize = m_Desc.ByteWidth;
	}

	D3D11_MAPPED_SUBRESOURCE tMapSub = {};
	CONTEXT->Map(m_SB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tMapSub);
	memcpy(tMapSub.pData, _pData, _DataSize);
	CONTEXT->Unmap(m_SB.Get(), 0);
}

void CStructuredBuffer::Binding(UINT _RegisterNum)
{
	CONTEXT->VSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
	CONTEXT->HSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
	CONTEXT->DSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
	CONTEXT->GSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
	CONTEXT->PSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
}