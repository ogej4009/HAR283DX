#include <Windows.h>
#include <HGAMESTRING.h>
#include <HGAMEWINDOW.h>
#include <HGAMEDEVICE.h>
#include <HGAMESCENE.h>
#include "HCLIENTSCENECOM.h"
#include <HGAMEACTOR.h>

#pragma comment(lib, "HGAMEBASE.lib")
#pragma comment(lib, "HGAMEENGINE.lib")
#pragma comment(lib, "HGAMELOGIC.lib")

int __stdcall Start()
{
	HGAMESCENE::Create<HCLIENTSCENECOM>(L"TEST");
	HGAMESCENE::ChangeScene(L"TEST");

	return 1;
}

// ����Ÿ��
int __stdcall Loop()
{
	HGAMESCENE::Progress();
	return 1;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// HGMAESTRING TTT = L"cccccc, dddddd, ewersda, vcxzvxzc , asdfaef,";
	// List<HGAMESTRING>
	//                   "FAASDF" + 1.0F
	//                   "FAASDF1.0" + 1.0F
	//                   "FAASDF " + 1.0F
	// HGMAESTRING TTT = HGAMESTR1 + float;
	// HGMAESTRING TTT = HGAMESTR2 + int;
	// HGMAESTRING TTT = "adfasdfwerfd";
	// List<HGAMESTRING>

// #ifde
	new int();

	HGAMEWINDOW::Create(L"MainWindow");
	HGAMEWINDOW::MAINOBJ()->Size({ 1280, 720 });
	HGAMEDEVICE::Create(L"MainWindow");

	// HPTR<SPRITERENDER> AAA;
	// AAA->SetSprite("....png");


	// �Ʒ��� �������� �ϳ��� ��Ʈ�� ����.
	// �����̶�� ���׸��� ��Ƽ����

	// 2DIMAGE_BACK ���׸���
	// ���ؽ����̴� VS_2D_IMAGE
	// �ȼ����̴� PS_2D_IMAGE
	// �������ٽ� DEFDEPTH
	// ������ ���ĺ�����
	// �����Ͷ����� FRONT


	// 2DIMAGE_FRONT ���׸���
	// ���ؽ����̴� VS_2D_IMAGE
	// �ȼ����̴� PS_2D_IMAGE
	// �������ٽ� DEFDEPTH
	// ������ ���ĺ�����
	// �����Ͷ����� FRONT

	// �������� �迭�̶�� ���� �ȴ�.
	// HPTR<RENDER> CCC;
	// AAA->SETMAT("2DIMAGE");
	// AAA->SETTEXTURE("DIFTEX", ".png");
	// AAA->SAMPLER("SMP", ".png");
	// AAA->CBUFFER("TRANSDATA", );

	// AAA->CBUFFER("UVCOLOR", ".png");
	// AAA->MESH("UVCOLOR", ".png");

	// AAA->Texture("UVCOLOR", ".png");

	HGAMEWINDOW::HWINMESSAGE(Start, Loop);

}