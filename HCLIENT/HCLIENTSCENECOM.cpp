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
		// �簢�� �ϳ� ������ �༮.
		HPTR<HGAMEACTOR> NewActor = SCENE()->CreateActor();

		NewActor->TRANS()->LPOS({0, 0, -10});

		// ���� �׷��� �����°� ȭ�鿡 ����(������)�� �͵��� �׷� ����°�
		// �� �׷��� ����?
		// �ϴ� ���״�� �������Ǵ� ������Ʈ���� ȭ�鿡 ǥ���ϴ� ����� �������� ���ϴ�.
		// �׸��� ī�޶󿡰� � �׷��� ����� Ư������� �ִ�.

		

		// RenderGroup
		HPTR<HCAM> NewCam = NewActor->CreateCom<HCAM>(0, (int)RENDERGROUP::PLAY);
		NewCam->MODE(CAMMODE::PERS);
		NewCam->CAMSIZE({ 12.8f, 7.2f });

		NewActor->CreateCom<HFREECAM>(10.0f);

	}

	// �׸���
	{
		// �簢�� �ϳ� ������ �༮.
		GRIDActor3D = SCENE()->CreateActor();
		HPTR<HRENDERER> NewRender = GRIDActor3D->CreateCom<HRENDERER>(L"GRIDMESH", L"GRID");
		GRIDActor3D->TRANS()->WSCALE({ 10000.0F, 10000.0F, 10000.0F });
	}

	{
		// �簢�� �ϳ� ������ �༮.
		TestActor = SCENE()->CreateActor();
		HPTR<HRENDERER> NewRender = TestActor->CreateCom<HRENDERER>(L"2DCOLORRECT", L"BASIC");
		// �̳༮ ��ŭ�� �츮 �����ӿ�ũ���� ����� ����.
		// HTRANSDATA��� �̸��̸� �̳༮��
		// Ʈ�������� �ִ� TRANSDATA�����͸� ���̴��� �־��ֱ�� ����Ѵ�.
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