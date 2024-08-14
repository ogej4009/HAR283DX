#pragma once
#include <HGAMECOM.h>

class HCLIENTSCENECOM : public HSCENECOM
{
private:
	HPTR<HGAMEACTOR> TestActor;

	// 테스트용=================
private:
	HPTR<HGAMEACTOR> GRIDActor3D;
	HVECTOR m_Dir;
	// =============================


public:

	void Init() override;
	void Update();

public:
	HCLIENTSCENECOM();
	~HCLIENTSCENECOM();
};

