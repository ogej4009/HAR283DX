#include "HTRANS.h"
#include "HGAMEACTOR.h"
#include "HGAMESCENE.h"
#include "HCAM.h"
#include "HLight.h"

#include <HGAMEDEBUG.h>

bool (*HTRANS::COLFUNC[(int)COLTYPE::MAX][(int)COLTYPE::MAX])(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right) = { nullptr,};

HTRANS::HGAMECOLSTART HTRANS::Starter;

HTRANS::HGAMECOLSTART::HGAMECOLSTART() 
{
	HTRANS::COLFUNC[(int)COLTYPE::AABB2D][(int)COLTYPE::AABB2D] =	AABB2DCOLAABB2D;
	HTRANS::COLFUNC[(int)COLTYPE::AABB2D][(int)COLTYPE::SPHERE2D] = AABB2DCOLSPHERE2D;
	HTRANS::COLFUNC[(int)COLTYPE::AABB2D][(int)COLTYPE::OBB2D] =	AABB2DCOLOBB2D;

	HTRANS::COLFUNC[(int)COLTYPE::OBB2D][(int)COLTYPE::AABB2D] =	OBB2DCOLAABB2D;
	HTRANS::COLFUNC[(int)COLTYPE::OBB2D][(int)COLTYPE::SPHERE2D] =	OBB2DCOLSPHERE2D;
	HTRANS::COLFUNC[(int)COLTYPE::OBB2D][(int)COLTYPE::OBB2D] =		OBB2DCOLOBB2D;

	HTRANS::COLFUNC[(int)COLTYPE::SPHERE2D][(int)COLTYPE::AABB2D] =		SPHERE2DCOLAABB2D;
	HTRANS::COLFUNC[(int)COLTYPE::SPHERE2D][(int)COLTYPE::SPHERE2D] =	SPHERE2DCOLSPHERE2D;
	HTRANS::COLFUNC[(int)COLTYPE::SPHERE2D][(int)COLTYPE::OBB2D] =		SPHERE2DCOLOBB2D;
}

HTRANS::HTRANS() 
	: m_LPOS(HVECTOR::ZERO), m_LSCALE(HVECTOR::ONE), m_LROT(HVECTOR::ZERO)
	, m_WPOS(HVECTOR::ZERO), m_WSCALE(HVECTOR::ONE), m_WROT(HVECTOR::ZERO)
	, m_TRANSDATA(), CALARRMATCHECK{ true, }, m_PARENT(nullptr)
{

	//HVECTOR PlayerPos;
	//PlayerPos.y += 100.0f;

	//// �÷��̾��� ������
	//HVECTOR RayPos = PlayerPos;
	//HVECTOR RayDir;
	//HVECTOR Tri0;
	//HVECTOR Tri1;
	//HVECTOR Tri2;
	//float Result = -1.0f;
	//DirectX::TriangleTests::Intersects(RayPos, RayDir, Tri0, Tri1, Tri2, Result);

	//if (0 != Result)
	//{
	//	// �浹�ߴ�.
	//	return Result;
	//}

	//HVECTOR Tri3;
	//HVECTOR Tri4;
	//HVECTOR Tri5;
	//DirectX::TriangleTests::Intersects(RayPos, RayDir, Tri3, Tri4, Tri5, Result);

	memset(&CALARRMATCHECK, 1, sizeof(CALARRMATCHECK));
	m_TRANSDATA.CALIDEN();
}

// ������ �� �θ� �Ǿ��شٴ°���?
void HTRANS::PARENT(HPTR<HTRANS> _Parent)
{
	// ������ �θ� ����� ���� Ʈ����������Ʈ���� �����°Ŵ�.
	ACTOR()->SCENE()->m_AllTrans.remove(this);

	if (nullptr != _Parent)
	{
		// ���ڵ尡 �־�� �Ѵ�.
		// ��������� ���� ���� �θ� ���ٴ°��� ������ �ϰ� �ִ� �ڵ尡.
		if (nullptr != m_PARENT)
		{
			m_PARENT->m_CHILDLIST.remove(this);
		}


		// �θ����????? �θ��� �ڽ����� ����.
		_Parent->m_CHILDLIST.push_back(this);

		// �θ���� �������� �ѹ��� ���� ����.
		CALARRMATCHECK[(int)MATTYPE::MATTYPE_PARENT] = true;
		// ���� ��������� �ڽ��� �θ���Ŀ� �Է����ְ�
		m_TRANSDATA.PARENT = _Parent->m_TRANSDATA.WWORLD;
		// �ָ��л��� �˾Ƴ� ���� �Ǽ���.
		// ���� ���� �θ�?
		m_PARENT = _Parent;

		LSCALE(WSCALE());
		LROT(WROT());
		LPOS(WPOS());
	}
	else 
	{
		if (nullptr != m_PARENT)
		{
			m_PARENT->m_CHILDLIST.remove(this);
		}
		ACTOR()->SCENE()->m_AllTrans.push_back(this);
		
		CALWPOS();
		CALWSCALE();
		CALWROT();

		m_PARENT = nullptr;
		m_TRANSDATA.PARENT.IDEN();
		LPOS(WPOS());
		LSCALE(WSCALE());
		LROT(WROT());
	}

	// ȯ���� �������Ƿ� ����� �� �ѹ� ���� ����.
	TransUpdate();
}

