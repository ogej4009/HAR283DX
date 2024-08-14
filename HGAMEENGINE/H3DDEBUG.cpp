#include "H3DDEBUG.h"
#include "HTEXTURE.h"
#include "HRENDERER.h"
#include "HRenderTarget.h"

std::vector<H3DDEBUG::DebugTextInfo> H3DDEBUG::m_AllDebugText;
HPTR<HGAMEFONT> H3DDEBUG::m_DebugFont;

float H3DDEBUG::m_BasicFontSize = 20.0f;
HVECTOR H3DDEBUG::m_BasicStartPos = HVECTOR(0.0F, 0.0F, 0.0F, 0.0F);
HVECTOR H3DDEBUG::m_CurTextSize = HVECTOR(0.0F, 0.0F, 0.0F, 0.0F);
HVECTOR H3DDEBUG::m_BasicColor = HVECTOR::RED;
HPTR<HRENDERPLAYER> H3DDEBUG::m_TargetDebugTextureRenderPlayer;
HPTR<HRENDERPLAYER> H3DDEBUG::m_TargetDebugTextureBackRenderPlayer;
std::vector<H3DDEBUG::DebugTextureInfo> H3DDEBUG::m_AllDebugTexture;
HMATRIX H3DDEBUG::m_VPMAT;


void H3DDEBUG::Init(bool _IsOpenConsole)
{
	HMATRIX P;
	HMATRIX V;
	V.VIEWLH(HVECTOR(0.0F,0.0F, -10.0F), HVECTOR::FORWARD, HVECTOR::UP);
	P.ORTHLH(HGAMEDEVICE::MAINOBJ()->BackBufferRenderTarget()->Texture(0)->Size(), 0.1f, 1000.0f);
	m_VPMAT = V * P;


	HGAMEFONT::Init();

	m_DebugFont = new HGAMEFONT();
	m_DebugFont->CreateGameFont(L"±¼¸²");

	m_TargetDebugTextureRenderPlayer = new HRENDERPLAYER();

	m_TargetDebugTextureRenderPlayer->MESH(L"TargetDebugRect");
	m_TargetDebugTextureRenderPlayer->MATERIAL(L"TARGETDEBUG");
	m_TargetDebugTextureRenderPlayer->SAMPLER(L"Smp", L"LWSMP");

	m_TargetDebugTextureBackRenderPlayer = new HRENDERPLAYER();

	m_TargetDebugTextureBackRenderPlayer->MESH(L"TargetDebugRect");
	m_TargetDebugTextureBackRenderPlayer->MATERIAL(L"TARGETDEBUGBACK");

	

	m_AllDebugText.reserve(100);
	m_AllDebugTexture.reserve(100);

	if (true == _IsOpenConsole)
	{
		OpenConsole();
	}
}


void H3DDEBUG::DrawDebugText(const HGAMESTRING& _Text, float _Size, HVECTOR _Pos, HVECTOR _Color) 
{
	m_AllDebugText.push_back({ _Text, _Size, _Pos, _Color });
}

void H3DDEBUG::DrawDebugTexture(const HPTR<HTEXTURE>& _Texture, HVECTOR _Size, HVECTOR _Pos, HVECTOR _BackColor)
{
	HMATRIX MAT;
	_Size.z = 1.0F;

	_Pos.x += _Size.HX();
	_Pos.y -= _Size.HY();

	MAT.World(_Size, {0.0f, 0.0f, 0.0f, 1.0f}, _Pos);
	MAT = MAT * m_VPMAT;
	m_AllDebugTexture.push_back({ _Texture, _BackColor, MAT});
}


void H3DDEBUG::DebugRender() 
{
	for (size_t i = 0; i < m_AllDebugTexture.size(); i++)
	{
		m_TargetDebugTextureBackRenderPlayer->CBUFFER(L"WVPMATRIX", &m_AllDebugTexture[i].WVP, CBUFFERMODE::CB_LINK);
		m_TargetDebugTextureBackRenderPlayer->CBUFFER(L"BACKCOLOR", &m_AllDebugTexture[i].BackColor, CBUFFERMODE::CB_LINK);
		m_TargetDebugTextureBackRenderPlayer->Render();
		m_TargetDebugTextureBackRenderPlayer->Reset();

		m_TargetDebugTextureRenderPlayer->TEXTURE(L"Tex", m_AllDebugTexture[i].m_Tex);
		m_TargetDebugTextureRenderPlayer->CBUFFER(L"WVPMATRIX", &m_AllDebugTexture[i].WVP, CBUFFERMODE::CB_LINK);
		
		m_TargetDebugTextureRenderPlayer->Render();
		m_TargetDebugTextureRenderPlayer->Reset();

	}

	for (size_t i = 0; i < m_AllDebugText.size(); i++)
	{
		m_DebugFont->DrawFont(m_AllDebugText[i].Text, m_AllDebugText[i].Size, m_AllDebugText[i].Pos, m_AllDebugText[i].Color);
	}


	m_CurTextSize = m_BasicStartPos;

	m_AllDebugText.clear();
	m_AllDebugTexture.clear();
	HGAMEDEVICE::Reset();
}