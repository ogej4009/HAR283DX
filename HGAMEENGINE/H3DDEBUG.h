#pragma once
#include <HGAMESTRING.h>
#include "HGAMEFONT.h"
#include <vector>
#include <HGAMEDEBUG.h>

class HTEXTURE;
class HRENDERPLAYER;
class H3DDEBUG
{
private:
	static HPTR<HGAMEFONT> m_DebugFont;
	static float m_BasicFontSize;
	static HVECTOR m_BasicStartPos;
	static HVECTOR m_CurTextSize;
	static HVECTOR m_BasicColor;
	static HPTR<HRENDERPLAYER> m_TargetDebugTextureRenderPlayer;
	static HPTR<HRENDERPLAYER> m_TargetDebugTextureBackRenderPlayer;
	static HMATRIX m_VPMAT;

public:
	static void Init(bool _IsOpenConsole = false);

private:
	class DebugTextInfo 
	{
	public:
		HGAMESTRING Text;
		float Size;
		HVECTOR Pos;
		HVECTOR Color;
		
	};

	class DebugTextureInfo
	{
	public:
		HPTR<HTEXTURE> m_Tex;
		HVECTOR BackColor;
		HMATRIX WVP;
	};

	static std::vector<DebugTextInfo> m_AllDebugText;
	static std::vector<DebugTextureInfo> m_AllDebugTexture;



public:

	static void DrawDebugText(const HGAMESTRING& _Text, float _Size, HVECTOR _Pos, HVECTOR _Color);

	static void DrawDebugTexture(const HPTR<HTEXTURE>& _Texture, HVECTOR _Size, HVECTOR _Pos, HVECTOR _BackColor);

	template<typename ... REST>
	static void DrawDebugText(const HGAMESTRING& _Text, REST ... _Arg)
	{
		wchar_t ArrText[256];
		swprintf_s(ArrText, _Text, _Arg...);
		H3DDEBUG::DrawDebugText(ArrText, m_BasicFontSize, m_CurTextSize, m_BasicColor);
		m_CurTextSize.y += m_BasicFontSize;
	}

	template<typename ... REST>
	static void ConsolePrintText(const HGAMESTRING& _Text, REST ... _Arg)
	{
		HGAMEDEBUG::ConsolePrintText(_Text, _Arg...);
	}

	// HGAMEDEBUG BASE FUNC
public:

	static void OpenConsole() 
	{
		HGAMEDEBUG::OpenConsole();
	}

public:
	static void DebugRender();

};