void HTRANS::Init()
{
	if (nullptr != ACTOR()->m_TRANS)
	{
		AMSG(L"�� ���Ϳ� Ʈ�������� 2���� ������ �����ϴ�.");
	}

	ACTOR()->m_TRANS = this;
	ACTOR()->SCENE()->m_AllTrans.push_back(this);
}

void HTRANS::TransUpdate()
{
	// ũ�Ⱑ ����...
	if (true == CALARRMATCHECK[(int)MATTYPE::MATTYPE_SCALE])
	{
		m_TRANSDATA.SCALE.Scale3D(m_LSCALE);
		CALARRMATCHECK[(int)MATTYPE::MATTYPE_LWORLD] = true;
	}

	// ȸ���� ����...
	if (true == CALARRMATCHECK[(int)MATTYPE::MATTYPE_ROT])
	{
		m_TRANSDATA.ROT.RotDeg(m_LROT);

		// 3D�� ���� ������ �ٽ� �غ��ô�.
		// HMATRIX RotX;
		// HMATRIX RotY;
		// HMATRIX RotZ;
		// m_LROT.X = 90.0F;
		// m_LROT.Y = 90.0F;
		// RotX.RotXDeg(m_LROT.X);
		// RotY.RotYDeg(m_LROT.Y);
		// RotZ.RotZDeg(m_LROT.Z);
		// m_TRANSDATA.ROT = RotX * RotY * RotZ;

		CALARRMATCHECK[(int)MATTYPE::MATTYPE_LWORLD] = true;
	}

	if (true == CALARRMATCHECK[(int)MATTYPE::MATTYPE_POS])
	{
		m_TRANSDATA.POS.Pos3D(m_LPOS);
		CALARRMATCHECK[(int)MATTYPE::MATTYPE_LWORLD] = true;
	}

	if (true == CALARRMATCHECK[(int)MATTYPE::MATTYPE_LWORLD] ||
		true == CALARRMATCHECK[(int)MATTYPE::MATTYPE_PARENT])
	{
		// CALWORLD�� �Ѵٰ� �ؼ� Wpos�� ����ǳ���?
		m_TRANSDATA.CALLWORLD();
		m_TRANSDATA.CALWWORLD();
		// ���� WWORLD�� ����Ǿ��ٴ� �ǹ̷� �̰� TRUE�� ����
		CALARRMATCHECK[(int)MATTYPE::MATTYPE_WWORLD] = true;
		if (nullptr != m_PARENT)
		{
			CALWSCALE();
			CALWROT();
			CALWPOS();
		}
	}


	// �ڽĵ�
	for (auto& _Child : m_CHILDLIST)
	{
		// �̹��������� ����� ������ �־��ٴ� �̾߱���?
		if (true == CALARRMATCHECK[(int)MATTYPE::MATTYPE_WWORLD])
		{
			_Child->CALARRMATCHECK[(int)MATTYPE::MATTYPE_PARENT] = true;
			// ���� ��������� �ڽ��� �θ���Ŀ� �Է����ְ�
			// �ڽĿ��� ��������� �Է����ְ�
			_Child->m_TRANSDATA.PARENT = m_TRANSDATA.WWORLD;
		}

		// ���� ���ؼ� �ڽŸ��� ��������� �����.

		_Child->TransUpdate();
	}


	memset(&CALARRMATCHECK, 0, sizeof(CALARRMATCHECK));
}

void HTRANS::CamUpdate(HPTR<HCAM> _Cam)
{
	m_TRANSDATA.PROJ = _Cam->m_PROJ;
	m_TRANSDATA.VIEW = _Cam->m_VIEW;
	m_TRANSDATA.CALWVP();
}

