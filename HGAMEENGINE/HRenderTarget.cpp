#include "HRenderTarget.h"
#include "HTEXTURE.h"

HRENDERPLAYER HRenderTarget::TargetMergePlayer;
HRENDERPLAYER HRenderTarget::TargetPlusPlayer;

void HRenderTarget::Init() 
{
	TargetMergePlayer.MESH(L"TargetFullRect");
	TargetMergePlayer.MATERIAL(L"TargetMerge");
	TargetMergePlayer.SAMPLER(L"SAMPLER", L"LWSMP");

	TargetPlusPlayer.MESH(L"TargetFullRect");
	TargetPlusPlayer.MATERIAL(L"TargetPlus");
	TargetPlusPlayer.SAMPLER(L"SAMPLER", L"LWSMP");

	
}

HRenderTarget::HRenderTarget() : m_Depth(nullptr)
{

}
HRenderTarget::~HRenderTarget()
{

}

void HRenderTarget::CreateViewPort(D3D11_TEXTURE2D_DESC _Desc)
{
	D3D11_VIEWPORT ViewPort;
	ViewPort = { 0, };
	// ������ ��ǥ�� ����̴�.
	ViewPort.TopLeftX = 0.0f;
	ViewPort.TopLeftY = 0.0f;
	ViewPort.Width = (float)_Desc.Width;
	ViewPort.Height = (float)_Desc.Height;
	ViewPort.MinDepth = 0.0f;
	ViewPort.MaxDepth = 1.0f;
	m_VIEWPORT.push_back(ViewPort);
}

