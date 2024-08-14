#pragma once
#include <HGAMEDEBUG.h>
#include "HGAMECOM.h"
#include <set>
#include "HRenderingDataStructer.h"
#include <HLISTOBJMGR.h>

enum class CAMMODE
{
	ORTH, // ��������
	PERS, // ��������
};

class HTEXTRUE;
class HCAM;
class HRenderTarget;
class HFilter : public HGAMEREF 
{
	friend HCAM;
public:
	HCAM* m_Parent;
	HPTR<HRenderTarget> OutTarget;

public:
	void Init() {}
	void StartTargetCreate();

private:
	virtual void CamMergePrevEffect() {}
	virtual void CamMergeNextEffect() {}
	virtual void DefferdMergePrevEffect() {}
	virtual void DefferdMergeNextEffect() {}
};

class HTEXTURE;
class HRENDERER;
class HRENDERPLAYER;
class HRenderTarget;
class HCAM : public HACTORCOM, public HLISTOBJMGR<HFilter>
{
public:
	friend HTRANS;
	friend HGAMESCENE;

private:
	CAMMODE m_MODE;
	// ���ؽ��� �� �ΰ��� ��ķ� ��ȯ���Ѽ� �ڽ��� �þ߾ȿ��� ��� ǥ���Ѵ�.
	// ���� �̰� �� �ؾ��ϴ���?
	// ���� �̰� �ؾ� �Ѵ�.
	HMATRIX m_VIEW;
	HMATRIX m_PROJ;
	HVECTOR m_CAMSIZE;
	float m_CAMNEAR;
	float m_CAMFAR;
	float m_CAMFOV;

	// ���� �ٶ󺸴� ���������� �׷��� ī�޶� �˰� �־�� �Ѵ�.
	std::set<int> m_VIEWRENDERERS;

	HPTR<HRENDERPLAYER> DefferdLightPlayer;
	HPTR<HRENDERPLAYER> DefferdMergePlayer;

public:
	HVECTOR CAMSIZE() { return m_CAMSIZE; }
	void CAMSIZE(const HVECTOR _Value) { m_CAMSIZE = _Value; }

	float CAMFOV() { return m_CAMFOV; }
	float CAMNEAR() { return m_CAMNEAR; }
	float CAMFAR() { return m_CAMFAR; }

	void CAMFOV(float _Value) { m_CAMFAR = _Value; }
	void CAMNEAR(float _Value) { m_CAMNEAR = _Value; }
	void CAMFAR(float _Value) { m_CAMFAR = _Value; }

	//CBTRANSDATA.V.VIEWLH(CamPos, HVECTOR::FORWARD, HVECTOR::UP);
	//CBTRANSDATA.P.ORTHLH(CamScale, 0.1f, 100.0f);

private:
	void StartSetting(int _Order);

public:
	CAMMODE MODE() { return m_MODE; }
	void MODE(CAMMODE _MODE) { m_MODE = _MODE; }

public:
	// �� �ڷ� ��� ������
	// ���������̴�.
	template<typename ... REST>
	void Init(int _Order, REST ... _Arg) 
	{
		StartSetting(_Order);
		AddRenderGroup(_Arg...);
	}

	template<typename ... REST>
	void AddRenderGroup(int _GroupIndex, REST ... _Arg)
	{
		if (m_VIEWRENDERERS.end() != m_VIEWRENDERERS.find(_GroupIndex))
		{
			AMSG(L"ī�޶� ���� �׷��� �ι� ������ �߽��ϴ�.");
		}

		m_VIEWRENDERERS.insert(_GroupIndex);
		AddRenderGroup(_Arg...);
	}

	void AddRenderGroup(int _GroupIndex)
	{
		if (m_VIEWRENDERERS.end() != m_VIEWRENDERERS.find(_GroupIndex))
		{
			AMSG(L"ī�޶� ���� �׷��� �ι� ������ �߽��ϴ�.");
		}

		m_VIEWRENDERERS.insert(_GroupIndex);
	}

	void AddRenderGroup()	{}


	void RenderPrev() override;

	HVECTOR CamOrthMousePos2D();
	HVECTOR OrthWorldMousePos2D();

//////////////////////////////////////////
private:
	HPTR<HRenderTarget> m_CamTarget;
	HPTR<HRenderTarget> m_ForwardCamTarget;
	HPTR<HRenderTarget> m_GbufferTarget;
	HPTR<HRenderTarget> m_DefferdLightTarget;
	HPTR<HRenderTarget> m_DefferdCamTarget;

public:
	void CamTargetMerge();
	void CalDefferdLight(const LightData& _Data, HPTR<HTEXTURE> _Tex);
	void DefferdMerge();

	HPTR<HRenderTarget> CamTarget();
	HPTR<HRenderTarget> ForwardCamTarget();
	HPTR<HRenderTarget> DefferdCamTarget();
	HPTR<HRenderTarget> GbufferTarget();
	HPTR<HRenderTarget> DefferdLightTarget();


public:
	template<typename FILTERTYPE, typename ... REST>
	HPTR<FILTERTYPE> AddFilter(REST ... _ARG)
	{
		HPTR<FILTERTYPE> NewCom = HLISTOBJMGR<HFilter>::CreateObj<FILTERTYPE>();
		NewCom->m_Parent = this;
		NewCom->Init(_ARG...);
		return NewCom;
	}


	void DefferdMergePrevEffect();
	void DefferdMergeNextEffect();

	void CamMergePrevEffect();
	void CamMergeNextEffect();
};