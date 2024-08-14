#include "HSPRITERENDERER.h"
#include "HGAMEACTOR.h"
#include "HGAMESCENE.h"
#include "HGAMEDEVICE.h"
#include "HVBBUFFER.h"
#include "HIBBUFFER.h"
#include "HCBUFFER.h"
#include "HDEPTHSTENCIL.h"
#include "HBLEND.h"
#include "HRASTERIZER.h"
#include "HVTXSHADER.h"
#include "HPIXSHADER.h"
#include "HSAMPLER.h"
#include "HGAMESPRITE.h"
#include "HCAM.h"

void HSPRITERENDERER::Init(int _Order) {

	// 부모의 함수 호출하는 방법.
	// HRENDERER::Init(_Order);

	//if (nullptr == HCBUFFER::Find(L"TRANSDATA"))
	//{
	//	HCBUFFER::Create<HTRANSDATA>(L"TRANSDATA");
	//	HCBUFFER::Create<HVECTOR>(L"COLOR");
	//	HCBUFFER::Create<HVECTOR>(L"CUTDATA");
	//}

	m_Color = HVECTOR::WHITE;
}
void HSPRITERENDERER::Render(HPTR<HCAM> _Cam) 
{
	//HPTR<HVTXSHADER> VTXS = HVTXSHADER::Find(L"VS_2DIMG");
	//HPTR<HPIXSHADER> PIXS = HPIXSHADER::Find(L"PS_2DIMG");

	// auto& Arr = VTXS->m_ResData;

	// 텍스처를 넣어줘야 한다 정보
	// 텍스처를 넣어주면 되는데 => HTEXTURE

	//if (nullptr == m_SPRITE)
	//{
	//	AMSG(L"스프라이트가 세팅되지 않았습니다.");
	//}

	//// 부모인 트랜스폼의 기능
	//CamUpdate(_Cam);

	//HPTR<HRASTERIZER> RS = HRASTERIZER::Find(L"NONE");
	//HPTR<HDEPTHSTENCIL> DS = HDEPTHSTENCIL::Find(L"DEFDEPTH");
	//HPTR<HBLEND> BLEND = HBLEND::Find(L"AlphaBlend");

	//RS->Setting();
	//DS->Setting();
	//BLEND->Setting();

	//// HPTR<HTEXTURE> TEX = HTEXTURE::Find(L"WALKLEFT.png");
	//HPTR<HSAMPLER> SMP = HSAMPLER::Find(L"PMSMP");

	//m_SPRITE->Tex()->Setting(SHADERTYPE::SHADER_PS, 0);
	//// TEX->Setting(SHADERTYPE::SHADER_PS, 0);
	//SMP->Setting(SHADERTYPE::SHADER_PS, 0);


	////PIXS->Setting();

	//HPTR<HCBUFFER> CBTRANS = HCBUFFER::Find(L"TRANSDATA");
	//HPTR<HCBUFFER> CBCOLOR = HCBUFFER::Find(L"COLOR");
	//HPTR<HCBUFFER> CUTDATA = HCBUFFER::Find(L"CUTDATA");

	//CutData = m_SPRITE->SpriteData(m_SpriteIndex);

	//CBTRANS->DataChange(m_TRANSDATA);
	//CBCOLOR->DataChange(m_Color);
	//CUTDATA->DataChange(CutData);

	//CBTRANS->Setting(SHADERTYPE::SHADER_VS, 0);
	//CUTDATA->Setting(SHADERTYPE::SHADER_VS, 1);
	//CBCOLOR->Setting(SHADERTYPE::SHADER_PS, 0);

	//VTXS->Setting();
	//PIXS->Setting();

	//HPTR<HVBBUFFER> VB = HVBBUFFER::Find(L"2DCOLORRECT");
	//HPTR<HIBBUFFER> IB = HIBBUFFER::Find(L"2DCOLORRECT");
	//VB->Setting();
	//IB->Setting();

	//HGAMEDEVICE::MAINOBJ()->Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//HGAMEDEVICE::MAINOBJ()->Context()->DrawIndexed(IB->Count(), 0, 0);

}