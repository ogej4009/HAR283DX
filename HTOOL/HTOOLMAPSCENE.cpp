#include "pch.h"
#include "HTOOLMAPSCENE.h"
#include <HFREECAM.h>
#include <HGAMEACTOR.h>
#include <H3DDEBUG.h>
#include <HGAMESOUND.h>
#include <HCOL.h>
#include <HFRAMEANI.h>
#include "HRightView.h"
#include <HGAMEMOVIE.h>
#include <HFBX.h>
#include <HRENDERER.h>
#include <HBoneAnimationCom.h>
#include <HBoneAnimationComEx.h>
#include <HGAMEDEBUG.h>
#include <HRenderTarget.h>
#include <HLight.h>
#include <HFbxEx.h>
#include <HOutLineFilter.h>
#include <HHeightMap.h>
#include <HBloomFilter.h>
#include <HPaticleCompoent.h>


/////////////////////////////////////// STATIC

HTOOLMAPSCENE* HTOOLMAPSCENE::Inst;
HBoneAnimationCom* HTOOLMAPSCENE::AniCom = nullptr;

HPTR<HCAM> CamPtr;

HTOOLMAPSCENE::HTOOLMAPSCENE() 
{
	Inst = this;
}
HTOOLMAPSCENE::~HTOOLMAPSCENE() 
{

}

