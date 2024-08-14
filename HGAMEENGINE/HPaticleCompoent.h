#pragma once
#include "HGAMECOM.h"
#include "HMESH.h"
#include "HRENDERER.h"
#include "HStructuredBuffer.h"

class Particle
{
public:
	float4	vWorldPos;
	float4	vDir;
	float   fSpeed;
	float   fAddSpeed;
	float	fMaxLifeTime;
	float	fCurLifeTime;
	float4	vPad;
	int		iAlive;
	int		Temp0;
	int		Temp1;
	int		Temp2;
};

class ParticleShared
{
public:

	float4	vStartScale;
	float4	vEndScale;
	float4	vStartColor;
	float4	vEndColor;
	UINT	iSpawnCount;
	UINT	iCurCount;
	UINT	Temp0;
	UINT	Temp1;
};

class POINTVTX
{
public:
	float4	Pos;
	float4	Color;
	float4	UV;
};

class HPaticleCompoent : public HACTORCOM
{
private:
	std::vector<Particle> PData;
	std::vector<ParticleShared> SData;

	HPTR<HStructuredBuffer> m_pParticleBuffer; // 파이클 버퍼
	HPTR<HStructuredBuffer> m_pSharedBuffer; // 공유버퍼

	HPTR<HMESH> m_Mesh;
	HPTR<HRENDERER> m_Render;
	HPTR<HRENDERPLAYER> m_RenderPlayer;

public:
	void Init() override;
	void Update() override;
	void UpdateNext() override;

};

