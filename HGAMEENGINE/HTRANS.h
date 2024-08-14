#pragma once
#include "HGAMECOM.h"

enum class COLTYPE
{
	SPHERE2D, // API�� ��Ŭ�̴�.
	AABB2D,
	OBB2D,
	SPHERE3D,
	AABB3D,
	OBB3D,
	RAY3D,
	MAX,
};

struct RAY
{
	float4 Start;
	float4 Dir;
};


struct LightData;
class HCAM;
class HTRANS : public HACTORCOM
{
private:
	class HGAMECOLSTART
	{
	public:
		HGAMECOLSTART();
	};
	friend HGAMECOLSTART;
	static HGAMECOLSTART Starter;

public:
	static bool __stdcall SPHERE2DCOLOBB2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right);
	static bool __stdcall SPHERE2DCOLAABB2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right);
	static bool __stdcall SPHERE2DCOLSPHERE2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right);
	static bool __stdcall AABB2DCOLOBB2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right);
	static bool __stdcall AABB2DCOLAABB2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right);
	static bool __stdcall AABB2DCOLSPHERE2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right);
	static bool __stdcall OBB2DCOLOBB2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right);
	static bool __stdcall OBB2DCOLAABB2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right);
	static bool __stdcall OBB2DCOLSPHERE2D(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right);

	static bool (__stdcall *COLFUNC[(int)COLTYPE::MAX][(int)COLTYPE::MAX])(HPTR<HTRANS> _Left, HPTR<HTRANS> _Right);

protected:
	HVECTOR m_LPOS;
	HVECTOR m_LSCALE; // �������� ���� 0�̸� ��Ʈ���ڴ�. // ũ�Ⱑ 0�ΰ� �������� �ʴ´ٴ� ���̴ϱ�.
	HVECTOR m_LROT;
	HVECTOR m_WPOS;
	HVECTOR m_WSCALE; // �������� ���� 0�̸� ��Ʈ���ڴ�. // ũ�Ⱑ 0�ΰ� �������� �ʴ´ٴ� ���̴ϱ�.
	HVECTOR m_WROT;

	bool CALARRMATCHECK[(int)MATTYPE::MATTYPE_MAX];
	HTRANSDATA m_TRANSDATA;

	// Ʈ���� ���� �θ� ������ �ִ�.
	HTRANS* m_PARENT;
	std::list<HTRANS*> m_CHILDLIST;

public:
	HTRANSDATA TRANSDATA() {
		return m_TRANSDATA;
	}

	const HTRANSDATA& CRTRANSDATA() {
		return m_TRANSDATA;
	}

	HTRANSDATA* PTRANSDATA() {
		return &m_TRANSDATA;
	}


public:
	HTRANS* PARENT()
	{
		return m_PARENT;
	}

	void PARENT(HPTR<HTRANS> _Parent);


public:
	HTRANS();

public:
	HVECTOR LPOS() { return m_LPOS; }
	HVECTOR LSCALE() { return m_LSCALE; }
	HVECTOR LROT() { return m_LROT; }
	HVECTOR WPOS() { 
		return m_WPOS; 
	}

	const HVECTOR& CRWPOS() {
		return m_WPOS;
	}

	HVECTOR WPOS2D() 
	{
		return HVECTOR(m_WPOS.x, m_WPOS.y, 0.0f, m_WPOS.w);
	}
	HVECTOR WSCALE() { return m_WSCALE; }
	HVECTOR WROT() { return m_WROT; }