void HTRANS::LightUpdate(const LightData& _Light)
{
	m_TRANSDATA.PROJ = _Light.m_Proj;
	m_TRANSDATA.VIEW = _Light.m_View;
	m_TRANSDATA.CALWVP();
}

bool HTRANS::Col(COLTYPE _ThisType, HPTR<HTRANS> _Trans, COLTYPE _OtherType)
{
	if (nullptr == COLFUNC[(int)(_ThisType)][(int)(_OtherType)])
	{
		AMSG(L"�浹 �Լ��� �������� ���� �浹�� �Ϸ��� �߽��ϴ�.");
	}

	return COLFUNC[(int)(_ThisType)][(int)(_OtherType)](this, _Trans);

	//// AABB ȸ������ ���� �ڽ�
	//DirectX::BoundingOrientedBox ColThis;
	//DirectX::BoundingBox ColOther;

	//// XMFLOAT3   HVECTOR
	//ColThis.Center = WPOS();
	//// ����ٰ� �׳� ������ �־��ָ� ȸ���� �ν����� ���Ѵ�.
	//// X Y Z W�� �˲����ִ� ������� �־����
	//// �װɷ� �ѹ濡 ȸ������� ���� ȸ���� �νĵȴ�.
	//// WROT(); ���Ϸ����� �־������ �ƹ��� �ǹ̵� ����.
	//// Orientation ������� �־�޶�� �ϴ°Ŵϱ�.
	//// ������� ���ٴ� ���� 
	//// �츮�� �����ϱ� ����� ���Ҽ� ��� ����� ���յ� ����� ����ϰ� �ִ� ��.
	//// ���� �ӷ� �ʿ����.
	//// �������ΰ� ����. 
	//// ȸ������ ��׸��� �ѹ� �������� �ٲ�� �װ� �ٽ� ���ʹϿ��� �ؼ� ȸ���ϴµ�.
	//// WROT() ��ü�� �׳� ��׸��� ���̴�.
	//ColThis.Orientation = WROT().DegToQ();
	//// DirectX::XMQuaternionRotationRollPitchYaw()
	//ColThis.Extents = WSCALE().HalfVector();

	//ColOther.Center = _Trans->WPOS();
	//ColOther.Extents = _Trans->WSCALE().HalfVector();

	//if ((int)_ThisType < (int)COLTYPE::SPHERE3D)
	//{
	//	ColThis.Center.z = 0.0f;
	//}

	//if ((int)_OtherType < (int)COLTYPE::SPHERE3D)
	//{
	//	ColOther.Center.z = 0.0f;
	//}

	// �� �Լ��� �˾Ƽ� ���ݴϴ�.
	// return ColThis.Intersects(ColOther);

}

DirectX::BoundingBox HTRANS::AABB2D() 
{
	return DirectX::BoundingBox(WPOS2D(), WSCALE().HalfVector().AbsVector());
}
DirectX::BoundingSphere HTRANS::SPHERE2D() 
{
	return DirectX::BoundingSphere(WPOS2D(), abs(WSCALE().HalfVector().x));
}
DirectX::BoundingOrientedBox HTRANS::OBB2D() 
{
	//HVECTOR Pos = WPOS2D();
	//HVECTOR Scale = WSCALE();
	//HVECTOR Rot = WROT();

	return DirectX::BoundingOrientedBox(WPOS2D(), WSCALE().HalfVector().AbsVector(), WROT().DegToQ());
}


//DirectX::BoundingOrientedBox HTRANS::RAY3D()
//{
//	//HVECTOR Pos = WPOS2D();
//	//HVECTOR Scale = WSCALE();
//	//HVECTOR Rot = WROT();
//
//	return DirectX::BoundingOrientedBox(WPOS2D(), WSCALE().HalfVector().AbsVector(), WROT().DegToQ());
//}||||||| .r1535
//DirectX::BoundingOrientedBox HTRANS::RAY3D()
//{
//	//HVECTOR Pos = WPOS2D();
//	//HVECTOR Scale = WSCALE();
//	//HVECTOR Rot = WROT();
//
//	return DirectX::BoundingOrientedBox(WPOS2D(), WSCALE().HalfVector().AbsVector(), WROT().DegToQ());
//}
//RAY HTRANS::RAY3D()
//{
//	//HVECTOR Pos = WPOS2D();
//	//HVECTOR Scale = WSCALE();
//	//HVECTOR Rot = WROT();
//
//	return RAY();
//}
