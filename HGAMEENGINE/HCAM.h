#pragma once
#include <HGAMEDEBUG.h>
#include "HGAMECOM.h"
#include <set>
#include "HRenderingDataStructer.h"
#include <HLISTOBJMGR.h>

enum class CAMMODE
{
	ORTH, // 직교투영
	PERS, // 원근투영
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
	// 버텍스를 이 두가지 행렬로 변환시켜서 자신의 시야안에서 어떻게 표현한다.
	// 누가 이걸 또 해야하느냐?
	// 빛이 이걸 해야 한다.
	HMATRIX m_VIEW;
	HMATRIX m_PROJ;
	HVECTOR m_CAMSIZE;
	float m_CAMNEAR;
	float m_CAMFAR;
	float m_CAMFOV;

	// 내가 바라보는 랜더러들의 그룹을 카메라가 알고 있어야 한다.
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
	// 그 뒤로 몇개가 들어올지
	// 가변인자이다.
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
			AMSG(L"카메라가 같은 그룹을 두번 보려고 했습니다.");
		}

		m_VIEWRENDERERS.insert(_GroupIndex);
		AddRenderGroup(_Arg...);
	}

	void AddRenderGroup(int _GroupIndex)
	{
		if (m_VIEWRENDERERS.end() != m_VIEWRENDERERS.find(_GroupIndex))
		{
			AMSG(L"카메라가 같은 그룹을 두번 보려고 했습니다.");
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