void HRenderTarget::Clear(bool _IsDepthClear) 
{
	if (true == _IsDepthClear && nullptr != m_Depth)
	{
		HGAMEDEVICE::MAINOBJ()->Context()->ClearDepthStencilView(m_Depth->DSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	for (size_t i = 0; i < m_AllTexture.size(); i++)
	{
		if (false == m_Clear[i])
		{
			continue;
		}

		HGAMEDEVICE::MAINOBJ()->Context()->ClearRenderTargetView(m_AllTexture[i]->RTV(), m_ClearColor[i].Arr);
	}

}

void HRenderTarget::Setting(int _Index) 
{
	HGAMEDEVICE::MAINOBJ()->Context()->RSSetViewports((unsigned int)1, &m_VIEWPORT[_Index]);

	if (nullptr != m_Depth)
	{
		HGAMEDEVICE::MAINOBJ()->Context()->OMSetRenderTargets(1, &m_AllRTV[_Index], m_Depth->DSV());

	}
	else
	{
		HGAMEDEVICE::MAINOBJ()->Context()->OMSetRenderTargets(1, &m_AllRTV[_Index], nullptr);
	}
}

void HRenderTarget::Setting() 
{
	
	HGAMEDEVICE::MAINOBJ()->Context()->RSSetViewports((unsigned int)m_VIEWPORT.size(), &m_VIEWPORT[0]);

	if (nullptr != m_Depth)
	{
		HGAMEDEVICE::MAINOBJ()->Context()->OMSetRenderTargets((unsigned int)m_AllRTV.size(), &m_AllRTV[0], m_Depth->DSV());

	}
	else 
	{
		HGAMEDEVICE::MAINOBJ()->Context()->OMSetRenderTargets((unsigned int)m_AllRTV.size(), &m_AllRTV[0], nullptr);
	}
}

void HRenderTarget::Reset() 
{
	ID3D11RenderTargetView* ArrNullptr[8] = {nullptr,};
	HGAMEDEVICE::MAINOBJ()->Context()->OMSetRenderTargets((unsigned int)m_AllRTV.size(), ArrNullptr, nullptr);
}


void HRenderTarget::CreateTarget(HVECTOR _Size, HVECTOR _ClearColor, bool _Clear, DXGI_FORMAT _Fmt, unsigned int _BindFlag)
{
	HTEXTURE* NewRenderTargetTexture = new HTEXTURE();
	// D3D11_USAGE::D3D11_USAGE_DEFAULT �׷���ī�忡 �޸� �Ҵ��ض�. �׸��� �Ȱǵ�ڴ�.
	// D3D11_USAGE::D3D11_USAGE_DYNAMIC �׷���ī�忡 �޸𸮸� �Ҵ��ض�. �׸��� �ǵ�ڴ�.
	// D3D11_USAGE::D3D11_USAGE_ �׷���ī�忡 �޸𸮸� �Ҵ��ض�. �׸��� �ǵ�ڴ�.
	NewRenderTargetTexture->Create(_Size, _Fmt, _BindFlag, D3D11_USAGE::D3D11_USAGE_DEFAULT);

	m_AllTexture.push_back(NewRenderTargetTexture);
	if (nullptr == NewRenderTargetTexture->RTV())
	{
		AMSG(L"if (nullptr == NewRenderTargetTexture->RTV())");
	}

	m_ClearColor.push_back(_ClearColor);

	CreateViewPort(NewRenderTargetTexture->TextDesc());
	m_AllRTV.push_back(NewRenderTargetTexture->RTV());
	m_Clear.push_back(_Clear);
}

void HRenderTarget::CreateTarget(ID3D11Texture2D* _BackBufferTex, HVECTOR _ClearColor /*= HVECTOR::BLUE*/, bool _Clear)
{
	HTEXTURE* NewRenderTargetTexture = new HTEXTURE();
	NewRenderTargetTexture->Create(_BackBufferTex);

	CreateTarget(NewRenderTargetTexture, _ClearColor, _Clear);

}

void HRenderTarget::CreateTarget(HPTR<HTEXTURE> _TargetTex, HVECTOR _ClearColor, bool _Clear) 
{
	m_AllTexture.push_back(_TargetTex);
	if (nullptr == _TargetTex->RTV())
	{
		AMSG(L"if (nullptr == NewRenderTargetTexture->RTV())");
	}

	m_ClearColor.push_back(_ClearColor);
	m_Clear.push_back(_Clear);

	CreateViewPort(_TargetTex->TextDesc());
	m_AllRTV.push_back(_TargetTex->RTV());
}

void HRenderTarget::CreateDepth(unsigned int _TargetIndex /*= 0*/) 
{
	if (_TargetIndex >= m_AllTexture.size())
	{
		AMSG(L"if (_TargetIndex >= m_AllTexture.size())");
	}

	m_Depth = new HTEXTURE();

	// ���� 
	// ������ �ɹ������� ��� public�϶��� �ȴ�.
	// �׸��� �ƹ��� �����ڵ� ����� �Ѵ�.
	D3D11_TEXTURE2D_DESC TD = { 0, };

	TD.ArraySize = 1;

	TD.Width = m_AllTexture[0]->TextDesc().Width;
	TD.Height = m_AllTexture[0]->TextDesc().Height;
	TD.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	TD.SampleDesc.Count = 1;
	TD.SampleDesc.Quality = 0;
	TD.MipLevels = 1;
	// ������ �׷��� ī�忡 
	TD.Usage = D3D11_USAGE_DEFAULT;
	TD.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	m_Depth->Create(TD);

	/*m_pDevice->CreateTexture2D(&TD, 0, &m_DepthStencilTex);
	if (nullptr == m_DepthStencilTex)
	{
		AMSG(L"���� ���� �ؽ�ó�� ������ ���߽��ϴ�.");
	}

	m_pDevice->CreateDepthStencilView(m_DepthStencilTex, 0, &m_DSV);
	if (nullptr == m_DSV)
	{
		AMSG(L"���� ���� ������(DSV)�� ������ ���߽��ϴ�.");
	}*/
}

void HRenderTarget::Depth(HPTR<HTEXTURE> _Depth) 
{
	if (nullptr == _Depth)
	{
		AMSG(L"if (nullptr == _Depth)");
	}


	m_Depth = _Depth;
}

HPTR<HTEXTURE> HRenderTarget::Depth()
{
	return m_Depth;
}

void HRenderTarget::Merge(HPTR<HRenderTarget> _Target, int _ThisIndex, int _OtherIndex, bool _AlphaOption)
{
	// ����� ����Ÿ��
	Setting(_ThisIndex);

	Option.AlphaOption = _AlphaOption;

	TargetMergePlayer.CBUFFER(L"MergeOption", &Option, CBUFFERMODE::CB_LINK);
	TargetMergePlayer.TEXTURE(L"TargetTex", _Target->Texture(_OtherIndex));
	TargetMergePlayer.Render();
	TargetMergePlayer.Reset();

	// ���׸��� ã��
	// �Ž� ã������ �����ϸ� �Ǵµ�.

}

void HRenderTarget::Plus(HPTR<HRenderTarget> _Target, int _ThisIndex/* = 0*/, int _OtherIndex/* = 0*/, bool _AlphaOption /*= false*/) 
{
	// ����� ����Ÿ��
	Setting(_ThisIndex);

	Option.AlphaOption = _AlphaOption;

	TargetPlusPlayer.CBUFFER(L"MergeOption", &Option, CBUFFERMODE::CB_LINK);
	TargetPlusPlayer.TEXTURE(L"TargetTex", _Target->Texture(_OtherIndex));
	TargetPlusPlayer.Render();
	TargetPlusPlayer.Reset();

}