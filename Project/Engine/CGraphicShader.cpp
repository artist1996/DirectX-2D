#include "pch.h"
#include "CGraphicShader.h"

#include "CPathMgr.h"
#include "CDevice.h"

CGraphicShader::CGraphicShader()
	: CShader(ASSET_TYPE::GRAPHIC_SHADER)
	, m_Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, m_RSType(RS_TYPE::CULL_BACK)
	, m_DSType(DS_TYPE::LESS)
	, m_BSType(BS_TYPE::DEFAULT)
	, m_Domain(SHADER_DOMAIN::DOMAIN_NONE)
{
	SetEngineAsset();
}

CGraphicShader::~CGraphicShader()
{
}

int CGraphicShader::CreateVertexShader(const wstring& _RelativePath, const string& _FuncName)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	strFilePath += _RelativePath;
	

	HRESULT hr = D3DCompileFromFile(strFilePath.c_str()
		, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _FuncName.c_str(), "vs_5_0", D3DCOMPILE_DEBUG, 0, m_VSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf());

	if (FAILED(hr))
	{
		if (nullptr != m_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)m_ErrBlob->GetBufferPointer(), "Shader Compile Failed", MB_OK);
		}

		else
		{
			errno_t err = GetLastError();	// Error Number
			wchar_t szErrMsg[255] = {};
			swprintf_s(szErrMsg, 255, L"Error Code : %d", err);

			MessageBox(nullptr, szErrMsg, L"Vertex Shader Compile Failed", MB_OK);
		}

		return E_FAIL;
	}

	// Blob으로 컴파일된 Shader Code의 Pointer와 Size를 넘겨주고 VertexShader 생성
	DEVICE->CreateVertexShader(m_VSBlob->GetBufferPointer()
		, m_VSBlob->GetBufferSize(), nullptr, m_VS.GetAddressOf());

	// Layout 생성
	D3D11_INPUT_ELEMENT_DESC Element[6] = {};

	Element[0].AlignedByteOffset = 0;					      // 정점 데이터의 시작 위치
	Element[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;	      // Data 크기
	Element[0].InputSlot = 0;							      // Buffer가 여러 개 있을 경우 Index 지정
	Element[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;  // Vertex Data (Instance 아직 안함)
	Element[0].InstanceDataStepRate = 0;
	Element[0].SemanticName = "POSITION";					  // Semantic Name 요소의 의미를 나타내는 이름, Shader Code의 입력 Semantic과 일치 해야 함
	Element[0].SemanticIndex = 0;							  // Semantic Name 중복 시 증가

	Element[1].AlignedByteOffset = 12;
	Element[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	Element[1].InputSlot = 0;
	Element[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Element[1].InstanceDataStepRate = 0;
	Element[1].SemanticName = "COLOR";
	Element[1].SemanticIndex = 0;

	Element[2].AlignedByteOffset = 28;
	Element[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	Element[2].InputSlot = 0;
	Element[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Element[2].InstanceDataStepRate = 0;
	Element[2].SemanticName = "TEXCOORD";
	Element[2].SemanticIndex = 0;

	Element[3].AlignedByteOffset = 36;
	Element[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	Element[3].InputSlot = 0;
	Element[3].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Element[3].InstanceDataStepRate = 0;
	Element[3].SemanticName = "TANGENT";
	Element[3].SemanticIndex = 0;

	Element[4].AlignedByteOffset = 48;
	Element[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	Element[4].InputSlot = 0;
	Element[4].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Element[4].InstanceDataStepRate = 0;
	Element[4].SemanticName = "NORMAL";
	Element[4].SemanticIndex = 0;

	Element[5].AlignedByteOffset = 60;
	Element[5].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	Element[5].InputSlot = 0;
	Element[5].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Element[5].InstanceDataStepRate = 0;
	Element[5].SemanticName = "BINORMAL";
	Element[5].SemanticIndex = 0;

	DEVICE->CreateInputLayout(Element, 6
							, m_VSBlob->GetBufferPointer()
							, m_VSBlob->GetBufferSize()
							, m_Layout.GetAddressOf());

	return S_OK;
}

int CGraphicShader::CreateGeometryShader(const wstring& _RelativePath, const string& _FuncName)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _RelativePath;

	HRESULT hr = D3DCompileFromFile(strFilePath.c_str()
								  , nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
								  , _FuncName.c_str(), "gs_5_0", D3DCOMPILE_DEBUG, 0, m_GSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf());

	if (FAILED(hr))
	{
		if (nullptr != m_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)m_ErrBlob->GetBufferPointer(), "Shader Compile Failed", MB_OK);
		}

		else
		{
			errno_t err = GetLastError();
			wchar_t szErrMsg[255] = {};

			swprintf_s(szErrMsg, 255, L"Error Code : %d", err);
			MessageBox(nullptr, szErrMsg, L"Pixel Shader Compile Failed", MB_OK);
		}

		return E_FAIL;
	}

	DEVICE->CreateGeometryShader(m_GSBlob->GetBufferPointer()
							   , m_GSBlob->GetBufferSize(), nullptr, m_GS.GetAddressOf());

	return S_OK;
}

int CGraphicShader::CreatePixelShader(const wstring& _RelativePath, const string& _FuncName)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _RelativePath;

	HRESULT hr = D3DCompileFromFile(strFilePath.c_str()
									, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
									, _FuncName.c_str(), "ps_5_0", D3DCOMPILE_DEBUG, 0, m_PSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf());

	if (FAILED(hr))
	{
		if (nullptr != m_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)m_ErrBlob->GetBufferPointer(), "Shader Compile Failed", MB_OK);
		}

		else
		{
			errno_t err = GetLastError();
			wchar_t szErrMsg[255] = {};

			swprintf_s(szErrMsg, 255, L"Error Code : %d", err);
			MessageBox(nullptr, szErrMsg, L"Pixel Shader Compile Failed", MB_OK);
		}

		return E_FAIL;
	}

	DEVICE->CreatePixelShader(m_PSBlob->GetBufferPointer()
							, m_PSBlob->GetBufferSize(), nullptr, m_PS.GetAddressOf());

	return S_OK;
}

void CGraphicShader::Binding()
{
	CONTEXT->IASetPrimitiveTopology(m_Topology);
	CONTEXT->IASetInputLayout(m_Layout.Get());

	CONTEXT->VSSetShader(m_VS.Get(), nullptr, 0);
	CONTEXT->GSSetShader(m_GS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(m_PS.Get(), nullptr, 0);

	CONTEXT->RSSetState(CDevice::GetInst()->GetRSState(m_RSType));

	CONTEXT->OMSetDepthStencilState(CDevice::GetInst()->GetDSState(m_DSType), 0);
	CONTEXT->OMSetBlendState(CDevice::GetInst()->GetBSState(m_BSType), nullptr, 0xffffffff);
}