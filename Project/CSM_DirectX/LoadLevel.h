#pragma once

#include <Engine/CLevel.h>
#include <thread>
#include <mutex>

class LoadLevel
	: public CLevel
{
public:
	LoadLevel();
	virtual ~LoadLevel();

public:
	void Init();
	void Tick();
	void Load(std::mutex& _mtx);

private:
	void Reload();
	void FindAssetName(const wstring& _FolderPath, const wstring& _Filter);
	void LoadAsset(const path& _Path);

private:
	vector<wstring> m_vecAssetPath; // Content 폴더 내 Asset 들의 상대 경로
	std::thread		m_thread;
	std::mutex		m_mtx;
	bool			m_Complete;
	float			m_Time;
};

