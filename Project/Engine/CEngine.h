#pragma once

class CEngine
	: public CSingleton<CEngine>
{
	SINGLE(CEngine);
	
private:
	HWND  m_hWnd;			// Window Main Handle
	POINT m_ptResolution;	// Window Resolution

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();
	void ChangeWindowScale(UINT _Width, UINT _Height);
};