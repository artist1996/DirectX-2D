#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
{
}

CTransform::~CTransform()
{
}


void CTransform::FinalTick()
{
}

void CTransform::Binding()
{
	//tTransform tTrans = {};
	//tTrans.Pos = m_RelativePos;
	//tTrans.Scale = m_RelativeScale;
	//
	//CConstBuffer* pTranformCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	//pTranformCB->SetData(&tTrans);
	//pTranformCB->Binding();

	m_matWorld = XMMatrixIdentity();
	m_matWorld.Translation(); // 상태행렬에서 4행 1,2,3 열 반환, 이동 값

	// GPU 에 행렬 데이터를 전달하는 과정에서 발생하는 전치를 미리 예상해서 전치를 하거나
	// HLSL 에서 행렬 변수를 선언할 때 row_major를 붙여주어야 한다.
	// m_matWorld = XMMatrixTranspose(m_matWorld)
}