#include "pch.h"
#include "Temp.h"

#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

// Vertex Buffer
ComPtr<ID3D11Buffer>	    g_VB = nullptr;
Vtx g_Vtx[4] = {};

// Index Buffer
ComPtr<ID3D11Buffer>	    g_IB = nullptr;
UINT g_Idx[6] = {};

// Constant Buffer
ComPtr<ID3D11Buffer>		g_CB = nullptr;
tTransform				    g_ObjTrans = {};

// Vertex Shader 생성
ComPtr<ID3DBlob>		    g_VSBlob = nullptr;
ComPtr<ID3D11VertexShader>  g_VS = nullptr;

// Pixel Shader 생성
ComPtr<ID3DBlob>		    g_PSBlob = nullptr;
ComPtr<ID3D11PixelShader>   g_PS = nullptr;

// Error Blob
ComPtr<ID3DBlob>			g_ErrBlob = nullptr;

// Layout
ComPtr<ID3D11InputLayout>   g_Layout = nullptr;


int TempInit()
{
	g_ObjTrans.Scale = Vec4(1.f, 1.f, 1.f, 1.f);

	// Vertex Buffer 생성	(삼각형 그릴 것 정점 3개)
	g_Vtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	g_Vtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	
	g_Vtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	g_Vtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_Vtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	g_Vtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	g_Vtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	g_Vtx[3].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	D3D11_BUFFER_DESC tVtxBufferDesc = {};
	
	tVtxBufferDesc.ByteWidth = sizeof(Vtx) * 4;					// 중요
	tVtxBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tVtxBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tVtxBufferDesc.CPUAccessFlags = 0;
	tVtxBufferDesc.MiscFlags = 0;
	tVtxBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = g_Vtx;

	if (FAILED(DEVICE->CreateBuffer(&tVtxBufferDesc, &tSub, g_VB.GetAddressOf())))
	{
		MessageBox(nullptr, L"VertexBuffer 생성 실패", L"Temp 초기화 실패", MB_OK);
		return E_FAIL;
	}
	
	// Index Buffer 생성
	g_Idx[0] = 0; g_Idx[1] = 1; g_Idx[2] = 2;
	g_Idx[3] = 0; g_Idx[4] = 2; g_Idx[5] = 3;

	D3D11_BUFFER_DESC tIdxBufferDesc = {};

	tIdxBufferDesc.ByteWidth = sizeof(UINT) * 6;
	tIdxBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// Index Buffer가 생성된 이후에 데이터가 변경될 일이 없다.
	tIdxBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tIdxBufferDesc.CPUAccessFlags = 0;
	tIdxBufferDesc.MiscFlags = 0;
	tIdxBufferDesc.StructureByteStride = 0;
	
	tSub.pSysMem = g_Idx;

	if (FAILED(DEVICE->CreateBuffer(&tIdxBufferDesc, &tSub, g_IB.GetAddressOf())))
	{
		MessageBox(nullptr, L"IndexBuffer 생성 실패", L"Temp 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// Constant Buffer 생성
	D3D11_BUFFER_DESC tCBDesc = {};

	tCBDesc.ByteWidth = sizeof(tTransform);
	tCBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tCBDesc.Usage = D3D11_USAGE_DYNAMIC;
	tCBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	if (FAILED(DEVICE->CreateBuffer(&tCBDesc, nullptr, g_CB.GetAddressOf())))
	{
		MessageBox(nullptr, L"ConstantBuffer 생성 실패", L"Temp 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// Vertex Shader 생성
	wstring strShaderPath = CPathMgr::GetInst()->GetContentPath();

	HRESULT hr = D3DCompileFromFile((strShaderPath + L"shader\\test.fx").c_str()
								, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
								, "VS_Test", "vs_5_0", D3DCOMPILE_DEBUG, 0, g_VSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf());
	
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
							  , g_VSBlob->GetBufferSize(), nullptr, g_VS.GetAddressOf());

	
	// Pixel Shader 생성
	hr = D3DCompileFromFile((strShaderPath + L"shader\\test.fx").c_str()
							, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
							, "PS_Test", "ps_5_0", D3DCOMPILE_DEBUG, 0, g_PSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf());


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
							, g_PSBlob->GetBufferSize(), nullptr, g_PS.GetAddressOf());

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

	DEVICE->CreateInputLayout(Element, 2, g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize(), g_Layout.GetAddressOf());

	return S_OK;
}

void TempTick()
{
	float DeltaTime = CTimeMgr::GetInst()->GetDeltaTime();


	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT))
	{
		g_ObjTrans.Pos.x += DeltaTime * 1.f;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::LEFT))
	{
		g_ObjTrans.Pos.x -= DeltaTime * 1.f;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::UP))
	{
		g_ObjTrans.Pos.y += DeltaTime * 1.f;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::DOWN))
	{
		g_ObjTrans.Pos.y -= DeltaTime * 1.f;
	}

	D3D11_MAPPED_SUBRESOURCE tMapSub = {};

	CONTEXT->Map(g_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapSub);

	memcpy(tMapSub.pData, &g_ObjTrans, sizeof(tTransform));

	CONTEXT->Unmap(g_CB.Get(), 0);
}

void TempRender()
{
	UINT Stride = sizeof(Vtx);	// Vertex 크기
	UINT Offset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &Stride, &Offset);
	CONTEXT->IASetIndexBuffer(g_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 3개의 점을 하나의 삼각형으로 해석
	CONTEXT->IASetInputLayout(g_Layout.Get());
	
	CONTEXT->VSSetConstantBuffers(0, 1, g_CB.GetAddressOf());
	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	CONTEXT->DrawIndexed(6, 0, 0);
}

void TempRelease()
{
}