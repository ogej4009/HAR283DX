#include "HMATERIAL.h"
#include <HGAMEDEBUG.h>

HMATERIAL::HMATERIAL() : m_AllCheck(true)
{
	m_ALLSHADER.resize((int)SHADERTYPE::SHADER_END);
}
HMATERIAL::~HMATERIAL() 
{

}

RENDERPATHTYPE HMATERIAL::PathType() 
{
	return PIXSHADER()->RPType();
}

void HMATERIAL::VTXSHADER(const HGAMESTRING& _Name) 
{
	m_VTXSHADER = HVTXSHADER::Find(_Name);

	if (nullptr == m_VTXSHADER)
	{
		AMSG(L"존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다." + _Name);
	}

	m_ALLSHADER[(int)SHADERTYPE::SHADER_VS] = m_VTXSHADER;

}

void HMATERIAL::GEOSHADER(const HGAMESTRING& _Name) {
	m_GEOSHADER = HGEOMETRYSHADER::Find(_Name);

	if (nullptr == m_GEOSHADER)
	{
		AMSG(L"존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다." + _Name);
	}

	m_ALLSHADER[(int)SHADERTYPE::SHADER_GS] = m_GEOSHADER;
}
void HMATERIAL::PIXSHADER(const HGAMESTRING& _Name) 
{
	m_PIXSHADER = HPIXSHADER::Find(_Name);

	if (nullptr == m_PIXSHADER)
	{
		AMSG(L"존재하지 않는 픽셀 쉐이더를 세팅하려고 했습니다." + _Name);
	}

	m_ALLSHADER[(int)SHADERTYPE::SHADER_PS] = m_PIXSHADER;
}
void HMATERIAL::RASTERIZER(const HGAMESTRING& _Name) 
{
	m_RASTERIZER = HRASTERIZER::Find(_Name);

	if (nullptr == m_RASTERIZER)
	{
		AMSG(L"존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}
}
void HMATERIAL::DEPTHSTENCIL(const HGAMESTRING& _Name) 
{
	m_DEPTHSTENCIL = HDEPTHSTENCIL::Find(_Name);

	if (nullptr == m_DEPTHSTENCIL)
	{
		AMSG(L"존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}
}
void HMATERIAL::BLEND(const HGAMESTRING& _Name) 
{
	m_BLEND = HBLEND::Find(_Name);

	if (nullptr == m_BLEND)
	{
		AMSG(L"존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}
}

void HMATERIAL::Setting() 
{
	if (true == m_AllCheck)
	{
		if (	nullptr == m_VTXSHADER ||
				nullptr == m_PIXSHADER ||
				nullptr == m_RASTERIZER ||
				nullptr == m_DEPTHSTENCIL ||
				nullptr == m_BLEND)
		{
			AMSG(L"세팅중 nullptr이 있습니다.");
		}
	}

	// 라스트 세팅이라는걸 만들어야 한다고 나중에 말해주세요.
	if (nullptr != m_VTXSHADER)
	{
		m_VTXSHADER->Setting();
	}
	if (nullptr != m_GEOSHADER)
	{
		m_GEOSHADER->Setting();
	}
	if (nullptr != m_PIXSHADER)
	{
		m_PIXSHADER->Setting();
	}
	m_RASTERIZER->Setting();
	m_DEPTHSTENCIL->Setting();
	m_BLEND->Setting();
}