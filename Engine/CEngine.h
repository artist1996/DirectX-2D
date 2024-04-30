#pragma once
class CEngine
{
private:
	static CEngine* g_Inst;

public:
	static CEngine* GetInst()
	{
		if (nullptr == g_Inst)
		{
			g_Inst = new CEngine;
		}

		return g_Inst;
	}

	static void Destroy()
	{
		if (nullptr != g_Inst)
		{
			delete g_Inst;
			g_Inst = nullptr;
		}
	}

private:
	CEngine();
	CEngine(const CEngine& _Other) = delete;
	~CEngine();
};