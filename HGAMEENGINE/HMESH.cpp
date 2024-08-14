#include "HMESH.h"


HMESH::HMESH()  : m_InstancedRenderCount(0), m_DrawType(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{

}
HMESH::~HMESH() 
{

}

void HMESH::VB(const HGAMESTRING& _Name) 
{
	m_VB = HVBBUFFER::Find(_Name);

	if (nullptr == m_VB)
	{
		AMSG(L"버텍스 버퍼가 nullptr 입니다.");
	}

}
void HMESH::IB(const HGAMESTRING& _Name) 
{
	m_IB = HIBBUFFER::Find(_Name);

	if (nullptr == m_VB)
	{
		AMSG(L"인덱스 버퍼가 nullptr 입니다.");
	}
}

void HMESH::Render() 
{

	//HPTR<HVBBUFFER> VB = HVBBUFFER::Find(L"2DCOLORRECT");
	//HPTR<HIBBUFFER> IB = HIBBUFFER::Find(L"2DCOLORRECT");
	m_VB->Setting();
	m_IB->Setting();

	HGAMEDEVICE::MAINOBJ()->Context()->IASetPrimitiveTopology(m_DrawType);

	if (0 == m_InstancedRenderCount)
	{
		HGAMEDEVICE::MAINOBJ()->Context()->DrawIndexed(m_IB->Count(), 0, 0);
	}
	else 
	{
		HGAMEDEVICE::MAINOBJ()->Context()->DrawIndexedInstanced(m_IB->Count(), m_InstancedRenderCount, 0, 0, 0);
	}
}
//	m_IB->Setting();
//	HGAMEDEVICE::MAINOBJ()->Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
//	HGAMEDEVICE::MAINOBJ()->Context()->DrawIndexedInstanced(m_IB->Count(), InstancedRenderCount, 0, 0, 0);
//}

void HMESH::VB(HPTR<HVBBUFFER> _VB)
{
	if (nullptr == _VB)
	{
		return;
	}

	m_VB = _VB;
}
void HMESH::IB(HPTR<HIBBUFFER> _IB) 
{
	if (nullptr == _IB)
	{
		return;
	}

	m_IB = _IB;
}