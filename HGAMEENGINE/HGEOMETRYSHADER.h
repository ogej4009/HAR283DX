#pragma once
#include "HSHADER.h"

class HGEOMETRYSHADER : public HSHADER, public HFILEMGR<HGEOMETRYSHADER>
{
public:
	static HPTR<HGEOMETRYSHADER> Load(const HGAMESTRING& _Path, const HGAMESTRING& _FuncName, unsigned int _VH = 5, unsigned int _VL = 0)
	{
		HPTR<HGEOMETRYSHADER> Res = CreateToInsertToName(_Path, _FuncName);
		Res->Load(_FuncName, _VH, _VL);
		return Res;
	}

private:
	ID3D11GeometryShader* m_ShaderPtr;

public:
	void Load(const HGAMESTRING& _FuncName, unsigned int _VH = 5, unsigned int _VL = 0);
	void Setting();
public:
	HGEOMETRYSHADER() : m_ShaderPtr(nullptr)
	{
		m_Type = SHADERTYPE::SHADER_GS;
	}

	~HGEOMETRYSHADER()
	{
		m_ShaderPtr->Release();
	}
};

