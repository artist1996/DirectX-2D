#pragma once

class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wstring		m_Content;
	wstring		m_Solution;


public:
	void init();
	void render();

private:
	void GetParentPath(_Inout_ wchar_t* _Buffer);

public:
	const wstring& GetContehtPath() { return m_Content; }
	const wstring& GetSolutionPath() { return m_Solution; }	
};

