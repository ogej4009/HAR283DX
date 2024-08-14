#pragma once
#include <HPTR.h>
#include <HGAMEMATH.h>
#include <list>
#include "HVIRTUALPROGRESS.h"
// 가장 말단의 기능
// 오브젝트가 가져야할 기능들
// 내가 오브젝트로 몬스터
// 이녀석을 상속 받아서.

class HGAMECOM : public HGAMEREF, public HVIRTUALPROGRESS
{
};


// 분류한다.
class HGAMESCENE;
class HSCENECOM : public HGAMECOM
{
	friend HGAMESCENE;
private:
	HGAMESCENE* m_Scene;

public:
	HPTR<HGAMESCENE> SCENE();

private:
	// 세팅을 해줄수가 있나요 없나요?
	void Scene(HGAMESCENE* _Ptr)
	{
		m_Scene = _Ptr;
	}

};

class HTRANS;
class HGAMEACTOR;
class HACTORCOM : public HGAMECOM
{
private:
	friend HGAMEACTOR;

private:
	HGAMEACTOR* m_Actor;

public:
	HPTR<HGAMEACTOR> ACTOR();
	HPTR<HGAMESCENE> SCENE();
	HPTR<HTRANS> TRANS();

	bool IsUpdate() override;
	bool IsDeath() override;


private:
	// 세팅을 해줄수가 있나요 없나요?
	void ACTOR(HGAMEACTOR* _Ptr)
	{
		m_Actor = _Ptr;
	}
};

