#include "HGAMECOM.h"
#include "HTRANS.h"
#include "HGAMEACTOR.h"

HPTR<HGAMESCENE> HSCENECOM::SCENE()
{
	return m_Scene;
}

HPTR<HGAMEACTOR> HACTORCOM::ACTOR()
{
	return m_Actor;
}

HPTR<HGAMESCENE> HACTORCOM::SCENE() {
	return m_Actor->SCENE();
}

HPTR<HTRANS> HACTORCOM::TRANS() 
{
	return m_Actor->TRANS();
}

bool HACTORCOM::IsUpdate()
{
	// ������ bool���� true�� ���� bool���� true���� ���� ���� �����Ҽ� �ִ�. 
	return true == HVIRTUALPROGRESS::IsUpdate() && true == m_Actor->IsUpdate();
}

bool HACTORCOM::IsDeath()
{
	// ������ bool���� true�� ���� bool���� true���� ���� ���� �����Ҽ� �ִ�. 
	return true == HVIRTUALPROGRESS::IsDeath() || true == m_Actor->IsDeath();
}
