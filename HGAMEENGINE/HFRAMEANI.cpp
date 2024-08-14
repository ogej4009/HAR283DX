#include "HFRAMEANI.h"
#include "HGAMEACTOR.h"
#include <HGAMETIME.h>

void HFRAMEANI::Init(HPTR<HSPRITERENDERER> _SpriteRender)
{
	if (nullptr == _SpriteRender)
	{
		m_SpriteRender = ACTOR()->FindComType<HSPRITERENDERER>();
	}
	else {
		m_SpriteRender = _SpriteRender;
	}

	if (nullptr == m_SpriteRender)
	{
		AMSG(L"������ �ִϸ��̼��� ��������Ʈ �������� �־�� ����� �ֽ��ϴ�.");
	}
}

void HFRAMEANI::Update() 
{
	// float Time = HGAMETIME::DeltaTime();
	if (nullptr == m_CurAni)
	{
		AMSG(L"�ִϸ��̼��� �������� �ʾҽ��ϴ�.");
	}


	m_CurAni->m_CurFrameTime -= HGAMETIME::DeltaTime();

	if (0 >= m_CurAni->m_CurFrameTime)
	{
		m_CurAni->CheckEndFunc(m_CurAni->m_CurFrame);
		++m_CurAni->m_CurFrame;
		m_CurAni->CheckStartFunc(m_CurAni->m_CurFrame);
		// 10 ���������� ���ߴ�.
		// 10 �������� ����
		// START


		// �䶧 ���ָ� �ȴ�.

		m_CurAni->m_CurFrameTime = m_CurAni->m_FrameTime;

		unsigned int Frame = m_CurAni->m_CurFrame;

		if (m_CurAni->m_End < m_CurAni->m_CurFrame)
		{
			if (true == m_CurAni->m_Loop)
			{
				m_CurAni->m_CurFrame = m_CurAni->m_Start;
			}
			else {
				--m_CurAni->m_CurFrame;
			}
		}
	}

	unsigned int Check = m_CurAni->m_CurFrame;

	m_SpriteRender->SPRITE(m_CurAni->m_SpriteName, m_CurAni->m_CurFrame);


}

void HFRAMEANI::CreateAni(
	const HGAMESTRING& _AniName,
	const HGAMESTRING& _SpriteName,
	unsigned int _Start,
	unsigned int _End,
	float _FrameTime,
	bool _Loop) 
{
	if (m_Ani.end() != m_Ani.find(_AniName))
	{
		AMSG(_AniName + L"�̹� ������� �ִϸ��̼� �̸��Դϴ�");
	}

	if (nullptr == HGAMESPRITE::Find(_SpriteName))
	{
		AMSG(_AniName + L"��������Ʈ�� �������� �ʾ� �ִϸ��̼��� ����� �����ϴ�.");
	}

	// �ٷ� Ű�� �Բ� ���������.
	m_Ani[_AniName] = new HFRAMEANIMATION();
	m_Ani[_AniName]->m_AniName = _AniName;
	m_Ani[_AniName]->m_SpriteName = _SpriteName;
	m_Ani[_AniName]->m_Start = _Start;
	m_Ani[_AniName]->m_End = _End;
	m_Ani[_AniName]->m_FrameTime = _FrameTime;
	m_Ani[_AniName]->m_Loop = _Loop;
	m_Ani[_AniName]->Actor = ACTOR();
}

void HFRAMEANI::ChangeAni(const HGAMESTRING& _AniName) 
{
	if (m_Ani.end() == m_Ani.find(_AniName))
	{
		AMSG(_AniName + L"�ִϸ��̼��� �������� �ʽ��ϴ�");
	}

	m_CurAni = m_Ani[_AniName];
	m_CurAni->Reset();
	m_CurAni->CheckStartFunc(m_CurAni->m_Start);
}


HPTR<HFRAMEANI::HFRAMEANIMATION> HFRAMEANI::FindAni(const HGAMESTRING& _AniName) 
{
	if (m_Ani.end() == m_Ani.find(_AniName))
	{
		return nullptr;
	}

	return m_Ani[_AniName];
}