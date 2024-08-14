#pragma once
#include "HTEXTURE.h"

class HGAMESPRITE : public HMGR<HGAMESPRITE>
{
public:
	static HPTR<HGAMESPRITE> Create(const HGAMESTRING& _Name, unsigned int _X = 1, unsigned int _Y = 1)
	{
		HPTR<HGAMESPRITE> Res = CreateToInsert(_Name);

		// 텍스처가 없으면 스프라이트는 만들수 없다.
		Res->m_Tex = HTEXTURE::Find(_Name);
		if (nullptr == Res->m_Tex)
		{
			AMSG(L"존재하지 않는 텍스처에서 스프라이트를 만들어 내려고 했습니다");
		}

		Res->Create(_X, _Y);
		return Res;
	}

	static HPTR<HGAMESPRITE> Create(const HGAMESTRING& _TexName, const HGAMESTRING& _SpriteName, unsigned int _X, unsigned int _Y)
	{
		HPTR<HGAMESPRITE> Res = CreateToInsert(_SpriteName);

		// 텍스처가 없으면 스프라이트는 만들수 없다.
		Res->m_Tex = HTEXTURE::Find(_TexName);
		if (nullptr == Res->m_Tex)
		{
			AMSG(L"존재하지 않는 텍스처에서 스프라이트를 만들어 내려고 했습니다");
		}

		Res->Create(_X, _Y);
		return Res;
	}

private:
	// 텍스처를 알고 있어야 한다.
	HPTR<HTEXTURE> m_Tex;
	std::vector<HVECTOR> m_SpriteData;

private:
	void Create(unsigned int _X, unsigned int _Y);

public:
	HPTR<HTEXTURE> Tex() {
		return m_Tex;
	}

	HVECTOR SpriteData(unsigned int _Index) 
	{
		if (m_SpriteData.size() <= _Index)
		{
			AMSG(L"존재하지 않는 스프라이트의 인덱스를 입력했습니다.");
		}

		return m_SpriteData[_Index];
	}

};

