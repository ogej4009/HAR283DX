#include "HCAM.h"
#include <HGAMEDEBUG.h>
#include <HGAMEWINDOW.h>
#include "HGAMEACTOR.h"
#include "HTRANS.h"
#include "HGAMESCENE.h"
#include "HRenderTarget.h"
#include "HTEXTURE.h"


void HCAM::StartSetting(int _Order)
{
	//HVECTOR A = HVECTOR{ 1, 0 , 0 };
	//HVECTOR B = HVECTOR{ 1, 0 , 0 };

	//A.NORMAL3D();
	//B.NORMAL3D();

	//float Light = A.Dot3D(B);


	// 트랜스폼이 없는 엑터에 들어간것.
	if (nullptr == ACTOR()->TRANS())
	{
		AMSG(L"트랜스폼이 없는 액터에 캠을 넣었습니다.");
	}
	Order(_Order);

	m_CAMFOV = 60.0F;
	m_CAMFAR = 1000.0F;
	m_CAMNEAR = 0.1F;
	m_MODE = CAMMODE::ORTH;
	m_CAMSIZE = HGAMEWINDOW::MAINOBJ()->Size();

	ACTOR()->SCENE()->PushCam(this);

	m_CamTarget = new HRenderTarget();
	m_CamTarget->CreateTarget(HGAMEWINDOW::MAINOBJ()->Size(), HVECTOR::NONE);
	m_CamTarget->Depth(HGAMEDEVICE::MAINOBJ()->BackBufferRenderTarget()->Depth());

	m_ForwardCamTarget = new HRenderTarget();
	m_ForwardCamTarget->CreateTarget(HGAMEWINDOW::MAINOBJ()->Size(), HVECTOR::NONE);
	m_ForwardCamTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(1), HVECTOR::NONE, false);
	m_ForwardCamTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(2), HVECTOR::NONE, false);
	m_ForwardCamTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(3), HVECTOR::NONE, false);
	m_ForwardCamTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(4), HVECTOR::NONE, false);
	m_ForwardCamTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(5), HVECTOR::NONE, false);
	m_ForwardCamTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(6), HVECTOR::NONE, false);
	m_ForwardCamTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(7), HVECTOR::NONE, false);

	m_ForwardCamTarget->Depth(HGAMEDEVICE::MAINOBJ()->BackBufferRenderTarget()->Depth());

	m_DefferdCamTarget = new HRenderTarget();
	m_DefferdCamTarget->CreateTarget(HGAMEWINDOW::MAINOBJ()->Size(), HVECTOR::NONE);
	m_DefferdCamTarget->Depth(HGAMEDEVICE::MAINOBJ()->BackBufferRenderTarget()->Depth());


	m_GbufferTarget = new HRenderTarget();
	m_GbufferTarget->CreateTarget(HGAMEWINDOW::MAINOBJ()->Size(), HVECTOR::NONE); // 디퓨즈
	m_GbufferTarget->CreateTarget(HGAMEWINDOW::MAINOBJ()->Size(), HVECTOR::NONE); // 포지션
	m_GbufferTarget->CreateTarget(HGAMEWINDOW::MAINOBJ()->Size(), HVECTOR::NONE); // 노말
	m_GbufferTarget->CreateTarget(HGAMEWINDOW::MAINOBJ()->Size(), HVECTOR::NONE); // 깊이
	m_GbufferTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(4), HVECTOR::NONE, false);
	m_GbufferTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(5), HVECTOR::NONE, false);
	m_GbufferTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(6), HVECTOR::NONE, false);
	m_GbufferTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(7), HVECTOR::NONE, false);
	m_GbufferTarget->Depth(HGAMEDEVICE::MAINOBJ()->BackBufferRenderTarget()->Depth());


	DefferdLightPlayer = new HRENDERPLAYER();
	DefferdLightPlayer->MESH(L"TargetFullRect");
	DefferdLightPlayer->MATERIAL(L"DefferdLight");
	DefferdLightPlayer->SAMPLER(L"SAMPLER", L"LWSMP");
	DefferdLightPlayer->SAMPLER(L"SHADOWSAMPLER", L"LCSMP");
	DefferdLightPlayer->TEXTURE(L"PosTex", m_GbufferTarget->Texture(1));
	DefferdLightPlayer->TEXTURE(L"NorTex", m_GbufferTarget->Texture(2));


	m_DefferdLightTarget = new HRenderTarget();
	m_DefferdLightTarget->CreateTarget(HGAMEWINDOW::MAINOBJ()->Size(), HVECTOR::NONE); // 디퓨즈
	m_DefferdLightTarget->CreateTarget(HGAMEWINDOW::MAINOBJ()->Size(), HVECTOR::NONE); // 스펙큘러
	m_DefferdLightTarget->CreateTarget(HGAMEWINDOW::MAINOBJ()->Size(), HVECTOR::NONE); // 엠비언트
	m_DefferdLightTarget->CreateTarget(HGAMEWINDOW::MAINOBJ()->Size(), HVECTOR::NONE); // 그냥 다합쳐진 타겟
	m_DefferdLightTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(4), HVECTOR::NONE, false);
	m_DefferdLightTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(5), HVECTOR::NONE, false);
	m_DefferdLightTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(6), HVECTOR::NONE, false);
	m_DefferdLightTarget->CreateTarget(HGAMEDEVICE::MAINOBJ()->DataRenderTarget()->Texture(7), HVECTOR::NONE, false);
	m_DefferdLightTarget->Depth(HGAMEDEVICE::MAINOBJ()->BackBufferRenderTarget()->Depth());


	DefferdMergePlayer = new HRENDERPLAYER();
	DefferdMergePlayer->MESH(L"TargetFullRect");
	DefferdMergePlayer->MATERIAL(L"DefferdMerge");
	DefferdMergePlayer->SAMPLER(L"SAMPLER", L"LWSMP");
	DefferdMergePlayer->TEXTURE(L"DifColor", m_GbufferTarget->Texture(0));
	DefferdMergePlayer->TEXTURE(L"LightColor", m_DefferdLightTarget->Texture(3));
}

