#include "HSAMPLER.h"


HSAMPLER::HSAMPLER(const D3D11_SAMPLER_DESC& _Desc) : m_Desc(_Desc)
{
	Create();
}

HSAMPLER::~HSAMPLER()
{
	if (nullptr != m_State)
	{
		m_State->Release();
	}
}


void HSAMPLER::Create()
{
	if (S_OK != HGAMEDEVICE::MAINOBJ()->Device()->CreateSamplerState(&m_Desc, &m_State))
	{
		// L"레스터라이저 스테이트 생성에 실패했습니다"
		// const wchar_t* PTR;
		// PTR + 1;
		AMSG(L"레스터라이저 스테이트 생성에 실패했습니다.");
	}
}

void HSAMPLER::Setting(SHADERTYPE _Type, unsigned int _Reg)
{
	switch (_Type)
	{
	case SHADERTYPE::SHADER_VS:
		HGAMEDEVICE::MAINOBJ()->Context()->VSSetSamplers(_Reg, 1, &m_State);
		break;
	case SHADERTYPE::SHADER_HS:
		HGAMEDEVICE::MAINOBJ()->Context()->HSSetSamplers(_Reg, 1, &m_State);
		break;
	case SHADERTYPE::SHADER_DS:
		HGAMEDEVICE::MAINOBJ()->Context()->DSSetSamplers(_Reg, 1, &m_State);
		break;
	case SHADERTYPE::SHADER_GS:
		HGAMEDEVICE::MAINOBJ()->Context()->GSSetSamplers(_Reg, 1, &m_State);
		break;
	case SHADERTYPE::SHADER_PS:
		HGAMEDEVICE::MAINOBJ()->Context()->PSSetSamplers(_Reg, 1, &m_State);
		break;
	case SHADERTYPE::SHADER_END:
		break;
	default:
		break;
	}
}