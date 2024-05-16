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
	m_matWorld.Translation(); // ������Ŀ��� 4�� 1,2,3 �� ��ȯ, �̵� ��

	// GPU �� ��� �����͸� �����ϴ� �������� �߻��ϴ� ��ġ�� �̸� �����ؼ� ��ġ�� �ϰų�
	// HLSL ���� ��� ������ ������ �� row_major�� �ٿ��־�� �Ѵ�.
	// m_matWorld = XMMatrixTranspose(m_matWorld)
}