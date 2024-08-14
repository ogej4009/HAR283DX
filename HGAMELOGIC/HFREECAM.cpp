#include "HFREECAM.h"
#include <HGAMEACTOR.h>
#include <HCAM.h>
#include <HGAMEDEBUG.h> 
#include <HGAMEINPUT.h>
#include <HTRANS.h>
#include <HGAMETIME.h>

HFREECAM::HFREECAM() 
{
	// -50                          50
	// 0    10 0    10 0     10
	// 50 40
	// % 10
	// float A = 10.0F;
	// A % 10.0f;
}

HFREECAM::~HFREECAM() 
{
}

void HFREECAM::Init(float _Speed)
{
	m_Speed = _Speed;
	m_RotSpeed = 360.0f;

	if (nullptr == ACTOR()->FindComType<HCAM>())
	{
		AMSG(L"캠이 존재하지 않는 곳에 프리캠을 넣어줄수 없습니다.");
	}

	m_Cam = ACTOR()->FindComType<HCAM>();

	if (false == HGAMEINPUT::IsKey(L"CAML"))
	{
		HGAMEINPUT::CreateKey(L"CAMLEFT", 'A');
		HGAMEINPUT::CreateKey(L"CAMRIGHT", 'D');
		HGAMEINPUT::CreateKey(L"CAMUP", 'Q');
		HGAMEINPUT::CreateKey(L"CAMDOWN", 'E');
		HGAMEINPUT::CreateKey(L"CAMFORWARD", 'W');
		HGAMEINPUT::CreateKey(L"CAMBACK", 'S');

		HGAMEINPUT::CreateKey(L"CAMROT", VK_RBUTTON);
	}
}

void HFREECAM::Update() 
{
	// 줌인 줌아웃(위치를 바꾸면 절대 안된다. 투영이나 뷰행렬을 수정)
	// 초기화(최초 위치로 다시 돌린다.)
	// 부스트(속력을 내가 어떤키를 누르면)

	if (true == HGAMEINPUT::Press(L"CAMLEFT"))
	{
		TRANS()->LMOVE(TRANS()->WLEFT() * HGAMETIME::DeltaTime(m_Speed));
	}

	if(true == HGAMEINPUT::Press(L"CAMRIGHT"))
	{
		TRANS()->LMOVE(TRANS()->WRIGHT() * HGAMETIME::DeltaTime(m_Speed));
	}

	if(true == HGAMEINPUT::Press(L"CAMUP"))
	{
		TRANS()->LMOVE(TRANS()->WUP() * HGAMETIME::DeltaTime(m_Speed));
	}

	if(true == HGAMEINPUT::Press(L"CAMDOWN"))
	{
		TRANS()->LMOVE(TRANS()->WDOWN() * HGAMETIME::DeltaTime(m_Speed));
	}

	if(true == HGAMEINPUT::Press(L"CAMFORWARD"))
	{
		TRANS()->LMOVE(TRANS()->WFORWARD() * HGAMETIME::DeltaTime(m_Speed));
	}

	if(true == HGAMEINPUT::Press(L"CAMBACK"))
	{
		TRANS()->LMOVE(TRANS()->WBACK() * HGAMETIME::DeltaTime(m_Speed));
	}

	if (true == HGAMEINPUT::Press(L"CAMROT"))
	{
		TRANS()->WROTADDY(HGAMEINPUT::MouseDir3D().x * HGAMETIME::DeltaTime(m_RotSpeed));
		TRANS()->WROTADDX(-HGAMEINPUT::MouseDir3D().y * HGAMETIME::DeltaTime(m_RotSpeed));

		// TRANS()->LMOVE(TRANS()->WBACK() * HGAMETIME::DeltaTime(m_Speed));
	}
}