void HTOOLMAPSCENE::SceneChangeStart() 
{

}
void HTOOLMAPSCENE::SceneChangeEnd() 
{

}
void HTOOLMAPSCENE::Init() 
{
	// HGAMEDEBUG::OpenConsole();
	if (false == HGAMEINPUT::IsKey(L"TEST1"))
	{
		HGAMEINPUT::CreateKey(L"TEST1", '1');

		HGAMEINPUT::CreateKey(L"L", 'J');
		HGAMEINPUT::CreateKey(L"R", 'L');
		HGAMEINPUT::CreateKey(L"F", 'I');
		HGAMEINPUT::CreateKey(L"B", 'K');
	}

	{
		HGAMEDIRECTORY Dic;

		Dic.MoveParent(L"HAR283DX");
		Dic.Move(L"RES");
		Dic.Move(L"TEXTURE");
		Dic.Move(L"GLOBAL");

		auto FileList = Dic.DirAllFile();

		for (auto& _File : FileList)
		{
			HTEXTURE::Load(_File);
		}
	}

	{
		HGAMEDIRECTORY Dic;

		Dic.MoveParent(L"HAR283DX");
		Dic.Move(L"RES");
		Dic.Move(L"MESH");

		auto FileList = Dic.DirAllFile();

		HFbxEx::Load(Dic.PlusFileName(L"BladeKnight01.FBX"));
		HFbxEx::Load(Dic.PlusFileName(L"AnimMan.FBX"));
		HFbxEx::Load(Dic.PlusFileName(L"ALS_N_Run_B.FBX"));
	}



	HPTR<HGAMEACTOR> CamActor;
	{
		HPTR<HGAMEACTOR> NewActor = SCENE()->CreateActor();
		CamActor = NewActor;
		NewActor->TRANS()->LPOS({ 0, 0, -10 });
		HPTR<HCAM> NewCam = NewActor->CreateCom<HCAM>(0, (int)0);
		NewCam->MODE(CAMMODE::PERS);
		NewCam->CAMSIZE({ 12.8f, 7.2f });
		m_LineFilter = NewCam->AddFilter<HOutLineFilter>(10);
		m_BloomFilter = NewCam->AddFilter<HBloomFilter>(10);
		CamPtr = NewCam;
		NewActor->CreateCom<HFREECAM>(40.0f);
	}


	size_t Size = sizeof(ObjectLightData);

	{
		HPTR<HGAMEACTOR> NewActor = SCENE()->CreateActor();
		HPTR<HRENDERER> NewRender = NewActor->CreateCom<HRENDERER>(L"SPHERE", L"SKY");
		NewRender->GetRenderPlayer(0)->RenderOption.IsDifTexture = true;
		NewRender->TEXTURE(L"Tex",L"SKY.jpg");

		NewActor->TRANS()->LPOS({ 0.0F, 0.0F, 0.0F });
		NewActor->TRANS()->LSCALE({ 1000.0F, 1000.0F, 1000.0F });
	}

	{
		float4 Test = float4(0.5f, 0.5f, 0.5f, 0.9f);
		HPTR<HGAMEACTOR> NewActor = SCENE()->CreateActor();
		HPTR<HRENDERER> NewRender = NewActor->CreateCom<HRENDERER>(L"SPHERE", L"Defferd");
		NewActor->TRANS()->LPOS({ -2.0F, 2.0F, 2.0F });
		NewRender->ShadowOn();
	}

	{
		HPTR<HGAMEACTOR> NewActor = SCENE()->CreateActor();
		HPTR<HRENDERER> NewRender = NewActor->CreateCom<HRENDERER>(L"SPHERE", L"Foward");
		NewRender->GetRenderPlayer(0)->RenderOption.IsDifTexture = false;
		NewRender->GetRenderPlayer(0)->RenderOption.IsNormalTexture = true;
		NewRender->TEXTURE(L"NormalTexture", L"BumpTest.png");
		NewActor->TRANS()->LPOS({ 2.0F, 2.0F, 2.0F });
	}

	{
		HPTR<HGAMEACTOR> NewActor = SCENE()->CreateActor();
		// 이녀석이 y 레티오가 되준다.
		NewActor->TRANS()->LSCALE({ 100, 20, 100.0f });
		Map = NewActor->CreateCom<HHeightMap>(31, 31, L"MAPH.png", 0);
		Map->BaseTexture(L"Tile1.png");
		Map->Render()->ShadowOn();
	}

	{
		PlayerActor = SCENE()->CreateActor();
		PlayerActor->TRANS()->WPOS({ 0.00f, 0.00f , 0.0f });

		HPTR<HGAMEACTOR> MeshActor = SCENE()->CreateActor();
		MeshActor->TRANS()->WSCALE({ 0.01f, 0.01f , 0.01f });
		MeshActor->TRANS()->PARENT(PlayerActor->TRANS());

		HPTR<HRENDERER> NewRender = MeshActor->CreateCom<HRENDERER>();
		HPTR<HBoneAnimationComEx> NewPtr = MeshActor->CreateCom<HBoneAnimationComEx>();
		std::vector<HPTR<HRENDERPLAYER>> Ptr = NewPtr->MainFbx(L"AnimMan.FBX", L"Defferd", 0);
		std::vector<HPTR<HRENDERPLAYER>> Ptr2 = NewPtr->MainFbx(L"AnimMan.FBX", L"OUTLINE", 0);

		// NewPtr->FbxToPartRenderPlayer(L"AnimMan.FBX", L"OUTLINE", 0, 0, 0, 2);
		NewPtr->FbxToPartRenderPlayer(L"AnimMan.FBX", L"Emission", 0, 0, 0, 2);
		NewPtr->CreateAni(L"ALS_N_Run_B.FBX", L"Test", -1, -1, 0);
		NewPtr->ChangeAni(L"Test");

		NewRender->ShadowOn();
	}

	{
		HPTR<HGAMEACTOR> ParticleActor = SCENE()->CreateActor();
		HPTR<HPaticleCompoent> ParticleCom = ParticleActor->CreateCom<HPaticleCompoent>();

	}

	{
		LightTest = SCENE()->CreateActor();

		float4 Dir = HVECTOR(0.0f, 1.0f, -1.0f);
		Dir *= 5.0f;

		LightCom = LightTest->CreateCom<HLight>(0);
		HPTR<HRENDERER> NewRender = LightTest->CreateCom<HRENDERER>(L"DIRMESH", L"DebugMesh");
		LightTest->TRANS()->WPOS(Dir);
		LightTest->TRANS()->WROTADDX(45.0f);
	}

	//{
	//	LightTest = SCENE()->CreateActor();

	//	float4 Dir = HVECTOR(0.0f, 1.0f, 1.0f);
	//	Dir *= 5.0f;
	//	LightCom = LightTest->CreateCom<HLight>(0);
	//	HPTR<HRENDERER> NewRender = LightTest->CreateCom<HRENDERER>(L"DIRMESH", L"DebugMesh");
	//	LightTest->TRANS()->WPOS(Dir);
	//	LightTest->TRANS()->WROTADDX(135.0f);
	//}

	//{
	//	LightTest = SCENE()->CreateActor();
	//	LightCom = LightTest->CreateCom<HLight>(0);
	//	HPTR<HRENDERER> NewRender = LightTest->CreateCom<HRENDERER>(L"DIRMESH", L"DebugMesh");
	//	LightTest->TRANS()->WPOS({ 20.0f, 100.0f, 0.0f });
	//	LightTest->TRANS()->WROTADDX(45.0f);
	//}
}

