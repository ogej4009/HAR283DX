#pragma once
#include <HPTR.h>
#include <HGAMEMATH.h>
#include <list>
#include "HVIRTUALPROGRESS.h"
// ���� ������ ���
// ������Ʈ�� �������� ��ɵ�
// ���� ������Ʈ�� ����
// �̳༮�� ��� �޾Ƽ�.

class HGAMECOM : public HGAMEREF, public HVIRTUALPROGRESS
{
};


// �з��Ѵ�.
class HGAMESCENE;
class HSCENECOM : public HGAMECOM
{
	friend HGAMESCENE;
private:
	HGAMESCENE* m_Scene;

public:
	HPTR<HGAMESCENE> SCENE();

private:
	// ������ ���ټ��� �ֳ��� ������?
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
	// ������ ���ټ��� �ֳ��� ������?
	void ACTOR(HGAMEACTOR* _Ptr)
	{
		m_Actor = _Ptr;
	}
};

