#include "HGAMEACTOR.h"

HTRANS* HGAMEACTOR::TRANS()
{
	return m_TRANS;
}

HGAMESCENE* HGAMEACTOR::SCENE() 
{
	return m_SCENE;
}


void HGAMEACTOR::UpdatePrev() {
	HUPDATELISTOBJMGR<HACTORCOM>::UpdatePrev();
}
void HGAMEACTOR::Update() {
	HUPDATELISTOBJMGR<HACTORCOM>::Update();
}
void HGAMEACTOR::UpdateNext() {
	HUPDATELISTOBJMGR<HACTORCOM>::UpdateNext();
}
void HGAMEACTOR::RenderPrev() {
	HUPDATELISTOBJMGR<HACTORCOM>::RenderPrev();
}
void HGAMEACTOR::RenderNext() {
	HUPDATELISTOBJMGR<HACTORCOM>::RenderNext();
}
void HGAMEACTOR::CollisionPrev() {
	HUPDATELISTOBJMGR<HACTORCOM>::CollisionPrev();
}
void HGAMEACTOR::CollisionNext() {
	HUPDATELISTOBJMGR<HACTORCOM>::CollisionNext();
}
void HGAMEACTOR::SceneChangeEnd() {
	HUPDATELISTOBJMGR<HACTORCOM>::SceneChangeEnd();
}
void HGAMEACTOR::SceneChangeStart() {
	HUPDATELISTOBJMGR<HACTORCOM>::SceneChangeStart();
}
void HGAMEACTOR::Release() {
	HUPDATELISTOBJMGR<HACTORCOM>::Release();
}