void HTOOLMAPSCENE::Update()
{
	PlayerUpdate();

	// H3DDEBUG::DrawDebugText(L"AAAA");
	float Ratio = 2.0f;
	HVECTOR Scale = { 128 * Ratio, 72 * Ratio };
	
	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(0), Scale, HVECTOR{ (640.0f - Scale.x), 360, 0.0f }, HVECTOR::BLACK);
	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(1), Scale, HVECTOR{ (640.0f - Scale.x), 360 - Scale.y, 0.0f }, HVECTOR::BLACK);
	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(2), Scale, HVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 2, 0.0f }, HVECTOR::BLACK);
	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(3), Scale, HVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 3, 0.0f }, HVECTOR::BLACK);
	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(7), Scale, HVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 4, 0.0f }, HVECTOR::BLACK);

	H3DDEBUG::DrawDebugTexture(LightCom->ShadowTarget()->Texture(0), HVECTOR{ Scale.x, Scale.x }, HVECTOR{ (640.0f - Scale.x * 2.0f), (360 - Scale.y * 4) + Scale.x - Scale.y, 0.0f }, HVECTOR::BLACK);
	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(6), Scale, HVECTOR{ (640.0f - Scale.x * 2.0F), 360 - Scale.y * 3, 0.0f }, HVECTOR::BLACK);
	H3DDEBUG::DrawDebugTexture(m_BloomFilter->OutTarget->Texture(0), Scale, HVECTOR{ (640.0f - Scale.x * 2.0f), 360, 0.0f }, HVECTOR::BLACK);

	H3DDEBUG::DrawDebugTexture(CamPtr->DefferdLightTarget()->Texture(3), Scale, HVECTOR{ (640.0f - Scale.x * 2.0f), 360 - Scale.y * 1, 0.0f }, HVECTOR::BLACK);

	HRightView::View->PushFbxList();

	if (nullptr == AniCom)
	{
		return;
	}

	if (AniCom->CurAni()->IsEnd())
	{
		CString Text;

		HRightView::View->m_PlayBtn.GetWindowTextW(Text);

		if (Text != L"다시 재생")
		{
			HRightView::View->m_PlayBtn.SetWindowTextW(L"다시 재생");
		}
		return;
	}

	HRightView::View->CurFrame(AniCom->CurAni()->m_CurFrame);

}

void HTOOLMAPSCENE::CreateFBXObject(MeshCreateData _FbxObjectData)
{
	HPTR<HFBX> TestFbx = HFBX::Find(_FbxObjectData.m_MeshName);
	HPTR<HGAMEACTOR> NewActor = SCENE()->CreateActor();
	NewActor->TRANS()->WSCALE({ 0.1F, 0.1F, 0.1F });

	HPTR<HRENDERER> NewRenderer = NewActor->CreateCom<HRENDERER>(0);
	NewRenderer->LROT({ 0.0F, -90.0F, 0.0F });


	HPTR<HFBX> _Fbx = HFBX::Find(_FbxObjectData.m_MeshName);
	HFBXANIDATA* Ani = _Fbx->FindAniData(_FbxObjectData.m_TakeName);

	HRightView::View->RangeSetting((int)Ani->TimeStartCount, (int)Ani->TimeEndCount);

	HRightView::View->m_PlayBtn.SetWindowTextW(L"정지");

	AniCom = NewActor->CreateCom<HBoneAnimationCom>();
	AniCom->CreateAni(_FbxObjectData.m_MeshName, _FbxObjectData.m_TakeName, L"Test", (int)Ani->TimeStartCount, (int)Ani->TimeEndCount, L"3DANIFORWARD"/*, 2.0f, true*/);
	AniCom->ChangeAni(L"Test");
}

void HTOOLMAPSCENE::PlayerUpdate() 
{
	if (HGAMEINPUT::Press(L"L"))
	{
		PlayerActor->TRANS()->LROTADDY(360.0f * HGAMETIME::DeltaTime());

		// PlayerActor->TRANS()->WMOVE(PlayerActor->TRANS()->WLEFT());
	}

	if (HGAMEINPUT::Press(L"R"))
	{
		PlayerActor->TRANS()->LROTADDY(-360.0f * HGAMETIME::DeltaTime());
		// PlayerActor->TRANS()->WMOVE(PlayerActor->TRANS()->WRIGHT());
	}

	if (HGAMEINPUT::Press(L"F"))
	{
		PlayerActor->TRANS()->WMOVE(PlayerActor->TRANS()->WFORWARD() * HGAMETIME::DeltaTime(20.0F));
	}

	if (HGAMEINPUT::Press(L"B"))
	{
		PlayerActor->TRANS()->WMOVE(PlayerActor->TRANS()->WBACK() * HGAMETIME::DeltaTime(20.0F));
	}

	int2 Index = Map->Index(PlayerActor->TRANS()->WPOS());

	H3DDEBUG::DrawDebugText(L"Index %d %d", Index.x, Index.y);

	
	HVECTOR Pos = PlayerActor->TRANS()->WPOS();
	Pos.y = Map->YHeight(PlayerActor->TRANS()->WPOS());
	PlayerActor->TRANS()->WPOS(Pos);
}