#include "HTRANS.h"
#include "HGAMEACTOR.h"
#include "HGAMESCENE.h"

#include <HGAMEDEBUG.h>

bool HTRANS::SPHERE2DCOLOBB2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right)
{
	return _Left->SPHERE2D().Intersects(_Right->OBB2D());
}
bool HTRANS::SPHERE2DCOLAABB2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right) {
	return _Left->SPHERE2D().Intersects(_Right->AABB2D());;
}
bool HTRANS::SPHERE2DCOLSPHERE2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right) 
{
	{
		HVECTOR Pos1 = _Left->WPOS();
		HVECTOR Pos2 = _Right->WPOS();


		int a = 0;
	}


	return _Left->SPHERE2D().Intersects(_Right->SPHERE2D());;
}

bool HTRANS::AABB2DCOLOBB2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right) {
	return _Left->AABB2D().Intersects(_Right->OBB2D());;
}
bool HTRANS::AABB2DCOLAABB2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right) {
	return _Left->AABB2D().Intersects(_Right->AABB2D());;
}
bool HTRANS::AABB2DCOLSPHERE2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right) {
	return _Left->AABB2D().Intersects(_Right->SPHERE2D());;
}

bool HTRANS::OBB2DCOLOBB2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right) 
{
	return _Left->OBB2D().Intersects(_Right->OBB2D());;
}
bool HTRANS::OBB2DCOLAABB2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right) {
	return _Left->OBB2D().Intersects(_Right->AABB2D());;
}
bool HTRANS::OBB2DCOLSPHERE2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right)
{
	return _Left->OBB2D().Intersects(_Right->SPHERE2D());;
}
