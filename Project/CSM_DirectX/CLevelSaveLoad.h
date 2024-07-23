#pragma once

class CLevelSaveLoad
{
public:
	static void LevelSave(const wstring& _FilePath, CLevel* _pLevel);
	static void SaveGameObject(FILE* _pFile, CGameObject* _Object);

	static CLevel* LevelLoad(const wstring& _FilePath);
	static CGameObject* LoadGameObject(FILE* _pFile);
};

