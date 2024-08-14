#include "HPaticleCompoent.h"
#include "HGAMEACTOR.h"
#include <HGAMETIME.h>


void HPaticleCompoent::Init() 
{
	{
		PData.resize(1000);

		for (size_t i = 0; i < 1000; i++)
		{
			PData[i].iAlive = 1;
			PData[i].vWorldPos = float4((float)i, 0, 0, 0);
		}

		m_pParticleBuffer = new HStructuredBuffer();
		// m_pParticleBuffer->Create(sizeof(Particle), 1000, nullptr);
		m_pParticleBuffer->Create(sizeof(Particle), 1000, &PData[0], D3D11_USAGE_DYNAMIC);
	}

	{
		SData.resize(1000);

		for (size_t i = 0; i < 1000; i++)
		{
			SData[i].vStartScale = float4(HGAMEMATH::RandomFloat(0.0f, 1.0f), HGAMEMATH::RandomFloat(0.0f, 1.0f), 1.0f);
			SData[i].vEndScale = float4(HGAMEMATH::RandomFloat(0.0f, 1.0f), HGAMEMATH::RandomFloat(0.0f, 1.0f), 1.0f);
			SData[i].vStartColor = float4(HGAMEMATH::RandomFloat(0.0f, 1.0f), HGAMEMATH::RandomFloat(0.0f, 1.0f), HGAMEMATH::RandomFloat(0.0f, 1.0f));
			SData[i].vEndColor = float4(HGAMEMATH::RandomFloat(0.0f, 1.0f), HGAMEMATH::RandomFloat(0.0f, 1.0f), HGAMEMATH::RandomFloat(0.0f, 1.0f));
			SData[i].iCurCount = 1;
			SData[i].iSpawnCount = 1;
			SData[i].Temp0 = 1;
			SData[i].Temp1 = 1;
		}

		m_pSharedBuffer = new HStructuredBuffer();
		// m_pSharedBuffer->Create(sizeof(ParticleShared), 1, nullptr);
		m_pSharedBuffer->Create(sizeof(ParticleShared), 1000, &SData[0]);
	}

	{
		m_Mesh = new HMESH();
		m_Mesh->DrawType(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		

		std::vector<POINTVTX> m_VTX;
		m_VTX.resize(1);
		m_VTX[0].Pos = float4::ZERO;
		m_VTX[0].UV = float4::ZERO;
		m_VTX[0].Color = float4::BLACK;

		HPTR<HVBBUFFER> VB = new HVBBUFFER();
		VB->Create(m_VTX.size(), sizeof(POINTVTX), &m_VTX[0]);


		std::vector<UINT> m_IDX;
		HPTR<HIBBUFFER> IB = new HIBBUFFER();
		m_IDX.resize(1);
		m_IDX[0] = 0;
		IB->Create(m_IDX.size(), sizeof(UINT), &m_IDX[0], DXGI_FORMAT::DXGI_FORMAT_R32_UINT);

		m_Mesh->VB(VB);
		m_Mesh->IB(IB);
	}

	m_Render = ACTOR()->CreateCom<HRENDERER>();
	m_RenderPlayer = m_Render->CreateRenderPlayer(m_Mesh, "Particle");
	
	m_Mesh->InstancedRenderCount(1000);

	m_RenderPlayer->m_IsDebug = true;
	m_RenderPlayer->STRUCTURED("arrParticle", m_pParticleBuffer);
	m_RenderPlayer->STRUCTURED("ParticleShared", m_pSharedBuffer);
}

void HPaticleCompoent::Update() 
{
	{
		for (size_t i = 0; i < 1000; i++)
		{
			PData[i].vWorldPos += float4(-1.0f, 0, 0, 0) * HGAMETIME::DeltaTime();
			PData[i].fCurLifeTime = HGAMETIME::DeltaTime();
		}

		m_pParticleBuffer->SetData(&PData[0], sizeof(Particle) * 1000);
	}
}
void HPaticleCompoent::UpdateNext() 
{

}