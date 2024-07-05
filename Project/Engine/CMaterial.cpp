#include "pch.h"
#include "CMaterial.h"

#include "CDevice.h"
#include "CAssetMgr.h"
#include "CConstBuffer.h"

CMaterial::CMaterial()
	: CAsset(ASSET_TYPE::MATERIAL)
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::Binding()
{
	if (!m_Shader)
		return;

	for (int i = 0; i < TEX_PARAM::END; ++i)
	{
		if (nullptr == m_arrTex[i])
		{
			m_Const.btex[i] = 0;
			CTexture::Clear(i);
			continue;
		}
			
		m_Const.btex[i] = 1;
		m_arrTex[i]->Binding(i);
	}
	
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pCB->SetData(&m_Const);
	pCB->Binding();

	m_Shader->Binding();
}

int CMaterial::Save(const wstring& _RelativePath)
{
	SetRelativePath(_RelativePath);

	FILE* pFile = nullptr;

	wstring FilePath = CPathMgr::GetInst()->GetContentPath();

	FilePath += _RelativePath;

	_wfopen_s(&pFile, FilePath.c_str(), L"wb");

	if (nullptr == pFile)
		return E_FAIL;

	// 어떤 쉐이더를 참조 했는지
	SaveAssetRef(m_Shader, pFile);
	
	// 상수 데이터
	fwrite(&m_Const, sizeof(tMtrlConst), 1, pFile);
	
	for (UINT i = 0; i < TEX_PARAM::END; ++i)
	{
		SaveAssetRef(m_arrTex[i], pFile);
	}

	fclose(pFile);
	
	return S_OK;
}

int CMaterial::Load(const wstring& _FilePath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FilePath.c_str(), L"rb");

	if (nullptr == pFile)
		return E_FAIL;

	LoadAssetRef(m_Shader, pFile);

	fread(&m_Const, sizeof(tMtrlConst), 1, pFile);

	for (UINT i = 0; i < TEX_PARAM::END; ++i)
	{
		LoadAssetRef(m_arrTex[i], pFile);
	}

	fclose(pFile);

	return S_OK;
}
