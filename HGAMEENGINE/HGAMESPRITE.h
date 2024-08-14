#pragma once
#include "HTEXTURE.h"

class HGAMESPRITE : public HMGR<HGAMESPRITE>
{
public:
	static HPTR<HGAMESPRITE> Create(const HGAMESTRING& _Name, unsigned int _X = 1, unsigned int _Y = 1)
	{
		HPTR<HGAMESPRITE> Res = CreateToInsert(_Name);

		// �ؽ�ó�� ������ ��������Ʈ�� ����� ����.
		Res->m_Tex = HTEXTURE::Find(_Name);
		if (nullptr == Res->m_Tex)
		{
			AMSG(L"�������� �ʴ� �ؽ�ó���� ��������Ʈ�� ����� ������ �߽��ϴ�");
		}

		Res->Create(_X, _Y);
		return Res;
	}

	static HPTR<HGAMESPRITE> Create(const HGAMESTRING& _TexName, const HGAMESTRING& _SpriteName, unsigned int _X, unsigned int _Y)
	{
		HPTR<HGAMESPRITE> Res = CreateToInsert(_SpriteName);

		// �ؽ�ó�� ������ ��������Ʈ�� ����� ����.
		Res->m_Tex = HTEXTURE::Find(_TexName);
		if (nullptr == Res->m_Tex)
		{
			AMSG(L"�������� �ʴ� �ؽ�ó���� ��������Ʈ�� ����� ������ �߽��ϴ�");
		}

		Res->Create(_X, _Y);
		return Res;
	}

private:
	// �ؽ�ó�� �˰� �־�� �Ѵ�.
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
			AMSG(L"�������� �ʴ� ��������Ʈ�� �ε����� �Է��߽��ϴ�.");
		}

		return m_SpriteData[_Index];
	}

};

