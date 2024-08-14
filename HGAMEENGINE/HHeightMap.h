#pragma once
#include <HGAMEMATH.h>
#include <vector>
#include "HRENDERER.h"
#include <map>

//class NaviTri 
//{
//public:
//	HVECTOR Arr[3];
//	std::vector<NaviTri*> m_Tri;
//
//};

struct MAPOPTION
{
	float XCount;
	float ZCount;
	float YRatio;
	float YScale;
	HVECTOR PixelUv;
	HVECTOR PixelScale;
};

struct YTri 
{
	HVECTOR Arr[3];
};

struct YTile
{
	YTri Up;
	YTri Down;
};

class HHeightMap : public HACTORCOM
{
private:
	int X;
	int Z;

	MAPOPTION MapOption;

	// std::vector<NaviTri> m_Tri;
	HPTR<HMESH> m_Mesh;
	HPTR<HRENDERER> m_Render;
	HPTR<HRENDERPLAYER> m_RenderPlayer;
	std::vector<VTX3DMESHIN> m_VecVtx;
	std::map<__int64, YTile> m_YTileMap;
	HPTR<HTEXTURE> m_HTex;

	float Min;

public:
	HPTR<HRENDERER> Render()
	{
		return m_Render;
	}


public:
	float GetMin();
	int2 Index(float4 _Pos);
	float YHeight(float4 _Pos);
	HVECTOR CalTexelPos(const HVECTOR& _Pos);
	HVECTOR CalPosToWorld(const HVECTOR& _Pos);

public:
	void Init(int& _X, int& _Z, const HGAMESTRING _MapHeightTex, int _Order = 0);

	void BaseTexture(const HGAMESTRING _TextureName);
	void HTex(const HGAMESTRING _TextureName);;
};

