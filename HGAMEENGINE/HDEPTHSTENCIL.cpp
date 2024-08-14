#include "HDEPTHSTENCIL.h"

HDEPTHSTENCIL::HDEPTHSTENCIL(const D3D11_DEPTH_STENCIL_DESC& _Desc) : m_Desc(_Desc)
{
	Create();
}

HDEPTHSTENCIL::~HDEPTHSTENCIL() 
{
	if (nullptr != m_State)
	{
		m_State->Release();
	}
}


void HDEPTHSTENCIL::Create()
{
	if (S_OK != HGAMEDEVICE::MAINOBJ()->Device()->CreateDepthStencilState(&m_Desc, &m_State))
	{
		// L"�����Ͷ����� ������Ʈ ������ �����߽��ϴ�"
		// const wchar_t* PTR;
		// PTR + 1;
		AMSG(L"�����Ͷ����� ������Ʈ ������ �����߽��ϴ�.");
	}
}

void HDEPTHSTENCIL::Setting()
{
	//;


	// ���̷�Ʈ 11�� ������ 4���� ���Դ�. 
	HGAMEDEVICE::MAINOBJ()->Context()->OMSetDepthStencilState(m_State, 0);
}