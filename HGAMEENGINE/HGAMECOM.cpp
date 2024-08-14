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
	// 액터의 bool값도 true고 나의 bool값도 true여야 나는 나의 일을할수 있다. 
	return true == HVIRTUALPROGRESS::IsUpdate() && true == m_Actor->IsUpdate();
}

bool HACTORCOM::IsDeath()
{
	// 액터의 bool값도 true고 나의 bool값도 true여야 나는 나의 일을할수 있다. 
	return true == HVIRTUALPROGRESS::IsDeath() || true == m_Actor->IsDeath();
}
