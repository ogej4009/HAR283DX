#include "HCLIENTSCENECOM.h"
#include <HGAMESCENE.h>
#include <HGAMEACTOR.h>
#include <HCAM.h>
#include <HTRANS.h>
#include <HSPRITERENDERER.h>
#include <HGAMESPRITE.h>
#include <HFREECAM.h>
#include <HGAMETIME.h>


HCLIENTSCENECOM::HCLIENTSCENECOM() {

}
HCLIENTSCENECOM::~HCLIENTSCENECOM() {

}

enum class RENDERGROUP
{
	PLAY,
	UI,
};

void HCLIENTSCENECOM::Init() 
{
	{
		HGAMEDIRECTORY Dic;

		Dic.MoveParent(L"HAR283DX");
		Dic.Move(L"RES");
		Dic.Move(L"TEXTURE");
		Dic.Move(L"GLOBAL");

		auto FileList = Dic.DirAllFile();

		for (auto& _File : FileList)
		{
			HTEXTURE::Load(_File);
		}

		for (auto& _File : FileList)
		{
			HGAMESPRITE::Create(_File.FileName());
		}
	}

	{
		// 사각형 하나 띄우려는 녀석.
		HPTR<HGAMEACTOR> NewActor = SCENE()->CreateActor();

		NewActor->TRANS()->LPOS({0, 0, -10});

		// 먼저 그룹을 나누는건 화면에 보이(랜더링)는 것들을 그룹 지우는것
		// 왜 그룹을 짓죠?
		// 일단 말그대로 랜더링되는 오브젝트들의 화면에 표현하는 방식을 구분짓기 편하다.
		// 그리고 카메라에게 어떤 그룹을 보라고 특정지울수 있다.

		

		// RenderGroup
		HPTR<HCAM> NewCam = NewActor->CreateCom<HCAM>(0, (int)RENDERGROUP::PLAY);
		NewCam->MODE(CAMMODE::PERS);
		NewCam->CAMSIZE({ 12.8f, 7.2f });

		NewActor->CreateCom<HFREECAM>(10.0f);

	}

	// 그리드
	{
		// 사각형 하나 띄우려는 녀석.
		GRIDActor3D = SCENE()->CreateActor();
		HPTR<HRENDERER> NewRender = GRIDActor3D->CreateCom<HRENDERER>(L"GRIDMESH", L"GRID");
		GRIDActor3D->TRANS()->WSCALE({ 10000.0F, 10000.0F, 10000.0F });
	}

	{
		// 사각형 하나 띄우려는 녀석.
		TestActor = SCENE()->CreateActor();
		HPTR<HRENDERER> NewRender = TestActor->CreateCom<HRENDERER>(L"2DCOLORRECT", L"BASIC");
		// 이녀석 만큼은 우리 프레임워크에서 약속을 하자.
		// HTRANSDATA라는 이름이면 이녀석은
		// 트랜스폼에 있는 TRANSDATA데이터를 쉐이더에 넣어주기로 약속한다.
		// NewRender->CBUFFER(L"HTRANSDATA", NewRender->PTRANSDATA());
		NewRender->TEXTURE(L"DIFTEX", "COLTESTS.png");
		NewRender->SAMPLER(L"SAMPLER", "LWSMP");
	}


}

void HCLIENTSCENECOM::Update() 
{
	m_Dir += HVECTOR::LEFT * HGAMETIME::DeltaTime();
	TestActor->TRANS()->WMOVE(m_Dir * HGAMETIME::DeltaTime());
	// TestActor->TRANS()->LPOS({ 3, 3, 0 });
	//TestActor
}