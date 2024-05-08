#include "pch.h"
#include "CEngine.h"
#include "CDevice.h"
#include "CPathMgr.h"

#include "Temp.h"


CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
{}

CEngine::~CEngine()
{
	TempRelease();
}

int CEngine::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	ChangeWindowScale(m_ptResolution.x, m_ptResolution.y);

	// Device �ʱ�ȭ
	if (FAILED(CDevice::GetInst()->Init(m_hWnd, m_ptResolution.x, m_ptResolution.y)))
	{
		MessageBox(nullptr, L"��ġ �ʱ�ȭ ����", L"CDevice �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	CPathMgr::GetInst()->Init();

	if (FAILED(TempInit()))
	{
		MessageBox(nullptr, L"Failed TempInit", L"CEngine �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void CEngine::ChangeWindowScale(UINT _Width, UINT _Height)
{
	// Create Window and Change Window Size
	bool bMenu = false;

	if (GetMenu(m_hWnd))
		bMenu = true;
	
	RECT rt = { 0,0, (LONG)_Width, (LONG)_Height };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, bMenu);
	SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void CEngine::Progress()
{
	TempTick();

	CDevice::GetInst()->Clear();

	TempRender();

	CDevice::GetInst()->Present();
}