#include "pch.h"
#include "Temp.h"

#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

// Vertex Buffer
ID3D11Buffer* g_VB = nullptr;
Vtx g_Vtx[6] = {};

// Vertex Shader 생성
ID3DBlob*			g_VSBlob = nullptr;
ID3D11VertexShader* g_VS = nullptr;

// Pixel Shader 생성
ID3DBlob*		    g_PSBlob = nullptr;
ID3D11PixelShader*  g_PS = nullptr;

// Error Blob
ID3DBlob*			g_ErrBlob = nullptr;

// Layout
ID3D11InputLayout*  g_Layout = nullptr;


int TempInit()
{
	// Vertex Buffer 생성	(삼각형 그릴 것 정점 3개)
	g_Vtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	g_Vtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_Vtx[1].vPos = Vec3(0.5f, -0.5f, 0.f);
	g_Vtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_Vtx[2].vPos = Vec3(-0.5f, -0.5f, 0.f);
	g_Vtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	g_Vtx[3].vPos = Vec3(-0.5f, 0.5f, 0.f);
	g_Vtx[3].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	g_Vtx[4].vPos = Vec3(0.5f, 0.5f, 0.f);
	g_Vtx[4].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	
	g_Vtx[5].vPos = Vec3(0.5f, -0.5f, 0.f);
	g_Vtx[5].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	D3D11_BUFFER_DESC tVtxBufferDesc = {};
	
	tVtxBufferDesc.ByteWidth = sizeof(Vtx) * 6;					// 중요
	tVtxBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tVtxBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tVtxBufferDesc.CPUAccessFlags = 0;
	tVtxBufferDesc.MiscFlags = 0;
	tVtxBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = g_Vtx;

	if (FAILED(DEVICE->CreateBuffer(&tVtxBufferDesc, &tSub, &g_VB)))
	{
		MessageBox(nullptr, L"VertexBuffer 생성 실패", L"Temp 초기화 실패", MB_OK);
		return E_FAIL;
	}
	
	// Vertex Shader 생성
	wstring strShaderPath = CPathMgr::GetInst()->GetContentPath();

	HRESULT hr = D3DCompileFromFile((strShaderPath + L"shader\\test.fx").c_str()
									, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
									, "VS_Test", "vs_5_0", D3DCOMPILE_DEBUG, 0, &g_VSBlob, &g_ErrBlob);

	if (FAILED(hr))
	{
		if (nullptr != g_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)g_ErrBlob->GetBufferPointer(), "Shader Compile Failed", MB_OK);
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
	DEVICE->CreateVertexShader(g_VSBlob->GetBufferPointer()
							  , g_VSBlob->GetBufferSize(), nullptr, &g_VS);

	
	// Pixel Shader 생성
	hr = D3DCompileFromFile((strShaderPath + L"shader\\test.fx").c_str()
							, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
							, "PS_Test", "ps_5_0", D3DCOMPILE_DEBUG, 0, &g_PSBlob, &g_ErrBlob);


	if (FAILED(hr))
	{
		if (nullptr != g_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)g_ErrBlob->GetBufferPointer(), "Shader Compile Failed", MB_OK);
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

	DEVICE->CreatePixelShader(g_PSBlob->GetBufferPointer()
							, g_PSBlob->GetBufferSize(), nullptr, &g_PS);

	// Layout 생성
	D3D11_INPUT_ELEMENT_DESC Element[2] = {};		          // 현재 Vtx의 멤버가 Position, Color 2개 이기 때문에 2개를 초기화

	Element[0].AlignedByteOffset = 0;					      // 정점 데이터의 시작 위치
	Element[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;	      // Data 크기
	Element[0].InputSlot = 0;							      // Buffer가 여러 개 있을 경우 Index 지정
	Element[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;  // Vertex Data (Instance 아직 안함)
	Element[0].InstanceDataStepRate = 0;
	Element[0].SemanticName = "POSITION";					  // Semantic Name 요소의 의미를 나타내는 이름, Shader Code의 입력 Semantic과 일치 해야 함
	Element[0].SemanticIndex = 0;							  // SemanticName 중복 시 증가
	
	Element[1].AlignedByteOffset = 12;					    
	Element[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;	    
	Element[1].InputSlot = 0;							    
	Element[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Element[1].InstanceDataStepRate = 0;
	Element[1].SemanticName = "COLOR";					
	Element[1].SemanticIndex = 0;

	DEVICE->CreateInputLayout(Element, 2, g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize(), &g_Layout);

	return S_OK;
}

void TempTick()
{
}

void TempRender()
{
	UINT Stride = sizeof(Vtx);	// Vertex 크기
	UINT Offset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, &g_VB, &Stride, &Offset);
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 3개의 점을 하나의 삼각형으로 해석
	CONTEXT->IASetInputLayout(g_Layout);
	
	CONTEXT->VSSetShader(g_VS, nullptr, 0);
	CONTEXT->PSSetShader(g_PS, nullptr, 0);


	CONTEXT->Draw(6, 0);
}

void TempRelease()
{
	g_VB->Release();
	g_VSBlob->Release();
	g_VS->Release();

	g_PSBlob->Release();
	g_PS->Release();
	
	g_Layout->Release();

	if (nullptr != g_ErrBlob)
		g_ErrBlob->Release();
}