#include "pch.h"
#include "CPathMgr.h"

#include "CEngine.h"

CPathMgr::CPathMgr()	
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::Init()
{
	// �����θ� ����
	wchar_t szBuffer[256] = {};
	GetCurrentDirectory(256, szBuffer);

	// bin ������ ���������� �����Ѵ�.
	GetParentPath(szBuffer);

	// \\Content\\ �� �ٿ��д�
	m_Content = szBuffer;
	m_Content += L"\\content\\";	
}

void CPathMgr::render()
{	
}

void CPathMgr::GetParentPath(_Inout_ wchar_t* _Buffer)
{
	size_t len = wcslen(_Buffer);
	
	for (size_t i = len - 1; 0 < i; --i)
	{
		if (L'\\' == _Buffer[i])
		{
			_Buffer[i] = L'\0';
			break;
		}
	}
}

wstring CPathMgr::GetRelativePath(const wstring& _FilePath)
{
	// Content Path �� Pos �� ã�ƿ´�.
	size_t FindPos = _FilePath.find(m_Content);

	if (FindPos == wstring::npos)
		return L"";

	// ã�ƿ� FindPos �� Pos�� �� ���� Pos�� ��ȯ �ϴ°� �ƴ� �� ���� Pos��
	// ��ȯ�ϱ� ������ Content Path�� �� ���� �� _FilePath�� length �� �־��ش�.
	return _FilePath.substr(FindPos + m_Content.length(), _FilePath.length());
}
