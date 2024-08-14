#pragma once
#include <HMGR.h>
#include "HVTXSHADER.h"
#include "HGEOMETRYSHADER.h"
#include "HPIXSHADER.h"
#include "HRASTERIZER.h"
#include "HDEPTHSTENCIL.h"
#include "HBLEND.h"

class HRENDERPLAYER;
class HMATERIAL : public HMGR<HMATERIAL>
{
public:
	friend HRENDERPLAYER;

public:
	static HPTR<HMATERIAL> Create(const HGAMESTRING& _Name)
	{
		return CreateToInsert(_Name);
	}

private:
	bool m_AllCheck;
	HPTR<HVTXSHADER>			m_VTXSHADER;
	HPTR<HGEOMETRYSHADER>		m_GEOSHADER;
	HPTR<HPIXSHADER>			m_PIXSHADER;
	std::vector<HSHADER*>		m_ALLSHADER;

	HPTR<HRASTERIZER>	m_RASTERIZER;
	HPTR<HDEPTHSTENCIL> m_DEPTHSTENCIL;
	HPTR<HBLEND>		m_BLEND;

public:
	HPTR<HVTXSHADER> VTXSHADER()		{ return m_VTXSHADER; }
	HPTR<HGEOMETRYSHADER> GEOSHADER() { return m_GEOSHADER; }
	HPTR<HPIXSHADER> PIXSHADER()		{ return m_PIXSHADER; }
	HPTR<HRASTERIZER> RASTERIZER()		{ return m_RASTERIZER; }
	HPTR<HDEPTHSTENCIL> DEPTHSTENCIL()	{ return m_DEPTHSTENCIL; }
	HPTR<HBLEND>		BLEND()			{ return m_BLEND; }


	RENDERPATHTYPE PathType();

	void VTXSHADER(const HGAMESTRING& _Name);
	void GEOSHADER(const HGAMESTRING& _Name);
	void PIXSHADER(const HGAMESTRING& _Name);
	void RASTERIZER(const HGAMESTRING& _Name);
	void DEPTHSTENCIL(const HGAMESTRING& _Name);
	void BLEND(const HGAMESTRING& _Name);

public:
	HMATERIAL();
	~HMATERIAL();

public:
	void Setting();
};

