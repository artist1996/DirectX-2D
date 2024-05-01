#include "pch.h"
#include "CDevice.h"

CDevice::CDevice()
	: m_hWnd(nullptr)
	, m_Device(nullptr)
	, m_Context(nullptr)
	, m_SwapChain(nullptr)
	, m_RTTex(nullptr)
	, m_DSTex(nullptr)
	, m_RTView(nullptr)
	, m_DSView(nullptr)
	, m_BSState(nullptr)
	, m_DSState(nullptr)
	, m_Sampler(nullptr)
	, m_RSState(nullptr)
{}

CDevice::~CDevice()
{}

int CDevice::Init(HWND _hWnd, UINT _Width, UINT _Height)
{


	return S_OK;
}
