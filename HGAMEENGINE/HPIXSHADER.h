#pragma once
#include "HSHADER.h"

enum class RENDERPATHTYPE
{
	RP_FORWARD,
	RP_DEFFERD,
	RP_SHADOW,
};

class HPIXSHADER : public HSHADER, public HFILEMGR<HPIXSHADER>
{
public:
	static HPTR<HPIXSHADER> Load(const HGAMESTRING& _Path, const HGAMESTRING& _FuncName, unsigned int _VH = 5, unsigned int _VL = 0)
	{
		HPTR<HPIXSHADER> Res = CreateToInsertToName(_Path, _FuncName);
		Res->Load(_FuncName, _VH, _VL);
		return Res;
	}

private:
	RENDERPATHTYPE m_RPType;
	ID3D11PixelShader* m_ShaderPtr;

public:
	void RPType(RENDERPATHTYPE _RPType) 
	{
		m_RPType = _RPType;
	}

	RENDERPATHTYPE RPType()
	{
		return m_RPType;
	}

public:
	void Load(const HGAMESTRING& _FuncName, unsigned int _VH = 5, unsigned int _VL = 0);
	void Setting();
public:
	HPIXSHADER() : m_ShaderPtr(nullptr), m_RPType(RENDERPATHTYPE::RP_FORWARD)
	{
		m_Type = SHADERTYPE::SHADER_PS;
	}

	~HPIXSHADER()
	{
		m_ShaderPtr->Release();
	}
};

