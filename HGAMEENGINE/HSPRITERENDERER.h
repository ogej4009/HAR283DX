#pragma once
#include "HRENDERER.h"
#include "HGAMESPRITE.h"

class HSPRITERENDERER : public HRENDERER
{
public:
	HVECTOR m_Color;

private:
	HVECTOR CutData;
	HPTR<HGAMESPRITE> m_SPRITE;
	unsigned int m_SpriteIndex;

public:
	void SPRITE(const HGAMESTRING& _Name, unsigned int _SpriteIndex = 0)
	{
		m_SPRITE = HGAMESPRITE::Find(_Name);
		SpriteIndex(_SpriteIndex);
	}

	void SpriteIndex(unsigned int _SpriteIndex)
	{
		m_SpriteIndex = _SpriteIndex;
	}

public:
	void Alpha(float _A) 
	{
		m_Color.w = _A;
	}
	void Color(HVECTOR _Color) 
	{
		m_Color = _Color;
	}

public:
	void Init(int _Order = 0);
	void Render(HPTR<HCAM> _Cam) override;

};

