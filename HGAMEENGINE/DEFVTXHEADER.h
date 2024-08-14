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
	HVECTOR Normal; // �̳༮�� Y��
	HVECTOR BiNormal; // �̳༮�� X��
	HVECTOR Tangent; // �̳༮�� Z�� // ���߿� �ٲܼ� �ִ�.
	HVECTOR Weight; // �󸶳� ������ �޾ƾ� �ϴ°�? 0.5 ������ �޴´�.
					// ��Ű�� ������ ���¾ָ� 1.0f
	int Index[4]; // 21��° ���� 60 �� ���ؽ��� 60��° ���̶� ���ϴ� �༮�̴�.
	//  Weight:        0.5    0.5
	//  Index:         60     59
};