private:
	// m_LPOS�� ������ �־�� ��� ����.
	void CALWPOS() 
	{
		DEBUGCHECK;

		// ������ �߸��� �ڵ�. �θ���� WROT������ ��ġ�� ������ �����ǿ� ������ ��ġ�°�?
		// WROT()�� ������ ����� �༮�ε� �̳༮�� ���� �����ǿ� ������ ��ġ�� �־���.
		// m_WPOS = m_PARENT->WPOS() + ((m_LPOS * m_PARENT->WSCALE()).RotDegReturn(WROT()));

		// m_WPOS = m_PARENT->WPOS() + ((m_LPOS * m_PARENT->WSCALE()).RotDegReturn(m_PARENT->WROT()));
		// �������� �����ϸ� �ȉ´�.

		// �ڵ带 ������ �־�� �Ѵ�.
		// ��ƴ���� �����Ҽ� ������ �ڱ���̴�. 
		// �̰� ���ϴϱ� ũ�� -1�� ������ �ȵȴ�.
		// ȸ���� �ϰ� �������� ���ؾ� �Ѵ�.
		// �̰� ���ϰ� ����?

		// ���� ������ ���ϴµ� ���� �������� 
		// �̰� ���� �������Դϴ�.
		// ���� �������� * m_PARENT->WSCALE() ũ�⸦ Ű����. ũ�⸦ �����ϴϱ�
		// ���� �������� (m_LPOS.RotDegReturn(m_PARENT->WROT()) ȸ����Ų��.
		// -1�����Ϸ� ������ ��ġ�� ������ ���� �ʴ´�.

		// �κ� ��ť �� ���α׷��� �����ߴ�.
		m_WPOS = m_PARENT->WPOS() + ((m_LPOS.RotDegReturn(m_PARENT->WROT()) * m_PARENT->WSCALE()));
	}

	void CALCHILDPOS() {
		for (auto& _Child : m_CHILDLIST)
		{
			_Child->CALWPOS();
		}
	}

	void CALWROT()
	{
		m_WROT = m_PARENT->WROT() + m_LROT;
	}

	void CALCHILDROT() {
		for (auto& _Child : m_CHILDLIST)
		{
			_Child->CALWROT();
		}
	}

	void CALWSCALE()
	{
		m_WSCALE = m_PARENT->WSCALE() * m_LSCALE;
	}

	void CALCHILDSCALE() {
		for (auto& _Child : m_CHILDLIST)
		{
			_Child->CALWSCALE();
		}
	}

