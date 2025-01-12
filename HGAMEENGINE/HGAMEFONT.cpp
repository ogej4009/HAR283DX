#include "HGAMEFONT.h"
#include "HGAMEDEVICE.h"

IFW1Factory* HGAMEFONT::m_pFontFactory = nullptr;

HGAMEFONT::HGAMEFONTSTART HGAMEFONT::Starter;

void HGAMEFONT::Init() 
{
	if (S_OK != FW1CreateFactory(FW1_VERSION, &m_pFontFactory))
	{
		AMSG(L"폰트 팩토리 생성에 실패했습니다.");
	}
}

HGAMEFONT::HGAMEFONTSTART::~HGAMEFONTSTART() 
{
	if (nullptr != m_pFontFactory)
	{
		m_pFontFactory->Release();
	}
}



HGAMEFONT::HGAMEFONT() : m_pFontWrapper(nullptr)
{
}
HGAMEFONT::~HGAMEFONT() 
{
	if (nullptr != m_pFontWrapper)
	{
		m_pFontWrapper->Release();
	}
}

void HGAMEFONT::CreateGameFont(const HGAMESTRING& _Name) 
{
	if (S_OK != m_pFontFactory->CreateFontWrapper(HGAMEDEVICE::MAINOBJ()->Device(), _Name, &m_pFontWrapper))
	{
		AMSG(L"폰트 생성에 실패했습니다. " + _Name);
	}
}

void HGAMEFONT::DrawFont(const HGAMESTRING& _Text, float _Size, HVECTOR _Pos, HVECTOR _Color, FW1_TEXT_FLAG _Flag) 
{
	m_pFontWrapper->DrawString(HGAMEDEVICE::MAINOBJ()->Context(), _Text, _Size, _Pos.x, _Pos.y, _Color.ColorToUint(), _Flag);
}