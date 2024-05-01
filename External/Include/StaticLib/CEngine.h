#pragma once

class CEngine
	: public CSingleton<CEngine>
{
private:
	CEngine();
	~CEngine();
	friend class CSingleton<CEngine>;
};