public:
	// �̰͵� �� �ٲ��� �Ѵ�.
	void LPOS(const HVECTOR& _Value)
	{
		if (nullptr == m_PARENT)
		{
			m_LPOS = m_WPOS = _Value;
			CALARRMATCHECK[(int)MATTYPE::MATTYPE_POS] = true;
			CALCHILDPOS();
			return;
		}

		m_LPOS = _Value;
		CALWPOS();
		CALCHILDPOS();
		CALARRMATCHECK[(int)MATTYPE::MATTYPE_POS] = true;
	}
	void WPOS(const HVECTOR& _Value)
	{
		if (nullptr == m_PARENT)
		{
			m_LPOS = m_WPOS = _Value;
			CALARRMATCHECK[(int)MATTYPE::MATTYPE_POS] = true;
			CALCHILDPOS();
			return;
		}

		// ���� �������
		// ������ �³�?
		// �����е��� �ణ�� ������ ����� �ִٴ°��� ����ض�.
		m_LPOS = ((_Value - m_PARENT->WPOS()) / m_PARENT->WSCALE()).RotDegReturn(-WROT());
		CALWPOS();
		CALCHILDPOS();


		CALARRMATCHECK[(int)MATTYPE::MATTYPE_POS] = true;
	}

	void WPOS2D(const HVECTOR& _Value, float _Z = 0.0F)
	{
		HVECTOR Vec2D = _Value;

		Vec2D.z = _Z;

		if (nullptr == m_PARENT)
		{
			m_LPOS = m_WPOS = Vec2D;
			CALARRMATCHECK[(int)MATTYPE::MATTYPE_POS] = true;
			CALCHILDPOS();
			return;
		}

		// ���� �������
		// ������ �³�?
		// �����е��� �ణ�� ������ ����� �ִٴ°��� ����ض�.
		m_LPOS = ((Vec2D - m_PARENT->WPOS()) / m_PARENT->WSCALE()).RotDegReturn(-m_PARENT->WROT());
		CALWPOS();
		CALCHILDPOS();


		CALARRMATCHECK[(int)MATTYPE::MATTYPE_POS] = true;
	}

	void LROT(const HVECTOR& _Value)
	{
		if (nullptr == m_PARENT)
		{
			m_LROT = m_WROT = _Value;
			CALARRMATCHECK[(int)MATTYPE::MATTYPE_ROT] = true;
			CALCHILDROT();
			CALCHILDPOS();
			return;
		}

		m_LROT = _Value;
		CALWROT();
		CALCHILDROT();
		CALCHILDPOS();

		CALARRMATCHECK[(int)MATTYPE::MATTYPE_ROT] = true;

	}

	void WROT(const HVECTOR& _Value)
	{
		if (nullptr == m_PARENT)
		{
			m_LROT = m_WROT = _Value;
			CALCHILDROT();
			CALCHILDPOS();
			CALARRMATCHECK[(int)MATTYPE::MATTYPE_ROT] = true;
			return;
		}

		// �̿����� �����Ϸ���
		// ������ ���� �����ؼ�
		// �װɷ� ����� �غ��� �Ѵ�.

		//0 0 0  0 0 90 - 0 0 90
		m_LROT = _Value - m_PARENT->WROT();
		CALWROT();
		CALCHILDROT();
		CALCHILDPOS();

		CALARRMATCHECK[(int)MATTYPE::MATTYPE_ROT] = true;
	}


	void LSCALE(const HVECTOR& _Value)
	{
		if (nullptr == m_PARENT)
		{
			m_LSCALE = m_WSCALE = _Value;
			CALCHILDSCALE();
			CALCHILDPOS();
			CALARRMATCHECK[(int)MATTYPE::MATTYPE_SCALE] = true;
			return;
		}

		m_LSCALE = _Value;
		CALWSCALE();
		CALCHILDSCALE();
		CALCHILDPOS();
		CALARRMATCHECK[(int)MATTYPE::MATTYPE_SCALE] = true;

	}
	void WSCALE(const HVECTOR& _Value)
	{
		if (nullptr == m_PARENT)
		{
			m_LSCALE = m_WSCALE = _Value;
			CALCHILDSCALE();
			CALCHILDPOS();
			CALARRMATCHECK[(int)MATTYPE::MATTYPE_SCALE] = true;
			return;
		}

		// �������� � �Ӽ��� 0�ΰ� ������� �ʴ´�.

		m_LSCALE = _Value / m_PARENT->WSCALE();
		CALWSCALE();
		CALCHILDSCALE();
		CALCHILDPOS();

		CALARRMATCHECK[(int)MATTYPE::MATTYPE_SCALE] = true;
	}

	void LMOVE(const HVECTOR& _Value) { LPOS(LPOS() + _Value); }
	void WMOVE(const HVECTOR& _Value) { WPOS(WPOS() + _Value); }

	void LROTADDX(float _Value) { m_LROT.x += _Value;		LROT(m_LROT); }
	void LROTADDY(float _Value) { 
		m_LROT.y += _Value;		
		LROT(m_LROT); 
	}
	void LROTADDZ(float _Value) { m_LROT.z += _Value;		LROT(m_LROT); }
	void WROTADDX(float _Value) {
		m_WROT.x += _Value;		
		WROT(m_WROT);
	}
	void WROTADDY(float _Value) {
		m_WROT.y += _Value;		
		WROT(m_WROT);
	}
	void WROTADDZ(float _Value) { 
		m_WROT.z += _Value;		
		WROT(m_WROT); 
	}


	// �׸��� ��������? ���̰� ����?
	HVECTOR LFORWARD() { return m_TRANSDATA.ROT.ArrV[2]; }
	HVECTOR LBACK() { return -m_TRANSDATA.ROT.ArrV[2]; }
	HVECTOR LRIGHT() { return m_TRANSDATA.ROT.ArrV[0]; }
	HVECTOR LLEFT() { return -m_TRANSDATA.ROT.ArrV[0]; }
	HVECTOR LUP() { return m_TRANSDATA.ROT.ArrV[1]; }
	HVECTOR LDOWN() { return m_TRANSDATA.ROT.ArrV[1]; }

	HVECTOR WFORWARD() { return m_TRANSDATA.WWORLD.ArrV[2].NORMAL3DTORETURN(); }
	HVECTOR WBACK() { return -m_TRANSDATA.WWORLD.ArrV[2].NORMAL3DTORETURN(); }
	HVECTOR WRIGHT() { return m_TRANSDATA.WWORLD.ArrV[0].NORMAL3DTORETURN(); }
	HVECTOR WLEFT() { return -m_TRANSDATA.WWORLD.ArrV[0].NORMAL3DTORETURN(); }
	HVECTOR WUP() { return m_TRANSDATA.WWORLD.ArrV[1].NORMAL3DTORETURN(); }
	HVECTOR WDOWN() { return -m_TRANSDATA.WWORLD.ArrV[1].NORMAL3DTORETURN(); }

public:
	//      ���� _ThisType��    ��� Ʈ������        ���� _OtherType��
	bool Col(COLTYPE _ThisType, HPTR<HTRANS> _Trans, COLTYPE _OtherType);

public:
	DirectX::BoundingBox AABB2D();
	DirectX::BoundingSphere SPHERE2D();
	DirectX::BoundingOrientedBox OBB2D();
	//RAY RAY3D();

public:
	void Init() override;
	void TransUpdate();
	void CamUpdate(HPTR<HCAM> _Cam);
	void LightUpdate(const LightData& _Light);
};