void HCAM::RenderPrev() 
{
	//CBTRANSDATA.V.VIEWLH(CamPos, HVECTOR::FORWARD, HVECTOR::UP);
	//CBTRANSDATA.P.ORTHLH(CamScale, 0.1f, 100.0f);
	// 카메라를 들고 있는 액터의 위치가 곧 카메라가 보고있는 위치이다

	// 이녀석이 뷰행렬을 만드는 방법.
	// 회전행렬에서 얻어올수 있다.

	HVECTOR Pos = ACTOR()->TRANS()->WPOS();
	HVECTOR F = ACTOR()->TRANS()->WFORWARD();
	HVECTOR U = ACTOR()->TRANS()->WUP();

	m_VIEW.VIEWLH(ACTOR()->TRANS()->WPOS(), ACTOR()->TRANS()->WFORWARD(), ACTOR()->TRANS()->WUP());

	switch (m_MODE)
	{
	case CAMMODE::ORTH:
		m_PROJ.ORTHLH(m_CAMSIZE, m_CAMNEAR, m_CAMFAR);
		break;
	case CAMMODE::PERS:
		m_PROJ.PERSDEG(m_CAMFOV, m_CAMSIZE, m_CAMNEAR, m_CAMFAR);
		break;
	default:
		AMSG(L"캠 모드 설정이 잘못됐습니다.");
		break;
	}

}


HVECTOR HCAM::CamOrthMousePos2D()
{
	HVECTOR ScreenMousePos = HGAMEWINDOW::MAINOBJ()->MousePos();
	HMATRIX ScreenViewPort = HGAMEWINDOW::MAINOBJ()->ViewPort();
	ScreenViewPort.Inverse();
	ScreenMousePos *= ScreenViewPort;
	ScreenMousePos *= CAMSIZE().HalfVector();
	return ScreenMousePos;
}

HVECTOR HCAM::OrthWorldMousePos2D() 
{
	return TRANS()->WPOS2D() + CamOrthMousePos2D();
}

void HCAM::CamTargetMerge() 
{
	m_CamTarget->Clear(false);
	m_CamTarget->Merge(m_ForwardCamTarget);
	m_CamTarget->Merge(m_DefferdCamTarget);
}

HPTR<HRenderTarget> HCAM::CamTarget() 
{
	return m_CamTarget;
}

HPTR<HRenderTarget> HCAM::ForwardCamTarget() 
{
	return m_ForwardCamTarget;
}
HPTR<HRenderTarget> HCAM::DefferdCamTarget() 
{
	return m_DefferdCamTarget;
}

HPTR<HRenderTarget> HCAM::DefferdLightTarget() 
{
	return m_DefferdLightTarget;
}
HPTR<HRenderTarget> HCAM::GbufferTarget() 
{
	return m_GbufferTarget;
}

void HCAM::CalDefferdLight(const LightData& _Data, HPTR<HTEXTURE> _Tex) 
{
	m_DefferdLightTarget->Setting();
	DefferdLightPlayer->CBUFFER(L"ONELIGHTDATA", (void*)&_Data, CBUFFERMODE::CB_LINK);
	DefferdLightPlayer->TEXTURE(L"ShadowTex", _Tex);
	DefferdLightPlayer->Render();
	DefferdLightPlayer->Reset();
}

void HCAM::DefferdMerge() 
{
	m_DefferdCamTarget->Clear(false);
	m_DefferdCamTarget->Setting();
	DefferdMergePlayer->Render();
	DefferdMergePlayer->Reset();
}




void HFilter::StartTargetCreate()
{
	OutTarget = new HRenderTarget();
	OutTarget->CreateTarget(HGAMEWINDOW::MAINOBJ()->Size(), HVECTOR::NONE); // 디퓨즈
}


void HCAM::CamMergeNextEffect() 
{
	for (auto& _Filter : HLISTOBJMGR<HFilter>::m_ObjList)
	{
		_Filter.Obj->CamMergeNextEffect();
	}
}

void HCAM::CamMergePrevEffect()
{
	for (auto& _Filter : HLISTOBJMGR<HFilter>::m_ObjList)
	{
		_Filter.Obj->CamMergePrevEffect();
	}
}

void HCAM::DefferdMergeNextEffect()
{
	for (auto& _Filter : HLISTOBJMGR<HFilter>::m_ObjList)
	{
		_Filter.Obj->DefferdMergeNextEffect();
	}
}

void HCAM::DefferdMergePrevEffect()
{
	for (auto& _Filter : HLISTOBJMGR<HFilter>::m_ObjList)
	{
		_Filter.Obj->DefferdMergePrevEffect();
	}
}