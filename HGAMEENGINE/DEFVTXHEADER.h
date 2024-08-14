#pragma once

#include <HGAMEMATH.h>

class VTX2DIMGIN
{
public:
	HVECTOR Pos;
	HVECTOR Uv;
	HVECTOR Color;
};

class TARGETVTX
{
public:
	HVECTOR Pos;
	HVECTOR Uv;
};

// 

class VTX3DMESHIN
{
public:
	HVECTOR Pos;
	HVECTOR Uv;
	HVECTOR Color;
	HVECTOR Normal; // 이녀석이 Y축
	HVECTOR BiNormal; // 이녀석이 X축
	HVECTOR Tangent; // 이녀석이 Z축 // 나중에 바꿀수 있다.
	HVECTOR Weight; // 얼마나 영향을 받아야 하는가? 0.5 영향을 받는다.
					// 스키닝 정보가 없는애면 1.0f
	int Index[4]; // 21번째 본에 60 이 버텍스는 60번째 본이랑 곱하는 녀석이다.
	//  Weight:        0.5    0.5
	//  Index:         60     59
};


